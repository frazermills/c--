#pragma once

#include <ncurses.h>
#include <iostream>
#include <vector>
#include <fstream> 

WINDOW *winmain;
int xPos;
int line;
int maxLines;
int frame;
bool insert;

#define BLACK   9
#define YELLOW  10
#define OFFWIHTE  11