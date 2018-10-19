#ifndef DEF_TIIP_H
#define DEF_TIIP_H

#include <wiringPi.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <unistd.h>
#include <thread>
#include <fstream>
#include <curl/curl.h>
#include "Button.h"
#include "NFC.h"
#include "Tone.h"

#define NUM_BTN 3
#define BTN_1 0
#define BTN_2 2 
#define BTN_3 3
#define LED_1 1
#define LED_2 4
#define LED_3 5
#define LED_NFC 21
#define TONE_PIN 6
#define MAX_VAL 100

class Tiip {
public:
	Tiip();

	void init();
	void debounceAllExcept(int button);
	void enableButton(int button);
	int waitForButtonCall();
	void setAllLeds(int val);
	void successActionLED();
	void successActionTone();
	void pollButtons();
	void nfcLedAction();
	void saveToDatabase();
	void enableProcess();
	void startDevice();

private:
	Button btns[NUM_BTN] = {Button(LED_1, BTN_1, 0.5), Button(LED_2, BTN_2, 1), Button(LED_3, BTN_3, 2)};
	NFC nfc;
	Tone tone;
	int currButton;
	bool buttonEnabled;
	bool newCall;
	double currAmount;
	double timeDiff;
	int ISO;
	std::chrono::high_resolution_clock::time_point emptyTimeSpan;
	std::ofstream dataFile;
};

#endif
