#include "Instrument_01.h"



FingerKeys::FingerKeys(Hand * h)
  : Instrument(h)
{
  volume = 0.5;
  attackRate = 0.0001;
  fadeRate = 1.00005;
  waves.push_back(new Sine(440.0,0.5,48000));
  currentFrequency = 440.0;
  oldFrequency = 440.0;
  targetFrequency = 440.0;
  numWaves = 1;
  createHarmonicWaves(3);
}
double FingerKeys::computeNextSample()
{

  currentFrequency = waves[0]->getFrequency();
 
  int i = 0;

  hand->updateHand();

  if (volume <= 0.0001)
  {
      volume = 0.0001;
      setVolume(volume);
  }
  
  //check each finger for triggering

  if(200 < hand->getThumb() && hand->getThumb() < 1500)  { i = 0; }
 
  else if (200 < hand->getIndex() && hand->getIndex() < 1500)  { i = 1; }

  else if (200 < hand->getMiddle() && hand->getMiddle()< 1500)  { i = 2; }

  else if (200 < hand->getRing() && hand->getRing() < 1500)    { i = 3; }

  else if (200 < hand->getPinky() && hand->getPinky() < 400)   { i = 4 ; }

  else //turn the volume reaaal low 
  {
    volume = 0.00001;
   // setVolume(waves[0]->getAmplitude() * 0.9999);
    return runAllWaves();
  }

    if(volume < 0.5) {volume *= 1.0001; setVolume(volume);}
  
  //logic for sliding from note to note 
  
  double newTargetFrequency = (double) chooseFromAllScales(theCurrentScaleSetting, 440.0, 0, i);
  
  if (fabs(targetFrequency - newTargetFrequency) > 0.1)
  {
    oldFrequency = currentFrequency;
    targetFrequency = newTargetFrequency;
  }
 
  currentFrequency = twoNoteTransition(oldFrequency, targetFrequency, 1000, currentFrequency);
  
  if (fabs(currentFrequency - targetFrequency) < 0.2)
  {
    currentFrequency = targetFrequency;
  }
  
  
  //double vibrato = ((double) hand->getYAng() )* 0.01;
  changeAllFrequencies(currentFrequency);

  
  return runAllWaves() * volume;


}
double FingerKeys::getVolume()
{
  return volume;
}
void FingerKeys::setVolume(double v)
{
  
  for(int i = 0; i < numWaves; i++)
  {
    double amp = v - (((double) i)/5.0) * 0.5;
    waves[i]->setAmplitude(amp);
  }
}

void FingerKeys::createHarmonicWaves(int numHarmonics)
{
  for(int i = 0; i< numHarmonics; i++)
  {
    double amp = 0.5 - (((double) i)/5.0) * 0.5;
    int harmonic = 2 + i;
    waves.push_back(new Sine((waves[0]->getFrequency() * (double) harmonic ),amp, 48000));
    numWaves++;
  }
}
double FingerKeys::changeAllFrequencies(double baseF)
{
  for(int i = 0; i < numWaves; i++)
  {
    waves[i]->setFrequency(baseF + baseF * ((double) i));
  }
    
}
double FingerKeys::runAllWaves()
{
  double val = 0.0;
  for(int i = 0; i < numWaves; i++)
  {
    val += waves[i]->go();
  }
    return val;
}
