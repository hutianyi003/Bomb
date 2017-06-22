#pragma once
/*
	Ver 1.0
	This Headfile includes classes and functions for making and using chessboard.
	Commend:Using class UserBoard
	UserBoard(int x, int y, int num) makes a x*y board with num bombs.
	LeftClick(int x, int y) should work when mouse leftclicks point(x,y) on the board.
	RightClick(int x, int y) same.
*/
const int MaxBoardN = 100;
const int DeltaMove[8][2] = { {0, 1},{0,-1},{-1,0},{1,0},{-1,-1},{-1,1},{1,-1},{1,1} };

class ErrorBadData;
class ErrorUnknown;

class ChessBoard;
class ChessBoard {
private:
	const int meanBomb = 1;
	int board[MaxBoardN][MaxBoardN] = { 0 };//0 -> nobomb 1 -> bomb
protected:
	int x, y, num;
	void show(int output[MaxBoardN][MaxBoardN]);
public:
	ChessBoard(int, int, int); /*three positive numbers and no more than MaxBoardN*/
	inline bool isBomb(int, int);
	inline bool isGoodPosition(int, int);
	void showbomb();
};

class UserBoard :public ChessBoard {
private:
	const int meanFlag = -1, meanCover = 0, meanOpen = 1;
	int userboard[MaxBoardN][MaxBoardN] = { 0 };
	int numboard[MaxBoardN][MaxBoardN] = { 0 };
public:
	UserBoard(int, int, int);
	bool LeftClick(int, int);
	bool RightClick(int, int);
	bool isFinish();//check if all bombs are found
	inline bool isFlag(int, int);
	inline bool isCover(int, int);
	inline bool isOpen(int, int);
	void showUserBoard();
	void showNumBoard();
};
