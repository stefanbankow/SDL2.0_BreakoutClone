#ifndef BRICK_HPP
#define BRICK_HPP
#include "game_entity.hpp"
#include <SDL.h>
#include <string>

enum BrickTextures
{
    BRICK_RED = 1, //1 becayse 0 is reserved for empty spaces
    BRICK_GREEN,
    BRICK_BLUE,
    BRICK_YELLOW,
};
class Brick : public GameEntity
{
public:
    Brick(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int src_w, int src_h, int brick_type);

    //Renders the correct frame of the sprite sheet
    void render() override;

private:
    int texture_row;
    int texture_col;
};

#endif