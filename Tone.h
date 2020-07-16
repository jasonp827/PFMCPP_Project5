#pragma once

#include "Oscillator.h"
#include "Filter.h"
#include "LeakedObjectDetector.h"

struct Tone
{
    Tone();
    ~Tone();
    Oscillator triangleCore;
    Filter sem20;

    void changeTone();

    JUCE_LEAK_DETECTOR(Tone)
};
