#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <string>
#include <SDL2/SDL.h>

#include "game_entity.hpp"
#include "ball.hpp"

class Platform : public GameEntity
{
public:
    Platform(std::string texture_id, std::string ball_texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int movement_speed = 0);
    Platform(std::string texture_id, std::string ball_texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int width, int height, int movement_speed = 0);
    ~Platform();

    void move();
    void handle_input(SDL_Event &e);

    void set_size(int width, int height) override;

    void update() override;
    void render() override;

    int get_movement_speed() const { return movement_speed; }

private:
    int movement_speed;
    int x_vel = 0;
    Ball *ball;
};
#endif