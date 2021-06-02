#include <string>

using namespace std;
class Finger
{
public:
    int abs_x;
    int abs_y;

    Finger()
    {
        this->abs_x = 0;
        this->abs_y = 0;
    }

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
};