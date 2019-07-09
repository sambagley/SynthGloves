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
		int xAng;													// Also readings straight from arduino
		int yAng;
		int zAng;
		int xAcc;
		int yAcc;
		int zAcc;
		int gForce;

		int buttonPress;
		int overallPercent;								// Average of finger percentages, 100 if fist, zero if flat
		bool isOpen;


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
		int getXAng();										// Returns X angle
		int getYAng();										// Returns y angle
		int getZAng();
		int getXAcc();										// Returns X acc
		int getYAcc();										// Returns y acc
		int getZAcc();										// Returns z acc
		int getGs();											// Returns Gs value
		int getOverallPercent();
		int getGestures();
		int calibrateGestures();					// Returns average of each fingers percent
};

#endif
