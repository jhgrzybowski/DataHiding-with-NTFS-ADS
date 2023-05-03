#pragma once
#include <iostream>
#include <locale.h>
#include <fstream>
#include "File.h"
#include "Directory.h"
#include "Stream.h"
#include "Menu.h"

class DataHiding {
public:
	static void getUpdateFiles(std::vector<File*>& files, Directory* &currentDir);
	static void getInputForStream(std::string& streamName, std::string& extension, std::string& content, std::string mediaType);
	static void menuFunction(int function, Directory*& currentDir, std::vector<Directory*>& directories, std::vector<File*>& files);
	static void getInputName(std::string &name);
};
