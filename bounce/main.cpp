#include <iostream>
#include <SDL2/SDL.h>
#include "m.cpp"

#define WIDTH 500
#define HEIGHT 500 

auto S = NewScreen( WIDTH, HEIGHT, MyColor{0,0,0,128} );

int main(){

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
            }
        } 

        Background(S);
        // Actual drawing
        DrawRect( S, MyColor{128,128,128,128}, WIDTH / 4, HEIGHT / 4, WIDTH / 2, HEIGHT / 2 );
        DrawCircle(S, MyColor{255,0,0,255}, WIDTH/2, HEIGHT/2, 33, false );
        DrawCircle(S, MyColor{255,0,0,255}, WIDTH/2, HEIGHT/2, 30, true );
        DrawLine(S, MyColor{255,128,0,255}, 0, 0, WIDTH, HEIGHT, 20);
        DrawLine(S, MyColor{255,128,128,255}, 0, HEIGHT, WIDTH, 0, 20);

        Update(S);
    }
    Shutdown(S);  
    return 0;
}