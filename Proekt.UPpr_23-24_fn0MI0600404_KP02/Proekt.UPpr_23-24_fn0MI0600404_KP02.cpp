/*
* Solution to course project #02
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author <Esin Myumyun>
* @idnumber <0MI0600404>
* @compiler <VC>
*
* <Game of life entire file>
*/

#include <iostream>
using namespace std;


void printEmptySpaces() {


	for (int j = 1; j <= 10; j++) {

		cout << " ";
	}

}




void printDecoration() {

	for (int i = 1; i <= 16; i++) {
		cout << "~";
	}
}



void printMainMenu() { //nachalni opcii

	cout << "~~~~~~Welcome to the game of life :3~~~~~~" << endl << endl << "Please pick one of the following options!:" << endl << endl;

	printEmptySpaces();

	printDecoration();

	cout << endl;

	printEmptySpaces();

	cout << "[ 1. New game  ]" << endl;

	printEmptySpaces();

	cout << "[ 2. Load file ]" << endl;

	printEmptySpaces();

	cout << "[ 3. Exit      ]" << endl;

	printEmptySpaces();

	printDecoration();

	cout << endl << endl;

}


void printOptions() { //opcii za igra



	printDecoration();
	printDecoration();
	printDecoration();

	cout << endl << endl;

	cout << "Here are the changes you can make on the field: ";

	cout << endl << endl;

	cout << "1. Step Forward" << endl <<
		"2. Resize" << endl <<
		"3. Toggle Cell" << endl <<
		"4. Clear" << endl <<
		"5. Randomize" << endl;


	cout << endl;

	cout << "You also have the following options:" << endl << endl <<
		"6. Save to file" << endl <<
		"7. End the game" << endl;

	printDecoration();
	printDecoration();
	printDecoration();

	cout << endl << endl;
	cout << "Choose one of the options above:  ";


}

const int ROWMAX = 26;
const int COLMAX = 82;

void deadCellsInField(char field[ROWMAX][COLMAX], int rows, int cols) { //prevrushta vsichki kletki v murtvi


	for (int i = 0; i < ROWMAX; i++) {
		for (int j = 0; j < COLMAX; j++) {


			field[i][j] = '-';


		}


	}

}

void toggle(char field[ROWMAX][COLMAX], int row, int col) { //toggle-va kletkite ot murtvi na jivi ili ot jivi na murtvi

	if (field[row][col] == '-') {
		field[row][col] = '@';
	}
	else {
		field[row][col] = '-';
	}


}

int aliveNeighbours(char field[ROWMAX][COLMAX], int row, int col) //broi susedni kletki koito sa jivi, tazi funkciq e vutre v newFieldNeighbours funkciqta
{
	int i;
	int j;
	int neighboursCount = 0;
	for (i = row - 1; i <= row + 1; i++) {
		for (j = col - 1; j <= col + 1; j++) {
			if ((i == row && j == col) || (i >= row || j >= col) || (i < 0 || j < 0)) {
				continue;
			}
			if (field[i][j] == 1) {
				neighboursCount++;
			}
		}
	}
	return neighboursCount;


}

void newFieldNeighbours(char field[ROWMAX][COLMAX], int rows, int cols) { // prevrushta susednite kletki v murtvi ili jivi v zavisimost ot iziskvaniqta


	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			aliveNeighbours(field, i, j);

			if (field[i][j] == '@' && (aliveNeighbours(field, i, j) == 2 || aliveNeighbours(field, i, j) == 3)) {

				field[i][j] = '@';
			}

			else if (field[i][j] == '-' && aliveNeighbours(field, i, j) == 3) {

				field[i][j] = '@';
			}
			else if (field[i][j] == '@' && aliveNeighbours(field, i, j) > 3) {

				field[i][j] = '-';
			}
			else if (field[i][j] == '@' && aliveNeighbours(field, i, j) < 2) {

				field[i][j] = '-';
			}

		}
	}

}


void printField(char field[ROWMAX][COLMAX], int rows, int cols) { //izprintira igralnoto pole s koordinatite



	// coordinates above the field:
	for (int j = 1; j <= cols + 10; j++) {

		if (j == 11) {

			cout << "1";
		}
		else if (j == cols + 10) {

			cout << cols;
		}
		else {
			cout << " ";
		}

	}
	cout << endl;



	//field:
	for (int i = 1;i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {

			if (j == 1) {

				if (i == 1) {

					cout << "        1 ";

				}
				else if ((i == rows) && rows < 10) {
					cout << "        " << rows << " ";

				}
				else if ((i == rows) && rows >= 10) {
					cout << "       " << rows << " ";

				}
				else {

					cout << "          ";
				}

			}

			cout << field[i][j];

		}
		cout << endl;
	}



}

void randomizeField(char field[ROWMAX][COLMAX], int rows, int cols) { // printira pole s randomized simvoli
	cout << "Please enter a random number which will serve as probability: ";
	int n;
	cin >> n;
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			field[i][j] = (n == 0) ? '-' : (n == 1) ? '@' : (rand() % n == 0) ? '@' : '-'; // ako n e 0, field[i][j] stava -
			//ako n e 1, field[i][j] stava @
			//ako ostatuka kogato delim proizvolno chislo na n e 0 -> field[i][j] stava @
			//ako ostatuka kogato delim proizvolno chislo na n ne e 0 -> field[i][j] stava -
		}
	}
}

void printFieldDimension(char field[ROWMAX][COLMAX], int rows, int cols) { //printira shirochina i duljina na poleto

	cout << cols << " x " << rows << endl;

}

void printNewDimensions(char field[ROWMAX][COLMAX], int x, int y) { //trqbva da izprintira poleto s novite dimensions na usera obache ne raboti

	//coordinates above the field:
	for (int j = 1; j <= x + 10; j++) {

		if (j == 11) {

			cout << "1";
		}
		else if (j == x + 10) {

			cout << x;
		}
		else {
			cout << " ";
		}

	}
	cout << endl;

	//field:
	for (int i = 1;i <= y; i++) {
		for (int j = 1; j <= y; j++) {

			if (j == 1) {

				if (i == 1) {

					cout << "        1 ";

				}
				else if ((i == y) && y < 10) {
					cout << "        " << y << " ";

				}
				else if ((i == y) && y >= 10) {
					cout << "       " << y << " ";

				}
				else {

					cout << "          ";
				}

			}
			cout << field[i][j];
		}
		cout << endl;
	}


}

void saveFile(char field[ROWMAX][COLMAX], ostream& outputStream) { //trqbva da save-ne fayla na usera obache ne raboti


	for (int i = 0; i < ROWMAX; i++) {
		for (int j = 0; j < COLMAX; j++) {
			outputStream << field[i][j] << ' ';
		}
		outputStream << endl;
	}
}

void loadFile(char field[ROWMAX][COLMAX], const string& fileName) { //trqbva da load-ne fayla na usera obache ne raboti



	ifstream inFile(fileName);

	if (inFile.is_open()) {

		for (int i = 0; i < ROWMAX; ++i) {
			for (int j = 0; j < COLMAX; ++j) {
				inFile >> field[i][j];
			}
		}

		cout << "Here's the file: " << fileName << endl;
		inFile.close();
	}

}

void pickMenuOptions(char field[ROWMAX][COLMAX], int rows, int cols); //kopirana funkciq nad pick options poneje ni trqbva

void pickOptions(char field[ROWMAX][COLMAX], int rows, int cols) { //opcii za igrata

	int choiceOption;

	cin >> choiceOption;
	cout << endl;


	while (choiceOption < 1 || choiceOption >7) { //raboti

		cout << "Invalid option. ^~^ Please pick one of the following options!:" << endl << endl;
		printOptions();
		cin >> choiceOption;
		cout << endl << endl;
	}


	while (choiceOption >= 1 && choiceOption <= 7) { //nqmam funkciq za tova :C

		if (choiceOption == 1) {
			cout << "^~^ You've chosen to step forward. Here're the new changes: ";




		}
		else if (choiceOption == 2) { // ne raboti poradi funkciqta 

			cout << "Current dimensions of the field: ";
			printFieldDimension(field, rows, cols);

			int X;
			int Y;

			cout << "Please enter X (width): ";
			cin >> X;
			cout << "Please enter Y (height): ";
			cin >> Y;

			printNewDimensions(field, X, Y);

		}
		else if (choiceOption == 3) { //raboti

			int row;
			int col;

			cout << "Current dimensions of the field: ";
			printFieldDimension(field, rows, cols);

			cout << endl;

			cout << "^~^ Please input the row of the symbol you want to toggle: ";
			cin >> row;
			cout << "^~^ Please input the column of the symbol you want to toggle: ";
			cin >> col;


			toggle(field, row, col);

			printField(field, rows, cols);



		}
		else if (choiceOption == 4) { //raboti

			cout << "^~^ You've chosen to slaughter the cells. :C" << endl;

			deadCellsInField(field, rows, cols);
			printField(field, rows, cols);

		}
		else if (choiceOption == 5) { //raboti

			cout << "^~^ You've chosen to randomize. ";
			randomizeField(field, rows, cols);
			printField(field, rows, cols);

		}
		else if (choiceOption == 6) { //ne raboti


			string fileName;
			cout << "Enter a name for the file you want to save: ";
			cin >> fileName;


			ofstream outFile(fileName);

			if (outFile.is_open()) {

				saveFile(field, outFile);

				cout << "^~^ Your game has been successfully saved to the file: " << fileName << std::endl;
			}


		}
		else if (choiceOption == 7) { //raboti

			cout << "Byebye! ^~^";


			cout << endl << endl;


			pickMenuOptions(field, rows, cols);

		}

		printOptions();
		cin >> choiceOption;

	}


}

void pickMenuOptions(char field[ROWMAX][COLMAX], int rows, int cols) { //opcii

	printMainMenu();


	int menuOption;

	for (int o = 1; o <= 17; o++) {  //centered menu, prazni mesta za centrirano menyu
		cout << " ";                

			cin >> menuOption;
		}
	}


	cout << endl;


	while (menuOption < 1 || menuOption >3) { //raboti
		cout << "Invalid option. Please pick one of the following options!:" << endl << endl;
		printMainMenu();
		cin >> menuOption;
		cout << endl << endl;
	}



	if (menuOption == 1) { //raboti

		cout << "You've chosen to start a new game. The field is below: (I don't know how to center the field please help me, this is a call for help, help please)" << endl << endl;



		printField(field, rows, cols);

		cout << endl << endl << endl;


		printOptions();

		pickOptions(field, rows, cols);



	}

	else if (menuOption == 2) { //ne raboti

		{ cout << "Please enter the name of the file: ";
		string file;
		cin >> file;

		loadFile(field, file);



		}
	}
	else { //raboti

		"Bye, bye!";

	}



}



int main() {


	const int rows = 8;
	const int cols = 16;

	char field[ROWMAX][COLMAX];

	deadCellsInField(field, rows, cols);

	pickMenuOptions(field, rows, cols);




}
