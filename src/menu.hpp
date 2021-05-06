#ifndef MENU_HPP
#define MENU_HPP
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include "menu_text.hpp"

class Menu
{
public:
    Menu(TTF_Font *title_font, TTF_Font *item_font, SDL_Renderer *renderer, SDL_Color title_color, SDL_Color item_color, SDL_Color active_item_color,
         int title_dst_w, int title_dst_h);
    ~Menu();

    //Adds a title (Big text representing the menu)
    void add_title(std::string title_text, int x_pos = -1, int y_pos = -1);

    //Adds a selectable menu option
    void add_item(std::string item_text, int y_pos); //Since I want every item to be in the center of the screen horizontally, I don't need the x coordinate.

    //Renders all the elements of the menu
    void render();

    void handle_input(SDL_Event &e);

    //Getters/Setters/Util

    int get_title_width() const { return title_dst_w; };
    int get_title_height() const { return title_dst_h; };
    int get_selected_option() const { return active_index; };

private:
    //Pointers
    TTF_Font *title_font = nullptr;   //Will be cleared at the end of the program
    TTF_Font *item_font = nullptr;    //Will be cleared at the end of the program
    SDL_Renderer *renderer = nullptr; //Will be cleared at the end of the program

    //Menu title

    MenuText *title = nullptr;
    int title_dst_w;
    int title_dst_h;

    //Active item related
    std::vector<MenuText *> items;
    int item_count = 0;
    int active_index = 0;

    //Colors

    SDL_Color title_color;
    SDL_Color item_color;
    SDL_Color active_item_color;
};



#endif