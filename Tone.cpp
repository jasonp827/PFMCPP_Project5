#include "Tone.h"
#include <string>

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
