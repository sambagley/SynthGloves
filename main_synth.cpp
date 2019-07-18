#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include "sine.h"
#include <thread>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "scaleFunctions.hpp"
#include "hand.h"
#include <wiringSerial.h>
#include <vector>
#include <climits>
#include "jack_wrapper.h"
#include "instrument_finger_keys.h"
#include "instrument_looper.h"
#include "instrument_chords.h"
#include "instrument_sax.h"


using std::cout;
using std::endl;


int main(int argc, char *argv[]){
   
    Hand lefty("/dev/ttyACM0",57600);
    Hand * righty;
    bool haveTwoHands = true;
    try 
    {
        righty = new Hand("/dev/ttyACM1", 57600);
        
    }
    catch (...) 
    {
        std::cout << "Second hand not detected. Running in single-handed mode." << std::endl;
        haveTwoHands = false;
    }
    LoopingTrack * track = new LoopingTrack(&lefty);
    
    FingerKeys  * leftHandInst1 = new FingerKeys(&lefty);
    Chords  * leftHandInst2 = new Chords(&lefty);
    Looper * leftHandInst3 = new Looper(&lefty);
    FingerKeys  * rightHandInst1; 
    Chords  * rightHandInst2;
    Looper * rightHandInst3;
    
    if (haveTwoHands)
    {
        rightHandInst1 = new FingerKeys(righty);
        rightHandInst2 = new Chords(righty);
        rightHandInst3 = new Looper(righty);
    }
    
   
    
    
    JackWrapper * t = new JackWrapper();  //create the jack class

    
    t->addInstrumentOne(leftHandInst1); // send instrument to sound hardware wrapper.
   
    if (haveTwoHands)
    {
        t->addInstrumentTwo(rightHandInst1);
    }
    
    t->addLoopingTrack(track);
    /// activate the client
    t->start();

    /// connect sine ports to stereo ports
    t->connectToPhysical(0,0);		// connects this client out port 0 to physical destination port 0
    t->connectToPhysical(0,1);		// connects this client out port 1 to physical destination port 1

    ///print names
    cout << "outport names:" << endl;
    for(unsigned int i = 0; i < t->outPorts(); i++)
        cout << "\t" << t->getOutputPortName(i) << endl;



    /// run for EVER
    while(1)
    {
        int p = lefty.getButton3() % 3;
      
            if (p == 0)
            {
                t->addInstrumentOne(leftHandInst1);
                //std::cerr << "case 1" << std ::endl;
             }   
              
            else if (p == 1) 
            {
                t->addInstrumentOne(leftHandInst2);
                //std::cerr << "case 2" << std ::endl;
            }
            
            else if (p == 2) 
            {
                t->addInstrumentOne(leftHandInst3);
                //std::cerr << "case 3" << std ::endl;
            }
                
     
    }
    





    /// never reached:!=
    t->disconnectInPort(0);	// Disconnecting ports.
    t->disconnectOutPort(1);
    t->close();	// stop client.
    delete t;	// always clean up after yourself.
    exit(0);
}
