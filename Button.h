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
