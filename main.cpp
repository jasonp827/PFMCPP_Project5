/*
 Project 5: Part 3 / 4
 video: Chapter 3 Part 4: 

Create a branch named Part3

 the 'new' keyword

 1) add #include "LeakedObjectDetector.h" to main
 
 3) Add 'JUCE_LEAK_DETECTOR(OwnerClass)' at the end of your UDTs.
 
 4) write the name of your class where it says "OwnerClass"
 
 5) write wrapper classes for each type similar to how it was shown in the video
 
 7) update main() 
      replace your objects with your wrapper classes, which have your UDTs as pointer member variables.
      
    This means if you had something like the following in your main() previously: 
*/
#if false
Axe axe;
std::cout << "axe sharpness: " << axe.sharpness << "\n";
#endif
 /*
    you would update that to use your wrappers:
    
 */

#if false
AxeWrapper axWrapper( new Axe() );
std::cout << "axe sharpness: " << axWrapper.axPtr->sharpness << "\n";
#endif
/*
notice that the object name has changed from 'axe' to 'axWrapper'
You don't have to do this, you can keep your current object name and just change its type to your Wrapper class

 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 see here for an example: https://repl.it/@matkatmusic/ch3p04example

 you can safely ignore any warnings about exit-time-destructors.
 if you would like to suppress them, add -Wno-exit-time-destructors to the .replit file 
   with the other warning suppression flags
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
