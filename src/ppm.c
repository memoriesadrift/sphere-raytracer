#include <stdio.h>

#include "ppm.h"

Pixel Pixel_value(int r, int g, int b) {
  Pixel p = {r, g, b};

  return p;
}

Pixel Pixel_copy(Pixel p) {
  Pixel q = {
    .r = p.r,
    .g = p.g,
    .b = p.b
  };

  return q;
}

void Pixel_print(Pixel p) {
  printf("(%d, %d, %d)", p.r, p.g, p.b);
}

int ppm_save_to_file(Pixel *image, int h, int w, char *file_name) {
  FILE *file = fopen(file_name, "w");

  if (file == NULL) {
    return -1;
  }

  // Headers
  fprintf(file, "P3\n");
  fprintf(file, "%d %d\n", w, h);
  fprintf(file, "%d\n", 255);

  // Contents
  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {
      int idx = row * w + col;
      fprintf(file, " %d %d %d \n", image[idx].r, image[idx].g, image[idx].b);
    }
  }

  return fclose(file);
}

