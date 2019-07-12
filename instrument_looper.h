#ifndef INSTRUMENT_LOOPER_H
#define INSTRUMENT_LOOPER_H
#include "instrument_finger_keys.h"
#include "/home/pi/SynthGloves/AudioFile/AudioFile.h"

class Looper: public Instrument{

  private:
    //int updateHandCount;				    // Keeps track if we need to update hand
    double nextSample;				        // The voltage to be sent to the speakers
    int sampleNumber;                       // The sample number that we are getting the above voltage from
    int currentLoop;                        // The current wav or aif file that is playing
    int channel = 0;                        // Set the channel number to 0. This is needed for getting the sample voltages.

    int numSamplesLoop1;                  // The number of samples in each wav or aif file. We don't want to try to play samples that don't exsist!
    /*int numSamplesLoop2;              
    int numSamplesLoop3;
    int numSamplesLoop4;
    int numSamplesLoop5;
    int numSamplesLoop6;
    int numSamplesLoop7;
    int numSamplesLoop8;
    int numSamplesLoop9;
    int numSamplesLoop10;*/
    

    AudioFile<double> loop1;              // Declare loop one as an instance of the AudioFile class
    /*AudioFile<double> loop2;
    AudioFile<double> * loop3;
    AudioFile<double> * loop4;
    AudioFile<double> * loop5;
    AudioFile<double> * loop6;
    AudioFile<double> * loop7;
    AudioFile<double> loop8;
    AudioFile<double> loop9;
    AudioFile<double> loop10;*/
    //Sine * sine;
    
    

  public:
    Looper(Hand * h);                       // Declare looper class that will be instantiated
    double computeNextSample();             // Declare function that will compute next sample; to be called from jack_wrapper

};
#endif
