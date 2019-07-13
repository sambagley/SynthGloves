#ifndef INSTRUMENT_SLIDE_H
#define INSTRUMENT_SLIDE_H
#include "hand.h"
#include "sine.h"
#include "scaleFunctions.hpp"
#include "instrument.h"
class Slide: public Instrument{

private:
  std::vector <Sine*>  waves;
  int numWaves;
  double oldFrequency;
  double currentFrequency;
  double targetFrequency;
  double baseWaveAmp;
  double decibels;
public:


  Slide(Hand * h);
  double computeNextSample();
  void setVolume(double v);
  void   createHarmonicWaves(int numHarmonics);//don't create more than 5 harmonics
  double changeAllFrequencies(double baseF);
  double runAllWaves();

};
#endif
