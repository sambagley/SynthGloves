#include "Instrument_03.h"



Chords::Chords(Hand * h)
  : Instrument(h)
{
	//fill default values
  decibels = 0.0;
  baseWaveAmp = 0.5;
  attackRate = 0.0001;
  fadeRate = 1.00005;
  currentFrequency = 440.0;
  oldFrequency = 440.0;
  targetFrequency = 440.0;
  numWaves = 5;
  //createHarmonicWaves(3);
  oldState = 0b00000000;
  priorityF  = 0;
  thumbPressed = 0;
  indexPressed = 1;
  middlePressed = 2;
  ringPressed = 3;
  pinkyPressed = 4;
  
  
  //create wave(s) for 1st 3rd 5th 7th and 8th
  waves.push_back(new Sine(440.0,0.2,48000));
  waves.push_back(new Sine(440.0,0.2,48000));
  waves.push_back(new Sine(440.0,0.2,48000));
  waves.push_back(new Sine(440.0,0.2,48000));
  waves.push_back(new Sine(440.0,0.2,48000));	
}
double Chords::computeNextSample()
{
 hand->updateHand();
 
 
 if (200 < hand->getThumb() && hand->getThumb() < 400)
	findChordNotes(1,0);
 else
	findChordNotes(1,1);
 return runAllWaves();
 
 char newState = 0b00000000;


  //check each finger for triggering
/*
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

  currentFrequency = twoNoteTransition(oldFrequency, targetFrequency, 1000, currentFrequency);

  if (fabs(currentFrequency - targetFrequency) < 0.2)
  {
    currentFrequency = targetFrequency;
  }

  
  double vibrato = ((double) hand->getYAng() )* 0.01;
 
  changeAllFrequencies(currentFrequency *  pow(2.0, vibrato/12.0));


  return runAllWaves();
*/

}
void Chords::setVolume(double dB)
{
  for(int i = 0; i < numWaves; i++)
  {
    waves[i]->changeVolume(dB);
  }
}
void Chords::createHarmonicWaves(int numHarmonics)
{
  for(int i = 0; i< numHarmonics; i++)
  {
    double amp = 0.5 - (((double) i + 1.0)/5.0) * 0.5;
    int harmonic = 2 + i;
    waves.push_back(new Sine((waves[0]->getFrequency() * (double) harmonic ),amp, 48000));
    numWaves++;
  }
}
double Chords::changeAllFrequencies(double baseF)
{
  for(int i = 0; i < numWaves; i++)
  {
    waves[i]->setFrequency(baseF + baseF * ((double) i));
  }

}
double Chords::runAllWaves()
{
  double val = 0.0;
  for(int i = 0; i < numWaves; i++)
  {
    val += waves[i]->go();
  }
    return val;
}
void Chords::findChordNotes(int chordIndex, int type)
{
	double t;
	/*chordIndex is based off chord numbers
	 * 0 = root, don't use
	 * 1 = root
	 * 2 = II
	 * 3 = III
	 * 4 = IV
	 * 5 = V
	 * 6 = VI
	 * 7 = VII
	 * 8 = root, don't use
	 * 
	 * Table for chord types:
	 * 0 major
	 * 1 minor
	 * 2 dominant 7
	 */
	 switch (chordIndex){
		case 1:
			t = chromatic(220.0, octave, 0);
			waves[0]->setFrequency(t);
			t = chromatic(220.0, octave, 4);
			waves[1]->setFrequency(t);
			t = chromatic(220.0, octave, 7);
			waves[2]->setFrequency(t);
			t = chromatic(220.0, octave, 12);
			waves[3]->setFrequency(t);
			t = chromatic(220.0, octave-1, 0);
			waves[4]->setFrequency(t);
			
		
		break;
		/*
		case 2:
		break;
		case 3:
		break;
		case 4:
		break;
		case 5:
		break;
		case 6:
		break;
		case 7:
		break;
		case 8:
		break;
		* */
		default:
		break;
	}
	switch (type){
		case 0:
		break;
		case 1:
			t = chromatic(waves[1]->getFrequency(), octave, -1);
			waves[1]->setFrequency(t);
		break;
		
	}
	 
	 
}
