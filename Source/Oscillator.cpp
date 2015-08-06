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
    if(_buffer != nullptr)
        delete _buffer;
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
    _bufferLength = bufferLength;
    if(_buffer != nullptr)
        delete _buffer;
    _buffer = new double[_bufferLength];
    for(int i = 0; i < _bufferLength; ++i)
    {
        _buffer[i] = generateWhiteNoise();
    }
    return _buffer;
}

double* Oscillator::fillOscillatorBuffer(Type osc, double freq, double sampleRate, int bufferLength)
{
    _currentPhase = 0.0;
    _bufferLength = bufferLength;
    if(_buffer != nullptr)
        delete _buffer;
    _buffer = new double[bufferLength];
    for(int i = 0; i < bufferLength; ++i)
    {
        switch (osc)
        {
            case SINE:
                _buffer[i] = generateSineWave(freq, sampleRate);
                break;
            case UPWARD_SAWTOOTH:
                _buffer[i] = generateUpSawtooth(freq, sampleRate);
            case DOWNWARD_SAWTOOTH:
                _buffer[i] = generateDownSawtooth(freq, sampleRate);
            case SQUARE:
                _buffer[i] = generateSquareWave(freq, sampleRate);
                break;
            case TRIANGLE:
                _buffer[i] = generateTriangleWave(freq, sampleRate);
                break;
        }
    }
    return _buffer;
}

AudioSampleBuffer* Oscillator::fillAudioSampleBuffer(int channels)
{
    _sampleBuffer = new AudioSampleBuffer(channels, _bufferLength);
    
    float* temp = new float[_bufferLength];
    for(int i = 0; i < _bufferLength; ++i)
    {
       temp[i] = _buffer[i];
        if(channels == 1)
            _sampleBuffer->addSample(1, i, temp[i]);
        else if(channels == 2)
        {
            _sampleBuffer->addSample(1, i, temp[i]);
            _sampleBuffer->addSample(2, i, temp[i]);
        }
        else
            return nullptr;
    }
    delete temp;
    return _sampleBuffer;
}

