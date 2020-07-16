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

 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

#include "LeakedObjectDetector.h"
#include "Oscillator.h"
#include "Filter.h"
#include "CVSequencer.h"
#include "Tone.h"
#include "MelodyPlayer.h"
#include "Wrappers.h"

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
