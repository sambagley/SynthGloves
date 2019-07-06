#include "Instrument_01.h"



Instrument::Instrument(Hand * h)
{
  this->hand = h;
  key = 0;
  rootFrequency = 440.0;
  octave = 0;
}

void Instrument::setKey(int k)
{
  key = k;
 switch (k){
   case -12 : 
    rootFrequency = 220.0;
    break;
   case -11 :
    rootFrequency = 233.08;
    break;
   case -10 :
    rootFrequency = 246.94;
    break;
   case -9 :
    rootFrequency = 261.63;
    break;
   case -8 :
    rootFrequency = 277.18;
    break;
   case -7 :
    rootFrequency = 293.66;
    break;
   case -6 :
    rootFrequency = 311.13;
    break;
   case -5 :
    rootFrequency = 329.63;
    break;
   case -4 :
    rootFrequency = 349.23;
    break;
   case -3 :
    rootFrequency = 369.99;
    break;
   case -2 :
      rootFrequency = 392.00;
    break;
   case -1 :
    rootFrequency = 415.30;
    break;
   case 0 :
    rootFrequency = 440.0;
    break;
   case 1 :
    rootFrequency = 466.16;
    break;
   case 2 :
    rootFrequency = 493.88;
    break;
   case 3 :
    rootFrequency = 523.25;
    break;
   case 4 :
    rootFrequency = 554.37;
    break;
   case 5 :
    rootFrequency = 587.33;
    break;
   case 6 :
   rootFrequency = 622.25;
    break;
   case 7 :
    rootFrequency = 659.25;
    break;
   case 8 :
    rootFrequency = 698.46;
    break;
   case 9 :
    rootFrequency = 739.99;
    break;
   case 10 :
   rootFrequency = 783.99;
    break;
   case 11 :
    rootFrequency = 830.61;
    break;
   case 12 : 
    rootFrequency = 880.0;
    break;
   default:
    rootFrequency = 440.0;
    break;
}



}
void Instrument::setOctave(int o)
{
  octave = o;

}
void Instrument::setScale(int s)
{
  scaleVal = s;

}


