#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "level.hpp"

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

    bool load_level(std::string level_file_path, int platform_movement_speed, int ball_movement_speed);

    bool is_game_running() { return is_running; };

private:
    bool is_running;
    bool level_playing = false;
    int window_width;
    int window_height;
    Level *level = nullptr;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif
