#include<iostream>
#include<random>
#include<ctime>
#include"chessboard.h"
using namespace std;

int main() {
	UserBoard mainboard(5, 5, 5);
	mainboard.showbomb();
	mainboard.showNumBoard();
	mainboard.showUserBoard();
	return 0;
}