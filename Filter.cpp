#include <string>
#include "Filter.h"

Filter::Filter()
{}

Filter::~Filter()
{
    std::cout << "Filter\n";
}
std::vector<float> Filter::movingAvrgFilter(std::vector<float> signal)
{
    for (unsigned long i = 0; i < signal.size(); ++i)
    {
        signal[i] = (signal[i] + signal[i-1] + signal[i-2] + signal[i-3])/4;
    }
    return signal;
}

void Filter::changeResonance(float change)
{
    resonance += change;
}

void Filter::trackPitch(float cv)
{
    cutoff += cv;
}

void Filter::modFilter(float cv)
{
    cutoff += cv * fmAttenuator;
}
