#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ppm.h"

const char *USAGE = "<usage>";

int main (int argc, char *argv[]) {
  // Setup and CLI argument parsing
  int image_height = 480;
  int image_width = 640;

  extern char *optarg;
  int err_flag = 0;
  int c;
  while ((c = getopt(argc, argv, "h:w:")) != -1) {
    switch (c) {
      case 'h':
        image_height = atoi(optarg);
        break;
      case 'w':
        image_width = atoi(optarg);
        break;
      case '?':
        err_flag++;
        break;
    }
  }
  if (err_flag > 0) {
    fprintf(stderr, "Invalid arguments. Usage: %s\n", USAGE); 
    exit(2);
  }

  // Render set up
  printf("Starting render with glorious C99...\n");
  int image_size = image_width * image_height;
  Pixel *img = (Pixel*)malloc(sizeof(Pixel) * image_size); 

  printf("%d %d\n", image_height, image_width);
  // Render loop
  for (int row = 0; row < image_height; row++) {
    for (int col = 0; col < image_width; col++) {
      int this_pixel_idx = row * image_width + col;
      Pixel px; 
      if ((col > 100 & col < 300) && (row > 100 && row < 300)) {
        px = Pixel_value(1, 22, 255);
      } else {
        px = Pixel_value(0, 0, 0);
      }
      img[this_pixel_idx] = px;
    }
  }


  ppm_save_to_file(img, image_height, image_width, "test.ppm");
  
  printf("Render finished!\n");

  // Memory clean up
  free(img);
  return 0;
}
