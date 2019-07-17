#include "instrument_chords.h"



Chords::Chords(Hand * h)
  : Instrument(h)
{
	//fill default values
  decibels = 0.0;
  baseWaveAmp = 0.5;
  numWaves = 5;

  octave = -1;
  offsetTilt = 0.0;
  //create wave(s) for 1st 3rd 5th 7th and 8th
  waves.push_back(new Sine(STARTING_FREQUENCY,0.2,48000));
  waves.push_back(new Sine(STARTING_FREQUENCY,0.2,48000));
  waves.push_back(new Sine(STARTING_FREQUENCY,0.2,48000));
  waves.push_back(new Sine(STARTING_FREQUENCY,0.2,48000));
  waves.push_back(new Sine(STARTING_FREQUENCY,0.2,48000));
}
/***************************************************
* updates the hand, then computes frequency for chord that
* is mapped to the current hand gesture.
*
*
*
* Returns the next value to for the waveform.
*
*
********************************************************/
double Chords::computeNextSample()
{
  lastGesture = gesture;
  hand->updateHand();
  gesture = hand->getGestures();

  computeNextBackgroundSample();


  if (gesture == 0) // quickly fade to silence if no gesture is detected
  {
    if (decibels > -100.0)
    {
      decibels -= 0.01;

    }
    setVolume(decibels);
    return ((runAllWaves() / 2) + nextBackgroundSample);
  }
  int chordIndex = gesture;

  if(decibels < -0.00001) {decibels += 0.01; setVolume(decibels);} //raise volume back up

  int chordType = 0;
  if ( hand->getXAng() < +20.0)  //make minor chord if hand is tilted
  {
    chordType = 1;
  }
  
  if(lastGesture != gesture)
  {
     offsetTilt = hand->getYAng();
  }		
  
  double vibrato = ( hand->getYAng() - offsetTilt)* 0.01;//the + 20 is for default hand posture offset

  currentFrequency = rootFrequency * pow(2.0, (-vibrato)/12.0);

  findChordNotes(chordIndex, chordType);


  return ((runAllWaves() / 2) + nextBackgroundSample);



}
/***************************************************
*Raise or lower the volume between -100 (off) and 0.0
* (initial amplitude of the wave) dB.
*
*
********************************************************/
void Chords::setVolume(double dB)
{
  for(int i = 0; i < numWaves; i++)
  {
    waves[i]->changeVolume(dB);
  }
}
/***************************************************
* Goes through each wave that we have put in the vector and
* sums them together
*
*
********************************************************/
double Chords::runAllWaves()
{
  double val = 0.00001;
  for(int i = 0; i < numWaves; i++)
  {
    val += waves[i]->go();
  }
    return val;
}


/***************************************************
* findChordNotes is used to set all frequencies of the waves
* for a given chord.
* parameters are the chord number, and the type of chord,
* major, minor, etc.
*
*
********************************************************/
void Chords::findChordNotes(int chordIndex, int type)
{
	double t; //variable for temporary
	int voiceOne;
	int voiceTwo;
	int voiceThree;
	int voiceFour;
	int voiceFive;
	/*chordIndex is based off chord numbers
	 * 0 = root, don't use
	 * 1 = root
	 * 2 = II
	 * 3 = III
	 * 4 = IV
	 * 5 = V
	 * 6 = VI
	 * 7 = VII
	 * 8 = root up one octave
	 *
	 * Table for chord types:
	 * 0 major
	 * 1 minor
	 * 2 dominant 7
	 */
	 switch (chordIndex){
		case 1:
		voiceOne = 0;
		voiceTwo = 4;
		voiceThree = 7;
		voiceFour = 12;
		voiceFive = -12;
		break;
		case 2:
		voiceOne = 2;
		voiceTwo = 6;
		voiceThree = 9;
		voiceFour = 14;
		voiceFive = -10;
		break;
		case 3:
		voiceOne = 4;
		voiceTwo = 8;
		voiceThree = 11;
		voiceFour = 16;
		voiceFive = -8;
		break;
		case 4:
		voiceOne = 5;
		voiceTwo = 9;
		voiceThree = 12;
		voiceFour = 17;
		voiceFive = -7;
		break;
		case 5:
		voiceOne = 7;
		voiceTwo = 11;
		voiceThree = 14;
		voiceFour = 19;
		voiceFive = -5;
		break;
		case 6:
		voiceOne = 9;
		voiceTwo = 13;
		voiceThree = 16;
		voiceFour = 21;
		voiceFive = -3;
		break;
		case 7:
		voiceOne = 11;
		voiceTwo = 15;
		voiceThree = 18;
		voiceFour = 23;
		voiceFive = -1;
		break;
		case 8:
		voiceOne = 12;
		voiceTwo = 16;
		voiceThree = 19;
		voiceFour = 24;
		voiceFive = 0;
		break;
		default:
		voiceOne = 0;
		voiceTwo = 4;
		voiceThree = 7;
		voiceFour = 12;
		voiceFive = -12;
		break;
	}





	switch (type){
		case 0:
		break;
		case 1:
		voiceTwo -= 1; //minor
		break;
		case 2:
		voiceFour -= 1; //dominant seventh
		default:
		break;

	}


	t = chromatic(currentFrequency, octave, voiceOne);
	waves[0]->setFrequency(t);
	t = chromatic(currentFrequency, octave, voiceTwo);
	waves[1]->setFrequency(t);
	t = chromatic(currentFrequency, octave, voiceThree);
	waves[2]->setFrequency(t);
	t = chromatic(currentFrequency, octave, voiceFour);
	waves[3]->setFrequency(t);
	t = chromatic(currentFrequency, octave, voiceFive);
	waves[4]->setFrequency(t);



}
