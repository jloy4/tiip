/*
 *    Copyright 2018, Jonas Loy, All rights reserved.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 *    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
 *    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 *    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


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
