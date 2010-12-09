
#include <iostream>
#include "Utils.hpp"

void render();

int main(int argc, char * argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(800, 500);
   glutCreateWindow("Light Pre-Pass Test");
   glutDisplayFunc(&render);
   
   glutMainLoop();
   
   return 0;
}

void render()
{
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   
   glutSwapBuffers();
}
