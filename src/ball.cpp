#include "ball.hpp"

Ball::Ball(std::string texture_id, SDL_Renderer *renderer, int x_pos, int y_pos, int y_movement_speed) : GameEntity(texture_id, renderer, x_pos, y_pos)
{

    this->y_movement_speed = y_movement_speed > 0 ? y_movement_speed : 1;
}

void Ball::update()
{
    move();
}

void Ball::move()
{
    if (released)
    {
        int screen_width, screen_height;
        SDL_GetRendererOutputSize(get_renderer(), &screen_width, &screen_height);
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
    }
}

int distance_squared(int x1, int y1, int x2, int y2)
{
    int deltaX = x2 - x1; //Difference between x coordinates of the two point
    int deltaY = y2 - y1;

    return deltaX * deltaX + deltaY * deltaY;
}

bool Ball::check_collision(GameEntity &entity) const
{

    int other_entity_x = entity.get_x_pos();
    int other_entity_y = entity.get_y_pos();
    int other_entity_w = entity.get_desired_width();
    int other_entity_h = entity.get_desired_height();

    int closest_point_x, closest_point_y;

    if (this->x_pos < other_entity_x) //if ball is to the left of other entity
    {
        closest_point_x = other_entity_x;
    }
    else if (this->x_pos > other_entity_x + other_entity_w) // if it's to the right
    {
        closest_point_x = other_entity_x + other_entity_w;
    }
    else
    {
        closest_point_x = this->x_pos; //if its' inside the other entity
    }

    if (this->y_pos < other_entity_y)
    {
        closest_point_y = other_entity_y;
    }
    else if (this->y_pos > other_entity_y + other_entity_h)
    {
        closest_point_y = other_entity_y + other_entity_h;
    }
    else
    {
        closest_point_y = this->y_pos;
    }

    int distance = distance_squared(this->x_pos, this->y_pos, closest_point_x, closest_point_y);

    if (distance < (this->dst_w / 2) * (this->dst_w / 2)) //if distance is smaller than circle radius (closest point is inside circle)
    {
        std::cout << "Collided with " << &entity << "\n";
        return true;
    }

    return false;
}

void Ball::move_with_platform(int platform_velocity)
{
    if (!released)
    {
        x_pos += platform_velocity;
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