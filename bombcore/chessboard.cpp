#include<ctime>
#include<iostream>
#include<random>
#include"chessboard.h"
using namespace std;


ChessBoard::ChessBoard(int xx, int yy, int n) :x(xx), y(yy), num(n)
{
	//Error check
	if (x <= 0 || y <= 0 || num <= 0) {
		//throw ErrorBadData("Negative number!!");
		return;
	}
	if (x > MaxBoardN || y > MaxBoardN || num > x*y) {
		//throw ErrorBadData("Too large number!!");
		return;
	}
	//Make bombs
	default_random_engine generator((unsigned int)time(NULL));
	uniform_int_distribution<int> disx(0, x-1);
	uniform_int_distribution<int> disy(0, y-1);
	int t = num;
	while (t > 0) {
		int choosex = disx(generator), choosey = disy(generator);
		if (board[choosex][choosey] == 0) {
			t--;
			board[choosex][choosey] = 1;
		}
	}
}

inline bool ChessBoard::isGoodPosition(int x, int y) {
	if (x >= 0 && y >= 0 && x <= ChessBoard::x && y <= ChessBoard::y)
		return true;
	return false;
}
bool UserBoard::isFinish()
{
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++) {
			if (isBomb(i, j) == false){
				if (userboard[i][j] == meanOpen)
					continue;
				return false;
			}
		}
	return true;
}

UserBoard::UserBoard(int xx, int yy, int n) :ChessBoard(xx, yy, n)
{
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++) 
			for (int k = 0; k < 9; k++) {
				int nextx = i + DeltaMove[k][0], nexty = j + DeltaMove[k][1];
				if (isGoodPosition(nextx, nexty) && isBomb(nextx, nexty))
					numboard[i][j]++;
			}
	return;
}

bool UserBoard::search(int nowx, int nowy) {
	// GUI :open (x,y)
	hasWalk[nowx][nowy] = true;
	userboard[nowx][nowy] = meanOpen;
	if (numboard[nowx][nowy] > 0)
		return true;
	for (int i = 0; i < 8; i++) {
		int nextx = nowx + DeltaMove[i][0], nexty = nowy + DeltaMove[i][1];
		if (isGoodPosition(nextx, nexty) && hasWalk[nextx][nexty] == false
			&& isBomb(nextx, nexty) == false && userboard[nextx][nexty] == meanCover) {
			if (search(nextx, nexty) == false)
				return false;
		}
	}
	return true;
}

bool UserBoard::LeftClick(int x, int y)
{
	if (userboard[x][y] == meanFlag) {
		// GUI :clear flags on (x,y)
		userboard[x][y] = meanCover;
		return true;
	}
	if (userboard[x][y] == meanCover) {
		if (isBomb(x, y)) {
			//GameOver
			return true;
		}
		//reset hasWalk
		for (int i = 0; i < ChessBoard::x; i++)
			for (int j = 0; j < ChessBoard::y; j++)
				hasWalk[i][j] = false;
		if (search(x, y) == false) return false;
		if (isFinish()) {
			// GUI :finish
		}
		return true;
	}
	if (userboard[x][y] == meanOpen) {
		return true;
	}
	return false;
}

bool UserBoard::RightClick(int x, int y)
{
	if (userboard[x][y] == meanOpen) {
		return true;
	}
	if (userboard[x][y] == meanCover) {
		// GUI :put flag on (x,y)
		userboard[x][y] = meanFlag;
		return true;
	}
	if (userboard[x][y] = meanFlag) {
		return true;
	}
	return false;
}

inline bool ChessBoard::isBomb(int x, int y) {
	return (board[x][y] == meanBomb);
}

inline bool UserBoard::isCover(int x, int y) {
	return (userboard[x][y] == meanCover);
}

inline bool UserBoard::isFlag(int x, int y) {
	return (userboard[x][y] == meanFlag);
}

inline bool UserBoard::isOpen(int x, int y) {
	return (userboard[x][y] == meanOpen);
}

void ChessBoard::show(int output[MaxBoardN][MaxBoardN]) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++)
			cout << output[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

void ChessBoard::showbomb() {
	show(board);
	return;
}

void UserBoard::showNumBoard() {
	show(numboard);
	return;
}

void UserBoard::showUserBoard() {
	show(userboard);
	return;
}