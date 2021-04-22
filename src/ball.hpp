#ifndef BALL_HPP
#define BALL_HPP
#include <string>
#include <random>
#include <iostream>

#include "game_entity.hpp"

class Ball : public GameEntity
{
public:
    Ball(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int y_movement_speed = 0);

    //SDL-related
    void update() override;

    //Movement
    void move();
    void move_with_platform(int platform_velocity);
    void release();

    bool check_collision(GameEntity &entity) const;

    void set_location(int x, int y);
    void set_size(int width, int height);

    bool is_released() const { return released; }

private:
    int y_movement_speed;

    bool released = false;
    int x_velocity = 0;
    int y_velocity = 0;
};
#endif