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
#include "Instrument_01.h"

//class Instrument;

class SimpleSine: public JackCpp::AudioIO {

private:
    int numWaves;
   std::vector <Sine*>  sines;


   Instrument * i1;
   Instrument * i2;


    
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
                
                outBufs[0][frameCNT] = i2 == NULL ? i1->computeNextSample() : i1->computeNextSample() + i2->computeNextSample();
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

          numWaves = 0;
          //sines.push_back(new Sine(f1,0.5,48000));

    }
  
    void addWaveForm(Sine * s)
    {
      sines.push_back(s);
      numWaves++;
    }
    void setWaveFrequency(int index, double frequency)
    {
      sines[index]->setFrequency(frequency);
    }
    void setWaveAmp(int index, double a)
    {
      sines[index]->setAmplitude(a);
    }
    
    //sets global volume
    void setGlobalAmp(double a)
    {

        for(int i = 0; i < numWaves; i++)
        {
          sines[i]->setAmplitude(a);
        }
        return;

    }
    //This function will take a function pointer and then
    //use it to buffer the sound.
    void addInstrumentOne(Instrument * b)
    {
      i1 = b;
    }
    void addInstrumentTwo(Instrument * b)
    {
      i2 = b;
    }

};
