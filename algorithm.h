#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

void clearScreen(void);
void printGrid(bool gridOne[_gridSize + 1][_gridSize + 1]);
void compareGrid(bool gridOne[_gridSize + 1][_gridSize + 1], bool gridTwo[_gridSize + 1][_gridSize + 1]);
bool GameExit(bool gridOne[_gridSize + 1][_gridSize + 1], bool gridTwo[_gridSize + 1][_gridSize + 1]);
void determineState(bool gridOne[_gridSize + 1][_gridSize + 1]);