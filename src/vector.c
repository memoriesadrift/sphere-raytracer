#include <math.h> // sqrt

#include "vector.h"

Vector Vector_value(double x, double y, double z) {
  Vector v = {x, y, z};

  return v;
}

double Vector_magnitude(Vector v) {
  return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

Vector Vector_norm(Vector v) {
  double m = Vector_magnitude(v);
  Vector u = {
    .x = v.x / m,
    .y = v.y / m,
    .z = v.z / m
  };

  return u;
}

Vector Vector_add(Vector a, Vector b) {
  Vector v = {
    .x = a.x + b.x,
    .y = a.y + b.y,
    .z = a.z + b.z,
  };

  return v;
}

Vector Vector_sub(Vector a, Vector b) {
  Vector v = {
    .x = a.x - b.x,
    .y = a.y - b.y,
    .z = a.z - b.z,
  };

  return v;
}

double Vector_dot(Vector a, Vector b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector Vector_cross(Vector a, Vector b) {
  Vector v = {
    .x = a.y * b.z - a.z * b.y,
    .y = a.z * b.x - a.x * b.z,
    .z = a.x * b.y - a.y * b.x,
  };

  return v;
}

Vector Vector_neg(Vector v) {
  Vector u = {
    .x = -v.x,
    .y = -v.y,
    .z = -v.z,
  };

  return u;
}

Vector Vector_scale(Vector v, double by) {
  Vector u = {
    .x = v.x * by,
    .y = v.y * by,
    .z = v.z * by,
  };

  return u;
}

