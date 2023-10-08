#!/usr/bin/env bash

CXXFLAGS = -march=i686 -m32 -O3
CFLAGS = $(CXXFLAGS)

all: libmtrandom.so

libmtrandom.so: libmtrandom.cpp
	$(CXX) -std=gnu++11 $(CXXFLAGS) $^ -Wl,--version-script=libmtrandom.map -fno-pic -static-libstdc++ --shared -s -Wall -Wextra -Wpedantic -o $@

test: test.c
	$(CC) -std=gnu89 $(CFLAGS) -O1 $^ -o $@

clean:
	$(RM) test libmtrandom.so
