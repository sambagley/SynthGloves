//
#ifndef INSTRUMENT_FINGER_KEYS_H
#define INSTRUMENT_FINGER_KEYS_H
#include "hand.h"
#include "sine.h"
#include "scaleFunctions.hpp"
#include "instrument.h"
class FingerKeys: public Instrument{

private:
  double attackRate;
  double fadeRate;
  std::vector <Sine*>  waves;
  int numWaves;
  double oldFrequency;
  double currentFrequency;
  double targetFrequency;
  double baseWaveAmp;
  double decibels;
  bool thumbPressed;
  bool indexPressed;
  bool middlePressed;
  bool ringPressed;
  bool pinkyPressed;
  char oldState;
  int priorityF;
public:


  FingerKeys(Hand * h);
  double computeNextSample();
  void setVolume(double v);
  void   createHarmonicWaves(int numHarmonics);//don't create more than 5 harmonics
  double changeAllFrequencies(double baseF);
  double runAllWaves();

};
#endif
