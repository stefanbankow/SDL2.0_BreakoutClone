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

    //Wanted to put this in the constructor, but in my opining it made the constructor overrides too confusing
    void set_size(int dst_w, int dst_h);
    virtual ~GameEntity();
    virtual void update();
    virtual void render();
    int get_desired_width() { return dst_w; };
    int get_desired_height() { return dst_h; };
    SDL_Renderer *get_renderer() { return renderer; };
    std::string get_texture_id() { return texture_ID; };

protected:
    int x_pos;
    int y_pos;
    int src_w;
    int src_h;
    int dst_w;
    int dst_h;

private:
    //Renderer is destroyed at end of program, so no need to free it in destructor
    SDL_Renderer *renderer;
    std::string texture_ID;
};

#endif