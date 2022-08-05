#include<iostream>
using namespace std;

const int n = 3;

char nextStep(char gamer_name) {
	if (gamer_name == 'X')
		return 'O';
	else
		return 'X';
}

bool checkPos(int x, int y, bool currPlace) {
	if (currPlace == false) {
		if (x >= 0 && x < 3 && y >= 0 && y < 3)
			return true;
		else {
			cout << "Ошибка! Введите корректную координату!" << endl;
			return false;
		}
	}
	else {
		cout << "Ошибка! Введите корректную координату!" << endl;
		return false;
	}
}

bool checkWinner(char **game, bool **places) {
	int flagX3 = 0, flagX4 = 0;
	int flagO3 = 0, flagO4 = 0;
	for (int i = 0; i < n; i++) {
		int flagX1 = 0, flagX2 = 0;
		int flagO1 = 0, flagO2 = 0;
		for (int j = 0; j < n; j++) {
			if (places[i][j] && game[i][j] == 'X')
				flagX1++;
			if (places[j][i] && game[j][i] == 'X')
				flagX2++;
			if (places[i][j] && game[i][j] == 'O')
				flagO1++;
			if (places[j][i] && game[j][i] == 'O') 
				flagO2++;
			if ((i == j) && places[i][j] && game[i][j] == 'X')
				flagX3++;
			if ((i == j) && places[i][j] && game[i][j] == 'O')
				flagO3++;
			if ((i == n - j - 1) && places[i][j] && game[i][j] == 'X')
				flagX4++;
			if ((i == n - j - 1) && places[i][j] && game[i][j] == 'O')
				flagO4++;
		}
		if (flagX1 == 3 || flagX2 == 3 || flagX3 == 3 || flagX4 == 3) {
			cout << "Победитель крестики!" << endl;
			cout << endl;
			return 1;
		}
		if (flagO1 == 3 || flagO2 == 3 || flagO3 == 3 || flagO4 == 3) {
			cout << "Победитель нолики!" << endl;
			cout << endl;
			return 1;
		}
	}
	return 0;
}

void print(char **game) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (j > 0)
				cout << "|";
			cout << game[i][j];
		}
		cout << endl;
		if (i < 2)
			cout << "------" << endl;
	}
	cout << endl;
}

int main() {
	setlocale(LC_ALL, "RU");
	bool **places = new bool*[n];
	char **game = new char*[n];
	char gamer_name = 'X';

	for (int i = 0; i < 3; i++) {
		game[i] = new char[n];
		places[i] = new bool[n];
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			places[i][j] = false;
			game[i][j] = ' ';
		}
	}

	cout << "Начало игры!" << endl;
	cout << "------------------------------" << endl;
	cout << endl;
	print(game);
	for (int step = 0; step < n * n; step++) {
		int x, y;
		do {
			cout << "Введите координату (от 0 до 2) через пробел, куда хотите поставить свой символ: ";
			cin >> x >> y;
		} while (!checkPos(x, y, places[x][y]));
		game[x][y] = gamer_name;
		places[x][y] = true;
		cout << "Символ успешно поставлен!" << endl;
		cout << "------------------------------" << endl;
		if (checkWinner(game, places)) {
			print(game);
			cout << "Игра завершена!" << endl;
			return 0;
		}
		gamer_name = nextStep(gamer_name);
		print(game);
		cout << "------------------------------" << endl;
	}
	cout << "Ничья!" << endl;
	cout << "Игра завершена!" << endl;
	return 0;
}