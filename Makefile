
all: clean look_main

ps3:
	g++ -c ps3.cpp

serial:
	g++ -c serial.cpp

look:
	g++ -c look.cpp

look_main:
	g++ -c look.cpp
	g++ -c look_main.cpp
	g++ -c serial.cpp
	g++ -c ps3.cpp
	g++ -o look_main look.o look_main.o serial.o ps3.o

clean:
	rm -rf look_main *.o
