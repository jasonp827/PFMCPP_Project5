#include <vector>
#include <iostream>

/*
Project 5: Part 1 / 4
 video Chapter 2 - Part 12

 Create a branch named Part1

Purpose:  This project continues developing Project3.
       you will learn how to take code from existing projects and migrate only what you need to new projects
       you will learn how to write code that doesn't leak as well as how to refactor. 

 Destructors
        
 0) move all of your implementations of all functions to OUTSIDE of the class. 
 
 1) Copy 3 of your user-defined types (the ones with constructors and for()/while() loops from Project 3) here
 2) add destructors
        make the destructors do something like print out the name of the class.

 3) add 2 new UDTs that use only the types you copied above as member variables.

 4) add 2 member functions that use your member variables to each of these new UDTs

 5) Add constructors and destructors to these 2 new types that do stuff.  
        maybe print out the name of the class being destructed, or call a member function of one of the members.  be creative
 
 6) copy over your main() from the end of Project3 and get it to compile with the types you copied over.
        remove any code in main() that uses types you didn't copy over.
 
 7) Instantiate your 2 UDT's from step 4) in the main() function at the bottom.
 
 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 */

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
    Oscillator sto, csL;
    Filter sem20, ladderFilter;
    CVSequencer voltageBlock;
    sto.hardSync({1, 1, 1, 0, 1, 1, 1, 0});
    std::cout << "hardSynced! Phase on this sample is reset: phase = " << sto.phase << "\n\n";
    ladderFilter.movingAvrgFilter({2.32f, 23.2f, 86.3f, 43.1f, 92.6f, 123.0f, 62.5f, 53.9f, 24.2f});
    std::vector<int> revArp = voltageBlock.revArp({1,2,3,4});
    std::cout << "Reversed arp: ";
    for(unsigned long i = 0; i < revArp.size(); ++i)
    {
        std::cout << revArp[i];
    }
    std::cout << "\n";
    std::cout << "good to go!";

    Tone tone;
    MelodyPlayer melodyplayer;
}
