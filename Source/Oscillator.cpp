/*
  ==============================================================================

    Oscillator.cpp
    Created: 6 Aug 2015 4:23:34pm
    Author:  dtl

  ==============================================================================
*/

#include "Oscillator.h"

Oscillator::Oscillator()
: _currentPhase(0.0f)
{}

Oscillator::~Oscillator()
{
    if(buffer != nullptr)
        delete buffer;
}

double Oscillator::generateWhiteNoise()
{
    // generate random float
    float noise = (float)rand();
    // get max float value
    float maxValue = std::numeric_limits<float>::max();
    // normalize and make bipolar
    noise = 2.0 * (noise/maxValue) - 1.0;
    return noise;
}

double Oscillator::generateSineWave(double freq, double sampleRate)
{
    // increment amount based on the frequency and sample rate
    double incr = freq * twopi() / sampleRate;
    // output is the current sine phase
    double out = (float) sin(_currentPhase);
    // increment the phase
    _currentPhase += incr;
    if(_currentPhase >= twopi())
        _currentPhase -= twopi();
    return out;
}

double Oscillator::generateUpSawtooth(double freq, double sampleRate)
{
    double incr = freq * twopi() / sampleRate;
    double out = 1.0 - 2.0 * (_currentPhase * (1.0/ twopi()));
    _currentPhase += incr;
    if(_currentPhase >= twopi())
        _currentPhase -= twopi();
    if(_currentPhase < 0.0)
        _currentPhase += twopi();
    return out;
}

double Oscillator::generateDownSawtooth(double freq, double sampleRate)
{
    double incr = freq * twopi() / sampleRate;
    double out = (2.0 * (_currentPhase * (1.0 / twopi()) - 1.0));
    _currentPhase += incr;
    if(_currentPhase >= twopi())
        _currentPhase -= twopi();
    if(_currentPhase < 0.0)
        _currentPhase += twopi();
    return out;
}

double Oscillator::generateSquareWave(double freq, double sampleRate)
{
    double incr = freq * twopi() / sampleRate;
    double out;
    if(_currentPhase <= pi())
        out = 1.0;
    else
        out = -1.0;
    _currentPhase += incr;
    if(_currentPhase >= twopi())
        _currentPhase -= twopi();
    if(_currentPhase < 0.0)
        _currentPhase += twopi();
    return out;
}

double Oscillator::generateTriangleWave(double freq, double sampleRate)
{
    double incr = freq * twopi() / sampleRate;
    double out = (2.0 * (_currentPhase * (1.0 / twopi()))) - 1.0;
    _currentPhase += incr;
    if(_currentPhase >= twopi())
        _currentPhase -= twopi();
    if(_currentPhase < 0.0)
        _currentPhase += twopi();
    return out;
}

double* Oscillator::fillWhiteNoiseBuffer(int bufferLength)
{
    _currentPhase = 0.0;
    if(buffer != nullptr)
        delete buffer;
    buffer = new double[bufferLength];
    for(int i = 0; i < bufferLength; ++i)
    {
        buffer[i] = generateWhiteNoise();
    }
    return buffer;
}

double* Oscillator::fillOscillatorBuffer(Type osc, double freq, double sampleRate, int bufferLength)
{
    _currentPhase = 0.0;
    if(buffer != nullptr)
        delete buffer;
    buffer = new double[bufferLength];
    for(int i = 0; i < bufferLength; ++i)
    {
        switch (osc)
        {
            case SINE:
                buffer[i] = generateSineWave(freq, sampleRate);
                break;
            case UPWARD_SAWTOOTH:
                buffer[i] = generateUpSawtooth(freq, sampleRate);
            case DOWNWARD_SAWTOOTH:
                buffer[i] = generateDownSawtooth(freq, sampleRate);
            case SQUARE:
                buffer[i] = generateSquareWave(freq, sampleRate);
                break;
            case TRIANGLE:
                buffer[i] = generateTriangleWave(freq, sampleRate);
                break;
        }
    }
    return buffer;
}
