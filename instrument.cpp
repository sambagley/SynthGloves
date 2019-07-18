#include "instrument.h"

using namespace std;

Instrument::Instrument(Hand * h)
{
    this->hand = h;
    key = 0;
    rootFrequency = STARTING_FREQUENCY;
    octave = 0;

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
    loopBackground1->load("/home/pi/SynthGloves/WavFiles/Tabla.wav");
    loopBackground2->load("/home/pi/SynthGloves/WavFiles/StringChords.wav");
    loopBackground3->load("/home/pi/SynthGloves/WavFiles/PianoChords.wav");
    loopBackground4->load("/home/pi/SynthGloves/WavFiles/DigerydooSlaps.wav");
    loopBackground5->load("/home/pi/SynthGloves/WavFiles/AiryGuitar.wav");
    loopBackground6->load("/home/pi/SynthGloves/WavFiles/sample5.wav");
    loopBackground7->load("/home/pi/SynthGloves/WavFiles/sample4.wav");
    loopBackground8->load("/home/pi/SynthGloves/WavFiles/sample3.wav");
    loopBackground9->load("/home/pi/SynthGloves/WavFiles/sample2.wav");
    loopBackground10->load("/home/pi/SynthGloves/WavFiles/sample1.wav");

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


void Instrument::setKey(int k)
{
  key = k;
 switch (k){
   case -12 :
    rootFrequency = 220.0;
    break;
   case -11 :
    rootFrequency = 233.08;
    break;
   case -10 :
    rootFrequency = 246.94;
    break;
   case -9 :
    rootFrequency = 261.63;
    break;
   case -8 :
    rootFrequency = 277.18;
    break;
   case -7 :
    rootFrequency = 293.66;
    break;
   case -6 :
    rootFrequency = 311.13;
    break;
   case -5 :
    rootFrequency = 329.63;
    break;
   case -4 :
    rootFrequency = 349.23;
    break;
   case -3 :
    rootFrequency = 369.99;
    break;
   case -2 :
      rootFrequency = 392.00;
    break;
   case -1 :
    rootFrequency = 415.30;
    break;
   case 0 :
    rootFrequency = 440.0;
    break;
   case 1 :
    rootFrequency = 466.16;
    break;
   case 2 :
    rootFrequency = 493.88;
    break;
   case 3 :
    rootFrequency = 523.25;
    break;
   case 4 :
    rootFrequency = 554.37;
    break;
   case 5 :
    rootFrequency = 587.33;
    break;
   case 6 :
   rootFrequency = 622.25;
    break;
   case 7 :
    rootFrequency = 659.25;
    break;
   case 8 :
    rootFrequency = 698.46;
    break;
   case 9 :
    rootFrequency = 739.99;
    break;
   case 10 :
   rootFrequency = 783.99;
    break;
   case 11 :
    rootFrequency = 830.61;
    break;
   case 12 :
    rootFrequency = 880.0;
    break;
   default:
    rootFrequency = 440.0;
    break;
   }
}
void Instrument::setOctave(int o)
{
  octave = o;

}
void Instrument::setScale(int s)
{
  scaleVal = s;

}

void Instrument::computeNextBackgroundSample()
{ 
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
    
}
