#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
  double x;
  double y;
  double z;
} Vector ;

Vector Vector_value(double, double, double);

Vector Vector_add(Vector, Vector);

Vector Vector_sub(Vector, Vector);

Vector Vector_cross(Vector, Vector);

Vector Vector_neg(Vector);

Vector Vector_scale(Vector, double);

#endif // !VECTOR_H
