#include "brick_tile_map.hpp"

BrickTileMap::BrickTileMap(std::string texture_id, SDL_Renderer *renderer, int brick_cols, int brick_w, int brick_h)
{
    this->texture_id = texture_id;
    this->total_cols = brick_cols;
    this->brick_width = brick_w;
    this->brick_height = brick_h;
};
BrickTileMap::~BrickTileMap()
{
    for (auto brick : bricks)
    {
        delete brick;
    }
    bricks.clear();
}

void BrickTileMap::render()
{
    for (auto brick : bricks)
    {
        brick->render();
    }
}

void BrickTileMap::push_back_brick(SDL_Renderer *renderer, int brick_type)
{
    //Less readable than using a 2d array but it has faster performance
    if (brick_type)
    {
        Brick *new_brick = new Brick(texture_id, renderer, 0 + brick_width * current_col, 0 + brick_height * total_rows, 64, 32, brick_type);

        new_brick->set_size(brick_width, brick_height);

        this->bricks.push_back(new_brick);
    }

    //Update this outside the F to account for empty spaces
    current_col++;
    if (current_col == total_cols)
    {
        current_col = 0;
        total_rows++;
    }
}

void BrickTileMap::destroy_brick_at_index(int index)
{
    if (index >= 0 && index < bricks.size())
    {
        delete bricks[index]; //Free up the memory
        bricks.erase(bricks.begin() + index);
    }
}