#include "MelodyPlayer.h"
#include <string>

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
