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
#include "ScaleFunctions.hpp"
#include "Hand.h"
#include <wiringSerial.h>

using std::cout;
using std::endl;

//simple funtion to map flex value to note
int whatNote(int flexValue)
{
    return flexValue/10 - 50;
};


Hand * lefty;

class SimpleSine: public JackCpp::AudioIO {

private:

    Sine *sin1;
    Sine *sin2;

public:
    /// Audio Callback Function:
    /// - the output buffers are filled here
    virtual int audioCallback(jack_nframes_t nframes,
                              // A vector of pointers to each input port.
                              audioBufVector inBufs,
                              // A vector of pointers to each output port.
                              audioBufVector outBufs){


      
     lefty->updateHand();
     sin1->setFrequency(blues(440.0, 2, whatNote(lefty->getMiddle())));
     sin2->setFrequency(440.0);
        
/*
            bendvalue = (serialGetchar(fd) - '0') * 10 + (serialGetchar(fd)- '0');
            sin1->setFrequency(((double)  bendvalue) * 50.0);
            serialFlush(fd);
  */             
        



        /// LOOP over all output buffers
        for(unsigned int i = 0; i < 1; i++)
        {

            for(int frameCNT = 0; frameCNT  < nframes; frameCNT++)
            {
				//sin1->setFrequency( (double) bendvalue);
                outBufs[0][frameCNT] = sin1->go() + sin2->go();
            }
             
        }

        ///return 0 on success
        return 0;
    }

    /// Constructor
    SimpleSine(double f1) :
        JackCpp::AudioIO("bob", 0,1){
        
        reserveInPorts(2);
        reserveOutPorts(2);

        sin1        = new Sine(f1,0.3,48000);
        sin2        = new Sine(f1,0.3,48000);
        

    }

};

///
///
///
int main(int argc, char *argv[]){

lefty = new Hand("/dev/ttyACM0",9600);
    
    double f1 = 300.0;

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

    /// run for EVER
    sleep(100);

    /// never reached:!=
    t->disconnectInPort(0);	// Disconnecting ports.
    t->disconnectOutPort(1);
    t->close();	// stop client.
    delete t;	// always clean up after yourself.
    exit(0);
}



/*
void serialComms()
{
/*	
	if((fd=serialOpen("/dev/ttyACM0",9600))<0){
    fprintf(stderr,"Unable to open serial device: %s\n",strerror(errno));
    return;
  }
		//for (;;){
    bendvalue = (double) (serialGetchar(fd));
    //putchar(bendvalue);
    //sleep(1);
  //}
  return;
}

*/
