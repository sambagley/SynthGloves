#!/bin/sh

g++   -std=c++11 main_synth.cpp sine.cpp instrument.cpp scaleFunctions.cpp hand.cpp instrument_finger_keys.cpp instrument_looper.cpp instrument_chords.cpp instrument_sax.cpp instrument_slide.cpp /home/pi/SynthGloves/AudioFile/AudioFile.cpp -lwiringPi -lpthread -ljack -ljackcpp -g -o synth_test 

