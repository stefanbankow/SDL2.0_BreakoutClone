#include "game.hpp"
#include "texture_manager.hpp"
#include "menu_option_enums.hpp"

void Game::init(const char *title, int width, int height, bool fullscreen, int x_pos, int y_pos)
{
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {

        window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
        if (window == nullptr)
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
            is_running = false;
            return;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr)
        {
            std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
            is_running = false;

            return;
        }

        SDL_SetRenderDrawColor(renderer, 160, 210, 250, 0xFF);

        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
        {
            std::cout << "SDL_image could not be initialized! IMG_Error: " << IMG_GetError() << "\n";
            is_running = false;
            return;
        }

        if (TTF_Init() < 0)
        {
            std::cout << "SDL_ttf could not be initialized! TTF_Error: " << TTF_GetError() << "\n";
            is_running = false;
            return;
        }

        std::cout << "Successfully initialized game!\n";

        is_running = true;
        this->window_width = width;
        this->window_height = height;

        TextureManager::get_instance()->load_texture("assets/platform.png", "platform", renderer);
        TextureManager::get_instance()->load_texture("assets/bricks.png", "bricks", renderer);
        TextureManager::get_instance()->load_texture("assets/ball.png", "ball", renderer);
        TextureManager::get_instance()->load_texture("assets/particles.png", "particles", renderer);

        menu_title_font = TTF_OpenFont("assets/fonts/arial.ttf", 200);
        menu_item_font = TTF_OpenFont("assets/fonts/arial.ttf", 40);
        TTF_SetFontStyle(menu_title_font, TTF_STYLE_BOLD);
        TTF_SetFontStyle(menu_item_font, TTF_STYLE_BOLD);
        if (!menu_title_font)
        {
            std::cout << "Arial could not be loaded! TTF_Error: " << TTF_GetError() << "\n";
        }

        load_menus();
    }
    else
    {
        std::cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError << "\n";
        is_running = false;
        return;
    }
}

void Game::handle_input()
{
    SDL_Event e;
    SDL_PollEvent(&e);

    if (e.type == SDL_QUIT) //Exit the game when the X is pressed or on alt+f4
        is_running = false;

    //The code below is kind of confusing and bad, but I've tried my best to streamline it as much as possible and will improve it further if I get some
    //better ideas for handling the menu system

    if (current_game_state == STATE_PLAYING) //Handle the input for playing the game (controlling the platform)
    {
        if (level != nullptr)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE) //Pause the game on escape
            {
                set_state(STATE_PAUSED);
            }
            else
            {
                level->handle_input(e); //Send the input to the platform/ball
            }
        }
    }
    else
    {
        Menu *current_menu = nullptr; //Create a pointer to store the address of the menu we have to use
        switch (current_game_state)   //Set the current_menu to the appropriate menu depending on the game state value
        {
        case STATE_MAIN_MENU:
            current_menu = menus[MENU_MAIN];
            break;
        case STATE_CHOOSING_LEVEL:
            current_menu = menus[MENU_CHOOSE_LEVEL];
            break;
        case STATE_PAUSED:
            current_menu = menus[MENU_PAUSED];
            break;
        case STATE_GAME_OVER:
            current_menu = menus[MENU_GAME_OVER];
            break;
        case STATE_COMPLETED:
            current_menu = menus[MENU_LEVEL_COMPLETED];
            break;
        default:
            break;
        }
        if (current_menu != nullptr && e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_RETURN && e.key.repeat == 0) //Upon pressing enter, check the currently selected option
            {
                handle_menu_selection(current_menu->get_selected_option());
            }

            else
            {
                current_menu->handle_input(e);
            }
        }
    }
}

void Game::update()
{
    if (current_game_state == STATE_PLAYING)
    {
        if (level != nullptr)
        {
            level->update();
            if (level->is_failed())
            {
                set_state(STATE_GAME_OVER);
            }
            else if (level->is_completed())
            {
                set_state(STATE_COMPLETED);
            }
        }
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    switch (current_game_state)
    {
    case STATE_MAIN_MENU: //Render the menu
        if (menus[MENU_MAIN] != nullptr)
            menus[MENU_MAIN]->render();
        break;
    case STATE_CHOOSING_LEVEL:
        if (menus[MENU_CHOOSE_LEVEL] != nullptr)
            menus[MENU_CHOOSE_LEVEL]->render();
        break;
    case STATE_PAUSED: //Render the level with the paused menu on top
        if (level != nullptr)
            level->render();
        if (menus[MENU_PAUSED] != nullptr)
            menus[MENU_PAUSED]->render();
        break;
    case STATE_GAME_OVER: //Render the level with the paused menu on top
        if (level != nullptr)
            level->render();
        if (menus[MENU_GAME_OVER] != nullptr)
            menus[MENU_GAME_OVER]->render();
        break;
    case STATE_COMPLETED: //Render the level with the completed level menu on top
        if (level != nullptr)
            level->render();
        if (menus[MENU_LEVEL_COMPLETED] != nullptr)
            menus[MENU_LEVEL_COMPLETED]->render();
        break;
    case STATE_PLAYING: //Render the level
        if (level != nullptr)
            level->render();
    default:
        break;
    }
    SDL_RenderPresent(renderer);
}

bool Game::load_level(int level_index, int platform_movement_speed, int ball_movement_speed)
{
    if (level != nullptr)
    {
        delete level; //For memory safety make sure the previous (same) level is deleted
        level = nullptr;
    }
    std::string level_file_path;
    switch (level_index)
    {
    case 1:
        level_file_path = "assets/levels/level_1.txt";
        break;
    case 2:
        level_file_path = "assets/levels/level_2.txt";
        break;
    case 3:
        level_file_path = "assets/levels/level_3.txt";
        break;
    default:
        break;
    }

    level = new Level(level_file_path, renderer, window_width, window_height, platform_movement_speed, ball_movement_speed);

    if (level != nullptr) //if memory allocation was successful
        return level->is_successfully_loaded();

    return false;
}

void Game::load_menus()
{
    SDL_Color item_color = {0, 0, 0};
    SDL_Color active_item_color = {255, 255, 255};

    menus[MENU_MAIN] = new Menu(menu_title_font, menu_item_font, renderer, item_color, item_color, active_item_color, 600, 300);
    if (menus[MENU_MAIN] != nullptr) //Create the main men
    {
        menus[MENU_MAIN]->add_title("BREAKOUT", window_width / 2 - menus[MENU_MAIN]->get_title_width() / 2, 50);
        menus[MENU_MAIN]->add_item("START", 350);
        menus[MENU_MAIN]->add_item("SETTINGS", 450);
        menus[MENU_MAIN]->add_item("EXIT", 550);
    }

    menus[MENU_CHOOSE_LEVEL] = new Menu(menu_title_font, menu_item_font, renderer, item_color, item_color, active_item_color, 550, 200);
    if (menus[MENU_CHOOSE_LEVEL] != nullptr) //Create the main men
    {
        menus[MENU_CHOOSE_LEVEL]->add_title("CHOOSE A LEVEL", window_width / 2 - menus[MENU_CHOOSE_LEVEL]->get_title_width() / 2, 50);
        menus[MENU_CHOOSE_LEVEL]->add_item("LEVEL 1", 250);
        menus[MENU_CHOOSE_LEVEL]->add_item("LEVEL 2", 350);
        menus[MENU_CHOOSE_LEVEL]->add_item("LEVEL 3", 450);
        menus[MENU_CHOOSE_LEVEL]->add_item("BACK", 550);
    }

    menus[MENU_PAUSED] = new Menu(menu_title_font, menu_item_font, renderer, item_color, item_color, active_item_color, 300, 100);
    if (menus[MENU_PAUSED] != nullptr)
    {
        menus[MENU_PAUSED]->add_title("PAUSED", window_width / 2 - menus[MENU_PAUSED]->get_title_width() / 2, 200);
        menus[MENU_PAUSED]->add_item("CONTINUE", 350);
        menus[MENU_PAUSED]->add_item("BACK TO MENU", 450);
    }

    menus[MENU_LEVEL_COMPLETED] = new Menu(menu_title_font, menu_item_font, renderer, item_color, item_color, active_item_color, 300, 100);
    if (menus[MENU_LEVEL_COMPLETED] != nullptr)
    {
        menus[MENU_LEVEL_COMPLETED]->add_title("LEVEL COMPLETE", window_width / 2 - menus[MENU_LEVEL_COMPLETED]->get_title_width() / 2, 200);
        menus[MENU_LEVEL_COMPLETED]->add_item("PLAY AGAIN", 350);
        menus[MENU_LEVEL_COMPLETED]->add_item("BACK TO MENU", 450);
    }
    menus[MENU_GAME_OVER] = new Menu(menu_title_font, menu_item_font, renderer, item_color, item_color, active_item_color, 300, 100);
    if (menus[MENU_GAME_OVER] != nullptr)
    {
        menus[MENU_GAME_OVER]->add_title("GAME OVER", window_width / 2 - menus[MENU_GAME_OVER]->get_title_width() / 2, 200);
        menus[MENU_GAME_OVER]->add_item("RETRY", 350);
        menus[MENU_GAME_OVER]->add_item("BACK TO MENU", 450);
    }
}

void Game::handle_menu_selection(int selection)
{

    switch (current_game_state) //Do different things depending on which menu we're on
    {
    case STATE_MAIN_MENU: //Options for the main menu
        switch (selection)
        {
        case MENUOPT_START_PLAYING: //Load the level and start playing
            set_state(STATE_CHOOSING_LEVEL);
            break;
        case MENUOPT_GO_TO_SETTINGS: //Haven't implemented any settings so this button does nothing
            break;
        case MENUOPT_EXIT: //Stops the game
            is_running = false;
            break;
        }
        break;
    case STATE_CHOOSING_LEVEL:
        switch (selection)
        {
        case LEVELOPT_1:
            current_level = 1;
            load_level(current_level, 8, 5);
            set_state(STATE_PLAYING);
            break;
        case LEVELOPT_2:
            current_level = 2;
            load_level(current_level, 8, 5);
            set_state(STATE_PLAYING);

            break;
        case LEVELOPT_3:
            current_level = 3;
            load_level(current_level, 8, 5);
            set_state(STATE_PLAYING);

            break;
        case LEVELOPT_EXIT:
            set_state(STATE_MAIN_MENU);

            break;
        default:
            break;
        }
        break;

    case STATE_PAUSED: //Options for the pause menu
        switch (selection)
        {
        case PAUSEOPT_CONTINUE_OR_RETRY:
            set_state(STATE_PLAYING);
            break;
        case PAUSEOPT_EXIT_TO_MAIN_MENU:
            if (level != nullptr)
                delete level; //We don't need the level
            level = nullptr;
            set_state(STATE_MAIN_MENU);
            break;
        }
        break;

    case STATE_COMPLETED: //Options for the game over and completed menus
    case STATE_GAME_OVER:
        switch (selection)
        {
        case PAUSEOPT_CONTINUE_OR_RETRY:
            load_level(current_level, 6, 3); //Reset the level
            set_state(STATE_PLAYING);
            break;
        case PAUSEOPT_EXIT_TO_MAIN_MENU:
            if (level != nullptr)
                delete level;
            level = nullptr;
            set_state(STATE_MAIN_MENU);
            break;
        }
        break;

    default:
        break;
    }
}

void Game::clean()
{
    TextureManager::clean_instance();

    if (level != nullptr)
    {
        delete level;
        level = nullptr;
    }

    for (int i = 0; i < 5; i++)
    {
        if (menus[i] != nullptr)
        {
            delete menus[i];
            menus[i] = nullptr;
        }
    }

    TTF_CloseFont(menu_title_font);
    menu_title_font = nullptr;

    TTF_CloseFont(menu_item_font);
    menu_item_font = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    std::cout << "Game exited by user\n";
}