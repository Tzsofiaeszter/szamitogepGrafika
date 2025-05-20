#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#include "model.h"

typedef GLubyte Pixel[3];

GLuint load_texture(char* filename);

#endif 
