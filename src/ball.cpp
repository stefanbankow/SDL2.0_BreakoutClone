#include "ball.hpp"

Ball::Ball(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int y_movement_speed) : GameEntity(texture_id, renderer, x_pos, y_pos)
{

    this->y_movement_speed = y_movement_speed > 0 ? y_movement_speed : 1;
}

void Ball::update()
{
    move();
}

void Ball::move()
{
    if (released)
    {
        x_pos += x_velocity;
        y_pos += y_velocity;
    }
}

void Ball::move_with_platform(int platform_velocity)
{
    if (!released)
    {
        x_pos += platform_velocity;
    }
}

void Ball::release()
{

    std::random_device generator;
    std::uniform_int_distribution<int> distribution(-2 * y_movement_speed, 2 * y_movement_speed);
    released = true;
    x_velocity = distribution(generator);

    y_velocity = -y_movement_speed; // Use the negative value of the movement speed, because otherwise the balls goes downward
}

void Ball::set_location(int x, int y)
{
    x_pos = x;
    y_pos = y;
}

void Ball::set_size(int width, int height)
{
    dst_w = width;
    dst_h = height;
}