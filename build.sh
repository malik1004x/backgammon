#!/bin/bash

rm -rf build
mkdir build

gcc *.c -lncurses -Wall -o build/backgammon