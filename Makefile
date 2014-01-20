
all: clean look_main

serial:
	g++ -c serial.cpp

look:
	g++ -c look.cpp

look_main:
	g++ -c look.cpp
	g++ -c look_main.cpp
	g++ -c serial.cpp
	g++ -o look_main look.o look_main.o serial.o

clean:
	rm -rf look_main *.o
