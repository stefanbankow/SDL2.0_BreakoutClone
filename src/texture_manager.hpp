#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

/***
 * I've read that singletons are a bad practice in OOP programming, but I've also seen people that claim that Resource Managers (Texture, Audio, etc)
 * such as this one are exceptions to this "rule" so I decided to implement this system using a singleton
 */
class TextureManager
{
public:
    bool load_texture(std::string path, std::string id, SDL_Renderer *renderer);
    void draw(std::string id, SDL_Renderer *renderer, int x_pos, int y_pos, int src_w, int src_h, int dst_w = 0, int dst_h = 0);
    void draw_frame(std::string id, SDL_Renderer *renderer, int x_pos, int y_pos, int frame_col, int frame_row, int src_w, int src_h, int dst_w = 0, int dst_h = 0);
    void remove_texture(std::string id);
    void clear_all_textures();

    SDL_Texture *get_texture(std::string id);

    static TextureManager *get_instance()
    {
        if (ptr_instance == nullptr)
        {
            ptr_instance = new TextureManager();
            return ptr_instance;
        }
        return ptr_instance;
    }

private:
    static TextureManager *ptr_instance;
    TextureManager(){};
    std::map<std::string, SDL_Texture *> textures_map;
};

#endif