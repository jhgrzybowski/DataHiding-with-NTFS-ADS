#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Menu.h"

class Stream {
private:
	std::string streamName;
	std::string extension;
	std::string content;

	std::string listingName;
public:
	Stream(std::string name, std::string extension, std::string content);
	Stream(std::string name, std::string extension, std::string content, std::string listingName);

	std::string getName();
	std::string getListingName();

	std::string getExtension();

	void setContent(std::string content);
	
	void addToStream(std::string name, std::string mediaType);
	static void changeStreamContent(std::string name, std::string streamName, std::string extension, std::string content);

	// dla plików i folderów
	void readFromStream(std::string fileName);
	static void readFromStreams(std::string fileName, std::string streamName, std::string extension);
	static int readFromStreams(std::string fileName, std::string streamName, std::string extension, std::string appName);

	
	// otworzenie strumieni za pomoc¹ innych aplikacji
	void readFromStream(std::string fileName, std::string appName);

	void moveFileToStream(std::string srcName, std::string fileName);
	static void moveBinaryToStream(std::string srcName, std::string fileName, std::string streamName, std::string extension);
	
	void deleteStream(std::string fileName);

};

