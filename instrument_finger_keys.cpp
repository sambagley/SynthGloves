#include "instrument_finger_keys.h"



FingerKeys::FingerKeys(Hand * h)
  : Instrument(h)
{
  decibels = 0.0;
  baseWaveAmp = 0.5;
  attackRate = 0.0001;
  fadeRate = 1.00005;
  waves.push_back(new Sine(440.0,0.5,48000));
  currentFrequency = 440.0;
  oldFrequency = 440.0;
  targetFrequency = 440.0;
  numWaves = 1;
  createHarmonicWaves(3);
  oldState = 0b00000000;
  priorityF  = 0;
  thumbPressed = 0;
  indexPressed = 1;
  middlePressed = 2;
  ringPressed = 3;
  pinkyPressed = 4;
}
double FingerKeys::computeNextSample()
{

  char newState = 0b00000000;

 

  hand->updateHand();



  //check each finger for triggering

  if (200 < hand->getThumb() && hand->getThumb() < 400)   
  { 
    if(thumbPressed == 0)
      priorityF = 0;
    newState |= 0b00000001;
    thumbPressed = 1;
  }
  else
   {
     thumbPressed = 0;
   }
   if (200 < hand->getIndex() && hand->getIndex() < 1500) 
   { 
     if(indexPressed == 0)
      priorityF = 1;
     newState |= 0b00000010;
     indexPressed = 1;
     }
   else
   {
     indexPressed = 0;
   }
   if (200 < hand->getMiddle() && hand->getMiddle()< 1500) 
   { 
     if(middlePressed == 0)
      priorityF = 2; 
     newState |= 0b00000100;
     middlePressed = 1;
   }
    else
   {
     middlePressed = 0;
   }
   if (200 < hand->getRing() && hand->getRing() < 1500)  
   { 
     if(ringPressed == 0)
      priorityF = 3;
     newState |= 0b00001000;
     ringPressed = 1;
   }
    else 
    {
      ringPressed = 0 ;
    }
   if (200 < hand->getPinky() && hand->getPinky() < 1500) 
   {
      if(pinkyPressed == 0)
        priorityF = 4;
      newState |= 0b00010000;
      pinkyPressed = 1;
   }
    else
    {
      pinkyPressed = 0;
    }
     if (newState > oldState)
    {
      oldState = newState;
      //if the last button pressed was not pressed last time , make it the new one 
       
    }
  if (newState == 0b00000000) //turn the volume real low
  {
    
    if (decibels > -100.0)
    {
      decibels -= 0.01;
      
    }
    setVolume(decibels);
    return runAllWaves();
  }

   
    if(decibels < -0.00001) {decibels += 0.01; setVolume(decibels);}

  //logic for sliding from note to note

  double newTargetFrequency = (double) chooseFromAllScales(theCurrentScaleSetting, 440.0, 0, priorityF);

  if (fabs(targetFrequency - newTargetFrequency) > 0.1)
  {
    oldFrequency = currentFrequency;
    targetFrequency = newTargetFrequency;
  }

  currentFrequency = twoNoteTransition(oldFrequency, targetFrequency, 2000, currentFrequency);

  if (fabs(currentFrequency - targetFrequency) < 0.2)
  {
    currentFrequency = targetFrequency;
  }

  
  double vibrato = ( hand->getYAng() + 20.0 )* 0.01;//the + 20 is for default hand posture offset
 
  changeAllFrequencies(currentFrequency *  pow(2.0, (-vibrato)/12.0));


  return runAllWaves();


}
void FingerKeys::setVolume(double dB)
{
  for(int i = 0; i < numWaves; i++)
  {
    waves[i]->changeVolume(dB);
  }
}
void FingerKeys::createHarmonicWaves(int numHarmonics)
{
  for(int i = 0; i< numHarmonics; i++)
  {
    double amp = 0.5 - (((double) i + 1.0)/5.0) * 0.5;
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

