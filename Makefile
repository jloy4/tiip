CC=g++
CFLAGS=-std=c++11 -Wall

v1:
	g++ main1.cpp -o tiip -lwiringPi -std=c++11 -lnfc -Wall

tip:
	$(CC) -c Button.cpp -o Button.o $(CFLAGS) -lwiringPi
	$(CC) -c NFC.cpp -o NFC.o $(CFLAGS) -lnfc
	$(CC) -c Tone.cpp -o Tone.o $(CFLAGS) -lwiringPi -lpthread
	$(CC) -c Tiip.cpp -o Tiip.o $(CFLAGS) -lnfc -lwiringPi -lpthread
	$(CC) -g main.cpp Button.o NFC.o Tone.o Tiip.o -o tiip $(CFLAGS) -lnfc -lwiringPi -lpthread -lcurl

test:
	$(CC) tests.cpp -o tests $(CFLAGS) -lwiringPi -lpthread -lnfc

fire:
	$(CC) database_test.cpp -o database_test $(CFLAGS) -lcurl

clean:
	rm *.o
