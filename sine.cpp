#include "sine.h"

Sine::Sine(double frequency, double amplitude, int sampleRate)
{
	this->frequency = frequency;
	this->amplitude = amplitude;
	this->sampleRate = sampleRate;
	this->phase = 0.0;
	this->maxAmp = amplitude;

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

void Sine::setAmplitude(double a)
{
	if( a > maxAmp)
	{
		maxAmp = a;
	}
	this->amplitude = a;
}
void Sine::changeVolume(double dB)
{
	if (dB >= -0.000001)
	{
		amplitude = maxAmp;
		return;
	}
	if (dB < -99.99)
	{
		amplitude = 0.00001;
		return;
	}
 	amplitude = maxAmp * pow(10.0, dB/20.0);
}
