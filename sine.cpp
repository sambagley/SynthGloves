#include "sine.h"

Sine::Sine(double frequency, double amplitude, int sampleRate)
{
	this->frequency = frequency;
	this->amplitude = amplitude;
	this->sampleRate = sampleRate;
	this->phase = 1.0;
	
	
}

//make the sound 
double Sine::go()
{
	phase += 2.0 * 3.14159 * frequency * (1.0/ (double) sampleRate);

    // wrap to 2 pi
    if(phase>=2.0*3.14159)
    {
        phase -= 2.0*3.14159;

    }

    return sin(phase) * amplitude;
}


double Sine::getAmplitude()
{
	return amplitude;
}

double Sine::getFrequency()
{
	return frequency;
}

int Sine::getSampleRate()
{
	return sampleRate;
}

void Sine::setFrequency(double f)
{
	this->frequency = f;
}
