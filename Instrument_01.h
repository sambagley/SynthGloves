//
#ifndef INSTRUMENT_01_H
#define INSTRUMENT_01_H
#include "Hand.h"
#include "sine.h"
#include "scaleFunctions.hpp"
class FingerKeys{

private:


  typedef double (*ScaleFunctions) (double base_freq, int octave_offset, int note);
  enum scale {pentatonic, pentatonic_minor, blues, majorS, chromatic, wholeTone};


  Hand * hand;
  Sine * basicSine; // will make into a more dynamic sound later
  double frequency;
  double volume;
  int theCurrentScaleSetting;
  double outSignal;

public:


  FingerKeys(Hand * h);
  FingerKeys();
  void computeNextSample();
  void updateOnly();
  void setKey(int key);//build key thingy
  void setOctave(int i);
  void setScale(int s);
  Sine * getSineWaveToLink();



};
#endif
