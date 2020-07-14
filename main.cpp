/*
 Project 5: Part 4 / 4
 video: Chapter 3 Part 7

 Create a branch named Part4
 
 Don't #include what you don't use
 
 1) Your task is to refactor your Chapter 3 Part 4 task into separate source and header files.
         Add files via the pane on the left.
 
 2) Put all of your declarations for each class in .h files
         One header file per class ( i.e. Raider.h for a class named "Raider" )
 
 3) Put all of your implementations in .cpp files.
         one cpp file per class ( i.e. Raider.cpp for a class named "Raider" )
 
 4) Put all of your Wrapper classes in a single Wrappers.h file
         if you implemented your wrapper class functions in-class, you'll need to move them to Wrappers.cpp
 
 5) NO IN-CLASS IMPLEMENTATION ALLOWED.
         the only exception is the existing Atomic.h and LeakedObjectDetector.h
 
 6) for every .cpp file you have to make, insert it into the .replit file after 'main.cpp'.  Don't forget the spaces between file names.
 If you need help with this step, send me a DM.
 
 7) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Remember, your Chapter 3 Part 4 task worked when it was all in one file. so you shouldn't need to edit any of it.  
         just split it up into source files and provide the appropriate #include directives.
 */




#include <vector>
#include <string>
#include "LeakedObjectDetector.h"
#include <iostream>
/*
 copied UDT 1:
 */
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

struct OscillatorWrapper
{
    OscillatorWrapper(Oscillator* ptr): oscillatorPtr(ptr){}
    ~OscillatorWrapper()
    {
        delete oscillatorPtr;
    }
    Oscillator* oscillatorPtr = nullptr;
};
/*
 copied UDT 2:
 */
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

struct FilterWrapper
{
    FilterWrapper(Filter* ptr): filterPtr(ptr){}
    ~FilterWrapper()
    {
        delete filterPtr;
    }
    Filter* filterPtr = nullptr;
};
/*
 copied UDT 3:
 */
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

struct CVSequencerWrapper
{
    CVSequencerWrapper(CVSequencer* ptr):cvSequencerPtr(ptr){}
    ~CVSequencerWrapper()
    {
        delete cvSequencerPtr;
    }
    CVSequencer* cvSequencerPtr = nullptr;
};

/*
 new UDT 4:
 with 2 member functions
 */
struct Tone
{
    Tone();
    ~Tone();
    Oscillator triangleCore;
    Filter sem20;

    void changeTone();

    JUCE_LEAK_DETECTOR(Tone)
};

void Tone::changeTone()
{
    sem20.filterType = (sem20.filterType++)%3;
}

Tone::Tone()
{}

Tone::~Tone()
{
    changeTone();
    std::cout << "Tone\n";
}

struct ToneWrapper
{
    ToneWrapper(Tone* ptr): tonePtr(ptr){}
    ~ToneWrapper()
    {
        delete tonePtr;
    }
    Tone* tonePtr = nullptr;
};

/*
 new UDT 5:
 with 2 member functions
 */
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

MelodyPlayer::MelodyPlayer()
{}

MelodyPlayer::~MelodyPlayer()
{
    std::cout << "MelodyPlayer\n";
}
void MelodyPlayer::playArp()
{
    std::vector<int> newArp = voltageBlock.revArp({});
    triangleCore.receivePitchCV(newArp);
}

void MelodyPlayer::modWaveShape()
{
    std::vector<int> newArp = voltageBlock.revArp({});
    for (unsigned long i = 0; i < newArp.size(); i++)
    {
        triangleCore.waveshape += newArp[i];
    }
}

struct MelodyPlayerWrapper
{
    MelodyPlayerWrapper(MelodyPlayer* ptr): melodyPlayerPtr(ptr){}
    ~MelodyPlayerWrapper()
    {
        delete melodyPlayerPtr;
    }
    MelodyPlayer* melodyPlayerPtr = nullptr;
};

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

#include <iostream>
int main()
{
    OscillatorWrapper sto(new Oscillator()), csL(new Oscillator());
    FilterWrapper sem20(new Filter()), ladderFilter(new Filter());
    CVSequencerWrapper voltageBlock(new CVSequencer());

    sto.oscillatorPtr->hardSync({1, 1, 1, 0, 1, 1, 1, 0});
    std::cout << "hardSynced! Phase on this sample is reset: phase = " << sto.oscillatorPtr->phase << "\n";
    sto.oscillatorPtr->memberFunc();
    ladderFilter.filterPtr->movingAvrgFilter({2.32f, 23.2f, 86.3f, 43.1f, 92.6f, 123.0f, 62.5f, 53.9f, 24.2f});
    std::vector<int> revArp = voltageBlock.cvSequencerPtr->revArp({1,2,3,4});
    std::cout << "Reversed arp: ";
    for(unsigned long i = 0; i < revArp.size(); ++i)
    {
        std::cout << revArp[i];
    }
    std::cout << "\n";
    voltageBlock.cvSequencerPtr->memberFunc();
    std::cout << "good to go!\n";

    ToneWrapper tone(new Tone());
    MelodyPlayerWrapper melodyplayer(new MelodyPlayer());
}
