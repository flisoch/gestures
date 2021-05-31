#include "Finger.cpp"
#include "Phase.cpp"
#include <string>
#include <vector>

using namespace std;
class Gesture
{
public:
    vector<Finger> fingers;
    string command;
    Phase phase;
    Gesture(vector<Finger> fingers, string command, Phase phase)
    {
        this->fingers = fingers;
        this->command = command;
        this->phase = phase;
    }

    string to_string() const
    {
        string fingers_string = "";
        for (auto finger : fingers)
        {
            fingers_string += finger.to_string();
        }
        string phase_string =
            phase == Phase::start ? "start" : phase == Phase::update ? "update"
                                                                     : "end";
        return "command: " + command + "\nFingers: " + fingers_string + "\nPhase: " + phase_string;
    }
};