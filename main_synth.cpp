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

    //Hand * lefty = new Hand("/dev/ttyACM0",57600);
    //Hand righty("/dev/ttyACM1", 57600);
    LoopingTrack * track = new LoopingTrack(&lefty);


 
    SimpleSine * t = new SimpleSine();

    FingerKeys  * lefthandkey = new FingerKeys(&lefty);
    //lefthandkey->addSecondHand(&righty);

    //Chords * righthandkey = new Chords(righty);
    //Looper * lefthandkey = new Looper(lefty);
    t->addInstrumentOne(lefthandkey); // send instrument to sound hardware wrapper.
    //t->addInstrumentTwo(righthandkey);
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
    while(1){
      
    }





    /// never reached:!=
    t->disconnectInPort(0);	// Disconnecting ports.
    t->disconnectOutPort(1);
    t->close();	// stop client.
    delete t;	// always clean up after yourself.
    exit(0);
}
