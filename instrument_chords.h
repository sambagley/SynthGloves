//
#ifndef INSTRUMENT_CHORDS_H
#define INSTRUMENT_CHORDS_H
//#include "hand.h"
//#include "sine.h"
//#include "scaleFunctions.hpp"
#include "instrument.h"
class Chords: public Instrument{



private:
  std::vector <Sine*>  waves;
  int numWaves;
  double baseWaveAmp;
  double decibels;
  double currentFrequency;
  double offsetTilt;
public:


  Chords(Hand * h);
  double computeNextSample();
  void setVolume(double v);
  double runAllWaves();
  void findChordNotes(int chordIndex, int types);
};
#endif
