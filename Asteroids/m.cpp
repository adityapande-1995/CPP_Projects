// Module to hold SDL window functions
#include <iostream>
#include "SDL2_gfxPrimitives.h" 
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>

#define PI 3.1415926

struct MyColor{
    int r,g,b,alpha;
};

struct MyScreen{
    SDL_Window *window;
    SDL_Renderer *renderer;
    MyColor c;
};

MyScreen NewScreen(int w, int h, MyColor c){ // Constructor
    if (SDL_Init(SDL_INIT_VIDEO)) 
    { 
        printf ("SDL_Init Error: %s", SDL_GetError()); 
        //return NULL; 
    };
    
    SDL_Window *window = SDL_CreateWindow("MyScreen Window", 100, 100, w, h, SDL_WINDOW_OPENGL); 
    if (window == NULL) 
    { 
        printf ("SDL_CreateWindow Error: %s", SDL_GetError()); 
        SDL_Quit(); 
        //return NULL; 
    };
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
    if (renderer == NULL) 
    { 
        SDL_DestroyWindow(window); 
        printf ("SDL_CreateRenderer Error: %s", SDL_GetError()); 
        SDL_Quit(); 
        //return NULL; 
    }; 

    std::cout << "Screen initialized successfully " << std::endl;
    return MyScreen{window,renderer,c};

};

void Update(MyScreen &s){// update screen on every loop
    SDL_RenderPresent(s.renderer); 
    SDL_Delay(40); 
};

void Background(MyScreen &s){ //clear screen and set background
    SDL_SetRenderDrawColor(s.renderer, s.c.r, s.c.g, s.c.b, s.c.alpha); 
    SDL_RenderClear(s.renderer); 
};

void Shutdown(MyScreen &s){ // Shutdown and exit SDL
    SDL_DestroyRenderer(s.renderer); 
    SDL_DestroyWindow(s.window); 
    SDL_Quit(); 
};

// Draw functions
void DrawRect(MyScreen &s, MyColor c, int x, int y, int w, int h, bool filled=true){
    if (filled == true){
        SDL_Rect fillRect = { x,y,w,h };
        SDL_SetRenderDrawColor( s.renderer, c.r, c.g, c.b, c.alpha );        
        SDL_RenderFillRect( s.renderer, &fillRect );
        SDL_Rect outlineRect = { x,y,w,h };
        SDL_SetRenderDrawColor( s.renderer, 0, 0, 0, c.alpha );        
        SDL_RenderDrawRect( s.renderer, &outlineRect );
    }else{
        SDL_Rect outlineRect = { x,y,w,h };
        SDL_SetRenderDrawColor( s.renderer, c.r, c.g, c.b, c.alpha );        
        SDL_RenderDrawRect( s.renderer, &outlineRect );
    }

};

void DrawCircle(MyScreen &s, MyColor c, int x, int y, int r, bool filled=true){
    if (filled == true){
        filledCircleRGBA(s.renderer, x , y , r , c.r, c.g, c.b, c.alpha); 
        circleRGBA(s.renderer, x,y,r, 0, 0, 0, c.alpha);
    }else{
        circleRGBA(s.renderer, x,y,r, c.r, c.g, c.b, c.alpha);
    }
};

void DrawLine(MyScreen &s, MyColor c, int x1, int y1, int x2, int y2, int width){
    thickLineRGBA(s.renderer, x1, y1, x2, y2, width, c.r, c.g, c.b, c.alpha) ;
};

// Random number generator function
float My_random(float min, float max){
    return ( min + ( std::rand() % int( max - min + 1 ) ) );
};

// Class bullet
class bullet{
    public:
    float x,y,r,xv,yv;
    MyScreen s;

    bullet(MyScreen s1, float x1, float y1, float xv1, float yv1){
        x = x1; y = y1; xv = xv1; yv = yv1; s = s1; 
        r = 3;
    };

    void Show(){
        DrawCircle(s, MyColor{255,255,255,255}, x, y, r);
    };

    void Update(){
        x = x + xv;
        y = y + yv;
    };

};

// Shooter
class Shooter{
    public:
    float x,y,r;
    float a1,a2,a3;
    MyScreen s;
    float movestep;
    std::vector <bullet> bullets;

    Shooter(MyScreen s1){
        std::vector <bullet> bullets ; 
        s = s1;
        x = 250; y = 250; r = 10;
        a1 = 0; a2 = 2*PI/3; a3 = 4*PI/3; 
        movestep = 5;

    };

    void Show(){
        // Show shooter triangle
        float x1 = x + r*cos(a1); float y1 = y + r*sin(a1);
        float x2 = x + r*cos(a2); float y2 = y + r*sin(a2);
        float x3 = x + r*cos(a3); float y3 = y + r*sin(a3);

        DrawLine(s, MyColor{255,255,255,255}, x1, y1, x2, y2, 1);
        DrawLine(s, MyColor{255,255,255,255}, x2, y2, x3, y3, 1);
        DrawLine(s, MyColor{255,255,255,255}, x1, y1, x3, y3, 1);
        DrawCircle(s, MyColor{255,0,0,255}, x1,y1, 5 );

        // Show bullets
        for (int i=0; i < bullets.size(); i++){
            bullets[i].Show();
        }
    };

    void Rotate_right(){
        float right_inc = 0.2;
        a1 = a1 + right_inc;
        a2 = a2 + right_inc;
        a3 = a3 + right_inc; 
    };

    void Rotate_left(){
        float left_inc = 0.2;
        a1 = a1 - left_inc;
        a2 = a2 - left_inc;
        a3 = a3 - left_inc; 
    };

    void up(){
        y = y - movestep;
    };

    void down(){
        y = y + movestep;
    };

    void right(){
        x = x + movestep;
    };

    void left(){
        x = x - movestep;
    };

    void fire_bullet(){
        float x1 = x + r*cos(a1); float y1 = y + r*sin(a1);
        bullets.push_back( bullet(s, x1, y1, x1-x, y1-y) );
    };

    void update_bullets(){
        // Update positions
        for (int i=0; i < bullets.size(); i++){
            bullets[i].Update();
        }

        // Find out which bullets have left the screen
        int index; bool escaped = false;
        for (int i=0; i < bullets.size(); i++){
            if ( (bullets[i].x > 500 || bullets[i].x < 0) || (bullets[i].y > 500 || bullets[i].y < 0)  ){
                index = i;
                escaped = true;
            }
        }
        // Remove bullets according to indices array ?
        if (escaped){
            bullets.erase(bullets.begin() + index);
        }
        // std::cout << " length of bullet array : "<< bullets.size() << std::endl;
    };

};

// Asteroids
class asteroid{
    public:
    MyScreen s;
    float x,y;
    std::vector <float> x_array; std::vector <float> y_array;

    asteroid(MyScreen s1){
        s = s1;
        x = My_random(0,500); y = My_random(0,500); 
        // Generating vertices
        int n = int(My_random(3,10));
        for (int i=0; i<n; i++){
            float a = i*2*PI/n;
            float r = My_random(10,20);
            float x_vertex = x + r*cos(a); float y_vertex = y + r*sin(a);
            x_array.push_back(x_vertex); y_array.push_back(y_vertex);   
        }
    };

    void Show(){
        for (int i=0; i<x_array.size()-1; i++){
            DrawLine(s,MyColor{255,255,255,255}, x_array[i], y_array[i], x_array[i+1], y_array[i+1], 2);
        }
        DrawLine(s,MyColor{255,255,255,255}, x_array[0], y_array[0], x_array[x_array.size()-1], y_array[y_array.size()-1], 1);
    }; 

};


