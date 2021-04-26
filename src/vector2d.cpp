#include "vector2d.hpp"

Vector2D::Vector2D(float x_component, float y_component)
{
    x = x_component;
    y = y_component;
    length = sqrt(x * x + y * y);
}

Vector2D::Vector2D(float start_x, float start_y, float end_x, float end_y)
{
    x = end_x - start_x;
    y = end_y - start_y;

    length = sqrt(x * x + y * y);
}

Vector2D Vector2D::get_normalized_vector() const
{

    float x_comp, y_comp;

    x_comp = x / length;
    y_comp = y / length;

    return Vector2D(x_comp, y_comp);
}

void Vector2D::print() const
{
    std::cout << "Vector X: " << x << "\tVector Y: " << y << "\t Vector Length: " << length << "\n";
}