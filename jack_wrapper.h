#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include <jackaudioio.hpp>
#include "sine.h"
#include <thread>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "instrument_finger_keys.h"
#include "instrument_chords.h"
#include "looping_track.hpp"
#include "hand.h"
//class Instrument;

class JackWrapper: public JackCpp::AudioIO {

private:
   Instrument * i1;
   Instrument * i2;
   Instrument * i3;
   Instrument * i1H2;
   Instrument * i2H2;
   Instrument * i3H2;
   LoopingTrack * track;
   double tempInstSum;
   bool twoHands;
 
   Hand * hand;
   Hand * hand2;
   Instrument * instrumentToPlay;
   Instrument * instrumentToPlay2;

public:
   
    /// Audio Callback Function:
    /// - the output buffers are filled here
    virtual int audioCallback(jack_nframes_t nframes,
                              // A vector of pointers to each input port.
                              audioBufVector inBufs,
                              // A vector of pointers to each output port.
                              audioBufVector outBufs){
                                  
                                  
                                  
                                  

            int instSelect = hand->getButton3Presses() % 3;
        
            if (instSelect == 0)
            {
                instrumentToPlay = i1;
                //std::cerr << "case 1" << std ::endl;
             }   
              
            else if (instSelect == 1) 
            {
                instrumentToPlay = i2;
                //std::cerr << "case 2" << std ::endl;
            }
            
            else
            {
                instrumentToPlay = i3;
                //std::cerr << "case 3" << std ::endl;
            }
            
            if (i1H2)
            {  
                instSelect = hand2->getButton3Presses() % 3;
        
                if (instSelect == 0)
                {
                    instrumentToPlay2 = i1H2;
                    //std::cerr << "case 1" << std ::endl;
                }   
              
                else if (instSelect == 1) 
                {
                    instrumentToPlay2 = i2H2;
                    //std::cerr << "case 2" << std ::endl;
                }
                
                else
                {
                    instrumentToPlay2 = i3H2;
                    //std::cerr << "case 3" << std ::endl;
                }
            }


        /// LOOP over all output buffers
        for(unsigned int i = 0; i < 1; i++)
        {
            for(int frameCNT = 0; frameCNT  < nframes; frameCNT++)
            {
                if (i1H2)
                {
                    outBufs[0][frameCNT] = track->playBack((instrumentToPlay->computeNextSample() + instrumentToPlay2->computeNextSample()) / 2.0) ;
                }
                else
                {
                    outBufs[0][frameCNT] = track->playBack(instrumentToPlay->computeNextSample());
      
                } 
            }
        }
        ///return 0 on success
        return 0;
    }
    /// Constructor
    JackWrapper() :
        JackCpp::AudioIO("SynthGlove", 0,1){

          reserveInPorts(2);
          reserveOutPorts(2);



    }


    //This function will take a pointer and then
    //use it to buffer the sound.
    void addInstrumentOne(Instrument * b)
    {
        if (b != NULL)
        {
            i1 = b;
        }
    }
    void addInstrumentTwo(Instrument * b)
    {
        if (b != NULL)
        {
            i2 = b;
        }
    }
        void addInstrumentThree(Instrument * b)
    {
        if (b != NULL)
        {
            i3 = b;
        }
    }
    void addInstrumentOneHandTwo(Instrument * b)
    {
        if (b != NULL)
        {
            i1H2 = b;
        }
    }
    void addInstrumentTwoHandTwo(Instrument * b)
    {
        if (b != NULL)
        {
            i2H2 = b;
        }
    }
    void addInstrumentThreeHandTwo(Instrument * b)
    {
        if (b != NULL)
        {
            i3H2 = b;
        }
    }
    void addLoopingTrack(LoopingTrack * l)
    {
        track = l;
    }
    void addHand(Hand * h)
    {
        hand = h;
    }
    void addHand2(Hand * h)
    {
        hand2 = h;
    }
};
