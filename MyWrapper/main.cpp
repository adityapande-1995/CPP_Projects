#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include "m.cpp"

GLfloat anglePyramid = 0.0f;  
GLfloat angleCube = 0.0f;     

void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
   // Draw a cube
   glLoadIdentity();                 
   glTranslatef(1.5f, 0.0f, -7.0f);  
   glRotatef(angleCube, 1.0f, 1.0f, 1.0f);  
   Cube();
 
   // Render a pyramid consists of 4 triangles
   glLoadIdentity();                  
   glTranslatef(-1.5f, 0.0f, -6.0f);  
   glRotatef(anglePyramid, 1.0f, 1.0f, 0.0f);  
   Pyramid();

   // Draw Sphere
   glLoadIdentity();
   glTranslatef(0.0f, 0.0f, -6.0f);
   glRotatef(anglePyramid, 1.0f, 1.0f, 0.0f); 
   glutWireSphere(0.5, 10, 10);
 
   glutSwapBuffers();  // Swap buffers

   // Update the rotational angle after each refresh [NEW]
   anglePyramid += 0.2f;
   angleCube -= 0.15f;
}

int main(int argc, char** argv) {
   auto (*ptr_disp)() = display;
   BasicSetup(argc, argv, ptr_disp);
            
   return 0;
}