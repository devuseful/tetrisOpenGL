//game.h

#ifndef _GAME_H_
#define _GAME_H_

#include <cstdlib>
#include <cstdio>
#include "template.h"
#include "constants.h"
using namespace std;

class Game {

public:
	Game(void);
	~Game(void);

	void restart();
	void move(int direction, int rotate);
	bool checkCollision(bool down, bool left, bool rotate, int orient);
	void switchBlock();
	void clearRow();

	int getGrid(int rows, int cols);
	int getPos();
	int getRow();
	void removeRow();
	bool isRowCleared();
	int getClearedRow();
	bool isKilled();
	bool isFlashOn();
	void switchFlashOn();

	int getGamePoint();
	int getLinesCleared();
	bool isPaused();
	void switchPaused();
	int getTimer();
	void setTimer(int timer);

	int getNextBlock();
	void setNextBlock(int nextBlock);

	int getCurrentBlock();
	int getOrientation();
	int getNumTimes(int numTimesTag);
	int getLevel();



protected:

	enum enumGame {
		kLevelStep = 10,
		kTimerStep = 25,
		kClearRowPoint = 10,
	};

	void _clearGrid(bool clearRow);
	void _update(int rowCleared);
	void _blockToGrid();
	void _checkDeath();
	void _addGamePoint(int point);

	int grid_[ROWS][COLS];						// 0 - �� �������� ������ 0 - �������� ������
	int pos_;									// ������� � ������� ��������� ����
	int row_;									// ������ � ������� ��������� ����
	bool rowCleared_;							// ������� ������
	int clearedRowTag_;							// ��������� ������
	bool killed_;								// ���� ����� �����������
	bool flashOn_;								// ������� ������� ��� ��������

	int gamePoint_;
	int linesCleared_;							// ������� �����
	bool paused_;								// �����
	int timer_;									// �������� ����
	int timerStart_;							// �������� ���� ���������

	int nextBlock_;								// ��������� ����
	int currentBlock_;							// ������� ����
	int orientation_;							// ���������� �����	
	int numTimes_[7];							// ������� ��� ����� ����
	int level_;
};

#endif