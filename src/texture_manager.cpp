#include "texture_manager.hpp"

TextureManager *TextureManager::ptr_instance = nullptr;

bool TextureManager::load_texture(std::string path, std::string id, SDL_Renderer *renderer)
{
    //Creates texture from surface
    SDL_Texture *new_texture = nullptr;

    SDL_Surface *tmp_surface = IMG_Load(path.c_str());
    if (tmp_surface == nullptr)
    {
        std::cout << "Could not load image at " << path << " IMG_Error: " << IMG_GetError() << "\n";
        return false;
    }

    new_texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
    if (new_texture == nullptr)
    {
        std::cout << "Could not create texture from surface SDL_Error: " << SDL_GetError() << "\n";
        SDL_FreeSurface(tmp_surface);
        return false;
    }

    SDL_FreeSurface(tmp_surface);
    std::cout << "Successfully loaded texture \"" << path << "\"\n";
    textures_map[id] = new_texture;
    return true;
}

SDL_Texture *TextureManager::get_texture(std::string id)
{
    SDL_Texture *texture = textures_map.find(id)->second;
    if (texture == nullptr)
        std::cout << "Texture with ID: \"" << id << "\" could not be found!\n";
    return texture; //This used to be return textures_map[id], but I've since found out that it inserts a new element in the map which is undesired behaviour
}

void TextureManager::draw(SDL_Texture *texture, SDL_Renderer *renderer, int x_pos, int y_pos, int src_w, int src_h, int dst_w, int dst_h)
{
    SDL_Rect src_rect;
    src_rect.x = src_rect.y = 0;
    src_rect.w = src_w;
    src_rect.h = src_h;

    SDL_Rect dst_rect;
    dst_rect.x = x_pos;
    dst_rect.y = y_pos;
    dst_rect.w = dst_w;
    dst_rect.h = dst_h;
    SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
}

void TextureManager::draw_frame(SDL_Texture *texture, SDL_Renderer *renderer, int x_pos, int y_pos, int frame_col, int frame_row, int src_w, int src_h, int dst_w, int dst_h)
{
    SDL_Rect src_rect;
    src_rect.x = 0 + frame_col * src_w;
    src_rect.y = 0 + frame_row * src_h;
    src_rect.w = src_w;
    src_rect.h = src_h;

    SDL_Rect dst_rect;
    dst_rect.x = x_pos;
    dst_rect.y = y_pos;
    dst_rect.w = dst_w;
    dst_rect.h = dst_h;
    SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
}

void TextureManager::remove_texture(std::string id)
{
    SDL_DestroyTexture(textures_map.find(id)->second);
    textures_map.erase(id);
}
void TextureManager::clear_all_textures()
{
    for (auto &map_obj : textures_map)
    {
        SDL_DestroyTexture(map_obj.second);
    }
    textures_map.clear();
}
