#ifndef INSTRUMENT_H
#define INSTRUMENT_H
#include "hand.h"
#include "sine.h"
#include "scaleFunctions.hpp"
#include "/home/pi/SynthGloves/AudioFile/AudioFile.h"


#define STARTING_FREQUENCY 349.23


class Instrument{

protected:
  //typedef double (*ScaleFunctions) (double base_freq, int octave_offset, int note);
  //enum scale {pentatonic, pentatonic_minor, blues, majorS, chromatic, wholeTone};


  Hand * hand;

  double rootFrequency;
  const int theCurrentScaleSetting = 3;
  double outSignal;
  int octave;
  int scaleVal;
  int key;
  int gesture;
  int lastGesture;

  int backgroundLoop = 0;                     // The current loop being played
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


  Instrument(Hand * h);
  virtual double computeNextSample() = 0;
  void setKey(int key);//build key thingy
  void setOctave(int i);
  void setScale(int s);
  //double quantize(int freq, )
  void computeNextBackgroundSample();




};
#endif
