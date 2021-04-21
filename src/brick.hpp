#ifndef BRICK_HPP
#define BRICK_HPP
#include "game_entity.hpp"
#include <SDL2/SDL.h>
#include <string>

enum BrickTextures
{
    BRICK_RED = 1,
    BRICK_GREEN,
    BRICK_BLUE,
    BRICK_YELLOW,
};
class Brick : public GameEntity
{
public:
    Brick(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int src_w, int src_h, int brick_type);
    void render() override;
    void set_destroyed(bool value) { destroyed = value; };
    bool is_destroyed() { return destroyed; };

private:
    bool destroyed = false;
    int texture_row;
    int texture_col;
};

#endif