#ifndef INSTRUMENT_SAX_H
#define INSTRUMENT_SAX_H
#include "hand.h"
#include "sine.h"
#include "scaleFunctions.hpp"
#include "instrument.h"
class Sax: public Instrument{

private:
  std::vector <Sine*>  waves;
  int numWaves;
  double oldFrequency;
  double currentFrequency;
  double targetFrequency;
  double baseWaveAmp;
  double decibels;
  Hand * rightHand;
public:


  Sax(Hand * h);
  void addSecondHand(Hand * h);
  double computeNextSample();
  void setVolume(double v);
  void   createHarmonicWaves(int numHarmonics);//don't create more than 5 harmonics
  double changeAllFrequencies(double baseF);
  double runAllWaves();

};
#endif
