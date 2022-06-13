#ifndef __FINGER_H__
#define __FINGER_H__


#include <string>

class Finger
{
public:
    int abs_x = -1;
    int abs_y = -1;

    int x_update = -1;
    int y_update = -1;

    bool moved = 0;

    Finger();
    Finger(int slot, int abs_x, int abs_y);

    std::string to_string() const;

    void move_x(int new_x);
    void move_y(int new_y);
};
#endif // __FINGER_H__