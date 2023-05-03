#pragma once
#include <string>
#include <vector>
#include "Directory.h"
#include "Stream.h"
#include "Menu.h"

class File {
private:
	std::string fileName;
	std::string location;
	Directory* dir;
public:

	static int fileStreamCount;
	std::vector<Stream*> streams;

	File(std::string name, Directory* dir);
	File(std::string name, Directory* dir, bool isPresent);
	File(std::string name);
	~File();
	
	static std::vector<File*> updateFilesList(std::vector<std::string> fileNames, Directory* currentDir);
	
	void addStream(std::string streamName, std::string extension, std::string content);
	void changeStream(std::string streamName, std::string extension, std::string content);
	void readStream(std::string streamName, std::string extension);
	void readStreamUsingApp(std::string streamName, std::string extension, std::string appName);

	std::vector<std::string> getStreamList();
	void updateStreamList(std::vector<std::string>);

	std::string getFileName();
	std::string getHiddenName();
	std::string getLocation();

	void setLocation(std::string location);
	void setRootLocation(std::string location);
	void setFileName(std::string name);
	void setHiddenName(std::string hidden);

	// ** nieaktywna funkcja dla debuggingu **
	// static void showListing(std::vector<std::string> s);
};

