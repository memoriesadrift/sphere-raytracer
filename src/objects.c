#include "vector.h"
#include "objects.h"

Camera Camera_value(Vector pos, Vector up, Vector look_at, int fov, int max_bounces) {
  Camera c = {
    .position = pos,
    .up = up,
    .look_at = look_at,
    .fov = fov,
    .max_bounces = max_bounces
  };

  return c;
}

Ray Ray_value(Vector origin, Vector direction) {
  Ray r = {
    .origin = origin,
    .direction = direction
  };

  return r;
}

Light Light_value(double r, double g, double b, LightType type, Vector v) {
  Light l = { r, g, b, type, v };

  return l;
}

Light Light_ambient_value(double r, double g, double b) {
  Light l = {
    .r = r,
    .g = g,
    .b = b,
    .type = LIGHT_AMBIENT,
    .v = Vector_value(0, 0, 0)
  };

  return l;
}

Light Light_parallel_value(double r, double g, double b, Vector dir) {
  Light l = {
    .r = r,
    .g = g,
    .b = b,
    .type = LIGHT_PARALLEL,
    .v = dir
  };

  return l;
}

Light Light_point_value(double r, double g, double b, Vector pos) {
  Light l = {
    .r = r,
    .g = g,
    .b = b,
    .type = LIGHT_POINT,
    .v = pos
  };

  return l;
}

Sphere Sphere_value(
    Vector position,
    double radius,
    double r,
    double g,
    double b,
    double phong_ambient,
    double phong_diffuse,
    double phong_specular,
    double phong_exponent,
    double reflectance,
    double transmittance,
    double iof
  ) {
  Sphere s = {
    position, radius,
    r, g, b, 
    phong_ambient, phong_diffuse, phong_specular, phong_exponent, 
    reflectance, transmittance, iof
  };

  return s;
}

