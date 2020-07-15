#include "Oscillator.h"
#include "Filter.h"
#include "CVSequencer.h"
#include "Tone.h"
#include "MelodyPlayer.h"

#include "Wrappers.h"

OscillatorWrapper::OscillatorWrapper(Oscillator* ptr): oscillatorPtr(ptr){}

OscillatorWrapper::~OscillatorWrapper()
{
    delete oscillatorPtr;
}

FilterWrapper::FilterWrapper(Filter* ptr): filterPtr(ptr){}

FilterWrapper::~FilterWrapper()
{
    delete filterPtr;
}

CVSequencerWrapper::CVSequencerWrapper(CVSequencer* ptr): cvSequencerPtr(ptr){}

CVSequencerWrapper::~CVSequencerWrapper()
{
    delete cvSequencerPtr;
}

ToneWrapper::ToneWrapper(Tone* ptr): tonePtr(ptr){}

ToneWrapper::~ToneWrapper()
{
    delete tonePtr;
}

MelodyPlayerWrapper::MelodyPlayerWrapper(MelodyPlayer* ptr): melodyPlayerPtr(ptr){}

MelodyPlayerWrapper::~MelodyPlayerWrapper()
{
    delete melodyPlayerPtr;
}
