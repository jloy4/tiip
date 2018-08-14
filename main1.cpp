#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <unistd.h>
#include <ctime>
#include <nfc/nfc.h>

#define NUM_BTN 3
#define BTN_1 0
#define BTN_2 2 
#define BTN_3 3
#define LED_1 1
#define LED_2 4
#define LED_3 5
#define MAX_VAL 100

class Button {
	public:
		Button(const int led_pin, const int button_pin, const double amount_) : ledPin(led_pin), buttonPin(button_pin), amount(amount_) {
			softPwmCreate(led_pin, 0, MAX_VAL);
			//pinMode(led_pin, PWM_OUTPUT);
			pinMode(button_pin, INPUT);
		}

		bool getStatus() {
			state = digitalRead(buttonPin);
			return state;
		}

		double getAmount() {return amount;}

		void setLed(int value) {
			softPwmWrite(ledPin, value);
			//pwmWrite(ledPin, value);
			usleep(1000);
		}

	private:
		const int ledPin;
		const int buttonPin;
		const double amount;
		int state;
};

int currButton = 0;
double currAmount = 0;
std::chrono::high_resolution_clock::time_point emptyTimeSpan;
double timeDiff = 0;

	// initialize buttons
	Button btns[NUM_BTN] = {Button(LED_1, BTN_1, 0.5), Button(LED_2, BTN_2, 1), Button(LED_3, BTN_3, 2)};

void debounceAllExcept(int button) {
	for (int i=0; i<NUM_BTN; i++) {
		if (i != button) btns[i].setLed(0);
	}
}

void waitForRelease(int button) {
	while (btns[button].getStatus());
}

void enableButton(int button) {
	emptyTimeSpan = std::chrono::high_resolution_clock::now();
	currAmount = btns[button].getAmount();
	std::cout << currAmount << std::endl;
	btns[button].setLed(255);
	debounceAllExcept(button);
	waitForRelease(button);
}

int waitForButtonCall() {
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

int main(int argc, char * argv[]) {
//	const int led = atoi(argv[1]);
	wiringPiSetup();

	while (true) {
		// check if no interaction (no button pressed)
		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double,std::milli> time_span = now - emptyTimeSpan;
		timeDiff = time_span.count();
		if (timeDiff > 10000 || timeDiff == 0) {
			currButton = waitForButtonCall();
			enableButton(currButton);
		}

		// check if button changed
		for (int i=0; i<NUM_BTN; i++) {
			if (btns[i].getStatus()) enableButton(i);
		}
	}
}

