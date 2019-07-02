//
#ifndef INSTRUMENT_H
#define INSTRUMENT_H
#include "Hand.h"
#include "sine.h"
#include "scaleFunctions.hpp"
#include "instrument.h"
class FingerKeys: public Instrument{

private:

  //Sine * basicSine; // will make into a more dynamic sound later

public:


  FingerKeys(Hand * h);
  double computeNextSample();
  void updateOnly();//actually not that useful when I think about it



};
#endif
