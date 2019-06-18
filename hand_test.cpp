#include "Hand.h"
#include <iostream>
#include <stdio.h>
//#include <string.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main(){
	
	Hand handy("/dev/ttyACM0",9600);
	
	
	while(1)
	{
		handy.updateHand();
		cout << handy.getMiddle() << endl;
	}
	
	
	
	return 0;
}
