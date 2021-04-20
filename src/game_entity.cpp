#include "game_entity.hpp"
#include "texture_manager.hpp"

GameEntity::GameEntity(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos)
{
    this->renderer = renderer;
    this->texture_ID = texture_id;
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    SDL_QueryTexture(TextureManager::get_instance()->get_texture(texture_id), nullptr, nullptr, &src_w, &src_h);
    this->dst_w = src_w;
    this->dst_h = src_h;
}

GameEntity::GameEntity(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int src_w = 0, int src_h = 0)
{
    this->renderer = renderer;
    this->texture_ID = texture_id;
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->src_w = src_w;
    this->src_h = src_h;
    this->dst_w = src_w;
    this->dst_h = src_h;
}

GameEntity::~GameEntity()
{
}
void GameEntity::set_size(int dst_w, int dst_h)
{
    this->dst_w = dst_w;
    this->dst_h = dst_h;
}

void GameEntity::update()
{
    x_pos += 1;
}

void GameEntity::render()
{
    TextureManager::get_instance()->draw(texture_ID, renderer, x_pos, y_pos, src_w, src_h, dst_w, dst_h);
}
