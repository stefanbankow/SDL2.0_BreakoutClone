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

bool Ball::check_brick_collision(Brick &entity)
{
    //We need the coordinates ot the center of the ball
    int ball_center_x = x_pos + dst_w / 2;
    int ball_center_y = y_pos + dst_h / 2;
    int other_entity_x = entity.get_x_pos();
    int other_entity_y = entity.get_y_pos();
    int other_entity_w = entity.get_desired_width();
    int other_entity_h = entity.get_desired_height();

    int closest_point_x, closest_point_y;

    if (ball_center_x < other_entity_x) //if ball is to the left of other entity
    {
        closest_point_x = other_entity_x;
    }
    else if (ball_center_x > other_entity_x + other_entity_w) // if it's to the right
    {
        closest_point_x = other_entity_x + other_entity_w;
    }
    else
    {
        closest_point_x = ball_center_x; //if its' inside the other entity
    }

    if (ball_center_y < other_entity_y)
    {
        closest_point_y = other_entity_y;
    }
    else if (ball_center_y > other_entity_y + other_entity_h)
    {
        closest_point_y = other_entity_y + other_entity_h;
    }
    else
    {
        closest_point_y = ball_center_y;
    }

    int distance = distance_squared(ball_center_x, ball_center_y, closest_point_x, closest_point_y);

    if (distance < (dst_w / 2) * (dst_w / 2)) //if distance is smaller than circle radius (closest point is inside circle)
    {
        x_pos -= x_velocity;
        y_pos -= y_velocity;
        Vector2D directions[] = {
            Vector2D(0, -1),
            Vector2D(1, 0),
            Vector2D(0, 1),
            Vector2D(-1, 0),
        };

        //SDL DOESN'T USE THE CARTESIAN COORDINATE SYSTEM, THAT'S WHY THE UP VECTOR HAS -1 VALUE FOR Y
        //!!!!!!!!!!!!!!! CODE FOR DETERMINING THE COLLISION DIRECTION VECTOR STILL DOESN'T WORK PROPERLY AND HAS TO BE FIXED !!!!!!!!!!!!!!!!!!!!!!!!!!!!
        float entity_center_x = entity.get_x_pos() + entity.get_desired_width() / 2;
        float entity_center_y = entity.get_y_pos() + entity.get_desired_height() / 2;
        Vector2D hit_direction(entity_center_x, entity_center_y, closest_point_x, closest_point_y);
        Vector2D normalized_vector = hit_direction.get_normalized_vector();

        int direction_index = 0;
        double total_offset = 1;

        //Here we are checking the normalized vector against the 4 directions and deciding which one is closest to it, so that we can send off the ball in this direction
        for (int i = 0; i < 4; i++)
        {

            double x_offset = abs(normalized_vector.get_x() - directions[i].get_x());
            double y_offset = abs(normalized_vector.get_y() - directions[i].get_y());

            double new_offset = x_offset + y_offset;

            if (new_offset < total_offset)
            {
                total_offset = new_offset;
                direction_index = i;
            }
        }

        std::cout << "Hit Direction: ";
        hit_direction.print();
        std::cout << "\n";
        std::cout << "Direction normalized: ";
        normalized_vector.print();
        std::cout << "\n";

        switch (direction_index)
        {
        case VECTOR_UP:
            std::cout << "UP\n";
            break;
        case VECTOR_RIGHT:
            std::cout << "RIGHT\n";
            break;
        case VECTOR_DOWN:
            std::cout << "DOWN\n";
            break;
        case VECTOR_LEFT:
            std::cout << "LEFT\n";
            break;
        default:
            break;
        }

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