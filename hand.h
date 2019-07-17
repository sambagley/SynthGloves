#ifndef HAND_H
#define HAND_H

#ifdef __APPLE__
    #include "wiringSerial.h"
    #else
         #include <wiringSerial.h>
		#endif
#include <errno.h>

class Hand {
	private:
		// variables for hand
		const char * serialDevice;
		int serialBaud;
		int serialObj;

		int thumbBend;										// Bend values straight from arduino
		int indexBend;
		int middleBend;
		int ringBend;
		int pinkyBend;

		int thumbOpen;										// Readings of open fingers for calibration
		int indexOpen;
		int middleOpen;
		int ringOpen;
		int pinkyOpen;

		int thumbClosed;									// Readings of closed fingers for calibration
		int indexClosed;
		int middleClosed;
		int ringClosed;
		int pinkyClosed;

		int thumbPercent;									// Percent that finger is closed
		int indexPercent;									// Ex: if fist, fingers show 100, if flat, 0.
		int middlePercent;
		int ringPercent;
		int pinkyPercent;

		int thumbRange;										// Ranges will be computed after calibrating
		int indexRange;										// open and closed positions. They are used
		int middleRange;									// for calculating percents.
		int ringRange;
		int pinkyRange;

		int xVel;													// Readings from arduino
		int yVel;
		int zVel;
		float xAng;													// Also readings straight from arduino
		float yAng;
		float zAng;
		int xAcc;
		int yAcc;
		int zAcc;
		int gForce;
		int button1;
		int button2;
		int button3;

		int overallPercent;								// Average of finger percentages, 100 if fist, zero if flat
		bool isOpen;
		
		int thumb1;
		int index1;
		int middle1;
		int ring1;
		int pinky1;
		  
		int thumb2;
		int index2;
		int middle2;
		int ring2;
		int pinky2;
		
		int thumb3;
		int index3;
		int middle3;
		int ring3;
		int pinky3;
		
		int thumb4;
		int index4;
		int middle4;
		int ring4;
		int pinky4;
		
		int thumb5;
		int index5;
		int middle5;
		int ring5;
		int pinky5;
		  
		int thumb6;
		int index6;
		int middle6;
		int ring6;
		int pinky6;
	  
		int thumb7;
		int index7;
		int middle7;
		int ring7;
		int pinky7;
		  
		int thumb8;
		int index8;
		int middle8;
		int ring8;
		int pinky8;
		  
		int thumb9;
		int index9;
		int middle9;
		int ring9;
		int pinky9;
		  
		int thumb10;
		int index10;
		int middle10;
		int ring10;
		int pinky10;
		
		int deviation;


	public:

		Hand(const char *, int);
		void updateHand();								// Gets data from arduino sensors
		void calibrateOpen();							// Stores finger data for open Hand
		void calibrateClosed();						// Stores finger data for closed hand
		void updatePercents();						// Updates percents for each finger
		bool getIsClosed();								// Returns true if hand is closed
		bool getIfOpenUpwardPalm();				// Returns true if hand palm is open and upward facing
		bool getIfStopSign();							// Returns true if hand is vertical stop sign
		bool getIfDevilHorns();						// Returns true if devil horns
		bool getNumbers();								// Returns sign language number
		int getThumb();										// Returns thumb value
		int getIndex();										// Returns index value
		int getMiddle();									// Returns middle value
		int getRing();										// Returns ring value
		int getPinky();										// Returns pinky value
		int getXVel();										// Returns x velocity
		int getYVel();										// Returns y velocity
		int getZVel();										// Returns z velocity
		float getXAng();										// Returns X angle
		float getYAng();										// Returns y angle
		float getZAng();
		int getXAcc();										// Returns X acc
		int getYAcc();										// Returns y acc
		int getZAcc();										// Returns z acc
		int getGs();	
		int getButton1();									//returns 0 if button is pressed
		int getButton2();
		int getButton3();
		int getOverallPercent();
		int getGestures();
		void calibrateGestures();					
		
};

#endif
