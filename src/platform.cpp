#include "platform.hpp"

Platform::Platform(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos)
    : GameEntity(texture_id, renderer, x_pos, y_pos)
{
}
Platform::Platform(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int width, int height)
    : GameEntity(texture_id, renderer, x_pos, y_pos, width, height)
{
}

void Platform::handleInput(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        if (e.key.keysym.sym == SDLK_a)
        {
            x_vel -= movement_speed;
        }
        else if (e.key.keysym.sym == SDLK_d)
        {
            x_vel += movement_speed;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        if (e.key.keysym.sym == SDLK_a)
        {
            x_vel += movement_speed;
        }
        else if (e.key.keysym.sym == SDLK_d)
        {
            x_vel -= movement_speed;
        }
    }
}

void Platform::move()
{
    //Change position based on velocity
    int screen_width;
    SDL_GetRendererOutputSize(get_renderer(), &screen_width, nullptr);

    x_pos += x_vel;
    if (x_pos < 0 || x_pos + get_desired_width() > screen_width)
    {
        x_pos -= x_vel;
    }
}

void Platform::update()
{
    move();
}
