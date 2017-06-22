#include<iostream>
#include<random>
#include<ctime>
#include"chessboard.h"
using namespace std;

int main() {
	UserBoard mainboard(10, 10, 10);
	cout << "Bombs:" << endl;
	mainboard.showbomb();
	cout << "Numboard:" << endl;
	mainboard.showNumBoard();

	while (true) {
		cout << "userboard:" << endl;
		mainboard.showUserBoard();
		int tx, ty;
		cin >> tx >> ty;
		mainboard.LeftClick(tx, ty);
	}
	return 0;
}