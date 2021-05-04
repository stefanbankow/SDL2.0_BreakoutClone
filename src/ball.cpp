#include "ball.hpp"

enum Directions
{
    VECTOR_UP,
    VECTOR_DOWN,
    VECTOR_RIGHT,
    VECTOR_LEFT
};

Ball::Ball(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int platform_movement_speed, int y_movement_speed) : GameEntity(texture_id, renderer, x_pos, y_pos)
{
    this->platform_movement_speed = platform_movement_speed;
    this->y_movement_speed = y_movement_speed > 0 ? y_movement_speed : 1;
}

void Ball::update(Platform &entity)
{
    int closest_point_x, closest_point_y;
    if (check_collision(entity, closest_point_x, closest_point_y))
    {
        handle_platform_collision(entity, closest_point_x, closest_point_y);
    }
    move(entity.get_desired_width());
}

void Ball::handle_input(SDL_Event &e)
{
    if (!released)
    {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_a:
                touched_a = true;
                x_velocity -= platform_movement_speed;
                break;
            case SDLK_d:
                touched_d = true;
                x_velocity += platform_movement_speed;
                break;
            case SDLK_SPACE:
                release();
                break;
            default:
                break;
            }
        }
        else if (e.type == SDL_KEYUP && e.key.repeat == 0)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_a:
                if (touched_a)
                    x_velocity += platform_movement_speed;
                break;
            case SDLK_d:
                if (touched_d)
                    x_velocity -= platform_movement_speed;
                break;
            default:
                break;
            }
        }
    }
}

void Ball::move(int platform_width)
{
    int screen_width, screen_height;
    SDL_GetRendererOutputSize(get_renderer(), &screen_width, &screen_height);
    if (released)
    {
        x_pos += x_velocity;
        y_pos += y_velocity;
        if (x_pos < 0 || x_pos + dst_w > screen_width)
        {
            x_pos -= x_velocity;
            x_velocity = -x_velocity;
        }

        if (y_pos < 0) //Check only for top of screen
        {
            y_pos -= y_velocity;
            y_velocity = -y_velocity;
        }
        else if (y_pos > screen_height)
        {
            out_of_bounds = true;
        }
    }
    else
    {
        x_pos += x_velocity;

        if (x_pos < platform_width / 2 - dst_w / 2 || x_pos + dst_w > screen_width - platform_width / 2 + dst_w / 2)
        {
            x_pos -= x_velocity;
        }
    }
}

int distance_squared(int x1, int y1, int x2, int y2)
{
    int deltaX = x2 - x1; //Difference between x coordinates of the two point
    int deltaY = y2 - y1;

    return deltaX * deltaX + deltaY * deltaY;
}

bool Ball::check_collision(GameEntity &entity, int &closest_point_x_var, int &closest_point_y_var)
{
    //We use references to some external variables for the closest point coordinates, so that we can use those external variables as parameters in the collision handling functions
    //without having to re-do those checks

    //We need the coordinates to the center of the ball
    int ball_center_x = x_pos + dst_w / 2;
    int ball_center_y = y_pos + dst_h / 2;
    int other_entity_x = entity.get_x_pos();
    int other_entity_y = entity.get_y_pos();
    int other_entity_w = entity.get_desired_width();
    int other_entity_h = entity.get_desired_height();

    int closest_point_x, closest_point_y;

    if (ball_center_x < other_entity_x) //if the ball's center is to the left of other entity
    {
        closest_point_x = other_entity_x;
    }
    else if (ball_center_x > other_entity_x + other_entity_w) // if it's to the right
    {
        closest_point_x = other_entity_x + other_entity_w;
    }
    else
    {
        closest_point_x = ball_center_x; //if it's inside the other entity
    }

    if (ball_center_y < other_entity_y) //Above
    {
        closest_point_y = other_entity_y;
    }
    else if (ball_center_y > other_entity_y + other_entity_h) //Below
    {
        closest_point_y = other_entity_y + other_entity_h;
    }
    else //Inside
    {
        closest_point_y = ball_center_y;
    }

    //Distance between the closest point of the brick and the ball's center
    int distance = distance_squared(ball_center_x, ball_center_y, closest_point_x, closest_point_y);

    if (distance < (dst_w / 2) * (dst_w / 2)) //if the distance is smaller than the ball's radius (closest point is inside ball)
    {
        closest_point_x_var = closest_point_x;
        closest_point_y_var = closest_point_y;
        return true;
    }

    return false;
}

void Ball::handle_brick_collision(Brick &entity, int closest_point_x, int closest_point_y)
{
    //Move the ball back 1 frame
    x_pos -= x_velocity;
    y_pos -= y_velocity;

    Vector2D directions[] = {
        Vector2D(0, -1),
        Vector2D(0, 1),
        Vector2D(1, 0),
        Vector2D(-1, 0),
    };

    //SDL DOESN'T USE THE CARTESIAN COORDINATE SYSTEM, THAT'S WHY THE UP VECTOR HAS -1 VALUE FOR Y

    double entity_center_x = entity.get_x_pos() + entity.get_desired_width() / 2;
    double entity_center_y = entity.get_y_pos() + entity.get_desired_height() / 2;

    Vector2D hit_direction(entity_center_x, entity_center_y, closest_point_x, closest_point_y);

    //We have to account for the fact that the brick's width may be different than it's height and adjust the vector accordingly in order the get the appropriate direction,
    //since at the end we are effectively comparing the normalized vector against a square, not a rectangle
    double side_disparity_ratio = entity.get_desired_height() * 1.0 / entity.get_desired_width();
    hit_direction.set_x(hit_direction.get_x() * side_disparity_ratio);

    Vector2D normalized_vector = hit_direction.get_normalized_vector();

    int direction_index = 0;
    double max = 0;

    //Here we are checking the normalized vector against the 4 directions and deciding which one is closest to it, so that we can send off the ball in this direction
    for (int i = 0; i < 4; i++)
    {

        float dot_product = Vector2D::dot_product(normalized_vector, directions[i]);

        if (dot_product > max)
        {
            //The higher the dot product of between the vector and the direction, the smaller the angle between them. (Dot product of angle means angle of 0 degress)
            //So we just pick the direction which is closest to the vector between the center of the entity and the point of impact
            max = dot_product;
            direction_index = i;
        }
    }

    switch (direction_index)
    {
    case VECTOR_UP:
    case VECTOR_DOWN:
        y_velocity = -y_velocity;
        break;
    case VECTOR_RIGHT:
    case VECTOR_LEFT:
        x_velocity = -x_velocity;
        break;
    default:
        break;
    }
}

void Ball::handle_platform_collision(Platform &entity, int closest_point_x, int closest_point_y)
{
    if (y_velocity > 0) //Only change the velocity if the ball is going down to prevent the ball from getting stuck inside the platform at high platform speeds
    {
        int platform_x_pos = entity.get_x_pos();
        int platform_width = entity.get_desired_width();
        int platform_velocity = entity.get_x_velocity();

        //If the ball was going left and falls on the right side of the platform, while the platform is going right it will get sent back in the opposite direction
        //Same goes for the left side
        bool hard_impact_right = closest_point_x >= platform_x_pos + (platform_width - platform_width / 3) && platform_velocity > 0 && x_velocity < 0;
        bool hard_impact_left = closest_point_x <= platform_x_pos + platform_width / 3 && platform_velocity < 0 && x_velocity > 0;
        if (hard_impact_left || hard_impact_right)
        {
            x_velocity = -x_velocity;
        }

        y_velocity = -y_velocity;
    }
}

void Ball::release()
{

    std::random_device generator;
    std::uniform_int_distribution<int> distribution(-2 * y_movement_speed, 2 * y_movement_speed);
    released = true;
    x_velocity = distribution(generator);

    y_velocity = -y_movement_speed; // Use the negative value of the movement speed, because otherwise the balls goes downward
}

void Ball::set_location(int x, int y)
{
    x_pos = x;
    y_pos = y;
}

void Ball::set_size(int width, int height)
{
    dst_w = width;
    dst_h = height;
}