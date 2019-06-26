#ifndef HAND_H
#define DATE_H
#include <wiringSerial.h>
#include <errno.h>
class Hand {
	private:

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
