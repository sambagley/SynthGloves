#include "hand.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
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
	button1 = 1; //buttons are active low, so default state is 1
	button2 = 1;
	button3 = 1;
	button3Presses = 0;
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
 	char buf[6];
 	int x;
 	float f;
	if (serialDataAvail(serialObj)>45)
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
				sscanf(buf, "%f", &f);
				xAng = f;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%f", &f);
				yAng = f;

				/*while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%f", &f);
				zAng = f;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				//while((buf[i++] = serialGetchar(serialObj)) != ' ');
				//i = 0;
				//sscanf(buf, "%f", &f);
				//zAng = f;
				/*while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%f", &f);
				xAcc = f;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%f", &f);
				yAcc = f;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%f", &f);
				zAcc = f;*/
				
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				button1 = x;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				button2 = x;
				while((buf[i++] = serialGetchar(serialObj)) != ' ');
				i = 0;
				sscanf(buf, "%d", &x);
				button3Presses = button3 && !x ? button3Presses + 1 : button3Presses;
				button3 = x;

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

float Hand::getXAng()
{
	return xAng;
}

float Hand::getYAng()
{
	return yAng;
}

float Hand::getZAng()
{
	return zAng;
}

int Hand::getGs()
{
	return gForce;
}

int Hand::getButton1()
{
	return button1;
}

int Hand::getButton2()
{
	return button2;
}

int Hand::getButton3()
{
	return button3;
}

int Hand::getButton3Presses()
{
	return button3Presses;	
}

void Hand::calibrateOpen()											// Make sure to call calibrateOpen()
{	
	std::cerr << "Open Hand" << endl;
	sleep(2);									// before calling calibrateClosed()
	updateHand();													// or else the ranges will be incorrect
	thumbOpen = thumbBend;											// and percents will be wrong.
	ringOpen = ringBend;
	middleOpen = middleBend;
	ringOpen = ringBend;
	pinkyOpen = pinkyBend;
	return;
}

void Hand::calibrateClosed()										// Call calibrateOpen() first!
{
	std::cerr << "Close Hand" << endl;
	sleep(2);
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
	 std::cerr << "Make first loop gesture" << endl;
	 sleep(1);
	 updateHand();
	 //updateHand();
	 thumb1 = getThumb();
	 index1 = getIndex();
	 middle1 = getMiddle();
	 ring1 = getRing();
	 pinky1 = getPinky();
	 
	 // Get second gesture data 
	 std::cerr << "Make second loop gesture" << endl;
	 sleep(1);
	 updateHand();
	 //updateHand();
	 thumb2 = getThumb();
	 index2 = getIndex();
	 middle2 = getMiddle();
	 ring2 = getRing();
	 pinky2 = getPinky();
	 
	 // Get third gesture data
	 std::cerr << "Make third loop gesture" << endl;
	 sleep(1);
	 updateHand();
	 //updateHand();
	 thumb3 = getThumb();
	 index3 = getIndex();
	 middle3 = getMiddle();
	 ring3 = getRing();
	 pinky3 = getPinky();
	 
	 // Get fourth gesture data
	 std::cerr << "Make fourth loop gesture" << endl;
	 sleep(1);
	 updateHand();
	 //updateHand();
	 thumb4 = getThumb();
	 index4 = getIndex();
	 middle4 = getMiddle();
	 ring4 = getRing();
	 pinky4 = getPinky();
	 
	 // Get fifth gesture data
	 std::cerr << "Make fifth loop gesture" << endl;
	 sleep(1);
	 updateHand();
	 //updateHand();
	 thumb5 = getThumb();
	 index5 = getIndex();
	 middle5 = getMiddle();
	 ring5 = getRing();
	 pinky5= getPinky();
	 
	 // Get sixth gesture data
	 std::cerr << "Make sixth loop gesture" << endl;
	 sleep(1);
	 updateHand();
	 //updateHand();
	 thumb6 = getThumb();
	 index6 = getIndex();
	 middle6 = getMiddle();
	 ring6 = getRing();
	 pinky6 = getPinky();
	 
	 // Get seventh gesture data
	 std::cerr << "Make seventh loop gesture" << endl;
	 sleep(1);
	 updateHand();
	 //updateHand();
	 thumb7 = getThumb();
	 index7 = getIndex();
	 middle7 = getMiddle();
	 ring7 = getRing();
	 pinky7 = getPinky();
	 
	 // Get eighth gesture data
	 std::cerr << "Make eighth loop gesture" << endl;
	 sleep(1);
	 updateHand();
	 //updateHand();
	 thumb8 = getThumb();
	 index8 = getIndex();
	 middle8 = getMiddle();
	 ring8 = getRing();
	 pinky8 = getPinky();
	 
	 // Get ninth gesture data
	 std::cerr << "Make ninth loop gesture" << endl;
	 sleep(1);
	 updateHand();
	 //updateHand();
	 thumb9 = getThumb();
	 index9 = getIndex();
	 middle9 = getMiddle();
	 ring9 = getRing();
	 pinky9 = getPinky();
	 
	 // Get tenth gesture data
	 std::cerr << "Make tenth loop gesture" << endl;
	 sleep(1);
	 updateHand();
	 //updateHand();
	 thumb10 = getThumb();
	 index10 = getIndex();
	 middle10 = getMiddle();
	 ring10 = getRing();
	 pinky10 = getPinky(); 
}

int Hand::getGestures()
{
	char newState = 0b00000000;
	
	 if (thumbBend > 200 && thumbBend < 390)   
   { 
    newState |= 0b00000001;

   }

   if (indexBend >  200 && indexBend  < 1500) 
   { 

     newState |= 0b00000010;

   }

   if (middleBend > 200 && middleBend < 1500) 
   { 

     newState |= 0b00000100;

   }

   if (ringBend > 200 && ringBend < 1600)  
   { 

     newState |= 0b00001000;

   }

   if (pinkyBend > 200 && pinkyBend < 1500) 
   {
      newState |= 0b00010000;

   }

int gesture;	
	
switch (newState){
  case 0b00011101:
  gesture = 1;
  break;
  case 0b00011001:
  gesture = 2;
  break;
  case 0b00011000:
  gesture = 3;
  break;
  case 0b00000001:
  gesture = 4;
  break;
  case 0b00000000:
  gesture = 5;
  break;
  case 0b00010001:
  gesture = 6;
  break;
  case 0b00001001:
  gesture = 7;
  break;
  case 0b00000101:
  gesture = 8;
  break;
  case 0b00000011:
  gesture = 9;
  break;
  case 0b00011110:
  gesture = 10;
  break;
  default:
   gesture = 0;
  }

	return gesture;
}
