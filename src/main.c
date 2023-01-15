#include <stdio.h>  // fprintf
#include <stdlib.h> // free, malloc, EXIT_SUCCESS, EXIT_FAILURE, NULL
#include <string.h> // memset, strncpy
#include <unistd.h> // getopt
#include <getopt.h> // getopt -- on some systems

#include "objects.h"
#include "ppm.h"
#include "render.h"
#include "xml.h"

#define MAX_FILE_NAME_LEN 255

const char *USAGE = "./raytracer.x -f <input filename>";

int main (int argc, char *argv[]) {
  // Setup and CLI argument parsing
  char input_file_name[MAX_FILE_NAME_LEN];

  extern char *optarg;
  int err_flag = 0;
  int c;
  while ((c = getopt(argc, argv, "f:")) != -1) {
    switch (c) {
      case 'f':
        if (strlen(optarg) > MAX_FILE_NAME_LEN) {
          fprintf(stderr, "File name too long, please have your xml files have %d characters at most.\n", MAX_FILE_NAME_LEN); 
          exit(2);
        }

        memset(input_file_name, '\0', sizeof(input_file_name));
        strncpy(input_file_name, optarg, strlen(optarg));
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

  // File argument parsing
  printf("Starting XML Parsing...\n");

  char output_file_name[MAX_FILE_NAME_LEN];
  int image_height;
  int image_width;
  Camera camera;
  Colour background_colour;
  Sphere *spheres = NULL;
  int spheres_size;
  Light *lights = NULL;
  int lights_size;

  int xml_parse_result;
  xml_parse_result = parse_xml_inputs(input_file_name, output_file_name, &image_width, &image_height, &background_colour, &camera, &spheres, &spheres_size, &lights, &lights_size);

  if (xml_parse_result != 0) {
    return EXIT_FAILURE;
  }

  // Render set up
  printf("Starting render with glorious C99...\n");

  int image_size = image_width * image_height;
  Pixel *img = malloc(sizeof(Pixel) * image_size); 

  // Render function
  render_scene(img, image_width, image_height, background_colour, camera, spheres, spheres_size, lights, lights_size);

  printf("Render finished!\n");

  // Save to file
  printf("Saving to file...\n");
  ppm_save_to_file(img, image_height, image_width, output_file_name);
  

  // Memory clean up
  free(spheres);
  free(lights);
  free(img);

  return EXIT_SUCCESS;
}
