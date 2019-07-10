#include "instrument_looper.h"
#include <iostream>
#include <unistd.h>

using namespace std;


Looper::Looper(Hand * h)
  : Instrument(h)
{
	updateHandCount = 0;
	nextSample = 0.0;
	sampleNumber = 0;
	currentLoop = 0;
	
	//hand->calibrateGestures();
	
	//sleep(5);
	loop1 = new AudioFile<double>;
	loop2 = new AudioFile<double>;
	
	loop1->load("/home/pi/SynthGloves/AudioFile/tests/AudioFileTests/test-audio/aiff_stereo_8bit_44100.aif");
	loop2->load("/home/pi/SynthGloves/AudioFile/tests/AudioFileTests/test-audio/wav_stereo_8bit_48000.wav");
	loop3->load("/home/pi/SynthGloves/WavFiles/sample3.wav");
	loop4->load("/home/pi/SynthGloves/WavFiles/sample4.wav");/*
	loop5.load("/home/pi/SynthGloves/WavFiles/sample5.wav");
	loop6.load("/home/pi/SynthGloves/WavFiles/sample1.wav");
	loop7.load("/home/pi/SynthGloves/WavFiles/sample2.wav");
	loop8.load("/home/pi/SynthGloves/WavFiles/sample3.wav");
	loop9.load("/home/pi/SynthGloves/WavFiles/sample4.wav");
	loop10.load("/home/pi/SynthGloves/WavFiles/sample5.wav");*/
	
	//cout << "Sucessfully loaded all loop samples" << endl;
	//sleep(5);
	numSamplesLoop1 = loop1->getNumSamplesPerChannel();
	numSamplesLoop2 = loop2->getNumSamplesPerChannel();
	/*numSamplesLoop3 = loop3.getNumSamplesPerChannel();
	numSamplesLoop4 = loop4.getNumSamplesPerChannel();
	numSamplesLoop5 = loop5.getNumSamplesPerChannel();
	numSamplesLoop6 = loop6.getNumSamplesPerChannel();
	numSamplesLoop7 = loop7.getNumSamplesPerChannel();
	numSamplesLoop8 = loop8.getNumSamplesPerChannel();
	numSamplesLoop9 = loop9.getNumSamplesPerChannel();
	numSamplesLoop10 = loop10.getNumSamplesPerChannel();*/
	sine = new Sine(440.0, .5, 48000);
	//cout << "Got number of samples in each loop sample" << endl;
}
double Looper::computeNextSample()
{/*
  if ((updateHandCount % 8) == 0)
  {
	int tempLastLoop = currentLoop;
	currentLoop = hand->getGestures();
	//cout << "updated hand count" << endl;
	if (currentLoop != tempLastLoop)
	{
		sampleNumber = 0;
	}
  }
  switch (currentLoop)
  {
	case(1):
		//cout << "gesture 1" << endl;
		if (sampleNumber < numSamplesLoop1)
		{
			nextSample = loop1.samples[0][sampleNumber];
			num 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop1.samples[0][sampleNumber];
		}
		
	case(2):
		//cout << "gesture 2" << endl;
		if (sampleNumber < numSamplesLoop2)
		{
			nextSample = loop2.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop2.samples[0][sampleNumber];
		}
		
	case(3):
		//cout << "gesture 3" << endl;
		if (sampleNumber < numSamplesLoop3)
		{
			nextSample = loop3.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop3.samples[0][sampleNumber];
		}
		
	case(4):
		//cout << "gesture 4" << endl;
		if (sampleNumber < numSamplesLoop4)
		{
			nextSample = loop4.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop4.samples[0][sampleNumber];
		}
		
	case(5):
		//cout << "gesture 5" << endl;
		if (sampleNumber < numSamplesLoop5)
		{
			nextSample = loop5.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop5.samples[0][sampleNumber];
		}
		
	case(6):
		//cout << "gesture 6" << endl;
		if (sampleNumber < numSamplesLoop6)
		{
			nextSample = loop6.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop6.samples[0][sampleNumber];
		}
	case(7):
		//cout << "gesture 7" << endl;
		if (sampleNumber < numSamplesLoop7)
		{
			nextSample = loop7.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop7.samples[0][sampleNumber];
		}
		
	case(8):
		//cout << "gesture 8" << endl;
		if (sampleNumber < numSamplesLoop8)
		{
			nextSample = loop8.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop8.samples[0][sampleNumber];
		}
		
	case(9):
		//cout << "gesture 9" << endl;
		if (sampleNumber < numSamplesLoop9)
		{
			nextSample = loop9.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop9.samples[0][sampleNumber];
		}
		
	case(10):
		//cout << "gesture 10" << endl;
		if (sampleNumber < numSamplesLoop10)
		{
			nextSample = loop10.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop10.samples[0][sampleNumber];
		}
		
	default:
		//cout << "no sign detected" << endl;
		nextSample = 0.01;
	}*/
			
  //updateHandCount ++;
  //sampleNumber ++;
  //cout << "Updated hand count" << endl;
  //return nextSample;
  return sine->go();
}
