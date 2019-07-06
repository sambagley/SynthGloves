//
#ifndef INSTRUMENT_H
#define INSTRUMENT_H
#include "Hand.h"
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
  double volume;
public:


  FingerKeys(Hand * h);
  double computeNextSample();
  void setVolume(double v);
  double getVolume();
  void   createHarmonicWaves(int numHarmonics);//don't create more than 5 harmonics
  double changeAllFrequencies(double baseF);
  double runAllWaves();

};
#endif
