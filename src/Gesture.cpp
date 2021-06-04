#include "Finger.cpp"
#include "GesturePosition.cpp"
#include "GestureDirection.cpp"
#include "GestureType.cpp"
#include <string>
#include <vector>

#define DEBOUNCE = 0.04
#define THRESHOLD_SQUARED = 30 // threshold to be considered a move, squared sum of x and y
#define DECISION = 75          // sufficient movement to make decision on direction, scaled by the number of slots

using namespace std;

class Gesture
{

public:
    int fingers_count;
    GestureDirection direction;
    GesturePosition position;
    GestureType type;
    string command;

    Gesture()
    {
    }

    Gesture(vector<Finger> fingers, string command, Phase phase)
    {
        this->command = command;
    }

    string to_string() const
    {
        return "command: " + command + "\n";
    }

    void end()
    {
        fingers_count = 0;
        command = "";
    }

    void definePosition(int abs_x, int abs_y)
    {   
        //Todo: rewrite in relative values
        if ((abs_x < 100 || abs_x > 1120) && (abs_y < 100 || abs_y))
        {
            position = GesturePosition::edge;
        }
        else
        {
            position = GesturePosition::middle;
        }
    }

    void defineDirection(int x_prev, int x_new, int y_prev, int y_new) {
        
    }
};