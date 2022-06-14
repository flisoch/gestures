#include "Finger.h"

Finger::Finger() {}

Finger::Finger(int slot, int abs_x, int abs_y)
{
    this->abs_x = abs_x;
    this->abs_y = abs_y;
}

std::string Finger::to_string() const
{
    return "\nabs_x:" + std::to_string(abs_x) + "\n" +
               "abs_y:" + std::to_string(abs_y) + "\n";
}

void Finger::move_x(int new_x)
{
    if (abs_x == -1) {
        abs_x = new_x;
    }
    else {
        x_update += new_x - abs_x;
        abs_x = new_x;
    }
}

void Finger::move_y(int new_y)
{
    if (abs_y == -1) {
        abs_y = new_y;
    }
    y_update += new_y - abs_y;
    abs_y = new_y;
}
