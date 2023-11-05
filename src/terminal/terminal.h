#pragma once

#include <ncurses.h>
#include <iostream>
#include <vector>
#include <fstream> 

WINDOW *winmain;
int xPos;
int yPos;
int line;
int maxLines;
int frame;
int leftPad;
int charactorPos;
bool insert;
bool firstJ;

#define BLACK   9
#define YELLOW  10
#define OFFWIHTE  11