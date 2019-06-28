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
#include "Hand.h"
#include <wiringSerial.h>
#include <vector>
#include <climits>
#include "SimpleSine.h"
#include "Instrument_01.h"
using std::cout;
using std::endl;


int main(int argc, char *argv[]){

    Hand * lefty = new Hand("/dev/ttyACM0",9600);

    double f1 = 0.0;

    /// initial ports from constructor created here.
    //SimpleSine * t = new SimpleSine(f1);
    SimpleSine * t = new SimpleSine(lefty);

    /// activate the client
    t->start();

    /// connect sine ports to stereo ports
    t->connectToPhysical(0,0);		// connects this client out port 0 to physical destination port 0
    t->connectToPhysical(0,1);		// connects this client out port 1 to physical destination port 1

    ///print names
    cout << "outport names:" << endl;
    for(unsigned int i = 0; i < t->outPorts(); i++)
        cout << "\t" << t->getOutputPortName(i) << endl;
    //from here to the end of the while loop is where all the code can now go



    //FingerKeys * lefthandkey = new FingerKeys(lefty);

    //t->addWaveForm(lefthandkey->getSineWaveToLink());
    //t->addWaveForm(new Sine(440,0.5,48000));
     // t->testThing  


    /// run for EVER
    while(1){
        //lefty->update();
       // lefthandkey->computeNextSample();
       
        //t->setWaveFrequency(0, (double) lefty->getThumb());
    }





    /// never reached:!=
    t->disconnectInPort(0);	// Disconnecting ports.
    t->disconnectOutPort(1);
    t->close();	// stop client.
    delete t;	// always clean up after yourself.
    exit(0);
}
