#ifndef DEF_NFC_H
#define DEF_NFC_H

#include <nfc/nfc.h>

class NFC {
public:
	NFC();
	void initReader();
	bool isCardPresent(int cardType);

private:
	nfc_device *pnd;
	nfc_target nt;
	nfc_context *context;

	const uint8_t uiPollNr = 1;
	const uint8_t uiPeriod = 1;
	const nfc_modulation nmModulations[2] = {
    	{ NMT_ISO14443A, NBR_106 },
    	{ NMT_ISO14443B, NBR_106 },
  	};
	const nfc_modulation nmISO_A[1] = {
		{.nmt = NMT_ISO14443A,
		.nbr = NBR_106}
	};

	const nfc_modulation nmISO_B[1] = {
		{.nmt = NMT_ISO14443B,
		.nbr = NBR_106},
	};

  	const size_t szModulations = 1;

	int res = 0;
};

#endif