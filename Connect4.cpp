#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>	
#include <string.h>
#include <iomanip>
#include <fstream>
#include <conio.h>

using namespace std;

void game();
void XOX();
void C4();


// Function 1 : This function gets which game the game is.
char preference();
//*****************************************************************

// Function 2: This function gets our array size.
int findSize();
//*****************************************************************

// Function 3: These functions are related to the creation and deletion of the array.
int** createArray(int size);

void deleteArray(int** array, int size);
//*****************************************************************

// Function 4: This function shows array.
void printArray(int** array, int size);
//*****************************************************************

// Function 5: This function control the winning.
int checkWinXOX(int** array, int size);
//*****************************************************************

// Function 6:This function goes to Winning Screen
bool playerWin(int**array,int size);
//*****************************************************************

// Function 7: These functions are related to the saving and writing again.
void saveGame(int** array, int size, const string& fileName);
void loadGame(int** array, int size, const string& fileName);
//*****************************************************************

void updateGameTo1(int** array, int size,int glass_number);
void updateGameTo2(int** array, int size, int glass_number);
//*****************************************************************

int checkWinC4(int** array, int size);
bool playerWinC4(int** array, int size);

int main()
{
 
	game();


}
//*****************************************************************

// Game Flow

void game() {
	char choice;
	choice = preference();
	if (choice == 'X') {
		XOX();
	}
	else if (choice == 'C') {
		C4();
	}
}

void XOX() {
	int size;
	size = findSize();

	int** screen = createArray(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			screen[i][j] = 0;
		}
	}

	int fpRow, fpCol;
	int spRow, spCol;
	int controller;
	bool flag;
	bool general_flag = false;

	while (!general_flag) {
		flag = playerWin(screen, size);
		if (flag) {
			general_flag = true;
			break;  
		}

	jump1:
		printArray(screen, size);
		cout << "Where Would You Like To Write 1?" << endl;
		cin >> fpRow >> fpCol;

		if (screen[fpRow - 1][fpCol - 1] == 0) {
			screen[fpRow - 1][fpCol - 1] = 1;
		}
		else {
			cout << "Please Select An Unoccupied Place." << endl;
			this_thread::sleep_for(chrono::seconds(2));
			system("cls");
			goto jump1;
		}

		this_thread::sleep_for(chrono::seconds(2));
		system("cls");


		
		flag = playerWin(screen, size);
		if (flag) {
			general_flag = true;
			break;  
		}

	jump2:
		printArray(screen, size);
		cout << "Where Would You Like To Write 2?" << endl;
		cin >> spRow >> spCol;

		if (screen[spRow - 1][spCol - 1] == 0) {
			screen[spRow - 1][spCol - 1] = 2;
		}
		else {
			cout << "Please Select An Unoccupied Place." << endl;
			this_thread::sleep_for(chrono::seconds(2));
			system("cls");
			goto jump2;
		}

		this_thread::sleep_for(chrono::seconds(2));
		system("cls");
	}

	deleteArray(screen, size);
}

void C4() {
	int size;
	size = findSize();
	
	int** screen = createArray(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			screen[i][j] = 0;
		}
	}
	
	int fpGlass, spGlass;
	bool general_flag = false;
	bool flag;
	while (!general_flag) {
		
		flag = playerWinC4(screen, size);
		if (flag) {
			general_flag = true;
			break;
		}
	
		printArray(screen, size);
		cout << "Where Would You Like To Write 1?" << endl;
		cin >> fpGlass;
		fpGlass -= 1;
		
		updateGameTo1(screen,size,fpGlass);
		this_thread::sleep_for(chrono::seconds(2));
		system("cls");

		flag = playerWinC4(screen, size);
		if (flag) {
			general_flag = true;
			break;
		}

		printArray(screen, size);
		cout << "Where Would You Like To Write 2?" << endl;
		cin >> spGlass;
		spGlass -= 1;
		updateGameTo2(screen, size, spGlass);
		
		
		this_thread::sleep_for(chrono::seconds(2));
		system("cls");


	}


	deleteArray(screen, size);
}



// FUNCTİONS

//*****************************************************************

int findSize() {
	int size;
	bool flag = false;
	while (!flag) {
		cout << "How Much Would You Like To Play On A Sheet Of Paper?"<<endl;
		cin >> size;
		if (size > 4) {
			cout << "Creating Your Game Screen" << endl;
			this_thread::sleep_for(chrono::seconds(2));
			system("cls");
			flag = true;
		}
		else {
			cout << "Please Enter A Value Greater Than 4"<<endl;
			this_thread::sleep_for(chrono::seconds(2));
			system("cls");
			flag = false;
		}
	}
	return size;
}
//*****************************************************************

char preference() {
	
	char choice;
	string gameName;
	bool flag = false;
	while (!flag) {
		cout << "Which Game Would You Like To Play:\n: XOX / Connect 4 ? " << endl;
		getline(cin, gameName);

		if (gameName == "XOX" || gameName == "xox" || gameName == "Xox" || gameName == "xOX" || gameName == "XOx" || gameName == "XoX") {
			cout << "You chose XOX. Let's play!" << endl;
			this_thread::sleep_for(chrono::seconds(2));
			system("cls");
			choice = 'X';
			flag = true;
		}
		else if (gameName == "Connect 4" || gameName == "cONNECT 4" || gameName == "connect 4" || gameName == "CONNECT 4") {
			cout << "You chose Connect 4. Let's play!" << endl;
			this_thread::sleep_for(chrono::seconds(2));
			system("cls");
			choice = 'C';
			flag = true;
		}
		else {
			cout << "Invalid choice. Please select either XOX or Connect 4." << endl;
			this_thread::sleep_for(chrono::seconds(2));
			system("cls");
			flag = false;
		}
	}
	return choice;
}
//*****************************************************************

int** createArray(int size) {
	int** array = new int* [size];

	for (int i = 0; i < size; i++) {
		array[i] = new int[size];
	}
	return array;
}

void deleteArray(int** array, int size) {
	for (int i = 0; i < size; i++) {
		delete[] array[i];
	}
	delete[] array;
}

//*****************************************************************

void printArray(int** array, int size) {
	cout << "   ";
	for (int j = 0; j < size; j++) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 15);
		cout << setw(6) << j + 1;  // Use setw to set the width of each column
	}
	cout << endl;

	for (int i = 0; i < size; i++) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 15);
		cout << setw(2) << i + 1 << "  ";  // Use setw to set the width of row numbers

		for (int j = 0; j < size; j++) {
			int num = array[i][j];
			if (num == 0) {
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 15);
				cout << "| " << setw(2) << num << " |";  // Use setw to set the width of each square
			}
			else if (num == 1) {
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 5);  // Use num as the color attribute
				cout << "| " << setw(2) << array[i][j] << " |";  // Use setw to set the width of each square
			}
			else if (num == 2) {
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 6);  // Use num as the color attribute
				cout << "| " << setw(2) << array[i][j] << " |";  // Use setw to set the width of each square
			}
			else {
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 15);
				cout << "| " << setw(2) << array[i][j] << " |";  // Use setw to set the width of each square
			}
		}
		cout << "\n";
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
}
//*****************************************************************

int checkWinXOX(int** array, int size)
{
	for (int i = 0; i < size; i++) {
		// Check rows
		for (int j = 0; j < size - 2; j++) {
			int num = array[i][j];
			if (num != 0 && array[i][j + 1] == num && array[i][j + 2] == num) {
				return num;
			}
		}

		// Check columns
		for (int j = 0; j < size - 2; j++) {
			int num = array[j][i];
			if (num != 0 && array[j + 1][i] == num && array[j + 2][i] == num) {
				return num;
			}
		}

		// Check diagonals (top-left to bottom-right)
		for (int i = 0; i < size - 2; i++) {
			for (int j = 0; j < size - 2; j++) {
				int num = array[i][j];

				if (num != 0 && array[i + 1][j + 1] == num && array[i + 2][j + 2] == num) {
					return num;
				}
			}
		}

		// Check diagonals (top-right to bottom-left)
		for (int i = 0; i < size - 2; i++) {
			for (int j = size - 1; j >= 2; j--) {
				int num = array[i][j];

				if (num != 0 && array[i + 1][j - 1] == num && array[i + 2][j - 2] == num) {
					return num;
				}
			}
		}

		return 0;  // No winner yet
	}
}
//*****************************************************************

bool playerWin(int**array,int size) {
	int controller;
	bool flag;
	controller = checkWinXOX(array, size);

	if (controller == 1) {
		cout << "Player 1 Wins..." << endl;
		flag = true;
		return flag;
	}

	if (controller == 2) {
		cout << "Player 2 Wins..." << endl;
		flag = true;
		return flag;
	}
	else {
		flag = false;
		return false;
	}
}
//*****************************************************************

void saveGame(int** array, int size, const string& fileName)
{
	ofstream outFile(fileName);

	if (outFile.is_open())
	{
		outFile << size << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				outFile << array[i][j] << " ";
			}
			outFile << endl;
		}
		outFile.close();
		cout << "Game saved successfully!" << endl;
	}
	else
	{
		cout << "Unable to open the file for saving." << endl;
	}
}

void loadGame(int** array, int size, const string& fileName)
{
	ifstream inFile(fileName);

	if (inFile.is_open())
	{
		int savedSize;
		inFile >> savedSize;

		if (savedSize != size)
		{
			cout << "The saved game size doesn't match the current game size." << endl;
			inFile.close();
			return;
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				inFile >> array[i][j];
			}
		}

		cout << "Game loaded successfully!" << endl;
	}
	else
	{
		cout << "Unable to open the file for loading." << endl;
	}
}
//*****************************************************************

void updateGameTo1(int** array, int size,int glass_number) {
	for (int i = size-1; i >=0; i--) {
		if (array[i][glass_number] == 0) {
			array[i][glass_number] = 1;
			break;
		}
	}
}

void updateGameTo2(int** array, int size, int glass_number) {
	for (int i = size-1; i >= 0; i--) {
		if (array[i][glass_number] == 0) {
			array[i][glass_number] = 2;
			break;
		}
	}
}
//*****************************************************************

int checkWinC4(int** array, int size)
{
	for (int i = 0; i < size; i++) {
		// Check rows
		for (int j = 0; j < size - 2; j++) {
			int num = array[i][j];
			if (num != 0 && array[i][j + 1] == num && array[i][j + 2] == num) {
				return num;
			}
		}
	}
	// Check columns
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 2; j++) {
			int num = array[j][i];
			if (num != 0 && array[j + 1][i] == num && array[j + 2][i] == num) {
				return num;
			}
		}
	}
	// Check diagonals (top-left to bottom-right)
	for (int i = 0; i < size - 2; i++) {
		for (int j = 0; j < size - 2; j++) {
			int num = array[i][j];

			if (num != 0 && array[i + 1][j + 1] == num && array[i + 2][j + 2] == num) {
				return num;
			}
		}
	}

	// Check diagonals (top-right to bottom-left)
	for (int i = 0; i < size - 2; i++) {
		for (int j = size - 1; j >= 2; j--) {
			int num = array[i][j];

			if (num != 0 && array[i + 1][j - 1] == num && array[i + 2][j - 2] == num) {
				return num;
			}
		}
	}

	return 0;  // No winner yet
	
}
//*****************************************************************
bool playerWinC4(int** array, int size) {
	int controller;
	bool flag;
	controller = checkWinC4(array, size);

	if (controller == 1) {
		cout << "Player 1 Wins..." << endl;
		flag = true;
		return flag;
	}

	if (controller == 2) {
		cout << "Player 2 Wins..." << endl;
		flag = true;
		return flag;
	}
	else {
		flag = false;
		return false;
	}
}
//*****************************************************************