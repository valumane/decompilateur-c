CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic

RETRO_SOURCES := $(wildcard src/retro/*.cpp)
HEXA_SOURCES := $(wildcard src/hexa/*.cpp)

.PHONY: all
all: build/retro build/hexa build/exemple

build/retro: $(RETRO_SOURCES) $(wildcard src/retro/*.hpp) | build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(RETRO_SOURCES) $(LDFLAGS) -o $@

build/hexa: $(HEXA_SOURCES) $(wildcard src/hexa/*.hpp) | build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(HEXA_SOURCES) $(LDFLAGS) -o $@

build/exemple: exemples/exemple.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -O0 $< $(LDFLAGS) -o $@

build:
	mkdir -p $@
