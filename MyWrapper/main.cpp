#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include "m.cpp"

GLfloat anglePyramid = 0.0f;  
GLfloat angleCube = 0.0f;     

void display() {
   DrawBasic(); // Draws axes, xz plane

   //Draw a cube
   glPushMatrix(); 
   glTranslatef(0.0f, 0.0f, 0.0f);  
   glRotatef(angleCube, 1.0f, 0.0f, 0.0f);
   Cube();
   glPopMatrix();

   glPushMatrix(); 
   glTranslatef(3.0f, 0.0f, 3.0f);  
   glRotatef(angleCube, 0.0f, 1.0f, 0.0f);
   Square();
   glPopMatrix();

   // Update the rotational angle 
   angleCube -= 0.15f;
 
   glutSwapBuffers();  // Swap buffers
}

int main(int argc, char** argv) {
   auto (*ptr_disp)() = display;
   BasicSetup(argc, argv, ptr_disp);
            
   return 0;
}