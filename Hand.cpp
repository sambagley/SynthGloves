#include "Hand.h"
#include <stdio.h>

Hand::Hand(const char * dev, int baud)
{
	serialDevice = dev;
	serialBaud = baud;
	thumbBend= 0;
	indexBend = 0;
	middleBend = 0;
	ringBend = 0;
	pinkyBend = 0;
	xVel = 0;
	yVel = 0;
	zVel = 0;
	xAng = 0;
	yAng= 0;
	zAng = 0;
	gForce = 0;
	buttonPress = 0;
	if((serialObj=serialOpen(dev,baud))<0){
    //fprintf(stderr,"Unable to open serial device: %s\n",strerror(errno));
    throw "OH NO, it didn't work, try opening with sudo";
	}

}
/*This is how getChar works
getChar(const int fd)
{
	uint8_t x;

	if (read (fd, &x, 1) != 1)
		return -1;

		return ((int)x) & 0xFF;
};
*/
//once rest of sensors are coded and added we will get all the other data.
void Hand::updateHand()
{
	char temp;
 	char buf[2];
 	int x;
	if (serialDataAvail(serialObj)>0)
	{
		while (1)
		{
			if(serialGetchar(serialObj) == '$')
			{
				int i = 0;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				thumbBend = x;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				indexBend = x;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				middleBend = x;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				ringBend = x;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				pinkyBend = x;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				xAng = x;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				yAng = x;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				zAng = x;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				xAcc = x;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				yAcc = x;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				zAcc = x;
					serialFlush(serialObj);
					return;

			}
		}

		//middleBend = middleBend_temp > 0 ? middleBend_temp : middleBend;//hacky error checking
	}
	return;
}

int Hand::getThumb()
{
	return thumbBend;
}

int Hand::getIndex()
{
	return indexBend;
}

int Hand::getMiddle()
{
	return middleBend;
}

int Hand::getRing()
{
	return ringBend;
}

int Hand::getPinky()
{
	return pinkyBend;
}

int Hand::getXAcc()
{
	return xAcc;
}

int Hand::getYAcc()
{
	return yAcc;
}

int Hand::getZAcc()
{
	return zAcc;
}

int Hand::getXAng()
{
	return xAng;
}

int Hand::getYAng()
{
	return yAng;
}

int Hand::getZAng()
{
	return zAng;
}

int Hand::getGs()
{
	return gForce;
}

void Hand::calibrateOpen()											// Make sure to call calibrateOpen()
{																								// before calling calibrateClosed()
	updateHand();																	// or else the ranges will be incorrect
	thumbOpen = thumbBend;												// and percents will be wrong.
	ringOpen = ringBend;
	middleOpen = middleBend;
	ringOpen = ringBend;
	pinkyOpen = pinkyBend;
	return;
}

void Hand::calibrateClosed()										// Call calibrateOpen() first!
{
	updateHand();
	thumbClosed = thumbBend;
	ringClosed = ringBend;
	middleClosed = middleBend;
	ringClosed = ringBend;
	pinkyClosed = pinkyBend;
	thumbRange = thumbClosed - thumbOpen;					// Find ranges to be used
	indexRange = indexClosed - indexOpen;					// later in getPercentages()
	middleRange = middleClosed - middleOpen;
	ringRange = ringClosed - ringOpen;
	pinkyRange = pinkyClosed - pinkyOpen;
	return;
}

void Hand::updatePercents()						// Shows percent/ratio that hand is closed
{																		// Ex: Fist is 100, flat hand is 0.
	updateHand();
	thumbPercent = ((thumbBend - thumbOpen)*100) / thumbRange;
	indexPercent = ((indexBend - indexOpen)*100) / indexRange;
	middlePercent = ((middleBend - middleOpen)*100) / middleRange;
	ringPercent = ((ringBend - ringOpen)*100) / ringRange;
	pinkyPercent = ((pinkyBend - pinkyOpen)*100) / pinkyRange;
	return;
}

int Hand::getOverallPercent()
{
	updatePercents();
	overallPercent = (thumbPercent + indexPercent + middlePercent + ringPercent + pinkyPercent) / 5;
	return overallPercent;
}

bool Hand::getIsClosed()
{
	overallPercent = getOverallPercent();
	if (overallPercent > 8){
		return true;
	}
	else{
		return false;
	}
}

bool Hand::getIfDevilHorns(){
	updatePercents();
	if ((thumbPercent > 85) &&
			(indexPercent < 20) &&
			(middlePercent > 85) &&
			(ringPercent > 85) &&
			(pinkyPercent < 20)){
				return true;
			}
	else{
		return false;
	}
}

bool Hand::getIfStopSign(){
	if ((getOverallPercent() > 85) && ( yAng > 70))
	{
		return true;
	}
	return false;
}
