#include <GL/freeglut.h> 
#include <iostream>
#include <functional>

struct Colour{
   float r,g,b;
};

// GLobal
float zoom = 1;
float globW = 640; 
float globH = 480;
float camx = 0;
float camy = 0;
float camz = 5;

// Prototypes
float My_random(float min, float max);
void BasicSetup(int argc, char** argv, auto disp);
void initGL();
void reshape(GLsizei width, GLsizei height);
void mouseWheel(int button, int dir, int x, int y);
void timer(int value);
void DrawBasic(bool axes, bool grid);
void process_Normal_Keys(int key, int x, int y);
void process_genKeys(unsigned char key, int x, int y);
void LightingInit();

void Square(float x, float y);
void Cube(float x, Colour c);
void Pyramid();

// Functions
// Random number generator 
float My_random(float min, float max){
    return ( min + ( std::rand() % int( max - min + 1 ) ) );
}

void BasicSetup(int argc, char** argv, auto disp){
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
   glutInitWindowSize(640, 480);   
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   auto WindowiD = glutCreateWindow("3D Shapes");          
   glutDisplayFunc(disp);       // Main draw function
   glutMouseFunc(mouseWheel); // Mouse scroll
   glutSpecialFunc( process_Normal_Keys ); // Keyboard events
   glutKeyboardFunc( process_genKeys );
   glutReshapeFunc(reshape);       // Resize event
   initGL();                       // Further details
   LightingInit();
   glutTimerFunc(0, timer, 0);     // TImer call
   glutMainLoop();
} 

void initGL() {
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
   
   globW = width;
   globH = height;
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void LightingInit() {
   GLfloat light_position[] = { 0.0, 1.0, 0.0, 1.0 };
   GLfloat spot_direction[] = {0.0, 0.0, 0.0};
   GLfloat exp[] = {1.0};
   glShadeModel (GL_SMOOTH);

   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   // glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
   // glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, exp);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

void mouseWheel(int button, int dir, int x, int y){

   if (button == 3){
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(45.0*zoom, globW/globH, 0.1f, 100.0f);
      zoom = zoom*1.01;
      
   }
   if (button == 4){
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(45.0*zoom, globW/globH, 0.1f, 100.0f);
      zoom = zoom/1.01;
   }
}

void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(15, timer, 0); // next timer call 15 milliseconds later
}

void DrawBasic(bool axes, bool grid){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix
   glLoadIdentity(); 
   gluLookAt(camx, camy, camz,
             0.0, 0.0, 0.0,
             0.0, 1, 0.0);
   
   if (axes){
      // Draw Axes
      float len = 2;
      float origin_z = 0;
      glLineWidth(5);
      glBegin(GL_LINES);
      // glColor3f(1.0f, 0.0f, 0.0f);
      GLfloat mat_amb[] = { 1.0, 0, 0, 1.0 };
      GLfloat mat_spec[] = { 1.0, 0, 0, 1.0 };
      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_amb);

      glVertex3f(0, 0,origin_z);
      glVertex3f(len, 0, origin_z);
      glEnd();
      glBegin(GL_LINES);
      // glColor3f(0.0f, 1.0f, 0.0f);
      GLfloat mat1_amb[] = { 0, 1.0, 0, 1.0 };
      GLfloat mat1_spec[] = { 0, 1.0, 0, 1.0 };
      glMaterialfv(GL_FRONT, GL_AMBIENT, mat1_amb);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat1_amb);
      
      glVertex3f(0, 0,origin_z);
      glVertex3f(0, len, origin_z);
      glEnd();
      glBegin(GL_LINES);
      // glColor3f(0.0f, 0.0f, 1.0f);
      GLfloat mat2_amb[] = { 0, 0, 1.0, 1.0 };
      GLfloat mat2_spec[] = { 0, 0, 1.0, 1.0 };
      glMaterialfv(GL_FRONT, GL_AMBIENT, mat2_amb);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat2_amb);

      glVertex3f(0, 0,origin_z);
      glVertex3f(0, 0, origin_z+len);
      glEnd();
   }
   if (grid){
   GLfloat mat_amb[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_spec[] = { 1.0, 1.0, 1.0, 1.0 };
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_amb);
   // Draw grid
   float gridL = 10;
   glLineWidth(1);
   glPushMatrix();
   for (int i=-10; i<=10; i++){
      
         glBegin(GL_LINES);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex3f(-gridL, 0,i);
            glVertex3f(gridL, 0, i);
         glEnd();
      
   }
   glPopMatrix();

      glPushMatrix();
   for (int i=-10; i<=10; i++){
      
         glBegin(GL_LINES);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex3f(i, 0,-gridL);
            glVertex3f(i, 0, gridL);
         glEnd();
      
   }
   glPopMatrix();
   }
   
}

void process_Normal_Keys(int key, int x, int y) {
   // std::cout<< key << std::endl;
     switch (key) 
    {    
       case 27 :      break;
       case 100 : 
         camx--;   break;
       case 102: 
         camx++;  break;
       case 101:
         camy++;
         break;
       case 103 : 
         camy--;
         break;
    }

}

void process_genKeys(unsigned char key, int x, int y){
   switch(key){
      case 'n': camz++; break;
      case 'm': camz--; break;
      case ' ' : camx = 0; camy = 0; camz = 5; break; 
   }
}

// Drawing objects
void Square(float x, float y){
   GLfloat mat_amb[] = { 0.0, 1.0, 0.0, 1.0 };
   GLfloat spec[] = { 0.0, 1.0, 0.0, 1.0 };
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_amb);

   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      // glColor3f(0.7f, 0.5f, 0.0f); // Red
      glVertex3f(-0.5f*x, -0.5f*y, 0.0f);    // x, y
      glVertex3f( 0.5f*x, -0.5f*y, 0.0f);
      glVertex3f( 0.5f*x,  0.5f*y, 0.0f);
      glVertex3f(-0.5f*x,  0.5f*y, 0.0f);
   glEnd();

}

void Cube(float x, Colour c){
   // Add color and material
   // glColor3f(0.0f, 0.5f, 0.5f);
   GLfloat mat_amb[] = { c.r, c.g, c.b, 1.0 };
   GLfloat mat_spec[] = { c.r, c.g, c.b, 1.0 };
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_amb);
   glutSolidCube(x);
  
}

void Sphere(){
   GLfloat mat_amb[] = { 0.0, 0.0, 1.0, 1.0 };
   GLfloat mat_spec[] = { 0.0, 0.0, 1.0, 1.0 };
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_amb);
   glutSolidSphere(0.5, 10, 10);
}

void Cube1(){
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.5f, 0.5f, 0.5f);     
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);
 
      // Bottom face (y = -1.0f)
      glColor3f(0.5f, 0.5f, 0.5f);        
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
 
      // Front face  (z = 1.0f)
      glColor3f(0.5f, 0.5f, 0.5f);       
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);
 
      // Back face (z = -1.0f)
      glColor3f(0.5f, 0.5f, 0.5f);        
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);
 
      // Left face (x = -1.0f)
      glColor3f(0.5f, 0.5f, 0.5f);        
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
 
      // Right face (x = 1.0f)
      glColor3f(0.5f, 0.5f, 0.5f);        
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();  // End of drawing color-cube
}

void Pyramid(){
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
 
      // Right
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);
 
      // Back
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f, -1.0f, -1.0f);
 
      // Left
      glColor3f(1.0f,0.0f,0.0f);       // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f,0.0f,1.0f);       // Blue
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glColor3f(0.0f,1.0f,0.0f);       // Green
      glVertex3f(-1.0f,-1.0f, 1.0f);
   glEnd();   // Done drawing the pyramid
}

void Teapot(float size){
   GLfloat mat_amb[] = { 1.0, 0.0, 0.0, 1.0 };
   GLfloat mat_spec[] = { 1.0, 0.0, 0.0, 1.0 };
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_amb);
   glutSolidTeapot(size);

}
