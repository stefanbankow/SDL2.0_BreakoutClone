#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP
#include <cmath>
#include <iostream>

class Vector2D
{
public:
    Vector2D(float start_x, float start_y, float end_x, float end_y);
    Vector2D(float x_component, float y_component);

    Vector2D get_normalized_vector() const;

    void print() const;

    float get_x() const { return x; }
    float get_y() const { return y; }
    float get_length() const { return length; }

private:
    float length;
    float x;
    float y;
};
#endif