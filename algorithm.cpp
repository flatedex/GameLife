#include "algorithm.h"

void clearScreen(void) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };

    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count);

    /* Fill the entire buffer with the current colors and attributes */
    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count);

    SetConsoleCursorPosition(hStdOut, homeCoords);

}

void printGrid(bool gridOne[_gridSize + 1][_gridSize + 1]) {
    for (int i = 1; i < _gridSize; i++)
    {
        for (int j = 1; j < _gridSize; j++)
        {
            if (gridOne[i][j] == true)
            {
                std::cout << " O ";
            }
            else
            {
                std::cout << " . ";
            }
            if (j == _gridSize - 1)
            {
                std::cout << std::endl;
            }
        }
    }
}

void compareGrid(bool(&gridOne)[_gridSize + 1][_gridSize + 1], bool(&gridTwo)[_gridSize + 1][_gridSize + 1]) {
    for (int a = 0; a < _gridSize; a++)
    {
        for (int b = 0; b < _gridSize; b++)
        {
            gridTwo[a][b] = gridOne[a][b];
        }
    }
}

bool GameExit(bool (&gridOne)[_gridSize + 1][_gridSize + 1], bool (&gridTwo)[_gridSize + 1][_gridSize + 1]) {
    for (int a = 0; a < _gridSize; a++)
    {
        for (int b = 0; b < _gridSize; b++)
        {
            if (gridTwo[a][b] != gridOne[a][b]) {
                return true;
            }
        }
    }
    return false;
}

void determineState(bool (& gridOne)[_gridSize + 1][_gridSize + 1]) {
    bool gridTwo[_gridSize + 1][_gridSize + 1] = {};
    compareGrid(gridOne, gridTwo);

    for (int a = 1; a < _gridSize; a++)
    {
        for (int b = 1; b < _gridSize; b++)
        {
            int alive = 0;
            for (int c = -1; c < 2; c++)
            {
                for (int d = -1; d < 2; d++)
                {
                    if (!(c == 0 && d == 0))
                    {
                        if (gridTwo[a + c][b + d])
                        {
                            ++alive;
                        }
                    }
                }
            }
            if (alive < 2)
            {
                gridOne[a][b] = false;
            }
            else if (alive == 3)
            {
                gridOne[a][b] = true;
            }
            else if (alive > 3)
            {
                gridOne[a][b] = false;
            }
        }
    }
}