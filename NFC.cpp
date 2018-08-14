#include "NFC.h"
#include <stdlib.h>

#include <iostream>
#include <chrono>

NFC::NFC() {}

void NFC::initReader() {
	nfc_init(&context);

	if (context == NULL) {
		std::cerr << "Unable to init libnfc (malloc)." << std::endl;
		exit(EXIT_FAILURE);
	}

	/*const char *acLibnfcVersion = nfc_version();
	(void)argc;
	std::cout << argv[0] << " uses libnfc " << acLibnfcVersion << "." << std::endl;*/

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
}

bool NFC::isCardPresent(int cardType) { //0 for type A, 1 for type B
	auto now = std::chrono::high_resolution_clock::now();
	int res = (cardType == 0) ? nfc_initiator_poll_target(pnd, nmISO_A, szModulations, uiPollNr, uiPeriod, &nt) : 
								nfc_initiator_poll_target(pnd, nmISO_B, szModulations, uiPollNr, uiPeriod, &nt);
	// int res = nfc_initiator_select_passive_target(pnd, nmISO_A, NULL, 0, &nt);
	std::chrono::duration<double,std::milli> time_span = std::chrono::high_resolution_clock::now() - now;
	std::cout << "polling time: " << time_span.count() << " ms" << std::endl;
	if (res > 0) return true;
	return false;
}