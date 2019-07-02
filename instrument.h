#include "Hand.h"
#include "sine.h"
#include "scaleFunctions.hpp"


class Instrument{

protected:


  typedef double (*ScaleFunctions) (double base_freq, int octave_offset, int note);
  enum scale {pentatonic, pentatonic_minor, blues, majorS, chromatic, wholeTone};


  Hand * hand;
  Sine * basicSine; // will make into a more dynamic sound later
  double frequency;
  double volume;
  const int theCurrentScaleSetting = 0;
  double outSignal;

public:


  Instrument(Hand * h);
  virtual double computeNextSample() = 0;
  virtual void updateOnly() = 0;//actually not that useful when I think about it
  void setKey(int key);//build key thingy
  void setOctave(int i);
  void setScale(int s);



};
