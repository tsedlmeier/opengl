CFLAGS= -O2 -Wall
LDFLAGS= -lGL -lSDL2 -lGLEW -lglfw
SRC= main.cpp shader.cpp

.PHONY: all

all: opengl

run: 
	./fft

opengl:
	g++ -std=c++17 $(SRC) $(CFLAGS) $(LDFLAGS) $< -o $@

debug:
	g++ -std=c++17 -g $(SRC) $(LDFLAGS) $< -o $@

clean:
	rm opengl
