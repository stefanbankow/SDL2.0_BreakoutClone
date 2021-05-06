#ifndef MENU_TEXTURE_HPP
#define MENU_TEXTURE_HPP
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

class MenuText
{
public:
    MenuText(TTF_Font *font, std::string text, SDL_Color color, SDL_Renderer *renderer, int x_pos, int y_pos, int dst_w, int dst_h);
    ~MenuText();

    //Set's the text's color using color modulation
    void set_color(Uint8 r, Uint8 g, Uint8 b);

    int get_x_pos() const { return x_pos; };
    void set_x_pos(int x) { x_pos = x; }
    int get_y_pos() const { return y_pos; }
    void set_y_pos(int y) { y_pos = y; }

    int get_width() const { return dst_w; };
    int get_height() const { return dst_h; };

    void render(SDL_Renderer *renderer);

private:
    SDL_Texture *text_texture = nullptr;
    int x_pos;
    int y_pos;
    int dst_w;
    int dst_h;
};

#endif