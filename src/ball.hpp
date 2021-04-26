#ifndef BALL_HPP
#define BALL_HPP
#include <string>
#include <random>
#include <iostream>

#include "game_entity.hpp"
#include "brick.hpp"
#include "vector2d.hpp"

class Ball : public GameEntity
{
public:
    Ball(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int y_movement_speed = 0);

    //SDL-related

    void update() override;

    //Movement

    //Moves the ball and checks for border-collision
    void move();
    //Moves the ball with the platform before the player releases it
    void move_with_platform(int platform_velocity);

    //Releases the ball in a random direction
    void release();

    //Checks if the ball is colliding with the given brick and destroys it if true
    bool check_brick_collision(Brick &entity);

    //Getters/Setters/Util

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