#include "Tiip.h"
#include <iomanip>
#include <ctime>

Tiip::Tiip() : currButton(0), buttonEnabled(false), newCall(false), currAmount(0), timeDiff(0), ISO(0) {}

void Tiip::init() {
	wiringPiSetup();
	tone.init(TONE_PIN);
	softPwmCreate(LED_NFC, 0, 100);
	nfc.initReader();
}

void Tiip::debounceAllExcept(int button) {
	for (int i=0; i<NUM_BTN; i++) {
		if (i != button) btns[i].setLed(0);
	}
}

void Tiip::enableButton(int button) {
	buttonEnabled = true;
	emptyTimeSpan = std::chrono::high_resolution_clock::now();
	currAmount = btns[button].getAmount();
	std::cout << currAmount << std::endl;
	btns[button].setLed(255);
	debounceAllExcept(button);
	btns[button].waitForRelease();
}

int Tiip::waitForButtonCall() {
	buttonEnabled = false;
	while (true) {
		for (int i=0; i<MAX_VAL+1; i++) {
			for (int j=0; j<NUM_BTN; j++) {
				if (btns[j].getStatus()) return j;
				btns[j].setLed(i);
			}
			delay(4);
		}
		for (int i=MAX_VAL; i>=0; i--) {
			for (int j=0; j<NUM_BTN; j++) {
				if (btns[j].getStatus()) return j;
				btns[j].setLed(i);
			}
			delay(4);
		}
		delay(200);
	}
}

void Tiip::setAllLeds(int val) {
	for (int i=0; i<NUM_BTN; i++) btns[i].setLed(val);
}

void Tiip::successActionLED() {
	buttonEnabled = false;
	setAllLeds(255);
	delay(500);
	setAllLeds(0);
	delay(500);
	setAllLeds(255);
	delay(500);
	setAllLeds(0);
	delay(500);
	setAllLeds(255);
	delay(500);
	setAllLeds(0);
	delay(1000);
}

void Tiip::successActionTone() {
	tone.takeOnMe();
}

void Tiip::pollButtons() {
	while (true) {
		for (int i=0; i<NUM_BTN; i++) {
			if (btns[i].getStatus()) enableButton(i);
		}
	}
}

void Tiip::nfcLedAction() {
	while (true) {
		if (buttonEnabled) {
			for (int i=0;i<=100;i++) {
				softPwmWrite(LED_NFC, i);
				delay(3);
			}
			for (int i=100;i>=0;i--) {
				softPwmWrite(LED_NFC, i);
				delay(3);
			}
			delay(150);
		}
	}
}

void Tiip::saveDataToFile() {
	dataFile.open("dataFile.csv");
	std::time_t t = std::time(0);
	dataFile << std::put_time(std::localtime(&t), "%c %Z") << "," << currAmount << std::endl;
}

void Tiip::enableProcess() {
	while (true) {
		// check if no interaction (no button pressed)
		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double,std::milli> time_span = now - emptyTimeSpan;
		timeDiff = time_span.count();
		if (timeDiff > 10000 || timeDiff == 0 || newCall) {
			newCall = false;
			currButton = waitForButtonCall();
			enableButton(currButton);
		}

		if (buttonEnabled && nfc.isCardPresent(ISO^=1)) {
			newCall = true;
			saveDataToFile();
			std::thread toggle_leds(&Tiip::successActionLED, this);
			std::thread toggle_tone(&Tiip::successActionTone, this);
			toggle_leds.join();
			toggle_tone.join();
		}
	}
}

void Tiip::startDevice() {
	std::thread poll_buttons(&Tiip::pollButtons, this);
	std::thread enable_process(&Tiip::enableProcess, this);
	std::thread toggle_nfc_led(&Tiip::nfcLedAction, this);
	poll_buttons.join();
	enable_process.join();
	toggle_nfc_led.join();
}