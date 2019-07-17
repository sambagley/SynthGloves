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
//class Instrument;

class SimpleSine: public JackCpp::AudioIO {

private:
   Instrument * i1;
   Instrument * i2;
   LoopingTrack * track;
   double tempInstSum;
    
public:
    // FingerKeys *testThing;
    /// Audio Callback Function:
    /// - the output buffers are filled here
    virtual int audioCallback(jack_nframes_t nframes,
                              // A vector of pointers to each input port.
                              audioBufVector inBufs,
                              // A vector of pointers to each output port.
                              audioBufVector outBufs){

        //sines[0]->setFrequency(440.0);
         //setWaveFrequency(0, (double) lefty->getMiddle());

        /// LOOP over all output buffers
        for(unsigned int i = 0; i < 1; i++)
        {
            for(int frameCNT = 0; frameCNT  < nframes; frameCNT++)
            {
                //sines[0]->setAmplitude(sines[0]->getAmplitude()*0.9999);
                //outBufs[0][frameCNT] = sines[0]->go();
                
                outBufs[0][frameCNT] = track->playBack(i1->computeNextSample());
            }
        }
        ///return 0 on success
        return 0;
    }
    /// Constructor
    SimpleSine() :
        JackCpp::AudioIO("sineVectorTest", 0,1){

          reserveInPorts(2);
          reserveOutPorts(2);

    

    }
  
   
    //This function will take a pointer and then
    //use it to buffer the sound.
    void addInstrumentOne(Instrument * b)
    {
      i1 = b;
    }
    void addInstrumentTwo(Instrument * b)
    {
      i2 = b;
    }
    void addLoopingTrack(LoopingTrack * l)
    {
        track = l;
    }
};
