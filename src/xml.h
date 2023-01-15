#ifndef XML_H
#define XML_H

#include <stdio.h> // for lib below
#include "../lib/xml/src/xml.h"

#include "objects.h"
#include "render.h"

/**
 * Extracts the XML attribute at the given xml_node position.
 * Warning! don't forget to free the result!
 *
 * @param struct xml_node* a pointer to the xml node to extract the attribute from.
 * @param int the index of the attribute
 *
 * @returns char* a pointer to the string value extracted.
 */
char* extract_xml_attribute_at(struct xml_node*, int);

/**
 * Initialises the passed variables with data parsed from the given XML file
 *
 * @param char* the XML file name to parse
 * @param char* a pointer to save the file name at 
 * @param int* a pointer to save the image width at
 * @param int* a pointer to save the image height at
 * @param Camera* a pointer to save Camera data at
 * @param Sphere** a pointer to the array of spheres to save data to
 * @param int* a pointer to save the size of the spheres array at
 * @param Light** a pointer to the array of lights to save data to
 * @param int* a pointer to save the size of the lights array at
 *
 */
int parse_xml_inputs(char*, char*, int*, int*, Colour*, Camera*, Sphere**, int*, Light**, int*);


#endif // !XML_H
