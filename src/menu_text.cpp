#include "menu_text.hpp"
MenuText::MenuText(TTF_Font *font, std::string text, SDL_Color color, SDL_Renderer *renderer, int x_pos, int y_pos, int dst_w, int dst_h)
{
    SDL_Color white = {255, 255, 255};
    SDL_Surface *tmp_surface = TTF_RenderText_Blended(font, text.c_str(), white);
    text_texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
    SDL_SetTextureColorMod(text_texture, color.r, color.g, color.b); //Use color modulation instead of directly setting the color in order to make it easier to change it when it's active
    SDL_FreeSurface(tmp_surface);                                    //Memory isn't used anymore so it should be freed

    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->dst_w = dst_w;
    this->dst_h = dst_h;
}

void MenuText::set_color(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetTextureColorMod(text_texture, r, g, b);
}

MenuText::~MenuText()
{
    SDL_DestroyTexture(text_texture);
}

void MenuText::render(SDL_Renderer *renderer)
{

    SDL_Rect dst_rect = {x_pos, y_pos, dst_w, dst_h};
    SDL_RenderCopy(renderer, text_texture, nullptr, &dst_rect);
}