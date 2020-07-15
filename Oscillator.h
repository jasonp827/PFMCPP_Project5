#pragma once

#include <vector>
#include "LeakedObjectDetector.h"

struct Oscillator
{
    Oscillator();
    ~Oscillator();
    int negativeTwelvePower;
    int positiveTwelvePower;
    float waveshape;
    int outputType;
    float fmAttenuator = 0.0f;
    float phase = 0.0f;

    bool outputWave(int negativePower, int positivePower);
    void hardSync(std::vector<double> inputSignal);
    void receivePitchCV(std::vector<int> sequence);
    void resetPhase();
    void memberFunc();

    JUCE_LEAK_DETECTOR(Oscillator)
};
