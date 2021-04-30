#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <iostream>
#include <string>
#include <fstream>
#include "ball.hpp"
#include "platform.hpp"
#include "brick_tile_map.hpp"

class Level
{
public:
    Level(std::string bricks_file_path, SDL_Renderer *renderer, int screen_width, int screen_height, int platform_movement_speed, int ball_movement_speed);

    //Deletes ball, platform, and brick tile map
    ~Level();

    //Handles control of the ball and platform
    void handle_input(SDL_Event &e);

    //Updates every frame
    void update();

    //Renders components
    void render();

    bool load(SDL_Renderer *renderer, int screen_width, int screen_height);

    bool reset(SDL_Renderer *renderer, int screen_width, int screen_height);

    bool is_successfully_loaded() const { return successfully_loaded; }
    bool is_failed() const { return failed; }

private:
    bool successfully_loaded = false;
    bool failed = false;
    bool completed = false;
    Ball *ball = nullptr;
    Platform *platform = nullptr;
    BrickTileMap *bricks = nullptr;

    //Variables needed for resetting the level
    std::string bricks_file_path;
    int platform_movement_speed;
    int ball_movement_speed;
};

#endif