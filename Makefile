CC = g++
CFLAGS = -lSDL2 -ldl -I./include/ -lGL
EXEC = res

src = $(wildcard src/*.c*)

%.hpp: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

all: $(src)
	$(CC) $^ -o $(EXEC) $(CFLAGS)

clean:
	rm -f $(EXEC)