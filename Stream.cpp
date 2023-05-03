#include "Stream.h"

Stream::Stream(std::string name, std::string extension, std::string content) {
	this->streamName = name;
	this->extension = extension;
	this->content = content;
	this->listingName = "";
}

Stream::Stream(std::string name, std::string extension, std::string content, std::string listingName) {
	this->streamName = name;
	this->extension = extension;
	this->content = content;
	this->listingName = listingName;
}

std::string Stream::getName() {
	return this->streamName;
}

std::string Stream::getListingName() {
	return this->listingName;
}

std::string Stream::getExtension() {
	return this->extension;
}

void Stream::setContent(std::string content) {
	this->content = content;
}

void Stream::addToStream(std::string name, std::string mediaType) {
	std::string extSuffix;
	if (this->extension == "") extSuffix = this->streamName;
	else extSuffix = this->streamName + "." + this->extension;

	std::string checking = "if exist .\\ukryte\\temp\\ ( exit 1 ) else ( exit 0 )";
	int status = system(checking.c_str());

	// tworzenie tymczasowego folderu
	if (status == 0) {
		std::string creating = "md .\\ukryte\\temp";
		system(creating.c_str());
	}

	std::string buffering = "type nul > .\\ukryte\\temp\\" + this->streamName + "_temp.buffer";
	system(buffering.c_str());

	std::ofstream tmpFile;
	std::string filePath = ".\\ukryte\\temp\\" + this->streamName + "_temp.buffer";
	
	tmpFile.open(filePath);

	// przepisywanie zawartoœci do bufora
	tmpFile << this->content << std::endl;

	std::string adding = "more < .\\ukryte\\temp\\" + this->streamName + "_temp.buffer > " + name + ":" + extSuffix;

	system(adding.c_str());

	tmpFile.close();
	
	remove(filePath.c_str());

	Menu::showSubMenu("TWORZENIE NOWEGO STRUMIENIA W " + mediaType, "Pomyœlnie dodano strumieñ!");
	if(this->extension == "") Menu::printMenuIndex(10, 6, 11, name + ":" + this->streamName);
	else Menu::printMenuIndex(10, 6, 11, name + ":" + this->streamName + "." + this->extension);
	Menu::printMenuIndex(10, 8, 11, "Wciœnij klawisz ¿eby wróciæ...");
	system("timeout /t -1 > nul");

}


void Stream::changeStreamContent(std::string name, std::string streamName, std::string extension, std::string content) {

	std::string extSuffix;
	if (extension == "") extSuffix = streamName;
	else extSuffix = streamName + "." + extension;

	std::string checking = "if exist .\\ukryte\\temp\\ ( exit 1 ) else ( exit 0 )";
	int status = system(checking.c_str());

	// tworzenie tymczasowego folderu
	if (status == 0) {
		std::string creating = "md .\\ukryte\\temp";
		system(creating.c_str());
	}

	std::string buffering = "type nul > .\\ukryte\\temp\\" + streamName + "_temp.buffer";
	system(buffering.c_str());

	std::ofstream tmpFile;
	std::string filePath = ".\\ukryte\\temp\\" + streamName + "_temp.buffer";

	tmpFile.open(filePath);

	// przepisywanie zawartoœci do bufora
	tmpFile << content << std::endl;

	std::string adding = "more < .\\ukryte\\temp\\" + streamName + "_temp.buffer > " + name + ":" + extSuffix;

	system(adding.c_str());

	tmpFile.close();

	remove(filePath.c_str());

	Menu::showSubMenu("EDYCJA STRUMIENIA" + name + ":" + extSuffix, "Edycja siê powiod³a!");
	Menu::printMenuIndex(10, 6, 11, "Nowa wartoœæ: " + content);
	Menu::printMenuIndex(10, 8, 11, "Wciœnij klawisz ¿eby wróciæ...");
	system("timeout /t -1 > nul");
}

void Stream::readFromStream(std::string fileName) {
	std::string extSuffix;
	if (extension == "") extSuffix = this->streamName;
	else extSuffix = this->streamName + "." + this->extension;

	std::string adding = "type nul > .\\ukryte\\temp\\" + streamName + "_temp.streams";
	system(adding.c_str());

	std::string rewriting = "more < " + fileName + ":" + extSuffix + " > .\\ukryte\\temp\\" + this->streamName + "_temp.streams";

	std::ifstream tmpFile(".\\ukryte\\temp\\" + this->streamName + "_temp.streams");
	std::string streamLine;

	int currentLine = 8;

	if (tmpFile.is_open()) {
		while (tmpFile) {
			std::getline(tmpFile, streamLine);
			Menu::printMenuIndex(10, currentLine, 11, streamLine);
			currentLine++;
		}
	}

	tmpFile.close();
	std::string removing = ".\\ukryte\\temp\\" + this->streamName + "_temp.streams";
	remove(removing.c_str());

	std::cin.ignore();
}


void Stream::readFromStreams(std::string fileName, std::string streamName, std::string extension) {
	std::string extSuffix;
	if (extension == "") extSuffix = streamName;
	else extSuffix = streamName + "." + extension;

	std::string adding = "type nul > .\\ukryte\\temp\\" + streamName + "_temp.streams";
	system(adding.c_str());

	std::string rewriting = "more < " + fileName + ":" + extSuffix + " > .\\ukryte\\temp\\" + streamName + "_temp.streams";
	system(rewriting.c_str());

	std::ifstream tmpFile(".\\ukryte\\temp\\" + streamName + "_temp.streams");
	std::string streamLine;

	int currentLine = 6;

	if (tmpFile.is_open()) {
		while (tmpFile) {
			std::getline(tmpFile, streamLine);
			Menu::printMenuIndex(10, currentLine, 11, streamLine + " ");
			currentLine++;
		}
	}

	tmpFile.close();
	std::string removing = ".\\ukryte\\temp\\" + streamName + "_temp.streams";
	remove(removing.c_str());
}

int Stream::readFromStreams(std::string fileName, std::string streamName, std::string extension, std::string appName) {
	std::string extSuffix;
	if (extension == "") extSuffix = streamName;
	else extSuffix = streamName + "." + extension;

	if (appName == "groove" || appName == "Groove" || appName == "mp3" ) {
		std::string buffering = "expand " + fileName + ":" + extSuffix + " .\\ukryte\\temp\\" + streamName + "_buff.mp3";
		system(buffering.c_str());

		system("cls");
		Menu::showSubMenu("ODCZYTYWANIE ZAWARTOŒCI STRUMIENIA DANYCH W PLIKU", "zawartoœæ strumienia wyœwietli siê w nowym oknie aplikacji " + appName);
		std::string playing = "\".\\ukryte\\temp\\" + streamName + "_buff.mp3\"";
		system(playing.c_str());
		system("timeout /t -1 > nul");

		std::string erasing = "type nul > " + playing;
		system(erasing.c_str());
		std::string deleting = "del " + playing;
		system(deleting.c_str());
	}
	else if (appName == "movies" || appName == "Movies" || appName == "videos" || appName == "Videos" || appName == "mp4" || appName == "MP4") {
		std::string buffering = "expand " + fileName + ":" + extSuffix + " .\\ukryte\\temp\\" + streamName + "_buff.mp4";
		system(buffering.c_str());

		system("cls");
		Menu::showSubMenu("ODCZYTYWANIE ZAWARTOŒCI STRUMIENIA DANYCH W PLIKU", "zawartoœæ strumienia wyœwietli siê w nowym oknie aplikacji " + appName);
		std::string playing = "\".\\ukryte\\temp\\" + streamName + "_buff.mp4\"";
		system(playing.c_str());

		system("timeout /t -1 > nul");
		std::string erasing = "type nul > " + playing;
		system(erasing.c_str());
		std::string deleting = "del " + playing;
		system(deleting.c_str());
	}
	else if (appName == "notepad" || appName == "mspaint" || appName == "Notepad" || appName == "MSpaint" || appName == "Mspaint") {
		std::string reading = appName + " " + fileName + ":" + extSuffix;
		system(reading.c_str());
	}
	else if (appName == "txt") {
		std::string reading = "notepad " + fileName + ":" + extSuffix;
		system(reading.c_str());
	}
	else if (appName == "txt") {
		std::string reading = "notepad " + fileName + ":" + extSuffix;
		system(reading.c_str());
	}
	else if (appName == "doc") {
		std::string reading = "write " + fileName + ":" + extSuffix;
		system(reading.c_str());
	}
	else if (appName == "jpg" || appName == "png" || appName == "gif") {
		std::string reading = "mspaint " + fileName + ":" + extSuffix;
		system(reading.c_str());
	} else return -1;

	return 0;
}

void Stream::moveFileToStream(std::string srcName, std::string fileName) {
	std::string extSuffix;
	if (this->extension == "") extSuffix = this->streamName;
	else extSuffix = this->streamName + "." + this->extension;

	std::string moving = "more < " + srcName + " > " + fileName + ":" + extSuffix;
	system(moving.c_str());

}

void Stream::moveBinaryToStream(std::string srcName, std::string fileName, std::string streamName, std::string extension) {
	std::string extSuffix;
	if (extension == "") extSuffix = streamName;
	else extSuffix = streamName + "." + extension;

	std::string moving = "type " + srcName + " > " + fileName + ":" + extSuffix;
	system(moving.c_str());

	Menu::showSubMenu("PRZENOSZENIE PLIKÓW DO STRUMIENIA", "Przenoszenie udane! " + srcName + " -->" + fileName + ":" + extSuffix);
	system("timeout /t -1 > nul");
}
