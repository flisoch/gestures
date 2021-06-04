#include <string>

using namespace std;
class Finger
{
public:
    int abs_x = -1;
    int abs_y = -1;

    int x_update;
    int y_update;

    int x_updates;
    int y_updates;

    Finger() {}

    Finger(int slot, int abs_x, int abs_y)
    {
        this->abs_x = abs_x;
        this->abs_y = abs_y;
    }

    string to_string() const
    {
        return "\nabs_x:" + std::to_string(abs_x) + "\n" +
               "abs_y:" + std::to_string(abs_y) + "\n";
    }

    void move_x(int new_x)
    {
        if (abs_x == -1)
        {
            abs_x = new_x;
        }
        else
        {
            x_update = new_x - abs_x;
            abs_x = new_x;
            x_updates += 1;
        }
    }
    void move_y(int new_y)
    {
        if (abs_y == -1)
        {
            abs_y = new_y;
        }
        y_update = new_y - abs_y;
        abs_y = new_y;
        y_updates += 1;
    }
};