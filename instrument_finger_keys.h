#ifndef INSTRUMENT_FINGER_KEYS_H
#define INSTRUMENT_FINGER_KEYS_H
#include "hand.h"
#include "sine.h"
#include "scaleFunctions.hpp"
#include "instrument.h"
class FingerKeys: public Instrument{

private:
  std::vector <Sine*>  waves;
  int numWaves;
  double oldFrequency;
  double currentFrequency;
  double targetFrequency;
  double baseWaveAmp;
  double decibels;
  double offsetTilt;
public:


  FingerKeys(Hand * h);
  double computeNextSample();
  void setVolume(double v);
  void   createHarmonicWaves(int numHarmonics);//don't create more than 5 harmonics
  double changeAllFrequencies(double baseF);
  double runAllWaves();

};
#endif
