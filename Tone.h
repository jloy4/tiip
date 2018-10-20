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
