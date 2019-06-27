#ifndef HAND_H
#define DATE_H
#include <wiringSerial.h>
#include <errno.h>
class Hand {
	private:
<<<<<<< HEAD
//my own comment
=======
// variables for hand
>>>>>>> 07c26a6f3fecb0de10ce104a106eba24b143c1a4
		const char * serialDevice;
		int serialBaud;
		int serialObj;
		int thumbBend;
		int indexBend;
		int middleBend;
		int ringBend;
		int pinkyBend;
		int xPos;
		int yPos;
		int zPos;
		int xAng;
		int yAng;
		int zAng;
		int gForce;
		int buttonPress;

	public:

		Hand(const char *, int);
		void updateHand();
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


};

#endif
