# Makefile

# Variables
CC = g++
CFLAGS = -Wall -std=c++14 -D_DEFAULT_SOURCE -Wno-missing-braces -g -O0
LDFLAGS = -LC:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -DPLATFORM_DESKTOP -Wl,--subsystem,windows

# Targets and rules
all: pong_game

pong_game: main.o ball.o paddle.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -c $<

ball.o: ball.cpp
	$(CC) $(CFLAGS) -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -c $<

paddle.o: paddle.cpp
	$(CC) $(CFLAGS) -IC:/raylib/raylib/src -IC:/raylib/raylib/src/external -c $<

clean:
	del *.o pong_game.exe
