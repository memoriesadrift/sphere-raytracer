#include "vector.h"

Vector Vector_value(double x, double y, double z) {
  Vector v = {x, y, z};

  return v;
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

