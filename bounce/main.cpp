#include <iostream>
#include <SDL2/SDL.h>
#include "m.cpp"

#define WIDTH 500
#define HEIGHT 500 

auto S = NewScreen( WIDTH, HEIGHT, MyColor{50,50,50,128} );

int main(){
    Ball b(S);
    PipeArray pp(S); 
    
    int framecount = 0;

    // Loop
    SDL_Event e; bool quit = false; 
    while (!quit) 
    { 
        if (SDL_PollEvent(&e)) 
        { 
            switch (e.type){
                case SDL_QUIT:
                quit = true;
                break;

                case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_UP: b.jump(); break;
                }
            }
        } 

        Background(S);
        // Actual game loop

        if (framecount%50 == 0){
            pp.addPipe();
        }

        b.update();
        b.show();
        pp.update();
        pp.show();
        
        Update(S);
        framecount++;
    }
    Shutdown(S);  
    return 0;
}