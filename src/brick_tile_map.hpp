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
    void destroy_brick_at_index(int index);

    Brick *get_brick_at_index(int index) const
    {
        return bricks[index];
    };
    int get_brick_count() const { return bricks.size(); };

private:
    std::vector<Brick *> bricks;
};

#endif
