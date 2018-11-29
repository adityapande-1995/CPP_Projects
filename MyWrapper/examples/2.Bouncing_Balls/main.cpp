#include <GL/freeglut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include "m1.cpp"
#include <vector>

void display();

std::vector<Ball> Arr;

int main(int argc, char** argv) {

   // Fill ball array
      for (int i = 0; i<10; i++){
      float vx = My_random(-5,5)/15;
      float vy = My_random(-5,5)/15;
      float vz = My_random(-5,5)/15;
      Arr.push_back( Ball(0, 5, 0, 0.25, vx, vy , vz) );
   }

   // Basic setup for OpenGL
   auto (*loop_disp_fcn)() = display;
   BasicSetup(argc, argv, loop_disp_fcn);

   return 0;
}

void display() {
   DrawBasic(false, false); // Draws axes, xz plane

   // Draw the Ground plane
   glPushMatrix();
      glRotatef(90, 1, 0, 0);
      Square(10,10);
   glPopMatrix();

   for (int i = 0; i < Arr.size(); i++){
      Arr[i].show();
      Arr[i].update();
   }

   glutSwapBuffers();  // Swap buffers
   glFlush();
}

