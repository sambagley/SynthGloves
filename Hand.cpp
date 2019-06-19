#include "Hand.h"

Hand::Hand(const char * dev, int baud)
{
	serialDevice = dev;
	serialBaud = baud;
	thumbBend= 0;
	indexBend = 0;
	middleBend = 0;
	ringBend = 0;
	pinkyBend = 0;
	xPos = 0;
	yPos = 0;
	zPos = 0;
	yaw = 0;
	roll= 0;
	pitch = 0;
	gForce = 0;
	buttonPress = 0;
	if((serialObj=serialOpen(dev,baud))<0){
    //fprintf(stderr,"Unable to open serial device: %s\n",strerror(errno));
    throw "OH NO, it didn't work, try opening with sudo";
	}
		
}
//once rest of sensors are coded and added we will get all the other data. 
void Hand::updateHand()
{
	if (serialDataAvail(serialObj)>0)
	{
		while (1)
		{
			if(serialGetchar(serialObj) == 'S')
			{
				indexBend = (serialGetchar(serialObj) - '0') * 100 +(serialGetchar(serialObj) - '0') * 10 + (serialGetchar(serialObj)- '0');
		        serialGetchar(serialObj);
		        middleBend = (serialGetchar(serialObj) - '0') * 100 +(serialGetchar(serialObj) - '0') * 10 + (serialGetchar(serialObj)- '0');
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
int Hand::getX()
{
	return xPos;
}
int Hand::getY()
{
	return yPos;
}
int Hand::getZ()
{
	return zPos;
}
int Hand::getYaw()
{
	return yaw;
}
int Hand::getRoll()
{
	return roll;
}
int Hand::getPitch()
{
	return pitch;
}
int Hand::getGs()
{
	return gForce;
}
