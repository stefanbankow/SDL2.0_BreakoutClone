#include "game.hpp"
#include "platform.hpp"
#include "game.hpp"
#include "brick_tile_map.hpp"
#include "texture_manager.hpp"

Platform *platform = nullptr;
Ball *ball = nullptr;
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

        int brickArray[30] = {
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            0,
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
            4,
            4,
            4,
            4,
            4,
            4,
            4,
            4,
            4,
            4,
        }; //

        TextureManager::get_instance()->load_texture("assets/platform.png", "platform", renderer);
        TextureManager::get_instance()->load_texture("assets/bricks.png", "bricks", renderer);
        TextureManager::get_instance()->load_texture("assets/ball.png", "ball", renderer);

        int platform_dst_w = width / 7;
        int platform_dst_h = height / 25;
        int platform_x_pos = width / 2 - width / 14;
        int platform_y_pos = height - 50;

        platform = new Platform("platform", renderer, platform_x_pos, platform_y_pos, 128, 16, 2);
        platform->set_size(platform_dst_w, platform_dst_h);

        int ball_dst_w = platform_dst_w / 7;
        int ball_x_pos = platform_x_pos + platform_dst_w / 2 - ball_dst_w / 2;
        int ball_y_pos = platform_y_pos - 10 - ball_dst_w;

        ball = new Ball("ball", renderer, ball_x_pos, ball_y_pos, platform->get_movement_speed(), 5);
        ball->set_size(ball_dst_w, ball_dst_w);

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
        is_running = false;

    if (platform != nullptr)
        platform->handle_input(e);

    if (ball != nullptr)
        ball->handle_input(e);
}
void Game::update()
{
    if (platform != nullptr)
    {
        platform->update();

        if (brick_map != nullptr && ball != nullptr)
        {
            for (int i = 0; i < brick_map->get_brick_count(); i++)
            {
                int closest_point_x = 0;
                int closest_point_y = 0;

                Brick *brick = brick_map->get_brick_at_index(i);
                if (ball->check_brick_collision(*brick, closest_point_x, closest_point_y))
                {

                    ball->handle_brick_collision(*brick, closest_point_x, closest_point_y);

                    brick_map->destroy_brick_at_index(i);
                    break;
                }
            }
            ball->update(platform->get_desired_width());
        }
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    //The entities that should be rendered on top have to be last
    if (brick_map != nullptr)
        brick_map->render();

    if (platform != nullptr)
        platform->render();

    if (ball != nullptr)
        ball->render();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    TextureManager::clean_instance();

    delete platform;
    platform = nullptr;

    delete ball;
    ball = nullptr;

    delete brick_map;
    brick_map = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
    std::cout << "Game exited by user\n";
}