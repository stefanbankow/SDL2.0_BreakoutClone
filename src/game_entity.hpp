#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

class GameEntity
{
public:
    //Constructor for textures where the entity is the entire texture
    GameEntity(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos);
    //Constructor where the entity's texture is only part of the whole texture object
    GameEntity(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int src_w, int src_h);
    virtual ~GameEntity();

    //SDL-related

    virtual void update();
    virtual void render();

    //Getters/Setters/Util

    virtual void set_size(int dst_w, int dst_h); //Wanted to put this in the constructor, but in my opining it made the constructor overrides too confusing
    int get_desired_width() const { return dst_w; };
    int get_desired_height() const { return dst_h; };
    int get_x_pos() const { return x_pos; };
    int get_y_pos() const { return y_pos; };
    SDL_Renderer *get_renderer() const { return renderer; };
    std::string get_texture_id() const { return texture_ID; };

protected:
    int x_pos;
    int y_pos;
    int src_w;
    int src_h;
    int dst_w;
    int dst_h;

private:
    //Renderer is destroyed at end of program, so there is no need to free it in the destructor
    SDL_Renderer *renderer;
    std::string texture_ID;
};

#endif