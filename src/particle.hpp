#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include <cstdlib>
#include "game_entity.hpp"
#include "texture_manager.hpp"
enum ParticleColors
{
    PARTICLE_SHIMMER,
    PARTICLE_RED,
    PARTICLE_BLUE,
    PARTICLE_YELLOW,
    PARTICLE_GREEN
};
class Particle
{
public:
    Particle(SDL_Texture *texture, int x, int y, int lifespan,
             int src_w, int src_h, int dst_w = 0, int dst_h = 0); //We could make the particle class a child of GameEntity, but since
                                                                  //particles are much more simple, I don't see a reason that is compelling enough to do so

    void render(SDL_Renderer *renderer);
    bool should_be_destroyed() const { return current_frame > lifespan; };

private:
    SDL_Texture *texture = nullptr;
    int x_pos;
    int y_pos;
    int src_w;
    int src_h;
    int dst_w;
    int dst_h;
    int current_frame = 0;
    int lifespan = 10;
    int particle_color = 0;
};
#endif