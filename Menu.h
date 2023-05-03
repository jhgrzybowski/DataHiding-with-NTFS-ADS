#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Stream.h"

class Menu {
public:
	static int* Set;
	static int counter;
	static char key;

	static void showConsoleCursor(bool showFlag);

	static int showMenu();
	static void showSubMenu(std::string prompt, std::string description);
	static void printMenuIndex(int x, int y, int colorID, std::string prompt);
	static void printMainMenu();

	
	

};

