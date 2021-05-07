#include "particle.hpp"

Particle::Particle(SDL_Texture *texture, int x, int y, int lifespan,
                   int src_w, int src_h, int dst_w, int dst_h)
{
    //We don't need really need the coordinates to be completely random to get the desired effect, therefore we can simply use rand()
    x_pos = x + rand() % 25;
    y_pos = y + rand() % 25;

    current_frame = rand() % 5;

    this->texture = texture;

    this->particle_color = rand() % 4 + 1;

    this->lifespan = lifespan;
    this->src_w = src_w;
    this->src_h = src_h;
    this->dst_w = dst_w ? dst_w : src_w;
    this->dst_h = dst_h ? dst_h : src_h;
}

void Particle::render(SDL_Renderer *renderer)
{
    if (renderer != nullptr)
        if (current_frame % 5 == 0) //Render the shimmer effect every 3 frames
        {
            TextureManager::get_instance()->draw_frame(texture, renderer, x_pos, y_pos, PARTICLE_SHIMMER, 0, src_w, src_h, dst_w, dst_h);
        }
        else
        {
            TextureManager::get_instance()->draw_frame(texture, renderer, x_pos, y_pos, particle_color, 0, src_w, src_h, dst_w, dst_h);
        }

    current_frame++;
}