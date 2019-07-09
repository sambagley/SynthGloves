#!/bin/sh

g++  -std=c++11 synthMain.cpp sine.cpp instrument.cpp scaleFunctions.cpp Hand.cpp Instrument_01.cpp Instrument_03.cpp -lwiringPi -lpthread -ljack -ljackcpp  -o synth_test
