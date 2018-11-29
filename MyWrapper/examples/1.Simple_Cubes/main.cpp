#include <GL/freeglut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include "m.cpp"

GLfloat anglePyramid = 0.0f;  
GLfloat angleCube = 0.0f;     

void display() {
   DrawBasic(true, true); // Draws axes, xz plane

   for (GLfloat i = -8.0f; i<10.0f; i = i+4){
      for (GLfloat j = -8.0f; j<10.0f; j = j+4){
         glPushMatrix(); 
         glTranslatef(i, 0.0f, j);  
         glRotatef(angleCube, 1.0f, 0.0f, 0.0f);
         glRotatef(angleCube*2, 0.0f, 1.0f, 0.0f);
         Cube(1, Colour{0.3, 0.3, 0.0 });
         glPopMatrix();
      }
   }

   // Update the rotational angle 
   angleCube -= 0.15f;
 
   glutSwapBuffers();  // Swap buffers
   glFlush();
}

int main(int argc, char** argv) {
   auto (*loop_disp_fcn)() = display;
   BasicSetup(argc, argv, loop_disp_fcn);
            
   return 0;
}