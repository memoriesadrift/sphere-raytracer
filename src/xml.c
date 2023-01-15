#include <stddef.h>
#include <stdlib.h> // malloc
#include <string.h> // strncpy, memset
#include <stdio.h> // Required by lib/xml
#include <stdint.h> // Required by lib/xml

#include "../lib/xml/src/xml.h"

#include "vector.h"
#include "xml.h"
#include "render.h"
#include "objects.h"

char* extract_xml_attribute_at(struct xml_node *node, int idx) {
  struct xml_string *xstr = xml_node_attribute_content(node, idx);
  uint8_t *str = calloc(xml_string_length(xstr) + 1, sizeof(uint8_t));

  xml_string_copy(xstr, str, xml_string_length(xstr));

  return (char*)str;
}

int parse_xml_inputs(
    char *xml_file_name,
    char *file_name, 
    int *width, 
    int *height, 
    Colour *background_colour, 
    Camera *camera, 
    Sphere **spheres, 
    int *spheres_size,
    Light **lights,
    int *lights_size
    ) {
  // Read XML into string buffer
  FILE *file = fopen(xml_file_name, "rb");

  if (file == NULL) {
    printf("Error opening file!\n");
    return -1;
  }

  fseek(file, 0L, SEEK_END);
  long file_size = ftell(file);
  rewind(file);
  char *xml_source = malloc(sizeof(char) * (file_size + 1));

  fread(xml_source, sizeof(char), file_size, file);

  // Newlines in header mess up the windows generated xmls
  // so we check the header lines separately
  if (
      strstr(xml_source, "<?xml version=\"1.0\" standalone=\"no\" ?>") == NULL || 
      strstr(xml_source, "<!DOCTYPE scene SYSTEM \"scene.dtd\">") == NULL
    ) {
    printf("Required header not present in input XML file!\n");
    return -1;
  }

  // remove the header
  memset(xml_source, ' ', 75);

  // Parse XML
  // Doctype and DTD (first two lines) causes this to not work!
  // that is why we removed the header above
  struct xml_document *xml = xml_parse_document((uint8_t*)xml_source, file_size + 1);

  if (!xml) {
    printf("Error parsing XML document, this is most likely due to the XML parsing lib.\n");
    return -1;
  }

  struct xml_node *root = xml_document_root(xml);

  // Set ouput file name
  struct xml_string *scene_name = xml_node_attribute_content(root, 0);
  xml_string_copy(scene_name, (uint8_t*)file_name, xml_string_length(scene_name));

  // Replace png extension with ppm
  if (strstr(file_name, "png") != NULL) {
    printf("Replacing png with ppm...\n");
    strncpy(strstr(file_name, "png"), "ppm", 3);
  }

  // Parse background colour
  struct xml_node *bg_col_node = xml_node_child(root, 0);
  double r, g, b;

  char *r_str = extract_xml_attribute_at(bg_col_node, 0);
  char *g_str = extract_xml_attribute_at(bg_col_node, 1);
  char *b_str = extract_xml_attribute_at(bg_col_node, 2);

  r = strtod((char*)r_str, NULL);
  g = strtod((char*)g_str, NULL);
  b = strtod((char*)b_str, NULL);

  *background_colour = Colour_value(r, g, b);

  free(r_str);
  free(g_str);
  free(b_str);

  // Parse camera data
  struct xml_node *camera_node = xml_node_child(root, 1);
  // Reuse vars for vectors
  double x, y, z;

  // position
  struct xml_node *cam_pos_node = xml_node_child(camera_node, 0);

  char *x_pos_str = extract_xml_attribute_at(cam_pos_node, 0);
  char *y_pos_str = extract_xml_attribute_at(cam_pos_node, 1);
  char *z_pos_str = extract_xml_attribute_at(cam_pos_node, 2);
  
  x = strtod(x_pos_str, NULL);
  y = strtod(y_pos_str, NULL);
  z = strtod(z_pos_str, NULL);

  Vector camera_position = Vector_value(x, y, z);

  free(x_pos_str);
  free(y_pos_str);
  free(z_pos_str);

  // look at
  struct xml_node *cam_look_at_node = xml_node_child(camera_node, 1);

  char *x_look_at_str = extract_xml_attribute_at(cam_look_at_node, 0);
  char *y_look_at_str = extract_xml_attribute_at(cam_look_at_node, 1);
  char *z_look_at_str = extract_xml_attribute_at(cam_look_at_node, 2);
  
  x = strtod(x_look_at_str, NULL);
  y = strtod(y_look_at_str, NULL);
  z = strtod(z_look_at_str, NULL);

  Vector look_at = Vector_value(x, y, z);

  free(x_look_at_str);
  free(y_look_at_str);
  free(z_look_at_str);

  // up
  struct xml_node *cam_up_node = xml_node_child(camera_node, 2);

  char *x_up_str = extract_xml_attribute_at(cam_up_node, 0);
  char *y_up_str = extract_xml_attribute_at(cam_up_node, 1);
  char *z_up_str = extract_xml_attribute_at(cam_up_node, 2);
  
  x = strtod(x_up_str, NULL);
  y = strtod(y_up_str, NULL);
  z = strtod(z_up_str, NULL);

  Vector camera_up = Vector_value(x, y, z);

  free(x_up_str);
  free(y_up_str);
  free(z_up_str);

  // fov
  struct xml_node *cam_fov_node = xml_node_child(camera_node, 3);

  char *fov_angle_str = extract_xml_attribute_at(cam_fov_node, 0);

  int fov_angle = atoi(fov_angle_str);

  free(fov_angle_str);

  // Image resolution
  struct xml_node *cam_res_node = xml_node_child(camera_node, 4);

  char *img_w_str = extract_xml_attribute_at(cam_res_node, 0);
  char *img_h_str = extract_xml_attribute_at(cam_res_node, 1);

  *width = strtod(img_w_str, NULL);
  *height = strtod(img_h_str, NULL);

  free(img_w_str);
  free(img_h_str);

  // max bounces
  struct xml_node *cam_max_bounces_node = xml_node_child(camera_node, 5);

  char *max_bounces_str = extract_xml_attribute_at(cam_max_bounces_node, 0);

  int max_bounces = atoi(max_bounces_str);

  free(max_bounces_str);

  // at last, initialise the camera!
  *camera = Camera_value(camera_position, camera_up, look_at, fov_angle, max_bounces);

  // Parse lights
  struct xml_node *lights_node = xml_node_child(root, 2);

  size_t light_count = xml_node_children(lights_node);

  *lights = malloc(sizeof(Light) * light_count);
  *lights_size = light_count;

  // XML Light attribute names
  const char* ambient_name = "ambient_light";
  const char* parallel_name = "parallel_light";
  const char* point_name = "point_light";

  for (size_t i = 0; i < light_count; i++) {
    struct xml_node *curr = xml_node_child(lights_node, i);

    double r, g, b;

    struct xml_node *colour_node = xml_node_child(curr, 0);

    char *r_str = extract_xml_attribute_at(colour_node, 0);
    char *g_str = extract_xml_attribute_at(colour_node, 1);
    char *b_str = extract_xml_attribute_at(colour_node, 2);

    r = strtod(r_str, NULL);
    g = strtod(g_str, NULL);
    b = strtod(b_str, NULL);

    struct xml_string *type_xstr = xml_node_name(curr);
    char *type = calloc(xml_string_length(type_xstr) + 1, sizeof(uint8_t));
    xml_string_copy(type_xstr, (uint8_t*)type, xml_string_length(type_xstr));

    if (strncmp(ambient_name, type, strlen(ambient_name)) == 0) {
      
      (*lights)[i] = Light_ambient_value(r, g, b);
    } else if (strncmp(parallel_name, type, strlen(parallel_name)) == 0) {
      struct xml_node *vec_node = xml_node_child(curr, 1);

      char *x_str = extract_xml_attribute_at(vec_node, 0);
      char *y_str = extract_xml_attribute_at(vec_node, 1);
      char *z_str = extract_xml_attribute_at(vec_node, 2);

      double x, y, z;
      x = strtod(x_str, NULL);
      y = strtod(y_str, NULL);
      z = strtod(z_str, NULL);

      free(x_str);
      free(y_str);
      free(z_str);

      (*lights)[i] = Light_parallel_value(r, g, b, Vector_value(x, y, z));
    } else if (strncmp(point_name, type, strlen(point_name)) == 0) {
      struct xml_node *vec_node = xml_node_child(curr, 1);

      char *x_str = extract_xml_attribute_at(vec_node, 0);
      char *y_str = extract_xml_attribute_at(vec_node, 1);
      char *z_str = extract_xml_attribute_at(vec_node, 2);

      double x, y, z;
      x = strtod(x_str, NULL);
      y = strtod(y_str, NULL);
      z = strtod(z_str, NULL);

      free(x_str);
      free(y_str);
      free(z_str);

      (*lights)[i] = Light_point_value(r, g, b, Vector_value(x, y, z));
    } else {
      // Should be impossible!
    }

    free(r_str);
    free(g_str);
    free(b_str);
    free(type);
  }

  // Parse surfaces
  
  struct xml_node *surfaces_node = xml_node_child(root, 3);

  size_t surface_count = xml_node_children(surfaces_node);

  *spheres = malloc(sizeof(Sphere) * surface_count);
  *spheres_size = surface_count;

  for (int i = 0; i < surface_count; i++) {
    struct xml_node *curr = xml_node_child(surfaces_node, i);

    // Radius
    char *radius_str = extract_xml_attribute_at(curr, 0);

    double radius = strtod(radius_str, NULL);

    free(radius_str);

    // Position
    double x, y, z;
    struct xml_node *pos_node = xml_node_child(curr, 0);

    char *x_str = extract_xml_attribute_at(pos_node, 0);
    char *y_str = extract_xml_attribute_at(pos_node, 1);
    char *z_str = extract_xml_attribute_at(pos_node, 2);

    x = strtod(x_str, NULL);
    y = strtod(y_str, NULL);
    z = strtod(z_str, NULL);

    Vector position = Vector_value(x, y, z);

    free(x_str);
    free(y_str);
    free(z_str);

    // Material
    struct xml_node *material_node = xml_node_child(curr, 1);

    // Colour
    struct xml_node *colour_node = xml_node_child(material_node, 0);

    char *r_str = extract_xml_attribute_at(colour_node, 0);
    char *g_str = extract_xml_attribute_at(colour_node, 1);
    char *b_str = extract_xml_attribute_at(colour_node, 2);

    r = strtod(r_str, NULL);
    g = strtod(g_str, NULL);
    b = strtod(b_str, NULL);

    free(r_str);
    free(g_str);
    free(b_str);

    // Phong
    struct xml_node *phong_node = xml_node_child(material_node, 1);

    char *a_str = extract_xml_attribute_at(phong_node, 0);
    char *d_str = extract_xml_attribute_at(phong_node, 1);
    char *s_str = extract_xml_attribute_at(phong_node, 2);
    char *e_str = extract_xml_attribute_at(phong_node, 3);

    double phong_ambient = strtod(a_str, NULL);
    double phong_diffuse = strtod(d_str, NULL);
    double phong_specular = strtod(s_str, NULL);
    double phong_exponent = strtod(e_str, NULL);

    free(a_str);
    free(d_str);
    free(s_str);
    free(e_str);

    // Reflectance
    struct xml_node *reflect_node = xml_node_child(material_node, 2);

    char *reflect_str = extract_xml_attribute_at(reflect_node, 0);

    double reflectance = strtod(reflect_str, NULL);

    free(reflect_str);

    // Transmittance
    struct xml_node *transmit_node = xml_node_child(material_node, 3);

    char *transmit_str = extract_xml_attribute_at(transmit_node, 0);

    double transmittance = strtod(transmit_str, NULL);

    free(transmit_str);

    // Refraction
    struct xml_node *refract_node = xml_node_child(material_node, 4);

    char *refract_str = extract_xml_attribute_at(refract_node, 0);

    double iof = strtod(refract_str, NULL);

    free(refract_str);

    // Finally, construct the sphere!
    Sphere sphere = Sphere_value(position, radius, r, g, b, phong_ambient, phong_diffuse, phong_specular, phong_exponent, reflectance, transmittance, iof);

    (*spheres)[i] = sphere;
  }

  fclose(file);
  xml_document_free(xml, false);
  free(xml_source);
  return 0;
}
