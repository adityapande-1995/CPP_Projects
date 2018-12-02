#include <GL/freeglut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include "m1.cpp"

void display();

// Global initializations if any
std::vector <electron> E;

int main(int argc, char** argv) {
   // Animation setup stuff here

   int n = 50; // Number of electrons
   int s = 1;
   for (int i = 0; i < n; i++){
      float a1 = My_random(0, 180);
      float a2 = My_random(0, 180);
      float a3 = My_random(0, 180);
      float rad = My_random(2.0, 10.0);
      s = -s;
      E.push_back( electron(rad, 0.1, a1, a2, a3, s) );
   }


   // Basic setup for OpenGL
   auto (*loop_disp_fcn)() = display;
   BasicSetup(argc, argv, loop_disp_fcn);

   return 0;
}

void display() {
   DrawBasic(0, 0); // Draws axes, xz plane

   Show_Nucleus();
   // Show electrons
   for (int i = 0; i < E.size(); i++){
      E[i].update();
      E[i].show();
   }


   glutSwapBuffers();  // Swap buffers
   glFlush();
}

