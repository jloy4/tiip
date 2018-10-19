v1:
	g++ main1.cpp -o tiip -lwiringPi -std=c++11 -lnfc -Wall

v2:
	g++ -c Button.cpp -o Button.o -std=c++11 -lwiringPi
	g++ -c NFC.cpp -o NFC.o -std=c++11 -lnfc
	g++ -c Tone.cpp -o Tone.o -std=c++11 -lwiringPi -lpthread
	g++ -c Tiip.cpp -o Tiip.o -std=c++11 -lnfc -lwiringPi -lpthread -Wall
	g++ -g main.cpp Button.o NFC.o Tone.o Tiip.o -o tiip -std=c++11 -lnfc -lwiringPi -lpthread -Wall -lcurl

test:
	g++ tests.cpp -o tests -lwiringPi -lpthread -lnfc -std=c++11

fire:
	g++ database_test.cpp -o database_test -lcurl -std=c++11

clean:
	rm *.o
