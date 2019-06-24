#!/bin/sh

g++  -std=c++11 synthMain.cpp sine.cpp scaleFunctions.cpp Hand.cpp -lwiringPi -lpthread -ljack -ljackcpp  -o synth_test
