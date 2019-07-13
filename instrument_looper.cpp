#include "instrument_looper.h"
#include <iostream>


Looper::Looper(Hand * h)
  : Instrument(h)
{
	updateHandCount = 0;
	nextSample = 0.0;
	sampleNumber = 0;
	currentLoop = 0;
	
	
	loop1 = new AudioFile<double>;
	loop2 = new AudioFile<double>;
	loop3 = new AudioFile<double>;
	loop4 = new AudioFile<double>;
	loop5 = new AudioFile<double>;
	loop6 = new AudioFile<double>;
	loop7 = new AudioFile<double>;
	loop8 = new AudioFile<double>;
	loop9 = new AudioFile<double>;
	loop10 = new AudioFile<double>;
	
	
	loop1->load("wav_stereo_8bit_48000.wav");
	loop2->load("wav_stereo_24bit_48000.wav");
	loop3->load("wav_stereo_24bit_48000.wav");
	loop4->load("wav_stereo_24bit_48000.wav");
	loop5->load("wav_stereo_24bit_48000.wav");
	loop6->load("wav_stereo_24bit_48000.wav");
	loop7->load("wav_stereo_24bit_48000.wav");
	loop8->load("wav_stereo_24bit_48000.wav");
	loop9->load("wav_stereo_24bit_48000.wav");
	loop10->load("wav_stereo_24bit_48000.wav");
	
	numSamplesLoop1 = loop1->getNumSamplesPerChannel();
	numSamplesLoop2 = loop2->getNumSamplesPerChannel();
	numSamplesLoop3 = loop3->getNumSamplesPerChannel();
	numSamplesLoop4 = loop4->getNumSamplesPerChannel();
	numSamplesLoop5 = loop5->getNumSamplesPerChannel();
	numSamplesLoop6 = loop6->getNumSamplesPerChannel();
	numSamplesLoop7 = loop7->getNumSamplesPerChannel();
	numSamplesLoop8 = loop8->getNumSamplesPerChannel();
	numSamplesLoop9 = loop9->getNumSamplesPerChannel();
	numSamplesLoop10 = loop10->getNumSamplesPerChannel();
	
	
	//loop1->printSummary();
	//hand->calibrateGestures();
}
double Looper::computeNextSample()
{
  /*if ((updateHandCount % 8) == 0)
  {
	int tempLastLoop = currentLoop;
	currentLoop = hand->getGestures();
	if (currentLoop != tempLastLoop)
	{
		sampleNumber = 0;
	}
  }*/

 nextSample = loop1->samples[0][sampleNumber++]; 
 if (sampleNumber >= numSamplesLoop1)
	sampleNumber = 0;
  return nextSample;
}
