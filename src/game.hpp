#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game
{
public:
    void init(const char *title, int width, int height, bool fullscreen = false, int x_pos = SDL_WINDOWPOS_UNDEFINED, int y_pos = SDL_WINDOWPOS_UNDEFINED);
    void handle_input();
    void update();
    void render();
    void clean();
    bool is_game_running() { return is_running; };

private:
    bool is_running;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif
