#include "instrument_looper.h"
#include <iostream>
#include <unistd.h>


using namespace std;


Looper::Looper(Hand * h)			
  : Instrument(h)
{
	//updateHandCount = 0;	
	nextSample = 0.1;
	sampleNumber = 1;
	currentLoop = 1;
	
	
	
	//AudioFile<double> loop1;				// Don't uncomment																		// Here we actually instantiate the audiofile class for loop1
	
	loop1.load("/home/pi/SynthGloves/AudioFile/tests/AudioFileTests/test-audio/wav_stereo_16bit_48000.wav");		// Load the wav file into the loop1 class
	/*loop2.load("/home/pi/SynthGloves/AudioFile/tests/AudioFileTests/test-audio/wav_stereo_8bit_48000.wav");		
	loop3->load("/home/pi/SynthGloves/WavFiles/sample3.wav");
	loop4->load("/home/pi/SynthGloves/WavFiles/sample4.wav");
	loop5->load("/home/pi/SynthGloves/WavFiles/sample5.wav");
	loop6->load("/home/pi/SynthGloves/WavFiles/sample1.wav");
	loop7->load("/home/pi/SynthGloves/WavFiles/sample2.wav");
	loop8.load("/home/pi/SynthGloves/WavFiles/sample3.wav");
	loop9.load("/home/pi/SynthGloves/WavFiles/sample4.wav");
	loop10.load("/home/pi/SynthGloves/WavFiles/sample5.wav");*/
	
	//cout << "Sucessfully loaded all loop samples" << endl;
	//sleep(5);
	
	numSamplesLoop1 = loop1.getNumSamplesPerChannel();																// Now that the wav file is loaded, we can find out how many samples long it is.
	/*numSamplesLoop2 = loop2.getNumSamplesPerChannel();
	numSamplesLoop3 = loop3->getNumSamplesPerChannel();
	numSamplesLoop4 = loop4->getNumSamplesPerChannel();
	numSamplesLoop5 = loop5->getNumSamplesPerChannel();
	numSamplesLoop6 = loop6->getNumSamplesPerChannel();
	numSamplesLoop7 = loop7->getNumSamplesPerChannel();
	numSamplesLoop8 = loop8.getNumSamplesPerChannel();
	numSamplesLoop9 = loop9.getNumSamplesPerChannel();
	numSamplesLoop10 = loop10.getNumSamplesPerChannel();*/
	//sine = new Sine(440.0, .5, 48000);
	//cout << "Got number of samples in each loop sample" << endl;
	
	
    
}
double Looper::computeNextSample()
{
	char newState = 0b00000000;											// Set a clean slate for the finger positions to be read.	
  
	hand->updateHand();													// Update the hand
	
	
	
	// Check for finger positions
	if (200 < hand->getThumb() && hand->getThumb() < 400)				// Go through each finger, checking if the finger is depressed.    
	{ 																	
		newState |= 0b00000001;											// If the finger is depressed, add a bit to that finger's position in the bit-field.
	}
  
	if (200 < hand->getIndex() && hand->getIndex() < 1500) 
	{ 
		newState |= 0b00000010;
	}
	
    if (200 < hand->getMiddle() && hand->getMiddle()< 1500) 
    { 
		newState |= 0b00000100;
	}
    
	if (200 < hand->getRing() && hand->getRing() < 1500)  
	{ 
     newState |= 0b00001000;
    }
    
	if (200 < hand->getPinky() && hand->getPinky() < 1500) 
	{
       newState |= 0b00010000;
	}
    
 
 
	// Determine what to do with new finger positions
	switch (0b00011101)														
	{	
	case 0b00011101:													// Only index finger is extended
		/*if (sampleNumber < numSamplesLoop1)								// If we have not yet reached the end of the sample...
		{
		 	sampleNumber++;
			nextSample = loop1.samples[0][sampleNumber];			// Get the next sample voltage to go to the speakers
																		// and increment the sample number for the next time around
		}
		else 															// If we have reached the end of the wav or aif file...
		{
			sampleNumber = 1;											// Set the sample number to 1...
			nextSample = loop1.samples[0][sampleNumber];			// Get the sample voltage to go to the speaker
			sampleNumber++;												// Increment the sample number for the next time around.
		}*/
		return 0.1;
		break;
	/*case 0b00011001:
		if (sampleNumber < numSamplesLoop2)
		{
			nextSample = loop2.samples[channel][sampleNumber];
			sampleNumber++;
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop2.samples[channel][sampleNumber];
		}
		break;
	case 0b00011000:
		if (sampleNumber < numSamplesLoop3)
		{
			nextSample = loop3->samples[channel][sampleNumber];
			sampleNumber++;
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop3->samples[channel][sampleNumber];
		}
		break;
	case 0b00000001:
		if (sampleNumber < numSamplesLoop4)
		{
			nextSample = loop4->samples[channel][sampleNumber];
			sampleNumber++;
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop4->samples[channel][sampleNumber];
		}
		break;
	case 0b00000000:
		if (sampleNumber < numSamplesLoop5)
		{
			nextSample = loop5->samples[channel][sampleNumber];
			sampleNumber++;
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop5->samples[channel][sampleNumber];
		}
		break;
	case 0b00000011:
		if (sampleNumber < numSamplesLoop6)
		{
			nextSample = loop6->samples[channel][sampleNumber];
			sampleNumber++;
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop6->samples[channel][sampleNumber];
		}
		break;
	case 0b00000101:
		if (sampleNumber < numSamplesLoop7)
		{
			nextSample = loop7->samples[channel][sampleNumber];
			sampleNumber++;
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop7->samples[channel][sampleNumber];
		}
		break;*/
	default:															// Default to putting out virtually nothing
		{
		nextSample = 0.01;
		return nextSample;
		}
	}
			
  //updateHandCount ++;													// Update the update hand count variable to keep track of every 8th frame
  //sampleNumber ++;													
  //cout << "Updated hand count" << endl;
  //return nextSample;
  
}
