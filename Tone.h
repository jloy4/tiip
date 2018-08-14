#ifndef DEF_TONE_H
#define DEF_TONE_H

#include <map>
#include <string>
#include <wiringPi.h>
#include <softTone.h>

class Tone {
public:
	Tone();

	void init(int tone_pin);
	void play(int freq, double duration);
	void pause(double duration);
	void takeOnMe();

private:
	std::map<std::string, int> notes = {
		{"f#", 740},
		{"d", 587},
		{"b4", 494},
		{"e", 659},
		{"g#", 831},
		{"a", 880},
		{"e5", 659}
	};

	int tonePin;
};

#endif