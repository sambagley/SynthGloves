#include "instrument_02.h"



Looper::Looper(Hand * h)
  : Instrument(h)
{
	updateHandCount = 0;
	nextSample = 0;
	sampleNumber = 0;
	currentLoop = 0;
	
	hand->calibrateGestures();
	
	loop1.load("");
	loop2.load("");
	loop3.load("");
	loop4.load("");
	loop5.load("");
	loop6.load("");
	loop7.load("");
	loop8.load("");
	loop9.load("");
	loop10.load("");
	
	numSamplesLoop1 = loop1.getNumSamplesPerChannel();
	numSamplesLoop2 = loop2.getNumSamplesPerChannel();
	numSamplesLoop3 = loop3.getNumSamplesPerChannel();
	numSamplesLoop4 = loop4.getNumSamplesPerChannel();
	numSamplesLoop5 = loop5.getNumSamplesPerChannel();
	numSamplesLoop6 = loop6.getNumSamplesPerChannel();
	numSamplesLoop7 = loop7.getNumSamplesPerChannel();
	numSamplesLoop8 = loop8.getNumSamplesPerChannel();
	numSamplesLoop9 = loop9.getNumSamplesPerChannel();
	numSamplesLoop10 = loop10.getNumSamplesPerChannel();
}
double Looper::computeNextSample()
{
  if ((updateHandCount % 8) == 0)
  {
	int tempLastLoop = currentLoop;
	currentLoop = hand->getGestures();
	if (currentLoop != tempLastLoop)
	{
		sampleNumber = 0;
	}
  }
  switch (currentLoop)
  {
	case(1):
		if (sampleNumber < numSamplesLoop1)
		{
			nextSample = loop1.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop1.samples[0][sampleNumber];
		}
		
	case(2):
		if (sampleNumber < numSamplesLoop2)
		{
			nextSample = loop2.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop2.samples[0][sampleNumber];
		}
		
	case(3):
		if (sampleNumber < numSamplesLoop3)
		{
			nextSample = loop3.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop3.samples[0][sampleNumber];
		}
		
	case(4):
		if (sampleNumber < numSamplesLoop4)
		{
			nextSample = loop4.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop4.samples[0][sampleNumber];
		}
		
	case(5):
		if (sampleNumber < numSamplesLoop5)
		{
			nextSample = loop5.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop5.samples[0][sampleNumber];
		}
		
	case(6):
		if (sampleNumber < numSamplesLoop6)
		{
			nextSample = loop6.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop6.samples[0][sampleNumber];
		}
	case(7):
		if (sampleNumber < numSamplesLoop7)
		{
			nextSample = loop7.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop7.samples[0][sampleNumber];
		}
		
	case(8):
		if (sampleNumber < numSamplesLoop8)
		{
			nextSample = loop8.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop8.samples[0][sampleNumber];
		}
		
	case(9):
		if (sampleNumber < numSamplesLoop9)
		{
			nextSample = loop9.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop9.samples[0][sampleNumber];
		}
		
	case(10):
		if (sampleNumber < numSamplesLoop10)
		{
			nextSample = loop10.samples[0][sampleNumber]; 
		}
		else
		{
			sampleNumber = 0;
			nextSample = loop10.samples[0][sampleNumber];
		}
		
	default:
		nextSample = 0;
	}
	
	
		
  updateHandCount ++;
  return nextSample;
}
