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
    ~Level();

    void handle_input(SDL_Event &e);
    void update();
    void render();

private:
    bool successfully_loaded = false;
    Ball *ball;
    Platform *platform;
    BrickTileMap *bricks;
};

#endif