#include <iostream>
#include <fstream>
#include <filesystem>
#include "file.h"


FileWork::FileWork(std::string path) {
	m_path = path;
}

bool FileWork::NameForbidden(void) {
	try {
		bool isNameNormal = false;
		isNameNormal = std::filesystem::is_regular_file(m_path);
	}
	catch (std::exception&) {
		std::cout << "Name forbidden!" << std::endl;
		return true;
	}
	return false;
}

std::string FileWork::RewriteName(void) {
	m_path = GetInput<std::string>();
	while (NameForbidden()) {
		m_path = GetInput<std::string>();
	}
	return m_path;
}

bool FileWork::FileExist(void) {
	std::ifstream checkFile;
	checkFile.open(m_path);
	if (checkFile.is_open()) {
		checkFile.close();
		return true;
	}
	else {
		return false;
	}
}

bool FileWork::SaveFileNormal(void) {
	bool fileCreated = false;
	if (NameForbidden()) {
		return false;
	}
	if (FileExist()) {
		return true;
	}
	while (!fileCreated) {
		std::ofstream tryCreate;
		tryCreate.open(m_path);
		tryCreate << "check";
		tryCreate.close();
		std::ifstream tryOpen;
		tryOpen.open(m_path);
		if (tryOpen.is_open()) {
			tryOpen.close();
			remove(m_path.c_str());
			fileCreated = true;
		}
		else {
			tryOpen.close();
			fileCreated = false;
			std::cout << "Error occured during file creation. Check file name!" << std::endl;
			return false;
		}
	}
	return true;
}

bool FileWork::FileReadOnly(void) {
	std::ofstream outputFile;
	outputFile.open(m_path);
	if (outputFile.is_open()) {
		outputFile.close();
		return false;
	}
	else {
		std::cout << "File is readonly!" << std::endl;
		outputFile.close();
		return true;
	}
}

void FileWork::Output(bool input[_gridSize + 1][_gridSize + 1]) {
	std::ofstream outputFile;
	outputFile.open(m_path);
	/* save output here */
	outputFile.close();
}

void FileWork::SaveData(bool input[_gridSize + 1][_gridSize + 1]) {
	std::ofstream dataFile;
	dataFile.open(m_path);
	/* save input data here */
	dataFile.close();
}

bool FileWork::Input(bool (& input)[_gridSize + 1][_gridSize + 1]) {
	std::ifstream inputFile;
	std::string data;
	std::string temp;
	inputFile.open(m_path);

	if (!inputFile.is_open()) {
		std::cout << "File not found" << std::endl;
		return false;
	}
	if (inputFile.is_open())
	{
		std::string fileline, xx, yy;

		while (getline(inputFile, fileline))
		{
			std::stringstream ss(fileline);

			getline(ss, xx, ' ');
			getline(ss, yy, ' ');

			int x = stoi(xx);
			int y = stoi(yy);

			input[x][y] = true;
		}
	}


	if (input == NULL) {
		std::cout << "File is empty" << std::endl;
		inputFile.close();
		return false;
	}
	else {
		inputFile.close();
		return true;
	}
}

void WriteInFile(bool(&input)[_gridSize + 1][_gridSize + 1]) {
	std::string path;
	Menu rewrite = Menu::YES;
	std::cout << "Enter file name" << std::endl;
	path = GetInput<std::string>();
	FileWork inputSaveFile(path);
	while (!inputSaveFile.SaveFileNormal()) {
		std::cout << "Enter new file name:" << std::endl;
		path = inputSaveFile.RewriteName();
	}
	std::ifstream checkFile;
	checkFile.open(path);
	if (checkFile.is_open()) {
		rewrite = AskRewriteFile(path);
		checkFile.close();
		if (rewrite == Menu::YES) {
			std::string newFilePath = path;
			FileWork newInputSave(newFilePath);
			while (newFilePath == path) {
				std::cout << "Enter new file name:" << std::endl;
				newFilePath = newInputSave.RewriteName();
				while (!newInputSave.SaveFileNormal()) {
					std::cout << "" << std::endl;
					newFilePath = newInputSave.RewriteName();
				}
			}
			FileWork file(newFilePath);
			file.SaveData(input);
		}
		else {
			while (inputSaveFile.FileReadOnly()) {
				std::cout << "Enter new file name:" << std::endl;
				path = inputSaveFile.RewriteName();
			}
			FileWork file(path);
			file.SaveData(input);
		}
	}
	else {
		checkFile.close();
		while (inputSaveFile.FileReadOnly()) {
			std::cout << "Enter new file name:" << std::endl;
			path = inputSaveFile.RewriteName();
		}
		FileWork file(path);
		file.SaveData(input);
	}

}

void ReadFromFile(bool(&inputArray)[_gridSize + 1][_gridSize + 1]) {
	bool dataReaded = false;
	std::string path;
	std::cout << "Enter file name:" << std::endl;

	path = GetInput<std::string>();
	FileWork checkFile(path);

	while (checkFile.NameForbidden()) {
		std::cout << "Enter new file name:" << std::endl;
		path = checkFile.RewriteName();
	}
	FileWork input(path);
	dataReaded = input.Input(inputArray);
	while (!dataReaded) {
		std::cout << "Enter new file name:" << std::endl;
		path = input.RewriteName();
		dataReaded = input.Input(inputArray);
	}
}