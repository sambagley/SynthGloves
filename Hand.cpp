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
	xPos = 0;
	yPos = 0;
	zPos = 0;
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
void Hand::update()
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
