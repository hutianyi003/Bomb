#include<ctime>
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
			for (int k = 0; k < 4; k++) {
				int nextx = i + DeltaMove[k][0], nexty = j + DeltaMove[k][1];
				if (isGoodPosition(nextx, nexty) && isBomb(nextx, nexty))
					numboard[i][j]++;
			}
	return;
}

bool UserBoard::LeftClick(int x, int y)
{
	if (userboard[x][y] == meanFlag) {
		// GUI :clear flags on (x,y)
		userboard[x][y] = meanCover;
		return true;
	}
	if (userboard[x][y] == meanCover) {
		// GUI :open (x,y)
		if (isBomb(x, y)) {
			//GameOver
			return true;
		}
		//search for all 0 points and show numbers
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