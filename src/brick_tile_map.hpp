#ifndef BRICK_MAP_HPP
#define BRICK_MAP_HPP
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "brick.hpp"

class BrickTileMap
{
public:
    BrickTileMap(std::string texture_id, SDL_Renderer *renderer, int bricks[], int brick_rows, int brick_cols, int brick_w, int brick_h);
    ~BrickTileMap();
    void render();

private:
    std::vector<Brick *> bricks;
};

#endif
