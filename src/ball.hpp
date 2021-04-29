#ifndef BALL_HPP
#define BALL_HPP

#include <string>
#include <random>
#include <iostream>
#include "platform.hpp"
#include "brick.hpp"
#include "game_entity.hpp"

#include "vector2d.hpp"

class Ball : public GameEntity
{
public:
    Ball(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int platform_movement_speed = 0, int y_movement_speed = 0);

    /////SDL-related

    //Moves the ball and checks if it has collided with the platform
    void update(Platform &entity);
    //Handles input for moving the ball while it's still attached to the platform and for releasing the ball
    void handle_input(SDL_Event &e);

    //////Movement

    //Moves the ball
    void move(int platform_width);

    //Releases the ball in a random direction
    void release();

    ////Collisions

    //Checks if the ball is colliding with the given brick and sets the coordinates of the closest point on the brick if they do
    bool check_collision(GameEntity &entity, int &closest_point_x, int &closest_point_y);

    //Changes the ball's velocity depending on the point of impact
    void handle_brick_collision(Brick &entity, int closest_point_x, int closest_point_y);

    //Send the ball back up upon collision with the platform
    void handle_platform_collision(Platform &platform, int closest_point_x, int closest_point_y);

    //////Getters/Setters/Util

    void set_location(int x, int y);
    void set_size(int width, int height);

    int get_x_velocity() const { return x_velocity; }
    void set_x_velocity(int velocity) { x_velocity = velocity; }

    int get_y_velocity() const { return y_velocity; }
    void set_y_velocity(int velocity) { y_velocity = velocity; }

    bool is_released() const { return released; }

private:
    int platform_movement_speed;

    int y_movement_speed;

    bool released = false;
    int x_velocity = 0;
    int y_velocity = 0;
};
#endif