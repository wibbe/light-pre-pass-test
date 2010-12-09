
#ifndef OPENGL_UTILS_HPP
#define OPENGL_UTILS_HPP

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <gl/gl.h>
#include <gl/glut.h>
#endif

namespace gl
{
   
   GLuint makeBuffer(GLenum target, void const * bufferData, GLsizei bufferSize);
   
}

#endif