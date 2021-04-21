#include "game.hpp"
#include "platform.hpp"
#include "brick_tile_map.hpp"
#include "texture_manager.hpp"

Platform *platform = nullptr;
BrickTileMap *brick_map = nullptr;

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

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

        int brickArray[30] = {
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1, //
            2,
            2,
            2,
            2,
            2,
            2,
            2,
            2,
            2,
            2, //
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
        }; //

        TextureManager::get_instance()
            ->load_texture("assets/platform.png", "platform", renderer);
        TextureManager::get_instance()->load_texture("assets/bricks.png", "bricks", renderer);
        platform = new Platform("platform", renderer, width / 2 - width / 14, height - 50, 128, 16);
        platform->set_size(width / 7, height / 25);
        brick_map = new BrickTileMap("bricks", renderer, brickArray, 3, 10, 128, 64);
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
    {
        is_running = false;
    }
    if (platform != nullptr)
        platform->handleInput(e);
}
void Game::update()
{
    if (platform != nullptr)
        platform->update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    if (platform != nullptr)
        platform->render();

    if (brick_map != nullptr)
        brick_map->render();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    TextureManager::clean_instance();

    delete platform;
    platform = nullptr;

    delete brick_map;
    brick_map = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
    std::cout << "Game exited by user\n";
}