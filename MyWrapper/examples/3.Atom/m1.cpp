#include "m.cpp"
#include <vector>

void Show_Nucleus(){

    glPushMatrix();
        glTranslatef(0.0, 0.0 , 0.0);
        Sphere(0.5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.75, 0.0 , 0.0);
        Sphere(0.5, Colour{1.0, 0.0, 0.0});
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.75, 0.0 , 0.0);
        Sphere(0.5, Colour{1.0, 0.0, 0.0});
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 0.75 , 0.0);
        Sphere(0.5, Colour{0.0, 0.0, 1.0});
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, -0.75 , 0.0);
        Sphere(0.5, Colour{1.0, 0.0, 0.0});
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 0.0 , 0.75);
        Sphere(0.5, Colour{1.0, 0.0, 0.0});
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 0.0 , -0.75);
        Sphere(0.5, Colour{0.0, 0.0, 1.0});
    glPopMatrix();
}


class electron{
    public:
    float R,r;
    float phase, omega; 
    float ax, ay, az;
    int spin;

    electron(float R, float r, float ax, float ay, float az, int spin){
        this->R = R; this->r = r; 
        this->phase = 0; 
        // this->omega = 0.02; 
        this->omega = My_random(2,5)/100;
        this->ax = ax; this->ay = ay; this->az = az; 
        this->spin = spin;
    };

    void update(){
        if(this->spin > 0){
            this->phase = this->phase + this->omega;
        }
        else{
            this->phase = this->phase - this->omega;
        }
        
    };

    void show(){
        float x = this->R*std::cos(this->phase);
        float y = this->R*std::sin(this->phase);

        glPushMatrix();
            glRotatef(this->ax, 1.0, 0.0, 0.0);
            glRotatef(this->ay, 0.0, 1.0, 0.0);
            glRotatef(this->az, 0.0, 0.0, 1.0);
            glTranslatef(x ,y,0);
            Sphere(this->r);
        glPopMatrix();

        // Draw orbit
        glPushMatrix();
            glRotatef(this->ax, 1.0, 0.0, 0.0);
            glRotatef(this->ay, 0.0, 1.0, 0.0);
            glRotatef(this->az, 0.0, 0.0, 1.0);
            // Circle(0,0,this->R, 20);
            if (this->spin > 0){
                Arc(0,0,this->R, 20, (this->phase-3.1416/6), this->phase);    
            }
            else{
                Arc(0,0,this->R, 20, (this->phase+3.1416/6), this->phase);
            }
            
        glPopMatrix();        
        glEnd();

    };


};