#pragma once

#include <vector>
#include "LeakedObjectDetector.h"

struct CVSequencer
{
    CVSequencer();
    ~CVSequencer();
    int cvChannels;
    float outputLevel;
    int steps = 16;
    int trigPerStep = 1;
    int scale;

    void changeNumSteps(int newNumSteps);
    void divideClock(int division);
    std::vector<int> revArp(std::vector<int> noteOrder);
    void memberFunc();

    JUCE_LEAK_DETECTOR(CVSequencer)
};
