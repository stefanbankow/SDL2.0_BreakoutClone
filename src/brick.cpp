#include "brick.hpp"
#include "texture_manager.hpp"

Brick::Brick(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int src_w, int src_h, int brick_type)
    : GameEntity(texture_id, renderer, x_pos, y_pos, src_w, src_h)
{
    switch (brick_type)
    {
    case BRICK_RED:
        texture_row = 0;
        texture_col = 0;
        break;
    case BRICK_BLUE:
        texture_row = 0;
        texture_col = 1;
        break;
    case BRICK_GREEN:
        texture_row = 0;
        texture_col = 2;
        break;
    case BRICK_YELLOW:
        texture_row = 1;
        texture_col = 0;
        break;
    default:
        texture_col = 0;
        texture_row = 0;
        break;
    }
}

void Brick::render()
{
    SDL_Renderer *renderer = get_renderer();
    SDL_Texture *texture = get_texture();
    TextureManager::get_instance()->draw_frame(texture, renderer, x_pos, y_pos, texture_col, texture_row, src_w, src_h, dst_w, dst_h);
}