#include "Tiip.h"
#include <curl/curl.h>

int main(int argc, char * argv[]) {
	// const int time = atoi(argv[1]);
	Tiip tiip;
	
	tiip.init();
	tiip.startDevice();
}
