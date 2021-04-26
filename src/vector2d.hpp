#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP
#include <cmath>
#include <iostream>

class Vector2D
{
public:
    //Construct using point coordinates
    Vector2D(float start_x, float start_y, float end_x, float end_y);

    //Construct using x and y components of the vector
    Vector2D(float x_component, float y_component);

    //Get the directional vector (Vector with length of 1)
    Vector2D get_normalized_vector() const;

    //For debugging. Prints the x, y and length
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