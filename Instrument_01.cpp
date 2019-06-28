#include "Instrument_01.h"



FingerKeys::FingerKeys(Hand * h)
{
  this->hand = h;
  basicSine = new Sine(440.0,  0.5, 48000);

}
void FingerKeys::computeNextSample()
{
  int i = 0;
  //update Hand
  hand->update();
  //find out our pose
  basicSine->setAmplitude(0.5);

  if(hand.->getThumb() < 1500)
  {
    i = 0;
  }
  else if (hand->getIndex() < 1500)
  {
    i = 1;
  }
  else if (hand->getMiddle() < 1500)
  {
    i = 2;
  }
  else if (hand->getRing() < 1500)
  {
    i = 3;
  }
  else if (hand->getPinky() < 400)
  {
    i = 4 ;
  }
  else
  {
    basicSine->setAmplitude(0.0);
  }
  basicSine->setFrequency(double chooseFromAllScales(theCurrentScaleSetting, 440.0, 0, i));

}
void FingerKeys::updateOnly()
{

}
void FingerKeys::setKey(int key)
{


}
void FingerKeys::setOctave(int o)
{


}
void FingerKeys::setScale(int s)
{


}
Sine * FingerKeys::getSineWaveToLink()
{
  return basicSine;
}
