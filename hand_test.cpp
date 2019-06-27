#include "Hand.h"
#include <iostream>
#include <stdio.h>
//#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
//#include <string.h>
using namespace std;

int main(){
	
	
	
	
	Hand handy("/dev/ttyACM0",9600);
	
		int a = 0;
		int b = 0;
		int c = 0;
		int d = 0;
		int e = 0;
		int f = 0;
		int g = 0;
		int h = 0;
	while(1)
	{
		handy.updateHand();
		a = handy.getThumb();
		b = handy.getIndex();
		c = handy.getMiddle();
		d = handy.getRing();
		e = handy.getPinky();
		f = handy.getXAng();
		g = handy.getYAng();
		h = handy.getZAng();
		cout << "\r " <<  a << " ";
		cout << b << " ";
		cout << c << " ";
		cout << d << " ";
		cout << e << " ";
		cout << f << " ";
		cout << g << " ";
		cout << h << " ";
		cout.flush();
		usleep(100000);
		
	}
	
	
	
	return 0;
}
