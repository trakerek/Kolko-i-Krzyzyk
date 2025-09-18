CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -IC:/SFML/include -LC:/SFML/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard src/*.cpp) main.cpp
OUT = bin/main.exe

all: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC) $(LIBS)

clean:
	del /Q bin\main.exe
