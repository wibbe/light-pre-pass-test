
#include "Utils.hpp"
#include "SOIL/SOIL.h"

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

   GLuint makeTexture(std::string const& filename)
   {
     return SOIL_load_OGL_texture(filename.c_str(), 4, SOIL_CREATE_NEW_ID, 0);
   }
}

