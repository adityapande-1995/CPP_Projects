// Module to hold SDL window functions
#include <iostream>
#include "SDL2_gfxPrimitives.h" 
#include <SDL2/SDL.h>
#include <vector>

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

// Ball class
class Ball{
    public:
    MyScreen s;
    float x,y,r;
    float yv = 0;
    int g = 3;

    Ball(MyScreen sc){
        s = sc;
        x = 100;
        y = 250;
        r = 10;
    };

    void show(){
        DrawCircle(s,MyColor{200,200,200,255},x,y,r,true);
    };

    void update(){

        y = y+yv; // update position
        yv = yv + g; // update velocity
        
        if (y+r > 500){
		    yv = 0;
            y = 500 - r;
	    }

        // std::cout << "y : "<<y<<" yv : " << yv << std::endl;

    };

    void jump(){
        yv = -20;
        // std::cout<< "Jump command" << std::endl;
    };

};

// Pipe class
class Pipe{
    public:
    MyScreen s;
    float x,w,y1;

    Pipe(MyScreen sc){
        s = sc;
        x = 500; w = 30; 
        y1 = 0.2*500 + ( std::rand() % int( 0.6*500 - 0.2*500 + 1 ) );
    };

    void show(){
        DrawRect(s,MyColor{200,200,200,255},x,0,w,y1);
        float gap = 100;
        DrawRect(s,MyColor{200,200,200,255},x,y1+gap,w,500-y1-gap);
    };

    void update(){
        x = x-5;
    };

    bool isOffscreen(){
        return x < (-10);
    };

};

// Pipe array
class PipeArray{
    public:
    std::vector<Pipe> a;
    MyScreen s;

    PipeArray(MyScreen sc){
        s = sc;
        std::vector<Pipe> a;
    };

    void addPipe(){
        Pipe p(s);
        a.push_back(p);
        // std::cout<< "Pipe added !" << std::endl;
    };

    void show(){
        for (int i =0; i < a.size(); i++){
            a[i].show();
        }
    };

    void update(){
        // Shift pipes to left
        for (int i=0; i<a.size(); i++){
            a[i].update();
        }

        // Check for offscreen and remove
        if (a[0].isOffscreen()){
            a.erase(a.begin());
        }

        // std::cout << " Lenth of pipe vector " << a.size() << std::endl;
    };

};
