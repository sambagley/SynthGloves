//
//  scaleFunctions.cpp
//
//
//  Created by Sam Bagley on 6/14/19.
//

#include "scaleFunctions.hpp"

double chooseFromAllScales(int index, double base_freq, int octave_offset, int note)
{
  switch (index) {
    case 0: return pentatonic(base_freq, octave_offset, note);
    case 1: return pentatonic_minor(base_freq, octave_offset, note);
    case 2: return blues(base_freq, octave_offset, note);
    case 3: return majorS(base_freq, octave_offset, note);
    case 4: return chromatic(base_freq, octave_offset, note);
    case 5: return wholeTone(base_freq, octave_offset, note);
    default : return 0;
  }
}
double pentatonic(double base_freq, int octave_offset, int note)
{   int index;
    int offset;
    int mapping [] = {0, 2, 4, 7, 9};
    double adjusted_freq = base_freq;
    //This if statement corrects for negative numbers
    //there is definitely a better way to do this but this works for now.
    if (note < 0)
    {
        index = abs((5 + (note % 5))%5);
        offset = note % 5 == 0 ? octave_offset + (note / 5)  : octave_offset + (note / 5) -1 ; //get total offset
    }
    else
    {
        index = note % 5;
        offset = octave_offset + (note / 5); //get total offset
    }

    adjusted_freq *= pow(pow( 2.0, ((double) mapping[index])), (1.0/12.0)); //compute relative pitch
    return adjusted_freq * pow( 2.0, ((double) offset)); //adjust octave

}
double pentatonic_minor(double base_freq, int octave_offset, int note)
{
    int index;
    int offset;
    int mapping [] = {0, 3, 5, 7, 10};
    double adjusted_freq = base_freq;
    //This if statement corrects for negative numbers
    //there is definitely a better way to do this but this works for now.
    if (note < 0)
    {
        index = abs((5 + (note % 5))%5);
        offset = note % 5 == 0 ? octave_offset + (note / 5)  : octave_offset + (note / 5) -1 ; //get total offset
    }
    else
    {
        index = note % 5;
        offset = octave_offset + (note / 5); //get total offset
    }

    adjusted_freq *= pow(pow( 2.0, ((double) mapping[index])), (1.0/12.0)); //compute relative pitch
    return adjusted_freq * pow( 2.0, ((double) offset)); //adjust octave

}
double blues(double base_freq, int octave_offset, int note)
{
  const short SCALE_SIZE = 6;
    int index;
    int offset;
    int mapping [] = {0, 3, 5, 6, 7, 10};
    double adjusted_freq = base_freq;
    //This if statement corrects for negative numbers
    //there is definitely a better way to do this but this works for now.
    if (note < 0)
    {
        index = abs((SCALE_SIZE + (note % SCALE_SIZE))%SCALE_SIZE);
        offset = note % SCALE_SIZE == 0 ? octave_offset + (note / SCALE_SIZE)  : octave_offset + (note / SCALE_SIZE) -1 ; //get total offset
    }
    else
    {
        index = note % SCALE_SIZE;
        offset = octave_offset + (note / SCALE_SIZE); //get total offset
    }

    adjusted_freq *= pow(pow( 2.0, ((double) mapping[index])), (1.0/12.0)); //compute relative pitch
    return adjusted_freq * pow( 2.0, ((double) offset)); //adjust octave

}
double majorS(double base_freq, int octave_offset, int note)
{
    const short SCALE_SIZE = 7;
    int index;
    int offset;
    int mapping [] = {0, 2, 4, 5, 7, 9, 11};
    double adjusted_freq = base_freq;
    //This if statement corrects for negative numbers
    //there is definitely a better way to do this but this works for now.
    if (note < 0)
    {
        index = abs((SCALE_SIZE + (note % SCALE_SIZE))%SCALE_SIZE);
        offset = note % SCALE_SIZE == 0 ? octave_offset + (note / SCALE_SIZE)  : octave_offset + (note / SCALE_SIZE) -1 ; //get total offset
    }
    else
    {
        index = note % SCALE_SIZE;
        offset = octave_offset + (note / SCALE_SIZE); //get total offset
    }

    adjusted_freq *= pow(pow( 2.0, ((double) mapping[index])), (1.0/12.0)); //compute relative pitch
    return adjusted_freq * pow( 2.0, ((double) offset)); //adjust octave
  }
double chromatic(double base_freq, int octave_offset, int note)
{
    double adjusted_freq = base_freq;
    int offset = octave_offset + (note / 12); //get total offset
    adjusted_freq *= pow(pow( 2.0, ((double) (note % 12))), (1.0/12.0)); //compute relative pitch
    return adjusted_freq * pow( 2.0, ((double) offset)); //multiply

}
double wholeTone(double base_freq, int octave_offset, int note)
{
  const short SCALE_SIZE = 6;
  int index;
  int offset;
  int mapping [] = {0, 2, 4, 6, 8, 10};
  double adjusted_freq = base_freq;
  //This if statement corrects for negative numbers
  //there is definitely a better way to do this but this works for now.
  if (note < 0)
  {
      index = abs((SCALE_SIZE + (note % SCALE_SIZE))%SCALE_SIZE);
      offset = note % SCALE_SIZE == 0 ? octave_offset + (note / SCALE_SIZE)  : octave_offset + (note / SCALE_SIZE) -1 ; //get total offset
  }
  else
  {
      index = note % SCALE_SIZE;
      offset = octave_offset + (note / SCALE_SIZE); //get total offset
  }

  adjusted_freq *= pow(pow( 2.0, ((double) mapping[index])), (1.0/12.0)); //compute relative pitch
  return adjusted_freq * pow( 2.0, ((double) offset)); //adjust octave
}
double twoNoteTransition(double startingFreq ,double targetFreq,int millisToTravel,double lastOutputGenerated)
{
    const int SAMPLERATE = 48000;
    double steps =  (double) SAMPLERATE ;
    
    if (fabs(lastOutputGenerated - targetFreq) < 0.5)
        return targetFreq;
    else
        return lastOutputGenerated * pow(2.0, ((1.0/steps)/(log2(targetFreq/startingFreq))));
       
}

