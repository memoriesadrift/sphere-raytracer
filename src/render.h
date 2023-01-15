#ifndef RENDER_H
#define RENDER_H

#include "objects.h"
#include "ppm.h"
#include "vector.h"

// Colour vector for more convenient rendering

typedef struct Colour {
  double r;
  double g;
  double b;
} Colour;

/**
 * Initialises a Colour struct with the given values.
 * This differs from `Pixel` as it uses values from 0 to 1 only used
 * during rendering calculations.
 *
 * @param double the red colour component value
 * @param double the green colour component value
 * @param double the blue colour component value
 *
 * @returns a Colour struct initialised with the given values.
 */
Colour Colour_value(double, double, double);

/**
 * Clips a given RGB value, ensuring it's between 0 and 1.
 * @param double the given r, g or b value.
 *
 * @returns double the clipped colour value
 */
double clip_colour_value(double);

// Colour determination

/**
 * Calculates the effect of a parallel or point light source on a Colour.
 *
 * @param Colour the colour component with the previous lights' effects applied.
 * @param Light the light source to apply
 * @param Sphere the object illuminated by the light source
 * @param Vector the point of the light ray hitting the sphere
 * @param Vector the normal at the intersection point
 * @param Vector the direction of the camera ray
 * @param Sphere* the array of scene objects
 * @param int the size of the array of scene objects
 *
 * @returns Colour the resulting colour
 */
Colour calc_light_effect(Colour, Light, Sphere, Vector, Vector, Vector, Sphere*, int);

/**
 * Determines the resulting Pixel colour of the output image ar a given position.
 *
 * @param Vector the position of the intersection
 * @param Vector the direction of the ray
 * @param Sphere* the array of scene objects
 * @param int the size of the array of scene objects
 * @param Light* the array of scene lights
 * @param int  the size of the array of scene lights
 * @param int object_idx the intersected object index
 *
 * @returns Pixel the final Pixel colour to be save to the final image
 */
Pixel determine_pixel_colour(Vector, Vector, Sphere*, int, Light*, int, int);

// Intersection handling

/**
 * Finds the frontmost intersection's index, corresponding to an object.
 *
 * @param double* a pointer to the array of intersections
 * @param int the size of the array of intersections
 *
 * @returns int the index of the frontmost intersection
 */
int find_frontmost_intersection_idx(double* intersections, int size);

/**
 * Finds an intersection between a given sphere and ray.
 * Returns the root of the quadratic equation used to find the intersection.
 * This can then be tested against an epsilon later.
 *
 * @param Sphere the sphere to find an intersection with
 * @param Ray the ray to find an intersection with
 *
 * @returns double the intersection, or -1 if there was no intersection
 */
double find_intersection(Sphere sphere, Ray ray);

// Rendering

/**
 * Renders the given scene.
 *
 * @param Pixel* the image array to save the rendered image to
 * @param int the width of the image array
 * @param int the height of the image array
 * @param Colour the background colour of the image
 * @param Camera the scene's camera
 * @param Sphere* the array of scene objects
 * @param int the size of the array of scene objects
 * @param Light* the array of scene lights
 * @param int  the size of the array of scene lights
 *
 * @returns void the result is stored in the Pixel* passed to the function
 */
void render_scene(Pixel*, int, int, Colour, Camera, Sphere*, int, Light*, int);

#endif // !RENDER_H
