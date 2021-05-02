#include "platform.hpp"
#include "texture_manager.hpp"

Platform::Platform(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int movement_speed)
    : GameEntity(texture_id, renderer, x_pos, y_pos)
{
    this->movement_speed = movement_speed > 0 ? movement_speed : 1; //Make sure its a positive value larger than 0 or make it 1 otherwise
}
Platform::Platform(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int width, int height, int movement_speed)
    : GameEntity(texture_id, renderer, x_pos, y_pos, width, height)
{
    this->movement_speed = movement_speed > 0 ? movement_speed : 1; //Make sure its a positive value larger than 0 or make it 1 otherwise
}

Platform::~Platform()
{
}

void Platform::handle_input(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_a:
            touched = true;
            x_vel -= movement_speed;
            break;
        case SDLK_d:
            touched = true;
            x_vel += movement_speed;
            break;
        default:
            break;
        }
    }
    /*We have to check if the platform/ball was moved (the "touched flag") before resetting the velocity, because otherwise a bug occurs
    where the platform starts moving on its own towards one side of the screen if the level gets reset while the player is pressing A/D. This happens
    because when the ball reaches the bottom of the screen while the player is pressing A/D, a new instance of the platform/ball is created and when the A/D key is released
    the velocity becomes 0+movement speed or 0-movement speed and it becomes impossible to move the ball in one direction and it moves twice as fast in the other.
    There are other fixes to this problem, such as setting the x_velocity to 0 instead of doing subtraction/addition, but this makes the controls way less smooth and unnatural*/
    else if (e.type == SDL_KEYUP && e.key.repeat == 0 && touched)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_a:
            x_vel += movement_speed;
            break;
        case SDLK_d:
            x_vel -= movement_speed;
            break;
        default:
            break;
        }
    }
}

void Platform::set_size(int width, int height)
{
    //Change the platform size on screen and adjust the ball accordingly
    dst_w = width;
    dst_h = height;
}

void Platform::move()
{
    //Change position based on velocity
    int screen_width;
    SDL_GetRendererOutputSize(get_renderer(), &screen_width, nullptr);

    x_pos += x_vel;
    if (x_pos < 0 || x_pos + dst_w > screen_width)
    {
        x_pos -= x_vel;
    }
}

void Platform::update()
{
    move();
}

void Platform::render()
{
    TextureManager::get_instance()->draw(get_texture_id(), get_renderer(), x_pos, y_pos, src_w, src_h, dst_w, dst_h);
}
