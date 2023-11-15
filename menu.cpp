#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <Windows.h>
#include "menu.h"
#include "tests.h"
#include "file.h"
#include "algorithm.h"


void Greeting() {
	std::cout << "Zakirov Ilyas 404" << std::endl;
	std::cout << "Lab 1, variant #7" << std::endl;
	std::cout << "                         THE GAME OF life - Implementation in C++" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Also known simply as Life, " << std::endl;
	std::cout << "is a cellular automaton devised by the British mathematician John Horton Conway in 1970." << std::endl;
	std::cout << std::endl;
	std::cout << "Rules" << std::endl;
	std::cout << "The universe of the Game of life is an infinite two-dimensional orthogonal grid of square cells," << std::endl;
	std::cout << "each of which is in one of two possible states, life or dead. Every" << std::endl;
	std::cout << "cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent." << std::endl;
	std::cout << "At each step in time, the following transitions occur:" << std::endl;
	std::cout << "1. Any live cell with fewer than two live neighbours dies, as if caused by under-population." << std::endl;
	std::cout << "2. Any live cell with two or three live neighbours lives on to the next generation." << std::endl;
	std::cout << "3. Any live cell with more than three live neighbours dies, as if by over-population." << std::endl;
	std::cout << "4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction." << std::endl;
	std::cout << std::endl;
	std::cout << "O - living cell" << std::endl;
	std::cout << ". - dead cell" << std::endl;
	std::cout << std::endl;
}

bool RightMenuChoice(Menu choice) {
	if ((choice == Menu::NO) || (choice == Menu::YES)) {
		return true;
	}
	else {
		std::cout << "Use presented choises!" << std::endl;
		return false;
	}
}

bool RightInputChoice(InputType choice) {
	if ((choice == InputType::KEYBOARD) || (choice == InputType::FILE)) {
		return true;
	}
	else {
		std::cout << "Use presented choises!" << std::endl;
		return false;
	}
}

Menu AskTests(void) {
	std::cout << "Run tests?" << std::endl;
	std::cout << "1 - Yes" << std::endl;
	std::cout << "2 - No" << std::endl;
	std::cout << "Your choice:" << std::endl;
	Menu decision = static_cast<Menu>(GetInput<int>());
	while (!RightMenuChoice(decision)) {
		decision = static_cast<Menu>(GetInput<int>());
	}
	return decision;
}
Menu AskRepeat(void) {
	std::cout << "Would you like to run program again?" << std::endl;
	std::cout << "1 - Yes" << std::endl;
	std::cout << "2 - No" << std::endl;
	std::cout << "Your choice:" << std::endl;
	Menu decision = static_cast<Menu>(GetInput<int>());
	while (!RightMenuChoice(decision)) {
		decision = static_cast<Menu>(GetInput<int>());
	}
	return decision;
}

InputType AskInput(void) {
	std::cout << "How would you like to enter game state?" << std::endl;
	std::cout << "1 - From file" << std::endl;
	std::cout << "2 - Manually" << std::endl;
	std::cout << "Your choice:" << std::endl;
	InputType decision = static_cast<InputType>(GetInput<int>());
	while (!RightInputChoice(decision)) {
		decision = static_cast<InputType>(GetInput<int>());
	}
	return decision;
}

Menu AskSaveInput(void) {
	std::cout << "Save input to file?" << std::endl;
	std::cout << "1 - Yes" << std::endl;
	std::cout << "2 - No" << std::endl;
	std::cout << "Your choice:" << std::endl;
	Menu decision = static_cast<Menu>(GetInput<int>());
	while (!RightMenuChoice(decision)) {
		decision = static_cast<Menu>(GetInput<int>());
	}
	return decision;
}

Menu AskSaveResult(void) {
	std::cout << "Save result to file?" << std::endl;
	std::cout << "1 - Yes" << std::endl;
	std::cout << "2 - No" << std::endl;
	std::cout << "Your choice:" << std::endl;
	Menu decision = static_cast<Menu>(GetInput<int>());
	while (!RightMenuChoice(decision)) {
		decision = static_cast<Menu>(GetInput<int>());
	}
	return decision;
}

Menu AskRewriteFile(std::string path) {

	Menu decision = Menu::NO;

	std::cout << "File already exist!" << std::endl;
	std::cout << "1 - Create new" << std::endl;
	std::cout << "2 - Rewrite current" << std::endl;
	std::cout << "Your choice:" << std::endl;
	decision = static_cast<Menu>(GetInput<int>());
	while (!RightMenuChoice(decision)) {
		decision = static_cast<Menu>(GetInput<int>());
	}
	return decision;
}

Menu AskTypeOfGame() {
	Menu decision = Menu::NO;
	std::cout << "Grid setup is done. Start the game in manual mode or in auto mode?" << std::endl;
	std::cout << "1 - Manual" << std::endl;
	std::cout << "2 - Auto" << std::endl;
	std::cout << "Your choice:" << std::endl;
	decision = static_cast<Menu>(GetInput<int>());
	while (!RightMenuChoice(decision)) {
		decision = static_cast<Menu>(GetInput<int>());
	}
	return decision;
}

void MainFunction(void) {
	clearScreen();
	auto wantTests = Menu::YES;
	auto wantContinue = Menu::YES;
	auto wantSave = Menu::YES;
	auto wantRewrite = Menu::YES;
	auto inputType = InputType::KEYBOARD;
	auto gameType = Menu::YES;
	auto continueGame = Menu::YES;
	bool gridOne[_gridSize + 1][_gridSize + 1] = {};
	int x, y;
	std::string nc;
	std::string start;

	do {
		std::string filePath = "nothing";
		wantTests = AskTests();
		if (wantTests == Menu::YES) {
			Tests();
		}

		inputType = AskInput();

		if (inputType == InputType::FILE) {
			std::cout << "Grid input" << std::endl;
			ReadFromFile(gridOne);
			std::cout << "Source grid:" << std::endl;
			printGrid(gridOne);
		}
		else {
			std::cout << "Enter number of cells: " << std::endl;
			nc = GetInput<std::string>();
			for (int i = 0; i < stoi(nc); i++) {
				std::cout << stoi(nc) << "Enter the coordinates of cell " << i + 1 << " : ";
				x = GetInput<int>();
				y = GetInput<int>();
				gridOne[x][y] = true;
				printGrid(gridOne);
			}
		}
		gameType = AskTypeOfGame();
		if (gameType == Menu::YES) {
			bool ethalon[_gridSize + 1][_gridSize + 1] = {};
			compareGrid(gridOne, ethalon);
			while (GameExit(gridOne, ethalon)) {
				printGrid(gridOne);
				determineState(gridOne);
				compareGrid(gridOne, ethalon);
				std::cout << "___________________________________________________" << std::endl;
				std::cout << "Press any key to continue" << std::endl;
				std::cin.get();
			}
		}
		else {
			bool ethalon[_gridSize + 1][_gridSize + 1] = {};
			while (GameExit(gridOne, ethalon)) {
				printGrid(gridOne);
				determineState(gridOne);
				compareGrid(gridOne, ethalon);
				Sleep(50);
				std::cout << "___________________________________________________" << std::endl;
			}
		}

		if (inputType != InputType::FILE) {
			wantSave = AskSaveInput();
			if (wantSave == Menu::YES) {
				std::cout << "Saving source text" << std::endl;
				WriteInFile(gridOne);
			}
		}

		wantSave = AskSaveResult();
		if (wantSave == Menu::YES) {

			std::cout << "Enter file name:" << std::endl;
			filePath = GetInput<std::string>();
			FileWork outputSaveFile(filePath);
			while (!outputSaveFile.SaveFileNormal()) {
				std::cout << "Enter new file name" << std::endl;
				filePath = outputSaveFile.RewriteName();
			}
			wantRewrite = AskRewriteFile(filePath);
			if (wantRewrite == Menu::YES) {
				std::string newFilePath = filePath;
				FileWork newOutputSave(newFilePath);
				while (newFilePath == filePath) {
					std::cout << "Enter new file name" << std::endl;
					newFilePath = newOutputSave.RewriteName();
					while (!newOutputSave.SaveFileNormal()) {
						std::cout << "Enter new file name" << std::endl;
						newFilePath = newOutputSave.RewriteName();
					}
				}
				FileWork file(newFilePath);
				file.Output(gridOne);
			}
			else {
				while (outputSaveFile.FileReadOnly()) {
					std::cout << "Enter new file name" << std::endl;
					filePath = outputSaveFile.RewriteName();
				}
				FileWork file(filePath);
				file.Output(gridOne);
			}


		}
		wantContinue = AskRepeat();
	} while (wantContinue == Menu::YES);
}