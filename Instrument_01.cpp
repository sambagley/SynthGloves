#include "Instrument_01.h"



FingerKeys::FingerKeys(Hand * h)
  : Instrument(h)
{
  volume = 0.0;
  attackRate = 0.0001;
  fadeRate = 1.00005;
  basicSine = new Sine(440.0, 0.5, 48000);
}
double FingerKeys::computeNextSample()
{

  double frequency = 0;
  int i = 0;
  //update Hand
  hand->updateHand();
  //find out our pose


  if(200 < hand->getThumb() && hand->getThumb() < 1500)
  {
    i = 0;
    volume += volume < 0.5 ? volume + 0.002 : volume;
    basicSine->setAmplitude(volume);
  }
  else if (200 < hand->getIndex() && hand->getIndex() < 1500)
  {
    i = 1;
    volume += volume < 0.5 ? volume + 0.002 : volume;
    basicSine->setAmplitude(volume);
  }
  else if (200 < hand->getMiddle() && hand->getMiddle()< 1500)
  {
    i = 2;
    volume += volume < 0.5 ? volume + 0.002 : volume;
    basicSine->setAmplitude(volume);
  }
  else if (200 < hand->getRing() && hand->getRing() < 1500)
  {
    i = 3;
    volume += volume < 0.5 ? volume + 0.002 : volume;
    basicSine->setAmplitude(volume);
  }
  else if (200 < hand->getPinky() && hand->getPinky() < 400)
  {
    i = 4 ;
    volume += volume < 0.5 ? volume + 0.002 : volume;
    basicSine->setAmplitude(volume);
  }
  else
  {
    basicSine->setAmplitude(basicSine->getAmplitude()/fadeRate);
    //basicSine->setFrequency(basicSine->getFrequency()/fadeRate);
    return basicSine->go();
  }
  frequency = (double) chooseFromAllScales(theCurrentScaleSetting, 440.0, 0, i);
  double temp = ((double) hand->getYAng() )* 0.03;
  frequency *= pow(2, (temp/12.0)); //compute relative pitch

  basicSine->setFrequency(frequency);
  return basicSine->go();





}
void FingerKeys::updateOnly()
{

}
