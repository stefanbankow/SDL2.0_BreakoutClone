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

float Vector2D::dot_product(Vector2D vector1, Vector2D vector2)
{

    return (vector1.get_x() * vector2.get_x()) + (vector1.get_y() * vector2.get_y());
}

void Vector2D::print() const
{
    std::cout << "Vector X: " << x << "\tVector Y: " << y << "\t Vector Length: " << length << "\n";
}

void Vector2D::set_x(float value)
{
    x = value;
    length = sqrt(x * x + y * y);
}

void Vector2D::set_y(float value)
{
    y = value;
    length = sqrt(x * x + y * y);
}