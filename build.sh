#!/bin/sh

g++  -std=c++11 Simple_Synth.cpp sine.cpp ScaleFunctions.cpp Hand.cpp -lwiringPi -lpthread -ljack -ljackcpp  -o testy_boi
