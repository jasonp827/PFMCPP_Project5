#pragma once

#include <vector>
#include "LeakedObjectDetector.h"

struct Filter
{
    Filter();
    ~Filter();
    int filterType{1};
    float fmAttenuator{0.0f};
    float cutoff{1.0f};
    float resonance{0.0f};
    float gain{10.0f};

    std::vector<float> movingAvrgFilter(std::vector<float> signal);
    void changeResonance(float change);
    void trackPitch(float cv);
    void modFilter(float cv);

    JUCE_LEAK_DETECTOR(Filter)
};
