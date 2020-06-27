/*
Project 5: Part 2 / 4
 video: Chapter 3 Part 1

Create a branch named Part2

 The 'this' keyword
 
 The purpose of this project part is to show you how accessing member variables of objects INSIDE member functions is very similar to accessing member variables of objects OUTSIDE of member functions, via 'this->' and via the '.' operator.
 This project part will break the D.R.Y. rule, but that is fine for the purpose of this project part.
 
 
 1) if you don't have any std::cout statements in main() that access member variables of your U.D.Ts
         write some.
    You can copy some from your Project3's main() if needed.
 
 2) For each std::cout statement in main() that accessed member variables of your types or printed out the results of your member function calls,
        a) write a member function that prints the same thing out, but uses the proper techniques inside the member functions to access the same member variables/functions.
        b) be explicit with your use of 'this->' in those member functions so we see how you're accessing/calling those member variables and functions *inside*
        c) call that member function after your std::cout statement in main.
        d) you should see 2 (almost) identical messages in the program output for each member function you add:
            one for the std::cout line, and one for the member function's output
 
 
 3) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 */

/*
 example:
 */
#include <iostream>
#include <vector>
namespace Example
{
    //a User-Defined Type
    struct MyFoo
    {
        MyFoo() { std::cout << "creating MyFoo" << std::endl; }
        ~MyFoo() { std::cout << "destroying MyFoo" << std::endl; }
		
		// 2a) the member function whose function body is almost identical to the std::cout statement in main.
        void memberFunc() 
		{ 
            // 2b) explicitly using 'this' inside this member function.
			std::cout << "MyFoo returnValue(): " << this->returnValue() << " and MyFoo memberVariable: " << this->memberVariable << std::endl; 
		}  
		
        int returnValue() { return 3; }
        float memberVariable = 3.14f;
    };
    
    int main()
    {
        //an instance of the User-Defined Type named mf
        MyFoo mf;
		
        // 1) a std::cout statement that uses mf's member variables
        std::cout << "mf returnValue(): " << mf.returnValue() << " and mf memberVariable: " << mf.memberVariable << std::endl; 
		
        // 2c) calling mf's member function.  the member function's body is almost identical to the cout statement above.
        mf.memberFunc();
        return 0;
    }
}

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
    void memberFunc();

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
    std::cout << "hardSynced! Phase on this sample is reset: phase = " << sto.phase << "\n";
    sto.memberFunc();
    ladderFilter.movingAvrgFilter({2.32f, 23.2f, 86.3f, 43.1f, 92.6f, 123.0f, 62.5f, 53.9f, 24.2f});
    std::vector<int> revArp = voltageBlock.revArp({1,2,3,4});
    std::cout << "Reversed arp: ";
    for(unsigned long i = 0; i < revArp.size(); ++i)
    {
        std::cout << revArp[i];
    }
    std::cout << "\n";
    voltageBlock.memberFunc();
    std::cout << "good to go!\n";

    Tone tone;
    MelodyPlayer melodyplayer;
}
