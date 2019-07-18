#ifndef INSTRUMENT_LOOPER_H
#define INSTRUMENT_LOOPER_H
#include "instrument.h"


class Looper: public Instrument{

  private:
   int backgroundLoop;                     // The current loop being played
  double nextBackgroundSample;				    // The next background sample to go to speakers
  int backgroundSampleNumber;        // The sample number that is being played from the wav file


   int numBackgroundSamplesLoop1;
  int numBackgroundSamplesLoop2;
  int numBackgroundSamplesLoop3;
  int numBackgroundSamplesLoop4;
  int numBackgroundSamplesLoop5;
  int numBackgroundSamplesLoop6;
  int numBackgroundSamplesLoop7;
  int numBackgroundSamplesLoop8;
  int numBackgroundSamplesLoop9;
  int numBackgroundSamplesLoop10;


  AudioFile<double> * loopBackground1;
  AudioFile<double> * loopBackground2;
  AudioFile<double> * loopBackground3;
  AudioFile<double> * loopBackground4;
  AudioFile<double> * loopBackground5;
  AudioFile<double> * loopBackground6;
  AudioFile<double> * loopBackground7;
  AudioFile<double> * loopBackground8;
  AudioFile<double> * loopBackground9;
  AudioFile<double> * loopBackground10;


  public:
    Looper(Hand * h);                       // Declare looper class that will be instantiated
    double computeNextSample();             // Declare function that will compute next sample; to be called from jack_wrapper

};
#endif
