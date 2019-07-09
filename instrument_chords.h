//
#ifndef INSTRUMENT_CHORDS_H
#define INSTRUMENT_CHORDS_H
//#include "hand.h"
//#include "sine.h"
//#include "scaleFunctions.hpp"
#include "instrument_finger_keys.h"
class Chords: public Instrument{



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


  Chords(Hand * h);
  double computeNextSample();
  void setVolume(double v);
  void   createHarmonicWaves(int numHarmonics);//don't create more than 5 harmonics
  double changeAllFrequencies(double baseF);
  double runAllWaves();
  void findChordNotes(int chordIndex, int types);
};
#endif
