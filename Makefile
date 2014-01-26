
all: clean main

ps3:
	g++ -c ps3.cpp

serial:
	g++ -c serial.cpp

look:
	g++ -c look.cpp

main:
	g++ -c look.cpp
	g++ -c main.cpp
	g++ -c serial.cpp
	g++ -c ps3.cpp
	g++ -o main look.o main.o serial.o ps3.o

clean:
	rm -rf main *.o
