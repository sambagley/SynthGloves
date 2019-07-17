#include "instrument_sax.h"
#define ATTACK_RATE 0.02
#define FADE_RATE 0.002
#define HAND_TILT_OFFSET 20.0
#define PITCH_BEND_COEFFICIENT 0.0222
Sax::Sax(Hand * h)
  : Instrument(h)
{
  decibels = 0.0;
  baseWaveAmp = 0.5;
  playingNote = 0;
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
void Sax::addSecondHand(Hand * h)
{
  rightHand = h;
}
double Sax::computeNextSample()
{
  rightHand->updateHand();

  hand->updateHand();
 
  short newState = 0b00000000000;
  bool octaveKeyPressed = 0;
  bool playKey = 0;
	 if (hand->getThumb() > 200 && hand->getThumb() < 400)
      octaveKeyPressed = 1;
   if (hand->getIndex() >  200 && hand->getIndex()  < 1500)
      newState |= 0b0000100000000;
   if (hand->getMiddle() > 200 && hand->getMiddle() < 1500)
      newState |= 0b0000010000000;
   if (hand->getRing() > 200 && hand->getRing() < 1420)
      newState |= 0b0000001000000;
   //if (hand->getPinky() > 200 && hand->getPinky() < 1500)
      //newState |= 0b0000000100000;
   if (rightHand->getThumb() > 200 && rightHand->getThumb() < 400)
      playKey = 1;
   if (rightHand->getIndex() >  200 && rightHand->getIndex()  < 1500)
      newState |= 0b0000000001000;
   if (rightHand->getMiddle() > 200 && rightHand->getMiddle() < 1500)
      newState |= 0b0000000000100;
   if (rightHand->getRing() > 200 && rightHand->getRing() < 1420)
      newState |= 0b0000000000010;
   if (rightHand->getPinky() > 200 && rightHand->getPinky() < 1500)
      newState |= 0b0000000000001;

int note;

switch (newState){
  case 0b0111001111:
  note = 1;
  break;
  case 0b0111001110:
  note = 2;
  break;
  case 0b0111001100:
  note = 3;
  break;
  case 0b0111001000:
  note = 4;
  break;
  case 0b0111000000:
  note = 5;
  break;
  case 0b0110000000:
  note = 6;
  break;
  case 0b0100000000:
  note = 7;
  break;
  case 0b0010000000:
  note = 8;
  break;
  //case 0b0010000000:
  //note = 8;
  //break;
  default:
   note = 0;
  }

  
  if (note != 0)
  {
    playingNote = note;
  }


  //fade out if not playing a note
  if (playKey == 0)
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

currentFrequency = (double) chooseFromAllScales(theCurrentScaleSetting, 440.0, -1 +(int) octaveKeyPressed, playingNote-1);
/*
  if (fabs(targetFrequency - newTargetFrequency) > 0.5)
  {
    oldFrequency = currentFrequency;
    targetFrequency = newTargetFrequency;
  }

  currentFrequency = twoNoteTransition(oldFrequency, targetFrequency, 2000, currentFrequency);

  if (fabs(currentFrequency - targetFrequency) < 0.5)
  {
    currentFrequency = targetFrequency;
  }


  //double vibrato = ( hand->getYAng() + HAND_TILT_OFFSET) * PITCH_BEND_COEFFICIENT;
  //changeAllFrequencies(currentFrequency *  pow(2.0, (-vibrato)/12.0));
*/
  changeAllFrequencies(currentFrequency );


  return runAllWaves();


}
void Sax::setVolume(double dB)
{
  for(int i = 0; i < numWaves; i++)
  {
    waves[i]->changeVolume(dB);
  }
}
void Sax::createHarmonicWaves(int numHarmonics)
{
  for(int i = 0; i< numHarmonics; i++)
  {
    double amp = 0.5 - (((double) i + 1.0)/5.0) * 0.5;
    int harmonic = 2 + i;
    waves.push_back(new Sine((waves[0]->getFrequency() * (double) harmonic ),amp, 48000));
    numWaves++;
  }
}
double Sax::changeAllFrequencies(double baseF)
{
  for(int i = 0; i < numWaves; i++)
  {
    waves[i]->setFrequency(baseF + baseF * ((double) i));
  }

}
double Sax::runAllWaves()
{
  double val = 0.0;
  for(int i = 0; i < numWaves; i++)
  {
    val += waves[i]->go();
  }
    return val;
}
