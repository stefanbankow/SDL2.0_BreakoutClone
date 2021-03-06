#ifndef BALL_HPP
#define BALL_HPP

#include <string>
#include <random>
#include <iostream>

#include "platform.hpp"
#include "brick.hpp"
#include "particle.hpp"
#include "game_entity.hpp"
#include "vector2d.hpp"

const int PARTICLE_COUNT = 20;

class Ball : public GameEntity
{
public:
    Ball(std::string texture_id, std::string particle_texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int platform_movement_speed, int y_movement_speed);
    ~Ball();

    /////SDL-related

    //Moves the ball and checks if it has collided with the platform
    void update(Platform &entity);
    //Handles input for moving the ball while it's still attached to the platform and for releasing the ball
    void handle_input(SDL_Event &e);
    void handle_key_pressed(SDL_Event &e);
    void handle_key_released(SDL_Event &e);
    //Renders the ball and checks for old particles to be destroyed
    void render() override;

    //Replaces the particles that have been on-screen long enough
    void replace_dead_particles();
    //Calls the render function for each particle
    void render_particles();

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
    bool is_out_of_bounds() const { return out_of_bounds; }

private:
    Particle *particles[PARTICLE_COUNT];
    SDL_Texture *particle_texture = nullptr;

    int platform_movement_speed;

    int ball_movement_speed;

    bool released = false;
    bool touched_a = false;
    bool touched_d = false;
    bool out_of_bounds = false;
    double initial_x_velocity = 0;
    double x_velocity = 0;
    double y_velocity = 0;
};
#endif