//
//  scaleFunctions.hpp
//
//
//  Created by Sam Bagley on 6/14/19.
//

#ifndef scaleFunctions_hpp
#define scaleFunctions_hpp

#include <stdio.h>
#include <math.h>




double chooseFromAllScales(int index, double base_freq, int octave_offset, int note);
double pentatonic(double base_freq, int octave_offset, int note);
double pentatonic_minor(double base_freq, int octave_offset, int note);
double blues(double base_freq, int octave_offset, int note);
double majorS(double base_freq, int octave_offset, int note);
double chromatic(double base_freq, int octave_offset, int note);
double wholeTone(double base_freq, int octave_offset, int note);
double twoNoteTransition(double startingFreq,double targetFreq,int millisToTravel,double lastOutputGenerated);   

#endif /* scaleFunctions_hpp */
