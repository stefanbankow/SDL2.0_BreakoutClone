#include "game.hpp"
#include "texture_manager.hpp"

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

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr)
        {
            std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
            is_running = false;
            return;
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
        {
            std::cout << "SDL_image could not be initialized! SDL_Error: " << IMG_GetError << "\n";
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

        load_level("assets/levels/level_2.txt", 6, 3);
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

    if (e.type == SDL_QUIT)
        is_running = false;

    if (level != nullptr)
        level->handle_input(e);
}
void Game::update()
{
    if (level != nullptr)
    {
        level->update();
        if (level->is_failed())
        {
            load_level("assets/levels/level_2.txt", 6, 3);
        }
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    //The entities that should be rendered on top have to be last
    if (level != nullptr)
        level->render();

    SDL_RenderPresent(renderer);
}

bool Game::load_level(std::string level_file_path, int platform_movement_speed, int ball_movement_speed)
{
    if (level != nullptr)
    {
        delete level; //For memory safety make sure the previous level is deleted
        level = nullptr;
    }

    level = new Level(level_file_path, renderer, window_width, window_height, platform_movement_speed, ball_movement_speed);

    if (level != nullptr) //if memory allocation was successful
        return level->is_successfully_loaded();

    return false;
}

void Game::clean()
{
    TextureManager::clean_instance();

    delete level;
    level = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
    std::cout << "Game exited by user\n";
}