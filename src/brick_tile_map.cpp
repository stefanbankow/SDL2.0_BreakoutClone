#include "brick_tile_map.hpp"

BrickTileMap::BrickTileMap(std::string texture_id, SDL_Renderer *renderer, int bricks[], int brick_rows, int brick_cols, int brick_w, int brick_h)
{
    for (int row = 0; row < brick_rows; row++)
    {
        for (int col = 0; col < brick_cols; col++)
        {
            int brick_type = bricks[row * brick_cols + col]; //Less readable but it has faster performance
            Brick *new_brick = new Brick(texture_id, renderer, 0 + brick_w * col, 0 + brick_h * row, 64, 32, brick_type);

            new_brick->set_size(brick_w, brick_h);

            this->bricks.push_back(new_brick);
        }
    }
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