// Module to hold SDL window functions
#include <iostream>
#include "SDL2_gfxPrimitives.h" 
#include <SDL2/SDL.h>

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
    SDL_Delay(30); 
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
    }else{
        SDL_Rect outlineRect = { x,y,w,h };
        SDL_SetRenderDrawColor( s.renderer, c.r, c.g, c.b, c.alpha );        
        SDL_RenderDrawRect( s.renderer, &outlineRect );
    }

};

void DrawCircle(MyScreen &s, MyColor c, int x, int y, int r, bool filled=true){
    if (filled == true){
        filledCircleRGBA(s.renderer, x , y , r , c.r, c.g, c.b, c.alpha); 
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
    MyScreen &s;
    float x,y,r;
    float yv = 0;
    int g = 3;

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
        std::cout<< "Jump command" << std::endl;
    };

};
