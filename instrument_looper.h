#ifndef INSTRUMENT_LOOPER_H
#define INSTRUMENT_LOOPER_H
#include "instrument.h"
#include "/home/pi/SynthGloves/AudioFile/AudioFile.h"

class Looper: public Instrument{

  private:

    int updateHandCount;				// Keeps track if we need to update hand
    double nextSample;				      // The current sample being played
    uint32_t sampleNumber;
    int currentLoop;

    uint32_t numSamplesLoop1;
    int numSamplesLoop2;
    int numSamplesLoop3;
    int numSamplesLoop4;
    int numSamplesLoop5;
    int numSamplesLoop6;
    int numSamplesLoop7;
    int numSamplesLoop8;
    int numSamplesLoop9;
    int numSamplesLoop10;*/
    

    AudioFile<double> * loop1;
    AudioFile<double> * loop2;
    AudioFile<double> * loop3;
    AudioFile<double> * loop4;
    AudioFile<double> * loop5;
    AudioFile<double> * loop6;
    AudioFile<double> * loop7;
    AudioFile<double> * loop8;
    AudioFile<double> * loop9;
    AudioFile<double> * loop10;


  public:
    Looper(Hand * h);                       // Declare looper class that will be instantiated
    double computeNextSample();             // Declare function that will compute next sample; to be called from jack_wrapper

};
#endif
