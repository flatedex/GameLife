#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>
#include "menu.h"

class FileWork {
	std::string m_path;
public:
	FileWork(std::string path);
	bool NameForbidden(void);
	std::string RewriteName(void);
	bool FileExist(void);
	bool SaveFileNormal(void);
	bool FileReadOnly();
	void Output(bool input[_gridSize + 1][_gridSize + 1]);
	void SaveData(bool input[_gridSize + 1][_gridSize + 1]);
	bool Input(bool (&input)[_gridSize + 1][_gridSize + 1]);
};

void WriteResultInFile(bool(&input)[_gridSize + 1][_gridSize + 1]);
void WriteDataInFile(bool(&input)[_gridSize + 1][_gridSize + 1]);

void ReadFromFile(bool(&inputArray)[_gridSize + 1][_gridSize + 1]);