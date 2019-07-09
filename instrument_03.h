//
#ifndef INSTRUMENT_03_H
#define INSTRUMENT_03_H
//#include "Hand.h"
//#include "sine.h"
//#include "scaleFunctions.hpp"
#include "Instrument_01.h"
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
