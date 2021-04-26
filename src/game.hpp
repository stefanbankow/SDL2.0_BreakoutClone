#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game
{
public:
    //Creates the SDL_Window
    void init(const char *title, int width, int height, bool fullscreen = false, int x_pos = SDL_WINDOWPOS_UNDEFINED, int y_pos = SDL_WINDOWPOS_UNDEFINED);
    //Handles user input
    void handle_input();
    //Update the properties of the objects inside the game
    void update();
    //Update what the player sees
    void render();
    //Clean the assets used by the game
    void clean();
    bool is_game_running() { return is_running; };

private:
    bool is_running;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif
