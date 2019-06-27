#include "Instrument_01.h"



FingerKeys::FingerKeys(Hand * h)
{
  this->hand = h;
  basicSine = new Sine(440.0,  0.5, 48000);

}
void FingerKeys::computeNextSample()
{
  //update Hand
  hand->update();
  //find out our pose
  //if(hand.->getThumb() == 0)
  {
    basicSine->setFrequency((double) hand->getThumb());
  }
  /*else*/ if (hand->getIndex() == 0)
  {
    basicSine->setFrequency(440.0);
  }
  else if (hand->getMiddle() == 0)
  {

  }
  else if (hand->getRing() == 0)
  {

  }
  else if (hand->getPinky() == 0)
  {

  }
  //play the right sounds


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
