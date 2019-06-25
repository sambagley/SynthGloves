#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include "sine.h"
#include <thread>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "ScaleFunctions.hpp"
#include "Hand.h"
#include <wiringSerial.h>
#include <vector>
#include <climits>
#include "SimpleSine.h"
using std::cout;
using std::endl;

//simple funtion to map flex value to note
int whatNote(int flexValue)
{
    return flexValue/10 - 50;
};





///
///
///
int main(int argc, char *argv[]){

    Hand lefty("/dev/ttyACM0",9600);

    double f1 = 0.0;

    /// initial ports from constructor created here.
    SimpleSine * t = new SimpleSine(f1);


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




    t->addWaveForm(new Sine(880.0, 0.25, 48000));
    t->addWaveForm(new Sine(1320.0, 0.125, 48000));
    t->addWaveForm(new Sine(1760.0, 0.1, 48000));
    //t->addWaveForm(new Sine(440.0, 0.3, 48000));






    /// run for EVER
    while(1){





        lefty.updateHand();
      //t->setWaveFrequency(1, blues(440.0, -3, whatNote(lefty.getIndex())));
        t->setWaveFrequency(0, blues(440.0, 1, whatNote(lefty.getMiddle())));
        t->setWaveFrequency(1, blues(1320.0, 1, whatNote(lefty.getMiddle())));
        t->setWaveFrequency(2, blues(1320.0, 1, whatNote(lefty.getMiddle())));
        t->setWaveFrequency(3, blues(1760.0, 1, whatNote(lefty.getMiddle())));
        t->setGlobalAmp(0.3 *((double)  abs(lefty.getIndex()- 500) / 400.0));
    }





    /// never reached:!=
    t->disconnectInPort(0);	// Disconnecting ports.
    t->disconnectOutPort(1);
    t->close();	// stop client.
    delete t;	// always clean up after yourself.
    exit(0);
}
