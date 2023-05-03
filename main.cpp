#include "DataHiding.h"

int main() {

	setlocale(LC_ALL, "polish");

	std::vector<File*> files;
	std::vector<Directory*> directories;
	Directory* currentDir;

	Directory* dir = new Directory("ukryte");
	directories.push_back(dir);
	currentDir = dir;

	

	std::string prompt = "";
	std::string description = "";
	int currentLineNumber;

	//std::string clearing = "del .\\ukryte\\temp\\\"*_buff*\\\"";

	while (true) {
	
		int opt = Menu::showMenu();
		switch (opt) {
		case 1:
			prompt = "TWORZENIE NOWEGO PLIKU";
			description = "Utw�rz nowy plik o podanej nazwie. Je�li plik istnieje zostanie wy�wietlony komunikat.";
			Menu::showSubMenu(prompt, description);
			DataHiding::menuFunction(1, currentDir, directories, files);
			break;
		case 2:
			prompt = "TWORZENIE NOWEGO FOLDERU";
			description = "Utw�rz nowy folder o podanej nazwie. Je�li folder istnieje zostanie wy�wietlony komunikat.";
			Menu::showSubMenu(prompt, description);
			DataHiding::menuFunction(2, currentDir, directories, files);
			break;
		case 3:
			prompt = "ZMIANA AKTUALNEGO FOLDERU";
			description = "Zmie� aktualn� �cie�k�. Zmiana zostanie wy�wietlona.";
			Menu::showSubMenu(prompt, description);
			DataHiding::menuFunction(3, currentDir, directories, files);
			break;
		case 4:
			prompt = "TWORZENIE NOWEGO STRUMIENIA";
			description = "Utw�rz alternatywny strumie� danych w pliku albo folderze.";
			Menu::showSubMenu(prompt, description);
			DataHiding::menuFunction(4, currentDir, directories, files);
			break;
		case 5:
			prompt = "EDYCJA STRUMIENIA";
			description = "Edytuj zawarto�� alternatywnego strumienia danych w pliku albo folderze.";
			Menu::showSubMenu(prompt, description);
			DataHiding::menuFunction(5, currentDir, directories, files);
			break;
		case 6:
			prompt = "ODCZYTYWANIE ZAWARTO�CI STRUMIENIA DANYCH";
			description = "Odczytaj zawarto�� alternatywnego strumienia danych okre�lonego pliku lub folderu w konsoli.";
			Menu::showSubMenu(prompt, description);
			DataHiding::menuFunction(6, currentDir, directories, files);
			break;
		case 7:
			prompt = "ODCZYTYWANIE ZAWARTO�CI STRUMIENIA DANYCH ZA POMOC� APLIKACJI";
			description = "Odczytaj zawarto�� alternatywnego strumienia danych okre�lonego pliku innym programem.";
			Menu::showSubMenu(prompt, description);
			DataHiding::menuFunction(7, currentDir, directories, files);
			break;
		case 8:
			prompt = "PRZENOSZENIE PLIK�W DO STRUMIENIA";
			description = "Przenie� istniej�cy plik do osobnego strumienia danych. Najpierw podaj plik �r�d�owy, a potem docelowy.";
			Menu::showSubMenu(prompt, description);
			DataHiding::menuFunction(8, currentDir, directories, files);
			break;
		case 9:
			Menu::showSubMenu("O PROGRAMIE", "[ AUTOR ] : [ Jakub Grzybowski ] [ s184670 ]");
			DataHiding::menuFunction(9, currentDir, directories, files);
			break;
		case 10:
			system("color 7");
			system("cls");
			//system(clearing.c_str());
			remove(".\\ukryte\\temp\\temp.files");
			system("rmdir .\\ukryte\\temp\\");
			std::cout << "BYE!\n";
			exit(0);
			break;
		case 'A':
			Menu::showSubMenu("AKTUALNA �CIE�KA", currentDir->getPath());

			currentLineNumber = 6;

			for (int i = 0; i < files.size(); i++) {
				Menu::printMenuIndex(10, currentLineNumber, 11, "\t" + files[i]->getFileName());
				if (!files[i]->streams.empty()) {
					for (int j = 0; j < files[i]->streams.size(); j++) {

						currentLineNumber++;
						if (files[i]->streams[j]->getName() == "") {

							Menu::printMenuIndex(10, currentLineNumber, 11, files[i]->streams[j]->getListingName());

						}
						else {
							std::string extSuffix;
							if (files[i]->streams[j]->getExtension() == "") extSuffix = files[i]->streams[j]->getName();
							else extSuffix = files[i]->streams[j]->getName() + "." + files[i]->streams[j]->getExtension();
							Menu::printMenuIndex(10, currentLineNumber, 11, "\t\t:" + extSuffix + ":$DATA");
						}
						
					}
				}
				currentLineNumber++;
			}
			system("timeout /t -1 > nul");
			break;
		case 'S':
			system("cls");
			Menu::printMenuIndex(10, 3, 0, "UTWORZONE STRUMIENIE PLIK�W");
			
			currentLineNumber = 5;

			for (int i = 0; i < files.size(); i++) {
				
				if (!files[i]->streams.empty()) {
					for (int j = 0; j < files[i]->streams.size(); j++) {
						if (files[i]->streams[j]->getName() != "") {
							std::string extSuffix;
							if (files[i]->streams[j]->getExtension() == "") extSuffix = files[i]->streams[j]->getName();
							else extSuffix = files[i]->streams[j]->getName() + "." + files[i]->streams[j]->getExtension();
							Menu::printMenuIndex(10, currentLineNumber, 11, extSuffix);
							currentLineNumber++;
						}
						else if (files[i]->streams[j]->getListingName() != "") {
							Menu::printMenuIndex(10, currentLineNumber, 11, files[i]->streams[j]->getListingName());
							currentLineNumber++;
						}
					}
				}
			}

			Menu::printMenuIndex(60, 3, 0, "UTWORZONE STRUMIENIE FOLDER�W");

			currentLineNumber = 5;
			
				if (!currentDir->streams.empty()) {
					for (int j = 0; j <	currentDir->streams.size(); j++) {

						if (currentDir->streams[j]->getName() != "") {
							std::string extSuffix;
							if 	(currentDir->streams[j]->getExtension() == "") extSuffix = currentDir->streams[j]->getName();
							else extSuffix = currentDir->streams[j]->getName() + "." + currentDir->streams[j]->getExtension();
							Menu::printMenuIndex(60, currentLineNumber, 11, extSuffix);
							currentLineNumber++;
						}
						else if (currentDir->streams[j]->getListingName() != "") {
							Menu::printMenuIndex(60, currentLineNumber, 11, currentDir->streams[j]->getListingName());
							currentLineNumber++;
						}
					}
				}
			

			system("timeout /t -1 > nul");
			break;
		case 'D':
			Menu::showSubMenu("AKTUALNA �CIE�KA", currentDir->getPath());

			currentLineNumber = 6;

			for (int i = 0; i < files.size(); i++) {
				Menu::printMenuIndex(10, currentLineNumber, 11, "\t" + files[i]->getFileName());
				currentLineNumber++;	
			}
			system("timeout /t -1 > nul");
			break;
		}

		// aktualizacja plik�w tymczasowych odpowiedzialnych za przechowywanie metadanych o plikach
		DataHiding::getUpdateFiles(files, currentDir);

	}



}