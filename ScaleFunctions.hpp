//
//  ScaleFunctions.hpp
//  
//
//  Created by Sam Bagley on 6/14/19.
//

#ifndef ScaleFunctions_hpp
#define ScaleFunctions_hpp

#include <stdio.h>
#include <math.h>
double pentatonic(double base_freq, int octave_offset, int note);
double pentatonic_minor(double base_freq, int octave_offset, int note);
double blues(double base_freq, int octave_offset, int note);
double majorS(double base_freq, int octave_offset, int note);
double chromatic(double base_freq, int octave_offset, int note);


#endif /* ScaleFunctions_hpp */
