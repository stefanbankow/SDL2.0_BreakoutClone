#include "ball.hpp"

enum Directions
{
    VECTOR_UP,
    VECTOR_RIGHT,
    VECTOR_DOWN,
    VECTOR_LEFT
};

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

        if (y_pos < 0 || y_pos + dst_h > screen_height) //Check only for top of screen
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

bool Ball::check_brick_collision(Brick &entity)
{
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
        //I wanted to remove the code for handling the ball velocity upon impact out of this function entirely, as to satisfy the Single Responsibility Principle,
        //but I couldn't find a simple enough method to do it without rewriting the code for finding the closest point coordinates once again, so I decided to leave it here
        handle_brick_collision(entity, closest_point_x, closest_point_y);
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
        Vector2D(1, 0),
        Vector2D(0, 1),
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
        std::cout << "Dot product of " << i << ": " << dot_product << "\n";
        if (dot_product > max)
        {
            //The higher the dot product of between the vector and the direction, the smaller the angle between them. (Dot product of angle means angle of 0 degress)
            //So we just pick the direction which is closest to the vector between the center of the entity and the point of impact
            max = dot_product;
            direction_index = i;
        }
    }

    std::cout << "Direction normalized: ";
    normalized_vector.print();
    std::cout << "\n";

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