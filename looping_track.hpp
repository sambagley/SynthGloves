#include "hand.h"
#include <vector>


		 /***************************************
		 * TODO: figure out a way to play recorded stuff 
		 * and also output from the current instrument 
		 * without also recording that too
		 ********************************************/

class LoopingTrack{
	private:
		std::vector<double> recordedTrack;
		bool isPlaying;
		bool isRecording;
		bool reset;
		int trackIndex;
		int trackMax;
		int trackMin;
		Hand * hand;
		uint32_t timeout;
	public:
		LoopingTrack(Hand * h)
		{
			recordedTrack.resize(2880000);
			timeout = 0;
			isPlaying = 0;
			isRecording = 0;
			trackIndex = 0;
			trackMax = (2880000) - 1;
			trackMin = 0;
			reset = 1;
			hand = h;
		};
		
		void clearTrack()
		{
			if (!reset)
			{
				reset = 1;
				trackMax = (2880000) - 1;
			}
		};
		
		void startRecording()
		{
			isRecording = 1;
		}
		void stopRecording()
		{
			if (isRecording)
			{
				isRecording = 0;
				if (reset) {trackMax = trackIndex;}
				reset = 0;
				
			}
		}
		void togglePlaying()
		{
			isPlaying = !isPlaying;
		}
		
		void record(double input)
		{	
		  
		  recordedTrack[trackIndex] = reset == 1 ? input : recordedTrack[trackIndex] + input ;				
			
		};
		
		/*************************************************
		 * checks hand for certian button presses.
		 * 
		 * if 1 and 2 are pressed, it will reset
		 * 
		 * button 1 will toggle recording
		 * 
		 * button 2 will toggle playing, sort of a mute button
		 * 
		 * 
		 *************************************************/
		  
		void checkHand()
		{
		if (timeout > 50000)
			{
			if (!hand->getButton1() && !hand->getButton2())
			{
				reset = 1;
				isRecording = 0;
				isPlaying = 0;
				trackIndex = 0;
				trackMax = (2880000) - 1;
				trackMin = 0;
				timeout = 0;
				std::cerr << "reset" << std::endl;
			}
			else if (!hand->getButton1() && !isRecording)
			{
				isPlaying = 1;
				startRecording();
				std::cerr << "started Recording" << std::endl;
				timeout = 0;
			}
			else if (!hand->getButton1() && isRecording)
			{
				stopRecording();
				std::cerr << "stopped Recording" << std::endl;
				timeout = 0;
			}
			else if (!hand->getButton2())
			{
				togglePlaying();	
				std::cerr << "toggled Recording" << std::endl;
				timeout = 0;
			}
			}
			timeout++;
		}
		
		double playBack(double sound)
		{
		   checkHand();
		   double returnVal;
		   
		   if (isPlaying)
		   {
			   if (isRecording)
				{
					record(sound/2.0);
				}
			 returnVal = recordedTrack[trackIndex];
			 trackIndex++;
		   } 
		   else
		   {
			   returnVal = sound/2.0;
		   }
		   
		   if (trackIndex >= trackMax || trackIndex >= (2880000))
		   {
			   trackIndex = trackMin;
			   reset = 0;
		   }
		   return returnVal;
		};
		
		
		
		
		
	
	
	
};
