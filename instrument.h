#include "Hand.h"
#include "sine.h"
#include "scaleFunctions.hpp"


class Instrument{

protected:

  
  //typedef double (*ScaleFunctions) (double base_freq, int octave_offset, int note);
  //enum scale {pentatonic, pentatonic_minor, blues, majorS, chromatic, wholeTone};


  Hand * hand;
  
  double rootFrequency;
  const int theCurrentScaleSetting = 5;
  double outSignal;
  int octave;
  int scaleVal; 
  int key;

public:


  Instrument(Hand * h);
  virtual double computeNextSample() = 0;
  void setKey(int key);//build key thingy
  void setOctave(int i);
  void setScale(int s);
  



};
