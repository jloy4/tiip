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

#include "Tiip.h"
#include <iomanip>
#include <ctime>
#include <string.h>
#include <iostream>
#include <sstream>

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

/*void Tiip::saveDataToFile() {
	dataFile.open("dataFile.csv");
	std::time_t t = std::time(0);
	dataFile << std::put_time(std::localtime(&t), "%c %Z") << "," << currAmount << std::endl;
}*/
<<<<<<< HEAD
=======

std::string getTime() {
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S %Z");
	auto str = oss.str();

	std::cout << str << std::endl;
	return str;
}
>>>>>>> 299ea3b8e683987bbb0d8774e1e23fc406904dea

void Tiip::saveToDatabase() {
	CURL *curl;
	CURLcode res;
	char data[80];
	snprintf(data, 80, "{\"time\":\"%s\",\"amount\":%.2f}\0",getTime().c_str(), currAmount);

	curl_global_init(CURL_GLOBAL_ALL);
	struct curl_slist *list = NULL;

	curl = curl_easy_init();
	if(curl) {
		// url to database
		curl_easy_setopt(curl, CURLOPT_URL, "https://tiips-fr.firebaseio.com/bar.json");

		//request headers
		list = curl_slist_append(list, "Content-Type: application/x-www-form-urlenconded");

		//curl options
		curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		curl_easy_setopt(curl, CURLOPT_HEADER, true);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(data));

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
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
<<<<<<< HEAD
			//saveDataToFile();
=======
>>>>>>> 299ea3b8e683987bbb0d8774e1e23fc406904dea
			std::thread toggle_leds(&Tiip::successActionLED, this);
			std::thread toggle_tone(&Tiip::successActionTone, this);
			std::thread send_data(&Tiip::saveToDatabase, this);
			toggle_leds.join();
			toggle_tone.join();
			send_data.join();
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
