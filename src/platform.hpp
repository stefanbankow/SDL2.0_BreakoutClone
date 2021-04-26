#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <string>
#include <SDL2/SDL.h>

#include "game_entity.hpp"
#include "ball.hpp"

class Platform : public GameEntity
{
public:
    //Create a platform with the size of the given texture
    Platform(std::string texture_id, std::string ball_texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int movement_speed = 0);

    //Create a platform with a custom size
    Platform(std::string texture_id, std::string ball_texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int width, int height, int movement_speed = 0);
    ~Platform();

    //Move based on current x_vel value
    void move();
    //Change x_vel based on input
    void handle_input(SDL_Event &e);

    //Wrapper function for calling the check_collision function of the ball object
    bool check_brick_collision(Brick &entity);

    //SDL-related

    void update() override;
    void render() override;

    //Getters/Setters/Util
    int get_movement_speed() const { return movement_speed; }
    void set_size(int width, int height) override;

private:
    int movement_speed;
    int x_vel = 0;
    Ball *ball;
};
#endif