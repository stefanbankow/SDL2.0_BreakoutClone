#include "level.hpp"

Level::Level(std::string bricks_file_path, SDL_Renderer *renderer, int screen_width, int screen_height, int platform_movement_speed, int ball_movement_speed)
{
    std::ifstream level_file(bricks_file_path);
    if (level_file.good())
    {
        int brick_type, brick_count = 0;
        bricks = new BrickTileMap("bricks", renderer, 10, 128, 64);
        while (level_file >> brick_type)
        {
            bricks->push_back_brick(renderer, brick_type);
        }

        int platform_dst_w = screen_width / 7;
        int platform_dst_h = screen_height / 25;
        int platform_x_pos = screen_width / 2 - screen_width / 14;
        int platform_y_pos = screen_height - 50;

        platform = new Platform("platform", renderer, platform_x_pos, platform_y_pos, 128, 16, platform_movement_speed);
        platform->set_size(platform_dst_w, platform_dst_h);

        int ball_dst_w = platform_dst_w / 7;
        int ball_x_pos = platform_x_pos + platform_dst_w / 2 - ball_dst_w / 2;
        int ball_y_pos = platform_y_pos - 10 - ball_dst_w;

        ball = new Ball("ball", renderer, ball_x_pos, ball_y_pos, platform_movement_speed, ball_movement_speed);
        ball->set_size(ball_dst_w, ball_dst_w);

        level_file.close();
    }
    else
    {
        std::cout << "File " << bricks_file_path << " could not be opened or it doesn't exist!\n";
    }
}

Level::~Level()
{
    delete ball;
    delete platform;
    delete bricks;
}

void Level::handle_input(SDL_Event &e)
{
    if (ball != nullptr)
        ball->handle_input(e);

    if (platform != nullptr)
        platform->handle_input(e);
}

void Level::render()
{
    if (bricks != nullptr)
        bricks->render();

    if (platform != nullptr)
        platform->render();

    if (ball != nullptr)
        ball->render();
}

void Level::update()
{
    if (platform != nullptr)
    {
        platform->update();

        if (bricks != nullptr && ball != nullptr)
        {
            for (int i = 0; i < bricks->get_brick_count(); i++)
            {
                int closest_point_x = 0;
                int closest_point_y = 0;

                Brick *brick = bricks->get_brick_at_index(i);
                if (ball->check_collision(*brick, closest_point_x, closest_point_y))
                {

                    ball->handle_brick_collision(*brick, closest_point_x, closest_point_y);

                    bricks->destroy_brick_at_index(i);
                    break; //Break loop to prevent collisions with multiple bricks within the same frame
                }
            }
            ball->update(*platform);
        }
    }
}