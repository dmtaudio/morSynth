/*
  ==============================================================================

    Oscillator.h
    Created: 6 Aug 2015 4:23:34pm
    Author:  dtl

  ==============================================================================
*/

#ifndef OSCILLATOR_H_INCLUDED
#define OSCILLATOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

inline double pi() { return 3.14159265358979323846; }
inline double twopi() { return pi() * 2.0; }

class Oscillator
{
public:
    Oscillator();
    ~Oscillator();
    
    enum Type
    {
        SINE = 0x0001,
        UPWARD_SAWTOOTH = 0x0002,
        DOWNWARD_SAWTOOTH = 0x0003,
        SQUARE = 0x0004,
        TRIANGLE = 0x0005
    };
    
    double generateWhiteNoise();
    double generateSineWave(double freq, double sampleRate);
    double generateUpSawtooth(double freq, double sampleRate);
    double generateDownSawtooth(double freq, double sampleRate);
    
    double* fillWhiteNoiseBuffer(int bufferLength);
    double* fillOscillatorBuffer(Type osc, double freq, double sampleRate, int bufferLength);

private:
    double _currentPhase;
    double* buffer;
};



#endif  // OSCILLATOR_H_INCLUDED
