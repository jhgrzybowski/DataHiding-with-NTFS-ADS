#include "Menu.h"

void color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Menu::showConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void consoleSettings() {
	system("cls");
	WORD tab[] = { 0x4d, 0x45, 0x4e, 0x45, 0x44, 0x017b, 0x45, 0x52, 0x20, 0x41, 0x53, 0x44, 0x00 };
	SetConsoleTitleW(LPCWSTR(tab));
	Menu::showConsoleCursor(false);
}

void Menu::printMenuIndex(int x, int y, int colorID, std::string prompt) {
	gotoxy(x, y);
	color(Menu::Set[colorID]);
	std::cout << prompt;
}

void Menu::printMainMenu() {
	Menu::printMenuIndex(10, 3, 0, "MENEDŻER ALTERNATYWNYCH STRUMIENI DANYCH");
	Menu::printMenuIndex(10, 6, 1, "1. Utwórz nowy plik");
	Menu::printMenuIndex(10, 7, 2, "2. Utwórz nowy folder");
	Menu::printMenuIndex(10, 8, 3, "3. Zmień aktualny folder");
	Menu::printMenuIndex(10, 9, 4, "4. Dodaj alternatywny strumień danych (plik/folder)");
	Menu::printMenuIndex(10, 10, 5, "5. Zmień zawartość strumienia (plik/folder)");
	Menu::printMenuIndex(10, 11, 6, "6. Odczytaj alternatywny strumień (plik/folder)");
	Menu::printMenuIndex(10, 12, 7, "7. Odczytaj alternatywny strumień za pomocą...");
	Menu::printMenuIndex(10, 13, 8, "8. Przenieś plik do strumienia");
	Menu::printMenuIndex(10, 15, 9, "ABOUT");
	Menu::printMenuIndex(10, 16, 10, "EXIT");
	Menu::printMenuIndex(10, 19, 0, "\30 \31\t: sterowanie");
	Menu::printMenuIndex(10, 20, 0, "ENTER\t: wybór");
}


int* Menu::Set = new int[12];
int Menu::counter;
char Menu::key;

void Menu::showSubMenu(std::string prompt, std::string description) {
	
	system("cls");
	Menu::printMenuIndex(10, 3, 0, prompt);
	Menu::printMenuIndex(10, 4, 11, description);
	
}

int Menu::showMenu() {

	consoleSettings();
	Menu::Set[0] = 3;
	Menu::Set[11] = 7;
	for (int i = 1; i <= 10; i++) Menu::Set[i] = 0xf;

	Menu::counter = 2;

	for (int i = 0 ;;) {
		
		Menu::printMainMenu();

		Menu::key = _getch();

		if (key == '1') {
			return 1;
			break;
		}
		if (key == '2') {
			return 2;
			break;
		}
		if (key == '3' || toupper(key) == 'C') {
			return 3;
			break;
		}
		if (key == '4') {
			return 4;
			break;
		}
		if (key == '5') {
			return 5;
			break;
		}
		if (key == '6') {
			return 6;
			break;
		}
		if (key == '7') {
			return 7;
			break;
		}
		if (key == '8') {
			return 8;
			break;
		}
		if (key == '9') {
			return 9;
			break;
		}
		if (key == 27) {
			return 10;
			break;
		}
		if (toupper(key) == 'A') {
			return int('A');
			break;
		}
		if (toupper(key) == 'S') {
			return int('S');
			break;
		}
		if (toupper(key) == 'D') {
			return int('D');
			break;
		}
		
		if (key == 72 && counter != 1) counter--; else if (key == 72 && counter == 1) counter = 10; // 72 = strzałka w górę 
		if (key == 80 && counter != 10) counter++; else if (key == 80 && counter == 10) counter = 1; // 80 = strzałka w dół
		
		if (key == '\r') {
			switch (counter) {
			case 1:
				return 1;
				break;
			case 2:
				return 2;
				break;
			case 3:
				return 3;
				break;
			case 4:
				return 4;
				break;
			case 5:
				return 5;
				break;
			case 6:
				return 6;
				break;
			case 7:
				return 7;
				break;
			case 8:
				return 8;
				break;
			case 9:
				return 9;
				break;
			case 10:
				return 10;
				break;
			}
		}

		// Kolorowanie opcji na biały
		for (int i = 1; i <= 10; i++) Menu::Set[i] = 0xf;

		// Podświetlanie opcji na niebiesko
		switch (counter) {
			case 1:
				Set[1] = 3;
				break;
			case 2:
				Set[2] = 3;
				break;
			case 3:
				Set[3] = 3;
				break;
			case 4:
				Set[4] = 3;
				break;
			case 5:
				Set[5] = 3;
				break;
			case 6:
				Set[6] = 3;
				break;
			case 7:
				Set[7] = 3;
				break;
			case 8:
				Set[8] = 3;
				break;
			case 9:
				Set[9] = 3;
				break;
			case 10:
				Set[10] = 3;
				break;
		}
	}
}