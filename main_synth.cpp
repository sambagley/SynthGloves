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
    
    LoopingTrack  track(&lefty);
    Looper   leftHandInst1(&lefty);
    Chords   leftHandInst2(&lefty);
    FingerKeys  leftHandInst3(&lefty);
    
    Looper  * rightHandInst1; 
    Chords  * rightHandInst2;
    FingerKeys * rightHandInst3;
    
    if (haveTwoHands)
    {
        rightHandInst1 = new Looper(righty);
        rightHandInst2 = new Chords(righty);
        rightHandInst3 = new FingerKeys(righty);
    }
    
   
    
    
    JackWrapper * t = new JackWrapper();  //create the jack class

    
    t->addInstrumentOne(&leftHandInst2); // send instrument to sound hardware wrapper.
    t->addInstrumentTwo(&leftHandInst3); // send instrument to sound hardware wrapper.
    t->addInstrumentThree(&leftHandInst1); // send instrument to sound hardware wrapper.
    t->addHand(&lefty);
    
    if (haveTwoHands == true)
    {
        t->addInstrumentOneHandTwo(rightHandInst1); // send instrument to sound hardware wrapper.
        t->addInstrumentTwoHandTwo(rightHandInst2); // send instrument to sound hardware wrapper.
        t->addInstrumentThreeHandTwo(rightHandInst3); // send instrument to sound hardware wrapper.
        t->addHand2(righty);
    }
    
    t->addLoopingTrack(&track);
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
    }
    
    /// never reached:!=
    t->disconnectInPort(0);	// Disconnecting ports.
    t->disconnectOutPort(1);
    t->close();	// stop client.
    delete t;	// always clean up after yourself.
    exit(0);
}
