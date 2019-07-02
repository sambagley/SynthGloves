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
<<<<<<< HEAD
// variables for hand
=======
		// variables for hand
>>>>>>> 45a779a0ed6482501ac80c1d3f14a04ffe368b0f
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

		int xAng;													// Also readings straight from arduino
		int yAng;
		int zAng;
		int gForce;

		int buttonPress;
		int overallPercent;								// Average of finger percentages, 100 if fist, zero if flat
		bool isOpen;


	public:

		Hand(const char *, int);
<<<<<<< HEAD
		void update();
		int getThumb();
		int getIndex();
		int getMiddle();
		int getRing();
		int getPinky();
		int getX();
		int getY();
		int getZ();
		int getXAng();
		int getYAng();
		int getZAng();
		int getGs();
		void setThumb();
=======
		void updateHand();								// Gets data from arduino sensors
		void calibrateOpen();							// Stores finger data for open Hand
		void calibrateClosed();						// Stores finger data for closed hand
		void updatePercents();						// Gets percents for each finger
		bool getIsClosed();								// Tells if hand is closed
		int getThumb();										// Returns thumb value
		int getIndex();										// Returns index value
		int getMiddle();									// Returns middle value
		int getRing();										// Returns ring value
		int getPinky();										// Returns pinky value
		int getXVel();										// Returns x velocity
		int getYVel();										// Returns y velocity
		int getZVel();										// Returns z velocity
		int getXAng();										// Returns X angle
		int getYAng();										// Returns y angle
		int getZAng();										// Returns z angle
		int getGs();											// Returns Gs value
		int getOverallPercent();					// Returns average of each fingers percent
>>>>>>> 45a779a0ed6482501ac80c1d3f14a04ffe368b0f

};

#endif
