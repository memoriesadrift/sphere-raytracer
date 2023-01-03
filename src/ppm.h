#ifndef PPM_H
#define PPM_H

typedef struct Pixel
{
  int r;
  int g;
  int b;
} Pixel;

/**
 * Initialises a pixel struct with the given rgb values.
 *
 * @param int the red value, 0 - 255
 * @param int the green value, 0 - 255
 * @param int the blue value, 0 - 255
 *
 * @returns a Pixel struct initialised with the given values.
 */
Pixel Pixel_value(int, int, int);

/**
 * Initialises a pixel struct as a copy of the given Pixel.
 *
 * @param Pixel the pixel to copy
 *
 * @returns a Pixel struct initialised with the given Pixel
 */
Pixel Pixel_copy(Pixel);

/**
 * Prints a pixel using `printf` for debug purposes
 *
 * @param Pixel the pixel to print
 */
void Pixel_print(Pixel);

/**
 * Function to save the given pixel array to a PPM image
 *
 * @param Pixel* array of pixels to write
 * @param int the height of the array to write
 * @param int the width of the array to write
 * @param char* the file name to write to
 *
 * @returns int success code 0 or error code -1 / EOF
 */
int ppm_save_to_file(Pixel*, int, int, char*);

#endif // !PPM_H

