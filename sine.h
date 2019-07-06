

#ifndef SINE_H
#define SINE_H
#include<math.h>
#include<vector>
class Sine
{
private:
	int sampleRate;
	double frequency;
	double amplitude;
	double phase;
	double maxAmp;


public:

    Sine(double frequency, double amplitude, int sampleRate);

    double go();

    double getFrequency();

    double getAmplitude();

    int getSampleRate();

    void setFrequency(double f);

    void setAmplitude(double a);

		void changeVolume(double percent);


};

#endif // SINE_H
