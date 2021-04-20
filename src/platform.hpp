#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "game_entity.hpp"
#include <string>
#include <SDL2/SDL.h>

class Platform : public GameEntity
{
public:
    Platform(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos);
    Platform(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int width, int height);
    void handleInput(SDL_Event &e);
    void move();
    void update() override;

private:
    int movement_speed = 1;
    int x_vel = 0;
};
#endif