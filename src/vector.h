#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
  double x;
  double y;
  double z;
} Vector ;

/**
 * Initialises a vector struct with the given values.
 *
 * @param double the x value of the vector
 * @param double the y value of the vector
 * @param double the z value of the vector
 *
 * @returns Vector the created Vector.
 */
Vector Vector_value(double, double, double);

// Vector operations

/**
 * Calculates the magnitude of the given vector.
 *
 * @param Vector the vector
 *
 * @returns double the magnitude of the vector
 */
double Vector_magnitude(Vector);


/**
 * Normalises the given vector.
 *
 * @param Vector the vector
 *
 * @returns Vector the normalised input vector
 */
Vector Vector_norm(Vector);

/**
 * Adds two vectors together.
 *
 * @param Vector the first vector
 * @param Vector the second vector
 *
 * @returns Vector the addition of the two vectors
 */
Vector Vector_add(Vector, Vector);

/**
 * Subtracts a vector from another
 *
 * @param Vector the vector to be subtracted from
 * @param Vector the vector to be subtracted
 *
 * @returns Vector the subtraction of the two vectors
 */
Vector Vector_sub(Vector, Vector);

/**
 * Calculates the dot product of two vectors
 *
 * @param Vector the first vector 
 * @param Vector the second vector
 *
 * @returns double the dot product of the two vectors
 */
double Vector_dot(Vector, Vector);

/**
 * Calculates the cross product of two vectors
 *
 * @param Vector the first vector
 * @param Vector the second vector
 *
 * @returns Vector the cross product of the two vectors
 */
Vector Vector_cross(Vector, Vector);

/**
 * Calculates the negative of the given vector
 *
 * @param Vector the input vector
 *
 * @returns Vector the negative of the input vector
 */
Vector Vector_neg(Vector);

/**
 * Multiplies a vector with a scalar.
 *
 * @param Vector the vector to scale
 * @param double the scalar to scale by
 *
 * @returns Vector the scaled vector
 */
Vector Vector_scale(Vector, double);

#endif // !VECTOR_H
