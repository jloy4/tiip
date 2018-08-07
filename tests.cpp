#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>

int main() {
	wiringPiSetup();
	if (softPwmCreate(5, 0, 255) > 0);
	softPwmWrite(5, 255);
	usleep(4*1000*1000);
}
