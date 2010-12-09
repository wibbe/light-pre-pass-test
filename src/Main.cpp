
#include <iostream>
#include "Utils.hpp"
#include "HotValue.hpp"

void render();

int main(int argc, char * argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(800, 500);
   glutCreateWindow("Light Pre-Pass Test");
   glutDisplayFunc(&render);
   glutIdleFunc(&render);

   glewInit();

   // Make sure we have OpenGL 2.0
   if (!GLEW_VERSION_2_0)
   {
      std::cerr << "OpenGL Version 2.0 not supported!" << std::endl;
      return 1; 
   }
   
   glutMainLoop();
   
   return 0;
}

void render()
{
   updateHotValues();
   
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   
   glutSwapBuffers();
}

