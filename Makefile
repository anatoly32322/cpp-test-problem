all: main

main: main.cpp
	gcc main -fPIC -o main.cpp

clear:
	rm main results.out