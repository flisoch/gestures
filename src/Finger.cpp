#include <string>

using namespace std;
class Finger
{
public:
    int slot; // 0-9
    int abs_x;
    int abs_y;

    Finger()
    {
        this->slot = -1;
        this->abs_x = 0;
        this->abs_y = 0;
    }

    Finger(int slot, int abs_x, int abs_y)
    {
        this->slot = slot;
        this->abs_x = abs_x;
        this->abs_y = abs_y;
    }

    string to_string() const
    {
        return "Slot:" + std::to_string(slot) + "\n" +
               "abs_x:" + std::to_string(abs_x) + "\n" +
               "abs_y:" + std::to_string(abs_y) + "\n";
    }
};