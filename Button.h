#ifndef DEF_BUTTON_H
#define DEF_BUTTON_H

#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>

class Button {
public:
	Button(const int led_pin, const int button_pin, const double amount_);
	bool getStatus();
	double getAmount();
	void setLed(int value);
	void waitForRelease();

private:
	const int ledPin;
	const int buttonPin;
	const double amount;
	int state;
};

#endif