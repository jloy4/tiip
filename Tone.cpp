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

#include "Tone.h"
#include <unistd.h>

Tone::Tone() {}

void Tone::init(int tone_pin) {
	wiringPiSetup();
	tonePin = tone_pin;
	softToneCreate(tone_pin);
}

void Tone::play(int tone, double duration) {
	softToneWrite(tonePin, tone);
	usleep(duration*1000);
}

void Tone::pause(double duration) {
	play(0, duration);
}

void Tone::takeOnMe() {
	double notesDuration = 187.5;
	double pauseDuration = notesDuration * 1.5;
	
	play(notes["f#"], notesDuration);
	pause(10);
	play(notes["f#"], notesDuration);
	pause(10);
	play(notes["f#"], notesDuration);
	pause(10);
	play(notes["d"], notesDuration);
	pause(pauseDuration);
	play(notes["b4"], notesDuration);
	pause(pauseDuration);
	play(notes["e"], notesDuration);
	pause(pauseDuration);
	play(notes["e"], notesDuration);
	pause(pauseDuration);
	play(notes["e"], notesDuration);
	pause(10);
	play(notes["g#"], notesDuration);
	pause(10);
	play(notes["g#"], notesDuration);
	pause(10);
	play(notes["a"], notesDuration);
	pause(10);
	play(notes["b"], notesDuration);
	pause(10);
	play(notes["a"], notesDuration);
	pause(10);
	play(notes["a"], notesDuration);
	pause(10);
	play(notes["a"], notesDuration);
	pause(10);
	play(notes["e"], notesDuration);
	pause(pauseDuration);
	play(notes["d"], notesDuration);
	pause(pauseDuration);
	play(notes["f#"], notesDuration);
	pause(pauseDuration);
	play(notes["f#"], notesDuration);
	pause(pauseDuration);
	play(notes["f#"], notesDuration);
	pause(10);
	play(notes["e"], notesDuration);
	pause(10);
	play(notes["e"], notesDuration);
	pause(10);
	play(notes["f#"], notesDuration);
	pause(10);
	play(notes["f#"], notesDuration);
	pause(10);
	play(notes["f#"], notesDuration);
	pause(10);
	play(notes["d"], notesDuration);
	pause(pauseDuration);
	play(notes["b4"], notesDuration);
	pause(pauseDuration);
	play(notes["e"], notesDuration);
	pause(pauseDuration);
	play(notes["e"], notesDuration);
	pause(pauseDuration);
	play(notes["e"], notesDuration);
	pause(10);
	play(notes["g#"], notesDuration);
	pause(10);
	play(notes["g#"], notesDuration);
	pause(10);
	play(notes["a"], notesDuration);
	pause(10);
	play(notes["b"], notesDuration);
	pause(10);
	play(notes["a"], notesDuration);
	pause(10);
	play(notes["a"], notesDuration);
	pause(10);
	play(notes["a"], notesDuration);
	pause(10);
	play(notes["e"], notesDuration);
	pause(pauseDuration);
	play(notes["d"], notesDuration);
	pause(pauseDuration);
	play(notes["f#"], notesDuration);
	pause(pauseDuration);
	play(notes["f#"], notesDuration);
	pause(pauseDuration);
	play(notes["f#"], notesDuration);
	pause(10);
	play(notes["e"], notesDuration);
	pause(10);
	play(notes["e5"], notesDuration);
	pause(10);
}
