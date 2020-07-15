#pragma once

struct Oscillator;
struct Filter;
struct CVSequencer;
struct Tone;
struct MelodyPlayer;

struct OscillatorWrapper
{
    OscillatorWrapper(Oscillator* ptr);
    ~OscillatorWrapper();
    Oscillator* oscillatorPtr = nullptr;
};

struct FilterWrapper
{
    FilterWrapper(Filter* ptr);
    ~FilterWrapper();
    Filter* filterPtr = nullptr;
};

struct CVSequencerWrapper
{
    CVSequencerWrapper(CVSequencer* ptr);
    ~CVSequencerWrapper();
    CVSequencer* cvSequencerPtr = nullptr;
};

struct ToneWrapper
{
    ToneWrapper(Tone* ptr);
    ~ToneWrapper();
    Tone* tonePtr = nullptr;
};

struct MelodyPlayerWrapper
{
    MelodyPlayerWrapper(MelodyPlayer* ptr);
    ~MelodyPlayerWrapper();
    MelodyPlayer* melodyPlayerPtr = nullptr;
};
