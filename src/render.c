#include <math.h>
// If PI isn't defined, define it!
// Issue with building on some systems,
// should be solved by -lm compiler flag
#ifndef  M_PI
#define  M_PI  3.1415926535897932384626433
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ppm.h"
#include "render.h"
#include "objects.h"
#include "vector.h"


Colour Colour_value(double r, double g, double b) {
  Colour c = {r, g, b};

  return c;
}

double clip_colour_value(double val) {
  return (val > 0) 
    ? (val > 1)
      ? 1
      : val
    : 0;
}

Colour calc_light_effect(Colour colour, Light light, Sphere sphere, Vector point, Vector normal_at_point, Vector camera_ray_direction, Sphere* objects, int objects_size) {
  Vector light_direction = light.type == LIGHT_PARALLEL 
    ? Vector_norm(Vector_neg(light.v))
    : Vector_norm(Vector_add(light.v, Vector_neg(point))); // must be point light
  double cosine = Vector_dot(normal_at_point, light_direction);

  // Light ray missed this point
  if (cosine <= 0) return colour;

  double epsilon = 0.0001;
  Ray shadow = Ray_value(point, light_direction);

  bool isInShadow = false;
  for(int i = 0; i < objects_size; i++) {
    double intersection = find_intersection(objects[i], shadow);

    if (intersection > epsilon) {
      isInShadow = true;
      break;
    }
  }

  if (isInShadow == true) return colour;

  // Diffuse component
  colour = Colour_value(
      colour.r + (sphere.r * light.r * cosine * sphere.phong_diffuse),
      colour.g + (sphere.g * light.g * cosine * sphere.phong_diffuse),
      colour.b + (sphere.b * light.b * cosine * sphere.phong_diffuse)
      );

  // Specular component

  double specular = Vector_dot(
      Vector_norm(
        Vector_add(
          Vector_scale(
            Vector_add(
              Vector_scale(
                normal_at_point,
                Vector_dot(
                  normal_at_point,
                  Vector_neg(camera_ray_direction)
                  )
                ),
              camera_ray_direction
              ), 
            2),
          Vector_neg(camera_ray_direction)
          )
        ),
      light_direction);

  if (specular <= 0) return colour;

  colour = Colour_value(
      colour.r + (pow(specular, sphere.phong_exponent) * light.r * sphere.phong_specular),
      colour.g + (pow(specular, sphere.phong_exponent) * light.g * sphere.phong_specular),
      colour.b + (pow(specular, sphere.phong_exponent) * light.b * sphere.phong_specular)
      );

  return colour;
}

Pixel determine_pixel_colour(Vector at, Vector ray_direction, Sphere *objects, int objects_size, Light *lights, int lights_size, int object_idx) {
  Sphere sphere = objects[object_idx];
  Vector normal = Vector_norm(Vector_add(at, Vector_neg(sphere.position)));
  Colour final_colour = Colour_value(0, 0, 0);

  for(int i = 0; i < lights_size; i++) {
    Light light = lights[i];

    switch (light.type) {
      case LIGHT_AMBIENT:
        final_colour = Colour_value(
            sphere.r * light.r * sphere.phong_ambient, 
            sphere.g * light.g * sphere.phong_ambient,
            sphere.b * light.b * sphere.phong_ambient
            );
        break;
      case LIGHT_PARALLEL:
      case LIGHT_POINT:
        final_colour = calc_light_effect(final_colour, light, sphere, at, normal, ray_direction, objects, objects_size);
        break;
    }
  }

  // Reduce the colours to between 0 and 1
  final_colour = Colour_value(
      clip_colour_value(final_colour.r),
      clip_colour_value(final_colour.g),
      clip_colour_value(final_colour.b)
    );

  return Pixel_value(final_colour.r * 255, final_colour.g * 255, final_colour.b * 255);
}

int find_frontmost_intersection_idx(double* intersections, int size) {
  double min = INFINITY;
  int idx = -1;

  for (int i = 0; i < size; i++) {
    double intersection = intersections[i];

    // Miss!
    if (intersection < 0) continue;

    if (intersection < min) {
      min = intersection;
      idx = i;
    } 
  }

  return idx;
}

double find_intersection(Sphere sphere, Ray ray) {
  // time to solve a quadratic equation smile
  double b = (2 * ray.direction.x * (ray.origin.x - sphere.position.x)) +
             (2 * ray.direction.y * (ray.origin.y - sphere.position.y)) +
             (2 * ray.direction.z * (ray.origin.z - sphere.position.z));
  double c = pow(ray.origin.x - sphere.position.x, 2) + 
             pow(ray.origin.y - sphere.position.y, 2) +
             pow(ray.origin.z - sphere.position.z, 2) -
             pow(sphere.radius, 2);

  double disc = pow(b, 2) - 4 * c;

  // Miss :(
  if (disc <= 0) return -1;

  // Hit! Find out which side of the sphere was that hit
  double root = (-1 * b - sqrt(disc)) / 2;
  
  if (root > 0) return root;

  return (sqrt(disc) - b) / 2;
}

void render_scene(
    // Args relating to the resulting image
    Pixel* image,
    int width,
    int height,
    // Args relating to the scene
    Colour background_colour,
    Camera camera,
    Sphere* objects,
    int objects_size,
    Light* lights,
    int lights_size
) {

  // FoV is static, so we don't need to recalculate for each pixel
  double cam_fov_rad = camera.fov * (M_PI / 180.0);
  double x_fov, y_fov;
  if (width >= height) {
    x_fov = tan(cam_fov_rad);
    y_fov = tan(cam_fov_rad * ((double)height/width));
  } else {
    x_fov = tan(cam_fov_rad);
    y_fov = tan(cam_fov_rad * ((double)width/height));
  }

  // Render loop
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      int idx = row * width + col;

      double x_actual = ((2 * col - width) / (double)width) * x_fov;
      double y_actual = ((2 * row - height) / (double)height) * y_fov;

      Vector ray_direction = Vector_norm(
          Vector_value(x_actual, y_actual, -1)
        );

      Ray ray = Ray_value(camera.position, ray_direction);

      // Find intersections
      double *intersections = malloc(sizeof(double) * objects_size);
      for (int i = 0; i < objects_size; i++) {
        intersections[i] = find_intersection(objects[i], ray);
      }

      int intersecting_object_idx = find_frontmost_intersection_idx(intersections, objects_size);

      // Rendering / colour determination

      // No hits: set pixel to background colour
      if (intersecting_object_idx == -1) {
        image[idx] = Pixel_value(background_colour.r * 255, background_colour.g * 255, background_colour.b * 255);
        continue;
      }

      // Hit! calculate the colour based on the intersection
      Vector intersection_position = Vector_add(
          camera.position,
          Vector_scale(ray.direction, intersections[intersecting_object_idx])
          );

      image[idx] = determine_pixel_colour(intersection_position, ray.direction, objects, objects_size, lights, lights_size, intersecting_object_idx);
      free(intersections);
    }
  }
}
