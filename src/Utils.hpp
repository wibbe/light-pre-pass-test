
#ifndef OPENGL_UTILS_HPP
#define OPENGL_UTILS_HPP

#include "GL/glew.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>

namespace gl
{
   
   GLuint makeBuffer(GLenum target, void const * bufferData, GLsizei bufferSize);
   GLuint makeTexture(std::string const& filename);
   
}

#endif

