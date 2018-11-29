#include <GL/freeglut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include "m.cpp"
#include <cmath>

class Ball{
    public:
    float x, y, z, r;
    float g = -0.025;
    float vy = 0;
    float vx = -0.5;
    float vz = 0.5;
    float e = 0.9;

    Ball(float x, float y, float z, float r, float vx, float vy, float vz){
        this->x = x; this->y = y; this->z = z; this->r = r;
        this->vx = vx; this->vy = vy; this->vz = vz; 
    };

    void update(){
        // Update y vel and position
        this->y = this->y + this->vy;
        this->vy = this->vy + this->g;
        // Check for bottom ground
        if (this->y < this->r){
            this->y = this->r;
            this->vy = -(this->e)*this->vy;
        }
        // Update x vel and position
        this->x = this->x + this->vx;
        // Check for +yz plane wall
        if  ((this->x + this->r) > 5){
            this->x = 5;
            this->vx = -1*this->vx;
        }
        //Check for -yz plane wall
        if  ((this->x - this->r) < -5){
            this->x = -5;
            this->vx = -1*this->vx;
        }

        // Update z vel and position
        this->z = this->z + this->vz;
        // Check for +xy plane wall
        if  ((this->z + this->r) > 5){
            this->z = 5;
            this->vz = -1*this->vz;
        }
        //Check for -xy plane wall
        if  ((this->z - this->r) < -5){
            this->z = -5;
            this->vz = -1*this->vz;
        }

        // std::cout << vx << " " << vy << " " << vz << std::endl;

    };

    void show(){
        glPushMatrix();
        glTranslatef(this->x, this->y, this->z);
        Sphere(this->r);
        glPopMatrix();

        // std::cout << " Show called" << std::endl;
    };
};