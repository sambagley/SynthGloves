#!/bin/sh

g++  -std=c++11 synthMain.cpp sine.cpp instrument.cpp scaleFunctions.cpp Hand.cpp Instrument_01.cpp instrument_02.cpp /home/pi/SynthGloves/AudioFile/AudioFile.cpp -lwiringPi -lpthread -ljack -ljackcpp  -o synth_test 
