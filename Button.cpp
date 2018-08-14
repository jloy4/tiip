#include "Button.h"

#define MAX_VAL 100

Button::Button(const int led_pin, const int button_pin, const double amount_) : ledPin(led_pin), buttonPin(button_pin), amount(amount_) {
	wiringPiSetup();
	softPwmCreate(led_pin, 0, MAX_VAL);
	//pinMode(led_pin, PWM_OUTPUT);
	pinMode(button_pin, INPUT);
}

bool Button::getStatus() {
	state = digitalRead(buttonPin);
	return state;
}

double Button::getAmount() {
	return amount;
}

void Button::setLed(int value) {
	softPwmWrite(ledPin, value);
	//pwmWrite(ledPin, value);
	usleep(1000);
}

void Button::waitForRelease() {
	while (this->getStatus());
}