#include "Hand.h"
#include <stdio.h>
#include <iostream>
using namespace std;

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
	xAcc = 0;
	yAcc= 0;
	zAcc = 0;
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
	if (serialDataAvail(serialObj)>30)
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
				/*while((buf[i++] = serialGetchar(serialObj)) != ' ');
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
				zAcc = x;*/
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

void Hand::calibrateGestures()
{
	 // Get first gesture data
	 cout << "Make first loop gesture" << endl;
	 sleep(2);
	 thumb1 = getThumb();
	 index1 = getIndex();
	 middle1 = getMiddle();
	 ring1 = getRing();
	 pinky1 = getPinky();
	 
	 // Get second gesture data 
	 cout << "Make second loop gesture" << endl;
	 sleep(2);
	 thumb2 = getThumb();
	 index2 = getIndex();
	 middle2 = getMiddle();
	 ring2 = getRing();
	 pinky2 = getPinky();
	 
	 // Get third gesture data
	 cout << "Make third loop gesture" << endl;
	 sleep(2);
	 thumb3 = getThumb();
	 index3 = getIndex();
	 middle3 = getMiddle();
	 ring3 = getRing();
	 pinky3 = getPinky();
	 
	 // Get fourth gesture data
	 cout << "Make fourth loop gesture" << endl;
	 sleep(2);
	 thumb4 = getThumb();
	 index4 = getIndex();
	 middle4 = getMiddle();
	 ring4 = getRing();
	 pinky4 = getPinky();
	 
	 // Get fifth gesture data
	 cout << "Make fifth loop gesture" << endl;
	 sleep(2);
	 thumb5 = getThumb();
	 index5 = getIndex();
	 middle5 = getMiddle();
	 ring5 = getRing();
	 pinky5= getPinky();
	 
	 // Get sixth gesture data
	 cout << "Make sixth loop gesture" << endl;
	 sleep(2);
	 thumb6 = getThumb();
	 index6 = getIndex();
	 middle6 = getMiddle();
	 ring6 = getRing();
	 pinky6 = getPinky();
	 
	 // Get seventh gesture data
	 cout << "Make seventh loop gesture" << endl;
	 sleep(2);
	 thumb7 = getThumb();
	 index7 = getIndex();
	 middle7 = getMiddle();
	 ring7 = getRing();
	 pinky7 = getPinky();
	 
	 // Get eighth gesture data
	 cout << "Make eighth loop gesture" << endl;
	 sleep(2);
	 thumb8 = getThumb();
	 index8 = getIndex();
	 middle8 = getMiddle();
	 ring8 = getRing();
	 pinky8 = getPinky();
	 
	 // Get ninth gesture data
	 cout << "Make ninth loop gesture" << endl;
	 sleep(2);
	 thumb9 = getThumb();
	 index9 = getIndex();
	 middle9 = getMiddle();
	 ring9 = getRing();
	 pinky9 = getPinky();
	 
	 // Get tenth gesture data
	 cout << "Make tenth loop gesture" << endl;
	 sleep(2);
	 thumb10 = getThumb();
	 index10 = getIndex();
	 middle1 = getMiddle();
	 ring10 = getRing();
	 pinky10 = getPinky(); 
}

int Hand::getGestures()
{
	updateHand();
	
	// Check for first gesture
	if ((abs(getThumb() - thumb1) < deviation)&&
		(abs(getIndex() - index1) < deviation)&&
		(abs(getMiddle() - middle1) < deviation)&&
		(abs(getRing() - ring1) < deviation)&&
		(abs(getPinky() - pinky1) < deviation))
	{
		return 1;
	}
	
	// Check for second gesture
	else if ((abs(getThumb() - thumb2) < deviation)&&
		(abs(getIndex() - index2) < deviation)&&
		(abs(getMiddle() - middle2) < deviation)&&
		(abs(getRing() - ring2) < deviation)&&
		(abs(getPinky() - pinky2) < deviation))
	{
		return 2;
	}
	
	// Check for third gesture
	else if ((abs(getThumb() - thumb3) < deviation)&&
		(abs(getIndex() - index3) < deviation)&&
		(abs(getMiddle() - middle3) < deviation)&&
		(abs(getRing() - ring3) < deviation)&&
		(abs(getPinky() - pinky3) < deviation))
	{
		return 3;
	}
	
	// Check for fourth gesture
	else if ((abs(getThumb() - thumb4) < deviation)&&
		(abs(getIndex() - index4) < deviation)&&
		(abs(getMiddle() - middle4) < deviation)&&
		(abs(getRing() - ring4) < deviation)&&
		(abs(getPinky() - pinky4) < deviation))
	{
		return 4;
	}
	
	// Check for fifth gesture
	else if ((abs(getThumb() - thumb5) < deviation)&&
		(abs(getIndex() - index5) < deviation)&&
		(abs(getMiddle() - middle5) < deviation)&&
		(abs(getRing() - ring5) < deviation)&&
		(abs(getPinky() - pinky5) < deviation))
	{
		return 5;
	}
	
	// Check for sixth gesture
	else if ((abs(getThumb() - thumb6) < deviation)&&
		(abs(getIndex() - index6) < deviation)&&
		(abs(getMiddle() - middle6) < deviation)&&
		(abs(getRing() - ring6) < deviation)&&
		(abs(getPinky() - pinky6) < deviation))
	{
		return 6;
	}
	
	// Check for seventh gesture
	else if ((abs(getThumb() - thumb7) < deviation)&&
		(abs(getIndex() - index7) < deviation)&&
		(abs(getMiddle() - middle7) < deviation)&&
		(abs(getRing() - ring7) < deviation)&&
		(abs(getPinky() - pinky7) < deviation))
	{
		return 7;
	}
	
	// Check for eighth gesture
	else if ((abs(getThumb() - thumb8) < deviation)&&
		(abs(getIndex() - index8) < deviation)&&
		(abs(getMiddle() - middle8) < deviation)&&
		(abs(getRing() - ring8) < deviation)&&
		(abs(getPinky() - pinky8) < deviation))
	{
		return 8;
	}
	
	// Check for ninth gesture
	else if ((abs(getThumb() - thumb9) < deviation)&&
		(abs(getIndex() - index9) < deviation)&&
		(abs(getMiddle() - middle9) < deviation)&&
		(abs(getRing() - ring9) < deviation)&&
		(abs(getPinky() - pinky9) < deviation))
	{
		return 9;
	}
	
	// Check for tenth gesture
	else if ((abs(getThumb() - thumb10) < deviation)&&
		(abs(getIndex() - index10) < deviation)&&
		(abs(getMiddle() - middle10) < deviation)&&
		(abs(getRing() - ring10) < deviation)&&
		(abs(getPinky() - pinky10) < deviation))
	{
		return 10;
	}
	else
	{
		return 0;
	}
	
	
}
