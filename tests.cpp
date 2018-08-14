#include <iostream>
#include <stdlib.h>
#include <nfc/nfc.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>
#include <softTone.h>
#include <map>
#include <string>

static void print_nfc_target(const nfc_target *pnt) {
  char *s;
  str_nfc_target(&s, pnt, true);
  std::cout << s;
  nfc_free(s);
  std::cout << "ok" << std::endl;
}

std::map<std::string, int> notes = {
	{"f#", 740},
	{"d", 587},
	{"b4", 494},
	{"e", 659},
	{"g#", 831},
	{"a", 880},
	{"e5", 659}
};

double notesDuration = 187.5;
double pauseDuration = notesDuration*1.5;

void play(int tone, double duration) {
	softToneWrite(6, tone);
	usleep(duration*1000);
}

void pause(double duration) {
	play(0, duration);
}
int main(int argc, const char *argv[]) {
	// const int tone = atoi(argv[1]);

	wiringPiSetup();
	softPwmCreate(21, 0, 100);
	softPwmWrite(21, 100);
	usleep(1000);
	softToneCreate(6);
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

	/*nfc_device *pnd;
	nfc_target nt;
	nfc_context *context;
	nfc_init(&context);

	if (context == NULL) {
		std::cerr << "Unable to init libnfc (malloc)." << std::endl;
		exit(EXIT_FAILURE);
	}

	const char *acLibnfcVersion = nfc_version();
	(void)argc;
	std::cout << argv[0] << " uses libnfc " << acLibnfcVersion << "." << std::endl;

	pnd = nfc_open(context, NULL);
	if (pnd == NULL) {
		std::cerr << "Unable to open NFC device." << std::endl;
		nfc_exit(context);
		exit(EXIT_FAILURE);
	}

	if (nfc_initiator_init(pnd) < 0) {
		nfc_perror(pnd, "nfc_initiator_init");
		nfc_close(pnd);
    	nfc_exit(context);
		exit(EXIT_FAILURE);
	}

	std::cout << "NFC reader: " << nfc_device_get_name(pnd) << " opened." << std::endl;
	
	const uint8_t uiPollNr = 1;
	const uint8_t uiPeriod = 2;
	const nfc_modulation nmModulations[2] = {
    	{ NMT_ISO14443A, NBR_106 },
    	{ NMT_ISO14443B, NBR_106 },
  	};

  	const size_t szModulations = 2;
  	int res = 0;

  	std::cout << "NFC device will poll during " << (unsigned long) uiPollNr * szModulations * uiPeriod * 150 << " ms." << std::endl;
	if ((res = nfc_initiator_poll_target(pnd, nmModulations, szModulations, uiPollNr, uiPeriod, &nt)) < 0) {
		nfc_perror(pnd, "nfc_initiator_poll_target");
		nfc_close(pnd);
		nfc_exit(context);
		exit(EXIT_FAILURE);
	}

	if (res > 0) print_nfc_target(&nt);
	else std::cout << "No target found." << std::endl;
	
	const int led = atoi(argv[1]);
	wiringPiSetup();
	softPwmCreate(led, 0, 100);
	while (1) {
		softPwmWrite(led, 100);
		usleep(100*1000);
		softPwmWrite(led, 0);
		usleep(100*1000);
	}*/
}
