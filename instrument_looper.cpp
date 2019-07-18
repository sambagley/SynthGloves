#include "instrument_looper.h"
#include <iostream>


using namespace std;


Looper::Looper(Hand * h)			
  : Instrument(h)
{
	/*
	nextSample = 0.0;
	sampleNumber = 0;
	
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
	*/
}
double Looper::computeNextSample()
{
	// Check to see if we have changed the loop that is playing
	lastGesture = gesture;	
	hand->updateHand();
	gesture = hand->getGestures();
	
	computeNextBackgroundSample();


}
