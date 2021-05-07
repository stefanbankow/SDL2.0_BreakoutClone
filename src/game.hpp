#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "level.hpp"
#include "menu.hpp"

enum GameState
{
    STATE_MAIN_MENU,      //Player is in the main menu
    STATE_CHOOSING_LEVEL, //Player is at the level select screen
    STATE_PLAYING,        //Player is playing
    STATE_PAUSED,         //Player paused the game
    STATE_COMPLETED,      //Player completed the level
    STATE_GAME_OVER,      //Player failed the level
};

enum MenuIndexes
{
    MENU_MAIN,
    MENU_CHOOSE_LEVEL,
    MENU_PAUSED,
    MENU_LEVEL_COMPLETED,
    MENU_GAME_OVER,
};

class Game
{
public:
    //Creates the SDL_Window
    void init(const char *title, int width, int height, bool fullscreen = false, int x_pos = SDL_WINDOWPOS_UNDEFINED, int y_pos = SDL_WINDOWPOS_UNDEFINED);
    //Handles user input
    void handle_input();
    //Update the properties of the objects inside the game
    void update();
    //Update what the player sees
    void render();
    //Clean the assets used by the game
    void clean();

    bool load_level(int level_index, int platform_movement_speed, int ball_movement_speed);
    void load_menus();
    void handle_menu_selection(int selection);

    //Getters/Setters/Util
    bool is_game_running() const { return is_running; };
    void set_state(GameState new_state) { current_game_state = new_state; };

private:
    bool is_running;
    int window_width;
    int window_height;

    //Menus
    Menu *menus[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    GameState current_game_state = STATE_MAIN_MENU;

    //Level
    Level *level = nullptr;
    int current_level = 1;

    //Fonts
    TTF_Font *menu_title_font = nullptr;
    TTF_Font *menu_item_font = nullptr;

    //SDL related
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};

#endif
