#include "instrument_looper.h"
#include <iostream>


using namespace std;


Looper::Looper(Hand * h)			
  : Instrument(h)
{
	nextSample = 0.0;
	sampleNumber = 0;
	currentGesture = 0;
	
	// Instantiate new audio files
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
	
	// Load the wav files
	loop1->load("/home/pi/SynthGloves/WavFiles/Tabla.wav");
	loop2->load("/home/pi/SynthGloves/WavFiles/StringChords.wav");
	loop3->load("/home/pi/SynthGloves/WavFiles/PianoChords.wav");
	loop4->load("/home/pi/SynthGloves/WavFiles/DigerydooSlaps.wav");
	loop5->load("/home/pi/SynthGloves/WavFiles/AiryGuitar.wav");
	loop6->load("/home/pi/SynthGloves/WavFiles/sample5.wav");
	loop7->load("/home/pi/SynthGloves/WavFiles/sample4.wav");
	loop8->load("/home/pi/SynthGloves/WavFiles/sample3.wav");
	loop9->load("/home/pi/SynthGloves/WavFiles/sample2.wav");
	loop10->load("/home/pi/SynthGloves/WavFiles/sample1.wav");
	
	// Find out how long each wav file is
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
	
}
double Looper::computeNextSample()
{
	// Check to see if we have changed the loop that is playing
	int lastGesture = currentGesture;	
	hand->updateHand();
	
	currentGesture = hand->getGestures();
	
	// If the hand gesture has changed, reset the sample number to zero
	if (lastGesture != currentGesture)
	{
		sampleNumber = 0;
	}
	
	// Depending on the hand gesture/loop, get the correct audio sample to play 
	switch (currentGesture)
	{
	case(0):	
		return 0.01;					// default case of no gesture
		
	case (1):
		// If we have reached the end of the loop, reset to the beginning
		if (sampleNumber >= numSamplesLoop1)
		{
			sampleNumber = 0;
		}

		// Otherwise, set the next sound sample as it should be
		nextSample = loop1->samples[0][sampleNumber];
		break;
		
	case (2):
		if (sampleNumber >= numSamplesLoop2)
		{
			sampleNumber = 0;
		}
		nextSample = loop2->samples[0][sampleNumber];
		break;
	case (3):
		if (sampleNumber >= numSamplesLoop3)
		{
			sampleNumber = 0;
		}
		nextSample = loop3->samples[0][sampleNumber];
		break;
	case (4):
		if (sampleNumber >= numSamplesLoop4)
		{
			sampleNumber = 0;
		}
		nextSample = loop4->samples[0][sampleNumber];
		break;
	case (5):
		if (sampleNumber >= numSamplesLoop5)
		{
			sampleNumber = 0;
		}
		nextSample = loop5->samples[0][sampleNumber];
		break;
	case (6):
		if (sampleNumber >= numSamplesLoop6)
		{
			sampleNumber = 0;
		}
		nextSample = loop6->samples[0][sampleNumber];
		break;
	case (7):
		if (sampleNumber >= numSamplesLoop7)
		{
			sampleNumber = 0;
		}
		nextSample = loop7->samples[0][sampleNumber];
		break;
	case (8):
		if (sampleNumber >= numSamplesLoop8)
		{
			sampleNumber = 0;
		}
		nextSample = loop8->samples[0][sampleNumber];
		break;
	case (9):
		if (sampleNumber >= numSamplesLoop9)
		{
			sampleNumber = 0;
		}
		nextSample = loop9->samples[0][sampleNumber];
		break;
	case (10):
		if (sampleNumber >= numSamplesLoop10)
		{
			sampleNumber = 0;
		}
		nextSample = loop10->samples[0][sampleNumber];
		break;
	}	
	// Increment the sound sample and return the next sample value to the speakers
	sampleNumber++;			
	return nextSample;

}
