#!/bin/env bash
clang++ -I./include -I$SYSTEMC_HOME/include -c reset.cpp sc_main.cpp -std=c++17
g++ -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -o run.x reset.o sc_main.o -lsystemc -lm