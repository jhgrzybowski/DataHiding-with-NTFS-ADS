#include "Directory.h"

Directory::Directory(std::string path) {
	std::string checking = "if exist " + path + "\\ ( exit 1 ) else ( exit 0 )";
	
	int status = system(checking.c_str());

	// 0 == folder nie istnieje
	if (status == 0) {

		// tworzenie folderu nadrzêdnego (pierwotnego)
		// kolejne folderi bêd¹ po prostu dopisywane do listy folderów,
		// a obecny folder bêdzie zmieniany jeœli najdzie taka potrzeba
		std::string creating = "md " + path;
		system(creating.c_str());
		this->path = ".\\" + path;
		this->allPaths.push_back(this->path);
	}
	else {
		this->path = ".\\" + path;
	}
}

void Directory::createNewDirectory(std::string dir) {
	std::string checking = "if exist " + this->path + "\\" + dir + "\\ ( exit 1 ) else ( exit 0 )";
	int status = system(checking.c_str());

	// 0 == folder nie istnieje
	if (status == 0) {

		std::string creating = "md " + this->path + "\\" + dir; // utworzenie folderu
		system(creating.c_str());

		this->allPaths.push_back(this->path + "\\" + dir); // dodanie folderu do listy folderów

		Menu::printMenuIndex(10, 8, 11, "Folder '" + dir + "' zosta³ dodany prawid³owo!");
		Menu::printMenuIndex(10, 9, 11, "Œcie¿ka folderu : " + this->path + "\\" + dir);
		Menu::printMenuIndex(10, 11, 11, "Wciœnij klawisz ¿eby wróciæ...");
		system("timeout /t -1 > nul");
	}
	else {
		Menu::printMenuIndex(10, 8, 11, "Folder ju¿ istnieje!");
		Menu::printMenuIndex(10, 10, 11, "Wciœnij klawisz ¿eby wróciæ...");
		system("timeout /t -1 > nul");
	}
	
}

void Directory::changeDirectory(std::string dir) {
	if (dir == ".") {
		Menu::printMenuIndex(10, 8, 11, "Aktualna œcie¿ka : " + this->path);
		Menu::printMenuIndex(10, 10, 11, "Wciœnij klawisz ¿eby wróciæ...");
		system("timeout /t -1 > nul");

	}
	else {
		std::string changing = "if exist " + this->path + "\\" + dir + "\\ ( exit 1 ) else ( exit 0 )";

		int result = system(changing.c_str());

		// 0 == folder nie istnieje
		if (result == 0) {
			Menu::printMenuIndex(10, 8, 11, "Folder nie istnieje!");
			Menu::printMenuIndex(10, 10, 11, "Wciœnij klawisz ¿eby wróciæ...");
			system("timeout /t -1 > nul");
		}
		else {
			if (this->path == ".\\") {
				this->path = this->path + dir; // aby unikn¹æ podwojenia znaku backslash, np '.\\folder'
			}
			else {
				this->path = this->path + "\\" + dir; // wpisujemy normalnie podan¹ œcie¿ke dopisuj¹c backslash
				Menu::printMenuIndex(10, 8, 11, "Aktualna œcie¿ka : " + this->path);
				Menu::printMenuIndex(10, 10, 11, "Wciœnij klawisz ¿eby wróciæ...");
				system("timeout /t -1 > nul");
			}
		}
	}
	
	
}

void Directory::changeRootDirectory(std::string dir) {
	std::string changing = "if exist " + dir + "\\ ( exit 1 ) else ( exit 0 )";
	int status = system(changing.c_str());
	if (status == 0) {
		std::cout << "\n\tFolder nie istnieje!";
	}
	else {
		this->path += "\\" + dir;
	}

}

std::vector<std::string> Directory::getFileList() {
	
	std::string checking = "if exist .\\ukryte\\temp\\ ( exit 1 ) else ( exit 0 )";
	int status = system(checking.c_str());

	// dodawanie folderu tymczasowego
	if (status == 0) {
		std::string creating = "md .\\ukryte\\temp";
		system(creating.c_str());
	}

	// listing:
	// dir [œcie¿ka] /b /a-d > temp 
	// wszystkie pliki z katalogu zostan¹ umieszczone w pliku tymczasowym
	std::string listing = "dir " + this->path + " /b /a-d > .\\ukryte\\temp\\temp.files";
	system(listing.c_str());
	std::ifstream tmp(".\\ukryte\\temp\\temp.files");
	std::string ls;
	
	std::vector<std::string> filesList;

	if (tmp.is_open()) {
		while (tmp.good()) {
			std::getline(tmp, ls);
			filesList.push_back(ls);
		}
	}
	
	filesList.pop_back(); // usuniêcie dodatkowej linii, któr¹ zostawia listing

	return filesList;

}

void Directory::addStream(std::string streamName, std::string extension, std::string content, std::string path) {
	Stream* s = new Stream(streamName, extension, content);
	s->addToStream(path, "FOLDERZE");
	this->streams.push_back(s);

	std::cin.ignore();
}

void Directory::changeStream(std::string path, std::string streamName, std::string extension, std::string content) {
	Stream::changeStreamContent(path, streamName, extension, content);
	std::cin.ignore();
}


void Directory::readStream(std::string path, std::string streamName, std::string extension) {
	Menu::showSubMenu("ODCZYTYWANIE ZAWARTOŒCI STRUMIENIA W FOLDERZE", "zawartoœæ " + path + ":" + streamName + extension + "\n");
	Stream::readFromStreams(path, streamName, extension);
	system("timeout /t -1 > nul");
}

std::string Directory::getPath() {
	return this->path;
}







