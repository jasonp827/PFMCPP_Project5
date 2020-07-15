#pragma once

#include "Oscillator.h"
#include "CVSequencer.h"
#include "LeakedObjectDetector.h"

struct MelodyPlayer
{
    MelodyPlayer();
    ~MelodyPlayer();
    Oscillator triangleCore;
    CVSequencer voltageBlock;

    void playArp();
    void modWaveShape();

    JUCE_LEAK_DETECTOR(MelodyPlayer)
};
