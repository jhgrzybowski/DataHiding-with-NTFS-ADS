#include "File.h"

int File::fileStreamCount = 0;

void writeContent(std::string path, std::string file) {
	std::string content;
	Menu::showConsoleCursor(true);
	Menu::printMenuIndex(10, 10, 11, "Podaj treœæ: ");
	COORD c;
	c.X = 0;
	c.Y = 12;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

	std::cin.ignore();
	std::getline(std::cin, content, '`');
	std::ofstream buffer(path + "\\" + file, std::ios_base::app);
	buffer << content;

	system("cls");
	Menu::printMenuIndex(10, 3, 0, "TWORZENIE NOWEGO PLIKU");
	Menu::printMenuIndex(10, 5, 11, "Treœæ do pliku '" + file + "' zosta³a dodana prawid³owo");
	Menu::printMenuIndex(10, 6, 11, "Wciœnij klawisz ¿eby wróciæ...");
	system("timeout /t -1 > nul");
}

void createFile(std::string path, std::string file) {
	std::string creating = "type nul > " + path + "\\" + file;
	system(creating.c_str());
	Menu::printMenuIndex(10, 8, 11, "Plik '" + file + "' zosta³ dodany prawid³owo!");
	Menu::printMenuIndex(10, 9, 11, "Czy chcesz dodaæ do niego treœæ tekstow¹? [T/N] : ");
	char choice;
	std::cin >> choice;
	if (choice == 't' || choice == 'T') {
		writeContent(path, file);
	}
	else if (choice == 'n' || choice == 'N') {
		Menu::printMenuIndex(10, 11, 11, "Wciœnij klawisz ¿eby wróciæ...");
		system("timeout /t -1 > nul");
	}
	else {
		Menu::printMenuIndex(10, 11, 11, "Wciœnij klawisz ¿eby wróciæ...");
		system("timeout /t -1 > nul");
	}
}

File::File(std::string name, Directory* dir, bool isPresent) {
	if (isPresent) {
		this->fileName = name;
		this->dir = dir;
	}
	else {
		std::string checking = "if exist " + this->dir->getPath() + "\\" + this->fileName + " ( exit 1 ) else ( exit 0 )";
		int status = system(checking.c_str());

		if (status == 0) {
			createFile(this->dir->getPath(), this->fileName);
		}
		else {
			Menu::printMenuIndex(10, 8, 11, "Plik ju¿ istnieje!");
			Menu::printMenuIndex(10, 10, 11, "Wciœnij klawisz ¿eby wróciæ...");
			system("timeout /t -1 > nul");
		}
		std::cin.ignore();
	}

}

File::File(std::string name, Directory* dir) {
	this->fileName = name;
	this->dir = dir;

	std::string checking = "if exist " + this->dir->getPath() + "\\" + this->fileName + " ( exit 1 ) else ( exit 0 )";
	int status = system(checking.c_str());
	
	if (status == 0) {
		createFile(this->dir->getPath(), this->fileName);
	}
	else {
		Menu::printMenuIndex(10, 8, 11, "Plik ju¿ istnieje!");
		Menu::printMenuIndex(10, 10, 11, "Wciœnij klawisz ¿eby wróciæ...");
		system("timeout /t -1 > nul");
	}
	
	std::cin.ignore();
}

File::File(std::string name) {
	this->fileName = name;
	this->dir = new Directory("ukryte");

	std::string checking = "if exist " + this->dir->getPath() + "\\" + this->fileName + " ( exit 1 ) else ( exit 0 )";
	int status = system(checking.c_str());

	if (status == 0) {
		createFile(this->dir->getPath(), this->fileName);
	}
	else {
		Menu::printMenuIndex(10, 8, 11, "Plik ju¿ istnieje!");
		Menu::printMenuIndex(10, 10, 11, "Wciœnij klawisz ¿eby wróciæ...");
		system("timeout /t -1 > nul");

	}
	std::cin.ignore();
}

File::~File() {
	streams.clear();
	remove((this->dir->getPath() + "\\" + this->fileName).c_str());
}


std::vector<File*> File::updateFilesList(std::vector<std::string> fileNames, Directory* currentDir) {
	std::vector<File*> filesList;

	// aktualizacja listy plików o te, które znajduj¹ siê w obecnym folderze
	for (int i = 0; i < fileNames.size(); i++) {
		File* f = new File(fileNames[i], currentDir, true);
		filesList.push_back(f);
	}

	return filesList;
}

void File::addStream(std::string streamName, std::string extension, std::string content) {
	Stream* s = new Stream(streamName, extension, content);
	
	s->addToStream(this->dir->getPath() + "\\" + this->fileName, "PLIKU");
	this->streams.push_back(s);

	std::cin.ignore();
}

void File::changeStream(std::string streamName, std::string extension, std::string content) {

	Stream::changeStreamContent(this->dir->getPath() + "\\" + this->fileName, streamName, extension, content);


	std::cin.ignore();
}

void File::readStream(std::string streamName, std::string extension) {
	Menu::showSubMenu("ODCZYTYWANIE ZAWARTOŒCI STRUMIENIA DANYCH W PLIKU", "zawartoœæ " + this->fileName + ":" + streamName + extension + "\n");
	Stream::readFromStreams(this->dir->getPath() + "\\" + this->fileName, streamName, extension);
	system("timeout /t -1 > nul");
}

void File::readStreamUsingApp(std::string streamName, std::string extension, std::string appName) {
	Menu::showSubMenu("ODCZYTYWANIE ZAWARTOŒCI STRUMIENIA DANYCH W PLIKU", "zawartoœæ strumienia wyœwietli siê w nowym oknie aplikacji " + appName);
	int res = Stream::readFromStreams(this->dir->getPath() + "\\" + this->fileName, streamName, extension, appName);
	
	if (res == -1) {
		Menu::printMenuIndex(10, 6, 11, "Aplikacja nieobs³ugiwana!");
		system("timeout /t -1 > nul");
	}
	
}

std::vector<std::string> File::getStreamList() {
	std::string checking = "if exist .\\ukryte\\temp\\ ( exit 1 ) else ( exit 0 )";
	int status = system(checking.c_str());

	// tworzenie tymczasowego folderu
	if (status == 0) {
		std::string creating = "md .\\ukryte\\temp";
		system(creating.c_str());
	}

	// listing:
	// dir [œcie¿ka\plik] /r /a-d
	// wypisuje wszystkie pliki w³¹cznie z ich strumieniami
	std::string listing = "dir " + this->dir->getPath() + "\\" + this->fileName + " /r /a-d > .\\ukryte\\temp\\streams_" + this->fileName;
	system(listing.c_str());

	// tworzenie pliku tymczasowego 'streams_FILE'
	std::ifstream tmp(".\\ukryte\\temp\\streams_" + this->fileName);
	std::string ls;

	std::vector<std::string> streamsList;
	
	for (int i = 0; i < 6; i++) {
		std::getline(tmp, ls); // skasowanie niepotrzebnych danych z komendy dir (info o wolumenie itd.)
	}

	if (tmp.is_open()) {
		while (tmp.good()) {
			std::getline(tmp, ls); // pobieranie aktualnie znajduj¹cych siê strumieni danych
			streamsList.push_back(ls);
		}
	}

	// usuniêcie nadmiaru linii
	streamsList.pop_back();
	streamsList.pop_back();
	streamsList.pop_back();

	return streamsList;

	// trochê magii z pobieraniem inputu z listingu, ale dzia³a :)
}

void File::updateStreamList(std::vector<std::string> streamsList) {
	
	// aktualizacja obecnej listy strumieni o te, które nale¿¹ do danego pliku
	for (int i = 0; i < streamsList.size(); i++) { 
		streamsList[i].erase(0, 19); // usuniêcie bia³ych znaków z wyjœcia listingu
		this->streams.push_back(new Stream("", "", "", streamsList[i]));
	}


	// usuniêcie pliku tymczasowego 'streams_FILE'
	std::string tmpName = ".\\ukryte\\temp\\streams_" + this->fileName;
	remove(tmpName.c_str());

}

void File::setFileName(std::string name) {
	this->fileName = name;
}

void File::setRootLocation(std::string location) {
	this->location = location;
	this->dir->changeRootDirectory(location);
}

void File::setLocation(std::string location) {
	this->location = location;
	this->dir->changeDirectory(location);
}

std::string File::getFileName() {
	return this->fileName;
}

std::string File::getLocation() {
	return this->location;
}

/*** nieaktywna funkcja dla debuggingu ***
void File::showListing(std::vector<std::string> s) {

	system("cls");
	int cnt = 3;
	for (int i = 0; i < s.size(); i++) {
		Menu::printMenuIndex(10, ++cnt, 11, s[i]);
	}
}
*/
