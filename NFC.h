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
