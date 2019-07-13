#include "instrument_slide.h"
#define ATTACK_RATE 0.02
#define FADE_RATE 0.002
#define HAND_TILT_OFFSET 20.0
#define PITCH_BEND_COEFFICIENT 0.0222
Slide::Slide(Hand * h)
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
double Slide::computeNextSample()
{

  hand->updateHand();

  int gesture = hand->getGestures();


  //fade out if not playing a note
  if (gesture != 5)
  {
    
    if (decibels > -100.0)
    {
      decibels -= FADE_RATE;
      
    }
    setVolume(decibels);
    return runAllWaves();
  }

   
  if(decibels < -0.00001) {decibels += ATTACK_RATE; setVolume(decibels);}

  //logic for sliding from note to note

  currentFrequency = (double) chooseFromAllScales(0, 440.0, 0, (int) (hand->getYAng()/10.0));

  
  //double vibrato = ( hand->getYAng() + HAND_TILT_OFFSET) * PITCH_BEND_COEFFICIENT;
 
  changeAllFrequencies(currentFrequency );


  return runAllWaves();


}
void Slide::setVolume(double dB)
{
  for(int i = 0; i < numWaves; i++)
  {
    waves[i]->changeVolume(dB);
  }
}
void Slide::createHarmonicWaves(int numHarmonics)
{
  for(int i = 0; i< numHarmonics; i++)
  {
    double amp = 0.5 - (((double) i + 1.0)/5.0) * 0.5;
    int harmonic = 2 + i;
    waves.push_back(new Sine((waves[0]->getFrequency() * (double) harmonic ),amp, 48000));
    numWaves++;
  }
}
double Slide::changeAllFrequencies(double baseF)
{
  for(int i = 0; i < numWaves; i++)
  {
    waves[i]->setFrequency(baseF + baseF * ((double) i));
  }

}
double Slide::runAllWaves()
{
  double val = 0.0;
  for(int i = 0; i < numWaves; i++)
  {
    val += waves[i]->go();
  }
    return val;
}

