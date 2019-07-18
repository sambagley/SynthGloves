#include "instrument_looper.h"
#include <iostream>


using namespace std;


Looper::Looper(Hand * h)			
  : Instrument(h)
{
	 backgroundLoop = 0;                     // The current loop being played
  
    nextBackgroundSample = 0.0001;
    backgroundSampleNumber = 0;

	
	// Instantiate new audio files
    loopBackground1 = new AudioFile<double>;
    loopBackground2 = new AudioFile<double>;
    loopBackground3 = new AudioFile<double>;
    loopBackground4 = new AudioFile<double>;
    loopBackground5 = new AudioFile<double>;
    loopBackground6 = new AudioFile<double>;
    loopBackground7 = new AudioFile<double>;
    loopBackground8 = new AudioFile<double>;
    loopBackground9 = new AudioFile<double>;
    loopBackground10 = new AudioFile<double>;

    // Load the wav files
    loopBackground1->load("/home/pi/SynthGloves/WavFiles/sample1.wav");
    loopBackground2->load("/home/pi/SynthGloves/WavFiles/sample2.wav");
    loopBackground3->load("/home/pi/SynthGloves/WavFiles/sample3.wav");
    loopBackground4->load("/home/pi/SynthGloves/WavFiles/sample4.wav");
    loopBackground5->load("/home/pi/SynthGloves/WavFiles/sample5.wav");
    loopBackground6->load("/home/pi/SynthGloves/WavFiles/sample6.wav");
    loopBackground7->load("/home/pi/SynthGloves/WavFiles/sample7.wav");
    loopBackground8->load("/home/pi/SynthGloves/WavFiles/sample8.wav");
    loopBackground9->load("/home/pi/SynthGloves/WavFiles/sample9.wav");
    loopBackground10->load("/home/pi/SynthGloves/WavFiles/Tabla.wav");

    // Find out how long each wav file is
    numBackgroundSamplesLoop1 = loopBackground1->getNumSamplesPerChannel();
    numBackgroundSamplesLoop2 = loopBackground2->getNumSamplesPerChannel();
    numBackgroundSamplesLoop3 = loopBackground3->getNumSamplesPerChannel();
    numBackgroundSamplesLoop4 = loopBackground4->getNumSamplesPerChannel();
    numBackgroundSamplesLoop5 = loopBackground5->getNumSamplesPerChannel();
    numBackgroundSamplesLoop6 = loopBackground6->getNumSamplesPerChannel();
    numBackgroundSamplesLoop7 = loopBackground7->getNumSamplesPerChannel();
    numBackgroundSamplesLoop8 = loopBackground8->getNumSamplesPerChannel();
    numBackgroundSamplesLoop9 = loopBackground9->getNumSamplesPerChannel();
    numBackgroundSamplesLoop10 = loopBackground10->getNumSamplesPerChannel();
	
}
double Looper::computeNextSample()
{
	// Check to see if we have changed the loop that is playing
	lastGesture = gesture;	
	hand->updateHand();
	gesture = hand->getGestures();
	
	   if (gesture != backgroundLoop)
        {
            backgroundLoop = gesture;
            backgroundSampleNumber = 0;
        }
    
    else
    {
        switch (backgroundLoop)
        {
        case (0):
            nextBackgroundSample = 0.0;					// default case of no gesture
            break;

        case (1):
            // If we have reached the end of the loop, reset to the beginning
            if (backgroundSampleNumber >= numBackgroundSamplesLoop1)
            {
                backgroundSampleNumber = 0;
            }

            // Otherwise, set the next sound sample as it should be
            nextBackgroundSample = loopBackground1->samples[0][backgroundSampleNumber];
            break;

        case (2):
            if (backgroundSampleNumber >= numBackgroundSamplesLoop2)
            {
                backgroundSampleNumber = 0;
            }
            nextBackgroundSample = loopBackground2->samples[0][backgroundSampleNumber];
            break;
        case (3):
            if (backgroundSampleNumber >= numBackgroundSamplesLoop3)
            {
                backgroundSampleNumber = 0;
            }
            nextBackgroundSample = loopBackground3->samples[0][backgroundSampleNumber];
            break;
        case (4):
            if (backgroundSampleNumber >= numBackgroundSamplesLoop4)
            {
                backgroundSampleNumber = 0;
            }
            nextBackgroundSample = loopBackground4->samples[0][backgroundSampleNumber];
            break;
        case (5):
            if (backgroundSampleNumber >= numBackgroundSamplesLoop5)
            {
                backgroundSampleNumber = 0;
            }
            nextBackgroundSample = loopBackground5->samples[0][backgroundSampleNumber];
            break;
        case (6):
            if (backgroundSampleNumber >= numBackgroundSamplesLoop6)
            {
                backgroundSampleNumber = 0;
            }
            nextBackgroundSample = loopBackground6->samples[0][backgroundSampleNumber];
            break;
        case (7):
            if (backgroundSampleNumber >= numBackgroundSamplesLoop7)
            {
                backgroundSampleNumber = 0;
            }
            nextBackgroundSample = loopBackground7->samples[0][backgroundSampleNumber];
            break;
        case (8):
            if (backgroundSampleNumber >= numBackgroundSamplesLoop8)
            {
                backgroundSampleNumber = 0;
            }
            nextBackgroundSample = loopBackground8->samples[0][backgroundSampleNumber];
            break;
        case (9):
            if (backgroundSampleNumber >= numBackgroundSamplesLoop9)
            {
                backgroundSampleNumber = 0;
            }
            nextBackgroundSample = loopBackground9->samples[0][backgroundSampleNumber];
            break;
        case (10):
            if (backgroundSampleNumber >= numBackgroundSamplesLoop10)
            {
                backgroundSampleNumber = 0;
            }
            nextBackgroundSample = loopBackground10->samples[0][backgroundSampleNumber];
            break;
        }
    }
    backgroundSampleNumber++;
	
	return nextBackgroundSample;


}
