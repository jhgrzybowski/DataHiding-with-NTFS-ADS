#include "DataHiding.h"

void DataHiding::getUpdateFiles(std::vector<File*> &files, Directory* &currentDir) {
	files = File::updateFilesList(currentDir->getFileList(), currentDir);
	for (int i = 0; i < files.size(); i++) {
		files[i]->updateStreamList(files[i]->getStreamList());
	}
}


void DataHiding::getInputForStream(std::string& streamName, std::string& extension, std::string& content, std::string mediaType) {
	Menu::showSubMenu("TWORZENIE NOWEGO STRUMIENIA W " + mediaType, "Podaj nazwę, opcjonalnie rozszerzenie i zawartość strumienia danych.");
	Menu::printMenuIndex(10, 6, 11, "Podaj nazwę strumienia: ");

	std::cin.ignore(0);
	getline(std::cin, streamName);
	while (streamName.length() == 0) {
		Menu::showSubMenu("TWORZENIE NOWEGO STRUMIENIA W " + mediaType, "Podaj nazwę, opcjonalnie rozszerzenie i zawartość strumienia danych.");
		Menu::printMenuIndex(10, 6, 11, "Podaj nazwę strumienia: ");
		getline(std::cin, streamName);
	}


	Menu::printMenuIndex(10, 7, 11, "Podaj rozszerzenie: ");
	std::cin.ignore(0);
	getline(std::cin, extension);

	Menu::printMenuIndex(10, 8, 11, "Podaj treść: ");
	COORD c;
	c.X = 0;
	c.Y = 10;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	std::cin.ignore(0);
	getline(std::cin, content, '`');
}

void DataHiding::getInputName(std::string& name) {
	Menu::showConsoleCursor(true);
	Menu::printMenuIndex(10, 6, 11, "Podaj nazwę: ");
	getline(std::cin, name);
	while (name.length() == 0) {
		Menu::showConsoleCursor(true);
		Menu::printMenuIndex(10, 6, 11, "Podaj nazwę: ");
		getline(std::cin, name);
	}
}

void DataHiding::menuFunction(int function, Directory*& currentDir, std::vector<Directory*>& directories, std::vector<File*>& files) {
	File* file;
	std::string name;
	std::string srcName;
	std::string checking;
	int result;
	int fileIndex;
	char choice;


	switch (function) {
	
	// DODAWANIE NOWEGO PLIKU
	case 1:
		getInputName(name);
		file = new File(name, currentDir);
		getUpdateFiles(files, currentDir);
		break;
	
	// TWORZENIE NOWEGO FOLDERU
	case 2:
		getInputName(name);
		currentDir->createNewDirectory(name);
		break;

	// ZMIANA AKTUALNEGO FOLDERU
	case 3:
		Menu::showConsoleCursor(true);
		Menu::printMenuIndex(10, 6, 11, "Podaj ścieżkę: ");
		getline(std::cin, name);
		currentDir->changeDirectory(name);
		// TODO : nie robić update'a jeśli nie ma plików w folderze
		getUpdateFiles(files, currentDir);
		break;

	// TWORZENIE NOWEGO STRUMIENIA
	case 4:
		Menu::showConsoleCursor(true);
		Menu::printMenuIndex(10, 6, 11, "Utworzyć strumień dla pliku czy folderu? [P/F] : ");

		std::cin.get(choice);
		if (choice == 'p' || choice == 'P') {
			Menu::printMenuIndex(10, 7, 11, "Podaj nazwę pliku: ");
			std::cin.ignore();
			getline(std::cin, name);
			std::string checking = "if exist " + currentDir->getPath() + "\\" + name + " ( exit 0 ) else ( exit 1 )";
			int result = system(checking.c_str());
			int fileIndex = -1;

			if (result == 0) {
				for (int i = 0; i < files.size(); i++) {
					if (files[i]->getFileName() == name) {
						fileIndex = i;
						break;
					}
				}	
				std::string streamName;
				std::string extension;
				std::string content;
				getInputForStream(streamName, extension, content, "PLIKU");

				if (files[fileIndex]->streams.size() < 8) {
					files[fileIndex]->addStream(streamName, extension, content);
					getUpdateFiles(files, currentDir);
					break;
				}
				else {
					Menu::showSubMenu("TWORZENIE NOWEGO STRUMIENIA W PLIKU", "Przekroczono limit strumieni dla pliku!");
					Menu::printMenuIndex(10, 6, 11, "Wciśnij klawisz żeby wrócić...");
					system("timeout /t -1 > nul");
					break;
				}
				
			}
			else {
				Menu::showSubMenu("TWORZENIE NOWEGO STRUMIENIA W PLIKU", "Plik nie istnieje!");
				Menu::printMenuIndex(10, 6, 11, "Wciśnij klawisz żeby wrócić...");
				system("timeout /t -1 > nul");
				break;
			}	
			break;
		}
		else if (choice == 'f' || choice == 'F') {
			Menu::printMenuIndex(10, 8, 11, "Znajdujesz się w " + currentDir->getPath());
			Menu::printMenuIndex(10, 10, 11, "Składnia to [ folder1\\folder2 ] : ");
			Menu::printMenuIndex(10, 11, 11, "\t| tworzenie strumienia w folderze2 - podfolderze folderu 'folder1'");
			Menu::printMenuIndex(10, 12, 11, "\t| 'folder1' - podfolder aktualnego folderu");
			Menu::printMenuIndex(10, 14, 11, "Podaj nazwę folderu (począwszy od aktualnego folderu): ");
			std::cin.ignore();
			getline(std::cin, name);
			std::string checking = "if exist " + currentDir->getPath() + "\\" + name + "\\ ( exit 0 ) else ( exit 1 )";
			int result = system(checking.c_str());


			if (result == 0) {

				std::string streamName;
				std::string extension;
				std::string content;
				getInputForStream(streamName, extension, content, "FOLDERZE");

				if (currentDir->streams.size() < 8) {
					currentDir->addStream(streamName, extension, content, currentDir->getPath() + "\\" + name);
				} 
				else {
					Menu::showSubMenu("TWORZENIE NOWEGO STRUMIENIA W FOLDERZE", "Przekroczono limit strumieni dla folderu!");
					Menu::printMenuIndex(10, 6, 11, "Wciśnij klawisz żeby wrócić...");
					system("timeout /t -1 > nul");
					break;
				}

				break;
			}
			else {
				Menu::showSubMenu("TWORZENIE NOWEGO STRUMIENIA W FOLDERZE", "Folder nie istnieje!");
				Menu::printMenuIndex(10, 6, 11, "Wciśnij klawisz żeby wrócić...");
				system("timeout /t -1 > nul");
				break;
			}
		}
		else if(choice == '\n' || choice == '\r') {
			break;
		}
		else {
			std::cin.ignore();
		}
		for (int i = 0; i < files.size(); i++) {
			files[i]->updateStreamList(files[i]->getStreamList());
		}
		break;

	// EDYCJA STRUMIENIA
	case 5:
		Menu::showConsoleCursor(true);
		Menu::printMenuIndex(10, 6, 11, "Zmienić strumień dla pliku czy folderu? [P/F] : ");
		
		std::cin.get(choice);
		if (choice == 'p' || choice == 'P') {
			Menu::printMenuIndex(10, 7, 11, "Podaj nazwę pliku: ");
			std::cin.ignore();
			getline(std::cin, name);
			std::string checking = "if exist " + currentDir->getPath() + "\\" + name + " ( exit 0 ) else ( exit 1 )";
			int result = system(checking.c_str());
			int fileIndex = -1;

			if (result == 0) {
				for (int i = 0; i < files.size(); i++) {
					if (files[i]->getFileName() == name) {
						fileIndex = i;
						break;
					}
				}
				std::string streamName;
				std::string extension;
				std::string content;
				getInputForStream(streamName, extension, content, "PLIKU");
				files[fileIndex]->changeStream(streamName, extension, content);
				getUpdateFiles(files, currentDir);
				break;
			}
			else {
				Menu::showSubMenu("EDYCJA STRUMIENIA W PLIKU", "Plik nie istnieje!");
				Menu::printMenuIndex(10, 6, 11, "Wciśnij klawisz żeby wrócić...");
				system("timeout /t -1 > nul");
				break;
			}

		}
		else if (choice == 'f' || choice == 'F') {
			Menu::printMenuIndex(10, 8, 11, "Znajdujesz się w " + currentDir->getPath());
			Menu::printMenuIndex(10, 10, 11, "Składnia to [ folder1\\folder2 ] : ");
			Menu::printMenuIndex(10, 11, 11, "\t| edycja strumienia w folderze2 - podfolderze folderu 'folder1'");
			Menu::printMenuIndex(10, 12, 11, "\t| 'folder1' - podfolder aktualnego folderu");
			Menu::printMenuIndex(10, 14, 11, "Podaj nazwę folderu (począwszy od aktualnego folderu): ");
			std::cin.ignore();
			getline(std::cin, name);
			std::string checking = "if exist " + currentDir->getPath() + "\\" + name + "\\ ( exit 0 ) else ( exit 1 )";
			int result = system(checking.c_str());

			if (result == 0) {

				std::string streamName;
				std::string extension;
				std::string content;
				getInputForStream(streamName, extension, content, "FOLDERZE");

				Directory::changeStream(currentDir->getPath() + "\\" + name, streamName, extension, content);

				break;
			}
			else {
				Menu::showSubMenu("EDYCJA STRUMIENIA W FOLDERZE", "Folder nie istnieje!");
				Menu::printMenuIndex(10, 6, 11, "Wciśnij klawisz żeby wrócić...");
				system("timeout /t -1 > nul");
				break;
			}
		}
		else if (choice == '\n' || choice == '\r') {
			break;
		}
		else {
			std::cin.ignore();
		}
		for (int i = 0; i < files.size(); i++) {
			files[i]->updateStreamList(files[i]->getStreamList());
		}
		break;

	// ODCZYTYWANIE STRUMIENIA
	case 6:
		Menu::showConsoleCursor(true);
		Menu::printMenuIndex(10, 6, 11, "Odczytać strumień dla pliku czy folderu? [P/F] : ");

		std::cin.get(choice);
		if (choice == 'p' || choice == 'P') {
			Menu::printMenuIndex(10, 7, 11, "Podaj nazwę pliku: ");

			std::cin.ignore();
			getline(std::cin, name);
			std::string checking = "if exist " + currentDir->getPath() + "\\" + name + " ( exit 0 ) else ( exit 1 )";
			int result = system(checking.c_str());
			int fileIndex = -1;

			if (result == 0) {

				fileIndex = -1;
				for (int i = 0; i < files.size(); i++) {
					if (files[i]->getFileName() == name) {
						fileIndex = i;
						break;
					}
				}


				if (fileIndex != -1) {


					std::string streamName;
					std::string extension;

					Menu::showSubMenu("ODCZYTYWANIE ZAWARTOŚCI STRUMIENIA DANYCH W PLIKU", "Podaj nazwę oraz rozszerzenie strumienia, którego chcesz odczytać");
					Menu::printMenuIndex(10, 6, 11, "Podaj nazwę strumienia: ");


					std::cin.ignore(0);
					std::getline(std::cin, streamName);
					while (streamName.length() == 0) {
						Menu::showSubMenu("ODCZYTYWANIE ZAWARTOŚCI STRUMIENIA DANYCH W PLIKU", "Podaj nazwę oraz rozszerzenie strumienia, którego chcesz odczytać");
						Menu::printMenuIndex(10, 6, 11, "Podaj nazwę strumienia: ");
						std::getline(std::cin, streamName);
					}


					Menu::printMenuIndex(10, 7, 11, "Podaj rozszerzenie: ");
					std::cin.ignore(0);
					getline(std::cin, extension);

					Menu::showConsoleCursor(false);
					files[fileIndex]->readStream(streamName, extension);
					break;
				}
			}
			else {
				Menu::showSubMenu("ODCZYTYWANIE ZAWARTOŚCI STRUMIENIA DANYCH", "Plik nie istnieje!");
				Menu::printMenuIndex(10, 6, 11, "Wciśnij klawisz żeby wrócić...");
				system("timeout /t -1 > nul");
				break;
			}
		}
		else if (choice == 'f' || choice == 'F') {
			Menu::printMenuIndex(10, 8, 11, "Znajdujesz się w " + currentDir->getPath());
			Menu::printMenuIndex(10, 10, 11, "Składnia to [ folder1\\folder2 ] : ");
			Menu::printMenuIndex(10, 11, 11, "\t| odczytanie strumienia w folderze2 - podfolderze folderu 'folder1'");
			Menu::printMenuIndex(10, 12, 11, "\t| 'folder1' - podfolder aktualnego folderu");
			Menu::printMenuIndex(10, 14, 11, "Podaj nazwę folderu (począwszy od aktualnego folderu): ");
			std::cin.ignore();
			getline(std::cin, name);
			std::string checking = "if exist " + currentDir->getPath() + "\\" + name + "\\ ( exit 0 ) else ( exit 1 )";
			int result = system(checking.c_str());

			if (result == 0) {

				std::string streamName;
				std::string extension;

				Menu::showSubMenu("ODCZYTYWANIE ZAWARTOŚCI STRUMIENIA DANYCH W FOLDERZE", "Podaj nazwę oraz rozszerzenie strumienia, którego chcesz odczytać");
				Menu::printMenuIndex(10, 6, 11, "Podaj nazwę strumienia: ");


				std::cin.ignore(0);
				std::getline(std::cin, streamName);
				while (streamName.length() == 0) {
					Menu::showSubMenu("ODCZYTYWANIE ZAWARTOŚCI STRUMIENIA DANYCH W FOLDERZE", "Podaj nazwę oraz rozszerzenie strumienia, którego chcesz odczytać");
					Menu::printMenuIndex(10, 6, 11, "Podaj nazwę strumienia: ");
					std::getline(std::cin, streamName);
				}


				Menu::printMenuIndex(10, 7, 11, "Podaj rozszerzenie: ");
				std::cin.ignore(0);
				getline(std::cin, extension);

				Menu::showConsoleCursor(false);
				Directory::readStream(currentDir->getPath() + "\\" + name, streamName, extension);
				break;

			}
			else {
				Menu::showSubMenu("ODCZYTYWANIE ZAWARTOŚCI STRUMIENIA DANYCH W FOLDERZE", "Folder nie istnieje!");
				Menu::printMenuIndex(10, 6, 11, "Wciśnij klawisz żeby wrócić...");
				system("timeout /t -1 > nul");
				break;
			}
		} else if (choice == '\n' || choice == '\r') {
			break;
		}
		else {
			std::cin.ignore();
		}
		break;

	// ODCZYTYWANIE STRUMIENIA INNĄ APLIKACJĄ
	case 7:
	
		getInputName(name);

		fileIndex = -1;
		for (int i = 0; i < files.size(); i++) {
			if (files[i]->getFileName() == name) {
				fileIndex = i;
				break;
			}
		}

		if (fileIndex != -1) {

			std::string streamName;
			std::string extension;
			std::string appName;

			Menu::showSubMenu("ODCZYTYWANIE ZAWARTOŚCI STRUMIENIA DANYCH W PLIKU", "Podaj nazwę oraz rozszerzenie strumienia, którego chcesz odczytać");
			
			Menu::printMenuIndex(10, 6, 11, "Dostępne aplikacje to: mspaint [ ZDJĘCIA ], notepad [ TEKST ] groove [ MUZYKA ] oraz videos [ FILMY ]");
			Menu::printMenuIndex(10, 7, 11, "Można również podać znane rozszerzenie pliku, a program zadecyduje czym otworzyć strumień.");
			Menu::printMenuIndex(10, 9, 11, "Podaj nazwę strumienia: ");


			std::cin.ignore(0);
			std::getline(std::cin, streamName);
			while (streamName.length() == 0) {
				Menu::printMenuIndex(10, 6, 11, "Dostępne aplikacje to: mspaint [ ZDJĘCIA ], notepad [ TEKST ] groove [ MUZYKA ] oraz videos [ FILMY ].");
				Menu::printMenuIndex(10, 7, 11, "Można również podać znane rozszerzenie pliku, a program zadecyduje czym otworzyć strumień.");
				Menu::printMenuIndex(10, 9, 11, "Podaj nazwę strumienia: ");
				std::getline(std::cin, streamName);
			}

			Menu::printMenuIndex(10, 10, 11, "Podaj rozszerzenie: ");
			std::cin.ignore(0);
			getline(std::cin, extension);

			Menu::printMenuIndex(10, 11, 11, "Podaj nazwę aplikacji: ");
			std::cin.ignore(0);
			getline(std::cin, appName);
			while (appName.length() == 0) {
				Menu::printMenuIndex(10, 6, 11, "Dostępne aplikacje to: mspaint [ ZDJĘCIA ], notepad [ TEKST ] groove [ MUZYKA ] oraz videos [ FILMY ].");
				Menu::printMenuIndex(10, 7, 11, "Można również podać znane rozszerzenie pliku, a program zadecyduje czym otworzyć strumień.");
				Menu::printMenuIndex(10, 11, 11, "Podaj nazwę aplikacji: ");
				std::getline(std::cin, streamName);
			}

			Menu::showConsoleCursor(false);
			files[fileIndex]->readStreamUsingApp(streamName, extension, appName);
			break;
		}
		else {
			Menu::showConsoleCursor(false);
			Menu::showSubMenu("ODCZYTYWANIE ZAWARTOŚCI STRUMIENIA DANYCH W PLIKU", "Plik nie istnieje!");
			Menu::printMenuIndex(10, 6, 11, "Wciśnij klawisz żeby wrócić...");
			system("timeout /t -1 > nul");
			break;
		}
		break;

	// PRZENOSZENIE PLIKÓW
	case 8:

		Menu::printMenuIndex(10, 5, 11, "1. plik źródłowy");
		getInputName(srcName);

		Menu::showSubMenu("PRZENOSZENIE PLIKÓW DO STRUMIENIA", "Przenieś istniejący plik do osobnego strumienia danych. Najpierw podaj plik źródłowy, a potem docelowy.");
		Menu::printMenuIndex(10, 5, 11, "2. plik docelowy");
		getInputName(name);

		checking = "if exist " + currentDir->getPath() + "\\" + srcName + " ( exit 0 ) else ( exit 1 )";
		result = system(checking.c_str());

		if (result == 0) {

			std::string streamName;
			std::string extension;

			Menu::showSubMenu("PRZENOSZENIE PLIKÓW DO STRUMIENIA", "Podaj nazwę oraz rozszerzenie strumienia, do którego chcesz przenieść plik.");
			Menu::printMenuIndex(10, 6, 11, "Podaj nazwę strumienia: ");


			std::cin.ignore(0);
			std::getline(std::cin, streamName);
			while (streamName.length() == 0) {
				Menu::showSubMenu("PRZENOSZENIE PLIKÓW DO STRUMIENIA", "Podaj nazwę oraz rozszerzenie strumienia, do którego chcesz przenieść plik.");
				Menu::printMenuIndex(10, 6, 11, "Podaj nazwę strumienia: ");
				std::getline(std::cin, streamName);
			}


			Menu::printMenuIndex(10, 7, 11, "Podaj rozszerzenie: ");
			std::cin.ignore(0);
			getline(std::cin, extension);

			Menu::showConsoleCursor(false);
			Stream::moveBinaryToStream(currentDir->getPath() + "\\" + srcName, currentDir->getPath() + "\\" + name, streamName, extension);
			getUpdateFiles(files, currentDir);
			break;
		}
		else {
			Menu::showSubMenu("PRZENOSZENIE PLIKÓW DO STRUMIENIA", "Plik źródłowy nie istnieje!");
			Menu::printMenuIndex(10, 6, 11, "Wciśnij klawisz żeby wrócić...");
			system("timeout /t -1 > nul");
			break;
		}
		break;

	// INFORMACJA O PROGRAMIE
	case 9:
		Menu::printMenuIndex(10, 5, 11, "[ OPROGRAMOWNIE SYSTEMOWE - PROJEKT ]");
		Menu::printMenuIndex(10, 6, 11, "[ INFORMATYKA 5 SEMESTR - ETI - POLITECHNIKA GDAŃSKA ] [ 12.2022 ]");
		Menu::printMenuIndex(10, 9, 11, "[ TEMAT PROJEKTU ] : [ UKRYCIE DANYCH W SYSTEMIE PLIKÓW NTFS Z WYKORZYSTANIEM METADANYCH ]");
		Menu::printMenuIndex(10, 11, 11, "Program umożliwia użytkownikowi dodawanie i zarządzanie alternatywnych strumieni danych,");
		Menu::printMenuIndex(10, 12, 11, "które są obsługiwane przez system plików NTFS. Dzięki temu, użytkownik może ukrywać");
		Menu::printMenuIndex(10, 13, 11, "swoje pliki bez obawy o wykrycie z poziomu systemu operacyjnego.");
		Menu::printMenuIndex(10, 15, 11, "Strumienie mogą mieć różne rozszerzenia, program umożliwia ich otwieranie za pomocą aplikacji zewnętrznych.");
		Menu::printMenuIndex(10, 16, 11, "Wybór funkcjonalności odbywa się poprzez sterowanie strzałkami i zatwierdza klikając ENTER.");
		Menu::printMenuIndex(10, 17, 11, "W pierwszej wersji programu udostępniono 8 funkcjonalności: tworzenie plików i folderów,");
		Menu::printMenuIndex(10, 18, 11, "zmiana obecnego folderu, dodawanie strumieni oraz edycją ich zawartości, przeglądanie zawartości strumieni,");
		Menu::printMenuIndex(10, 19, 11, "również za pomocą aplikacji zewnętrznych oraz wylistowanie dodanych strumieni.");
		Menu::printMenuIndex(10, 20, 11, "W drugiej wersji dodano: za pomocą klawisza 'D' można podejrzeć aktualną ścieżkę roboczą");
		Menu::printMenuIndex(10, 21, 11, "wraz z plikami. Każdy klawisz od 1 do 9 służy również jako uruchomienie funkcji.");
		Menu::printMenuIndex(10, 22, 11, "Za pomocą klawisza 'C' można zmienić aktualny folder, klawisz 'S' wyświetla utworzone strumienie,");
		Menu::printMenuIndex(10, 23, 11, "a 'A' wyświetla wszystkie pliki wraz z ich strumieniami. ESC kończy pracę programu.");
		Menu::printMenuIndex(10, 25, 11, "[ AKTUALNA WERSJA ] : [ v2.2 ]");
		system("timeout /t -1 > nul");
		break;
	default:
		break;
	}
	
	DataHiding::getUpdateFiles(files, currentDir);
}
