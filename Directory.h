#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Stream.h";
#include "Menu.h";

class Directory {
private:
	std::string path;
public:

	std::vector<Stream*> streams;
	std::vector<std::string> allPaths;

	Directory(std::string path);
	
	void createNewDirectory(std::string path);

	void changeRootDirectory(std::string dir);
	void changeDirectory(std::string dir);

	std::vector<std::string> getFileList();

	
	std::string getPath();
	void setPath(std::string location);

	void addStream(std::string streamName, std::string extension, std::string content, std::string path);
	static void changeStream(std::string path, std::string streamName, std::string extension, std::string content);

	static void readStream(std::string path, std::string streamName, std::string extension);


};

