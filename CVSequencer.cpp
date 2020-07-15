#include "CVSequencer.h"
#include <string>

CVSequencer::CVSequencer() :
    cvChannels(8),
    outputLevel(0),
    scale(2)
{}

CVSequencer::~CVSequencer()
{
    std::cout << "CVSequencer\n";
}


void CVSequencer::changeNumSteps(int newNumSteps)
{
    steps = newNumSteps;
}

void CVSequencer::divideClock(int division)
{
    trigPerStep *= division;
}

std::vector<int> CVSequencer::revArp(std::vector<int> noteOrder)
{
    std::vector<int> revArp = {}; 
    for (unsigned long i = noteOrder.size(); i-- != 0;)
    {
        revArp.push_back(noteOrder[i]);
    }
    return revArp;
}

void CVSequencer::memberFunc()
{
    std::vector<int> revArp = this->revArp({1,7,8,1});
    std::cout << "This Reversed arp: ";
    for(unsigned long i = 0; i < revArp.size(); ++i)
    {
        std::cout << revArp[i];
    }
    std::cout << "\n";
}
