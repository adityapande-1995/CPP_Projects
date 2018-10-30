#include <iostream>
#include <SDL2/SDL.h>
#include "m.cpp"

#define WIDTH 500
#define HEIGHT 500 

auto S = NewScreen( WIDTH, HEIGHT, MyColor{0,0,0,128} );

int main(){

    auto b = Ball{S,250,250,20};

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
                std::cout << "Key pressed" << std::endl;
                switch (e.key.keysym.sym){
                    case SDLK_UP: b.jump(); break;
                }
            }
        } 

        Background(S);
        // Actual drawing

        b.update();
        b.show();


        Update(S);
    }
    Shutdown(S);  
    return 0;
}