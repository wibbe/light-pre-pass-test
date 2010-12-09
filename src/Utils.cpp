
#include "Utils.hpp"

namespace gl
{
   GLuint makeBuffer(GLenum target, void const * bufferData, GLsizei bufferSize)
   {
      GLuint buffer;
      glGenBuffers(1, &buffer);
      glBindBuffer(target, buffer);
      glBufferData(target, bufferSize, bufferData, GL_STATIC_DRAW);
      return buffer;
   }
}