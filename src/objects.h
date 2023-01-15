#ifndef OBJECTS_H
#define OBJECTS_H

#include "vector.h"

// Camera

typedef struct Camera {
  Vector position;
  Vector up;
  Vector look_at;
  int fov;
  int max_bounces;
} Camera ;

/**
 * Initialises a Camera struct with the given values.
 *
 * @param Vector the camera position
 * @param Vector the up direction of the camera 
 * @param Vector the position the camera is looking at
 * @param int the angle of the field of view of the camera
 * @param int the maximum amount of bounces during reflection calculation
 *
 * @returns a Camera struct initialised with the given values.
 */
Camera Camera_value(Vector, Vector, Vector, int, int);

// Ray

typedef struct Ray {
  Vector origin;
  Vector direction;
} Ray;

/**
 * Initialises a Ray struct with the given values.
 *
 * @param Vector the ray's origin
 * @param Vector the ray's direction
 *
 * @returns a Ray struct initialised with the given values.
 */
Ray Ray_value(Vector, Vector);

// Light

typedef enum {
  LIGHT_AMBIENT,
  LIGHT_PARALLEL,
  LIGHT_POINT
} LightType;

typedef struct Light {
  double r;
  double g;
  double b;
  LightType type;
  Vector v;
} Light ;

/**
 * Initialises a Light struct with the given values.
 *
 * @param double the red value, 0 - 1
 * @param double the green value, 0 - 1
 * @param double the blue value, 0 - 1
 * @param LightType the type of the light being initialised
 * @param Vector the direction of a parallel light or position of a point light
 *
 * @returns a Light struct initialised with the given values.
 */
Light Light_value(double, double, double, LightType, Vector);

/**
 * Initialises an ambient light with the given values.
 *
 * @param double the red value, 0 - 1
 * @param double the green value, 0 - 1
 * @param double the blue value, 0 - 1
 *
 * @returns a Light struct describing an ambient light initialised with the given values.
 */
Light Light_ambient_value(double, double, double);

/**
 * Initialises a parallel light with the given values.
 *
 * @param double the red value, 0 - 1
 * @param double the green value, 0 - 1
 * @param double the blue value, 0 - 1
 * @param Vector the direction of the light
 *
 * @returns a Light struct describing a parallel light initialised with the given values.
 */
Light Light_parallel_value(double, double, double, Vector);

/**
 * Initialises a parallel light with the given values.
 *
 * @param double the red value, 0 - 1
 * @param double the green value, 0 - 1
 * @param double the blue value, 0 - 1
 * @param Vector the position of the light
 *
 * @returns a Light struct describing a point light initialised with the given values.
 */
Light Light_point_value(double, double, double, Vector);

// Sphere

typedef struct Sphere {
  Vector position;
  double radius;
  // Colour
  double r;
  double g;
  double b;
  // Phong components
  double phong_ambient;
  double phong_diffuse;
  double phong_specular;
  double phong_exponent;
  // Light reflection
  double reflectance;
  double transmittance;
  // Refraction
  double iof;
} Sphere;

/**
 * Initialises a Sphere struct with the given values.  
 *
 * @param Vector the position of the origin of the sphere
 * @param double the radius of the sphere
 * @param double the red value, 0 - 1
 * @param double the green value, 0 - 1
 * @param double the blue value, 0 - 1
 * @param double the ambient component of phong illumination
 * @param double the diffuse component of phong illumination
 * @param double the specular component of phong illumination
 * @param double the exponent component of phong illumination, used in specular calculation
 * @param double the reflectance value
 * @param double the transmittance value
 * @param double the iof value
 *
 * @returns a Sphere struct initialised with the given values.
 */
Sphere Sphere_value(Vector, double, double, double, double, double, double, double, double, double, double, double);

#endif // !OBJECTS_H

