#include "instrument_finger_keys.h"
#define ATTACK_RATE 0.02
#define FADE_RATE 0.002
#define HAND_TILT_OFFSET 20.0
#define PITCH_BEND_COEFFICIENT 0.0222
FingerKeys::FingerKeys(Hand * h)
  : Instrument(h)
{
  decibels = 0.0;
  baseWaveAmp = 0.5;
  
  //initialize all variables
  currentFrequency = 440.0;
  oldFrequency = 440.0;
  targetFrequency = 440.0;
  
  //create initial wave
  waves.push_back(new Sine(rootFrequency,baseWaveAmp,48000));
  numWaves = 1;
  //add harmonics
  createHarmonicWaves(3);
}

/***************************************************
* updates the hand, then computes frequency for note that 
* is mapped to the current hand gesture. 
* 
* 
* 
* Returns the next value to for the waveform. 
* 
*  
********************************************************/
double FingerKeys::computeNextSample()
{

  hand->updateHand();

  int gesture = hand->getGestures();


  //fade out if not playing a note
  if (gesture == 0)
  {
    
    if (decibels > -100.0)
    {
      decibels -= FADE_RATE;
      
    }
    setVolume(decibels);
    return runAllWaves();
  }
  
   
  if(decibels < -0.00001) 
  {
    decibels += ATTACK_RATE; setVolume(decibels);
  }

  //logic for sliding from note to note

  double newTargetFrequency = (double) chooseFromAllScales(theCurrentScaleSetting, 440.0, 0, gesture-1);

  if (fabs(targetFrequency - newTargetFrequency) > 0.5)
  {
    oldFrequency = currentFrequency;
    targetFrequency = newTargetFrequency;
  }
  //makes the currently playing frequency slide up from the old frequency. 
  currentFrequency = twoNoteTransition(oldFrequency, targetFrequency, 2000, currentFrequency);

  if (fabs(currentFrequency - targetFrequency) < 0.5)
  {
    currentFrequency = targetFrequency;
  }

  
  double vibrato = ( hand->getYAng() + HAND_TILT_OFFSET) * PITCH_BEND_COEFFICIENT;
 
  changeAllFrequencies(currentFrequency *  pow(2.0, (-vibrato)/12.0));


  return runAllWaves();


}
/***************************************************
*Raise or lower the volume between -100 (off) and 0.0
* (initial amplitude of the wave) dB. 
*
*  
********************************************************/
void FingerKeys::setVolume(double dB)
{
  for(int i = 0; i < numWaves; i++)
  {
    waves[i]->changeVolume(dB);
  }
}
/***************************************************
* Creates integer multiple harmonics of the first wave in
* the vector. 
* Each new wave has a lower amplitude. 
* 
* Don't create more than 4 harmonic waves otherwise
* the amplitude will be negative
*
*  
********************************************************/
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
/***************************************************
* Will change each wave's frequency to an integer muliple
* of the base frequency given	
*
*  
********************************************************/
double FingerKeys::changeAllFrequencies(double baseF)
{
  for(int i = 0; i < numWaves; i++)
  {
    waves[i]->setFrequency(baseF + baseF * ((double) i));
  }

}
/***************************************************
* Goes through each wave that we have put in the vector and 
* sums them together	
*
*  
********************************************************/
double FingerKeys::runAllWaves()
{
  double val = 0.0;
  for(int i = 0; i < numWaves; i++)
  {
    val += waves[i]->go();
  }
    return val;
}

