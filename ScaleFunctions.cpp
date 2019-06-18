//
//  ScaleFunctions.cpp
//  
//
//  Created by Sam Bagley on 6/14/19.
//

#include "ScaleFunctions.hpp"


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
    
    /*
     may have found an easier way
    switch (note % 6) {
        case 0:
           //do nothing
            break;
        case 1:
            adjusted_freq *= pow(pow( 2, (note % 6)), (1.0/12.0));
            break;
        case 2:
            adjusted_freq *= pow(16.0, (1.0/12.0));
            break;
        default:
            break;
    }*/
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
    int index;
    int offset;
    int mapping [] = {0, 3, 5, 6, 7, 10};
    double adjusted_freq = base_freq;
    //This if statement corrects for negative numbers 
    //there is definitely a better way to do this but this works for now.
    if (note < 0)
    {   
        index = abs((6 + (note % 6))%6);
        offset = note % 6 == 0 ? octave_offset + (note / 6)  : octave_offset + (note / 6) -1 ; //get total offset
    }
    else 
    {
        index = note % 6;
        offset = octave_offset + (note / 6); //get total offset
    }
    
    adjusted_freq *= pow(pow( 2.0, ((double) mapping[index])), (1.0/12.0)); //compute relative pitch
    return adjusted_freq * pow( 2.0, ((double) offset)); //adjust octave 
 
}
double majorS(double base_freq, int octave_offset, int note)
{
    return 0.0;
}
double chromatic(double base_freq, int octave_offset, int note)
{
    double adjusted_freq = base_freq;
    int offset = octave_offset + (note / 12); //get total offset
    adjusted_freq *= pow(pow( 2.0, ((double) (note % 12))), (1.0/12.0)); //compute relative pitch
    return adjusted_freq * pow( 2.0, ((double) offset)); //multiply
    
}
