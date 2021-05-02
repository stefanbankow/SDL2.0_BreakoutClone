#ifndef BRICK_MAP_HPP
#define BRICK_MAP_HPP
#include <SDL.h>
#include <vector>
#include <string>
#include "brick.hpp"

class BrickTileMap
{
public:
    BrickTileMap(std::string texture_id, SDL_Renderer *renderer, int brick_cols, int brick_w, int brick_h);
    ~BrickTileMap();

    //Renders the appropriate brick texture
    void render();

    //Checks if index is inside vector range, deletes the brick and then removes it from the bricks vector
    void destroy_brick_at_index(int index);

    void push_back_brick(SDL_Renderer *renderer, int brick_type);

    //Getters/Setters/Util

    Brick *get_brick_at_index(int index) const
    {
        return bricks[index];
    };
    int get_brick_count() const { return bricks.size(); };

private:
    std::string texture_id;
    int total_rows = 0;
    int total_cols;
    int current_col = 0;
    int brick_width;
    int brick_height;
    std::vector<Brick *> bricks;
};

#endif
