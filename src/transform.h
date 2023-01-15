// This will be used in lab3b
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vector.h"

typedef struct Transform {
  Vector translate_by;
  Vector scale_by;
  int x_angle;
  int y_angle;
  int z_angle;
} Transform;

/**
 * Initialises a Transform struct with the given values.
 *
 * @param Vector the vector to translate by
 * @param Vector the vector to scale by
 * @param int the angle to rotate by around the X axis
 * @param int the angle to rotate by around the Y axis
 * @param int the angle to rotate by around the Z axis
 *
 * @returns the initialised Transform struct.
 */
Transform Transform_value(Vector, Vector, int, int, int);

#endif // !TRANSFORM_H
