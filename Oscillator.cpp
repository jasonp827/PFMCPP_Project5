#include <string>
#include "Oscillator.h"

Oscillator::Oscillator() :
negativeTwelvePower(40),
positiveTwelvePower(30),
waveshape(12.4f),
outputType(2)
{}

Oscillator::~Oscillator()
{
    std::cout << "Oscillator\n";
}

bool Oscillator::outputWave(int negativePower, int positivePower)
{
    return (negativePower >= negativeTwelvePower && positivePower >= positiveTwelvePower);
} 

void Oscillator::resetPhase()
{
    phase = 0.0f;
}

void Oscillator::hardSync(std::vector<double> inputSignal)
{ 
    for (unsigned long i = 0; i < inputSignal.size(); ++i)
    {
        if (inputSignal[i] == 0.0)
        {
            phase = 0.0f;
        }
    }
}

void Oscillator::receivePitchCV(std::vector<int> sequence)
{
    for (unsigned long i = 0; i < sequence.size(); i++)
    {
        std::cout << sequence[i] << ", ";
    }
    std::cout << "\n";
}

void Oscillator::memberFunc()
{
    std::cout << "Osc hardSynced! Phase on this sample is reset: phase = " << this->phase << "\n\n";
}
