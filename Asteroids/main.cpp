#include <iostream>
#include <SDL2/SDL.h>
#include "m.cpp"

#define WIDTH 500
#define HEIGHT 500 

auto S = NewScreen( WIDTH, HEIGHT, MyColor{50,50,50,128} );

void Key_actions(auto keyboard_state_array, auto& ship){
    if (keyboard_state_array[SDL_SCANCODE_RIGHT]){
            ship.Rotate_right();
        }
        if (keyboard_state_array[SDL_SCANCODE_LEFT]){
            ship.Rotate_left();
        }
        if (keyboard_state_array[SDL_SCANCODE_W]){
            ship.up();
        }
        if (keyboard_state_array[SDL_SCANCODE_S]){
            ship.down();
        }
        if (keyboard_state_array[SDL_SCANCODE_A]){
            ship.left();
        }
        if (keyboard_state_array[SDL_SCANCODE_D]){
            ship.right();
        }
        if (keyboard_state_array[SDL_SCANCODE_SPACE]){
            ship.fire_bullet();
        }
}

int main(){
    auto ship = Shooter(S);
    auto a = asteroid(S);
    
    int framecount = 0;
    // Loop
    SDL_Event e; bool quit = false; 
    while (!quit) 
    { 
        auto keyboard_state_array = SDL_GetKeyboardState(NULL);

        if (SDL_PollEvent(&e)) 
        { 
            switch (e.type){
                case SDL_QUIT: quit = true; break;
            }
        } 

        Background(S);
        // Actual game loop
        // Keyboard actions
        Key_actions(keyboard_state_array, ship);

        // Show and update objects
        ship.Show();
        ship.update_bullets(); 
        a.Show();
        
        Update(S);
        framecount++;
    }
    Shutdown(S);  
    return 0;
}