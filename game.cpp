//game.cpp

#include "game.h"

// конструктор
Game::Game() {
	currentBlock_ = rand() % NUM_BLOCK_TYPES;
	this->restart();
	numTimes_[currentBlock_] = 1;
	nextBlock_ = rand() % NUM_BLOCK_TYPES;
}

// деструктор
Game::~Game() {
}

// начать игру заново
void Game::restart() {
	for (int i = 0; i < NUM_BLOCK_TYPES; i++) {
		numTimes_[i] = 0;
	}
	numTimes_[currentBlock_] = 1;
	this->_clearGrid(false);
	pos_ = COLS / 2;
	row_ = ROWS;
	gamePoint_ = 0;
	linesCleared_ = 0;
	killed_ = false;
	paused_ = false;
	timer_ = TIMER;
	timerStart_ = TIMER;
	level_ = 1;
}

//функция двигает и вращает блоки
void Game::move(int direction, int rotate) {
	if (direction < 0 && pos_ > 1 && !this->checkCollision(false, true, false, orientation_))
		pos_--;
	else if (direction > 0 && pos_ < COLS - blockTemplates[currentBlock_][orientation_].w && !this->checkCollision(false, false, false, orientation_))
		pos_++;
	else if (!this->checkCollision(false, true, true, 0) && !this->checkCollision(false, false, true, 1)) {
		if (rotate < 0) {
			orientation_--;

			if (orientation_ < 0)
				orientation_ = 3;
		}
		else if (rotate > 0) {
			orientation_++;

			if (orientation_ > 3)
				orientation_ = 0;
		}
	}
}


// функция удаляет строку помеченную к удалению
// и вызывает обновление стакана
void Game::clearRow() {
	rowCleared_ = false;
	linesCleared_++;
	for (int c = 0; c < COLS - 1; c++) {
		grid_[clearedRowTag_][c] = -1;
	}
	this->_update(clearedRowTag_);
}

// функция переключает блок
void Game::switchBlock() {
	timer_ = timerStart_;
	this->_blockToGrid();
	this->_clearGrid(true);
	this->_checkDeath();
	currentBlock_ = nextBlock_;
	numTimes_[currentBlock_] += 1;
	row_ = ROWS;
	pos_ = COLS / 2;
	orientation_ = 0;
	nextBlock_ = rand() % NUM_BLOCK_TYPES;
	this->_addGamePoint(1);
}


// функция обработки столкновений
bool Game::checkCollision(bool down, bool left, bool rotate, int orient) {
	BrickBlock block = blockTemplates[currentBlock_][orient];
	int rotateOffset = 0;
	if (rotate)
		rotateOffset = 1;

	for (int i = 0; i < NUM_POS; i++) {
		for (int j = 0; j < NUM_POS; j++) {
			if (block.grid[i][j] == 'X') {
				if (down) {

					if (block.h - row_ == 0)
						return true;
					else if (grid_[row_ - i - 2][pos_ + j - 1] != -1) // если блок будет снизу
						return true;
				}
				else if (left) {
					if (grid_[row_ - i - 1][pos_ + j - 2 + rotateOffset] != -1 || row_ - block.h < 0 || pos_ + block.w < 0)
						return true;
				}
				else if (!left) {
					if (grid_[row_ - i - 1][pos_ + j - rotateOffset] != -1 || pos_ + block.w > COLS)
						return true;
				}
			}
		}
	}
	return false;
}


int Game::getGrid(int rows, int cols) {
	return grid_[rows][cols];
}

int Game::getPos() {
	return pos_;
}

int Game::getRow() {
	return row_;
}

void Game::removeRow() {
	row_--;
}

bool Game::isRowCleared() {
	return rowCleared_;
}

int Game::getClearedRow() {
	return clearedRowTag_;
}

bool Game::isKilled() {
	return killed_;
}

bool Game::isFlashOn() {
	return flashOn_;
}

void Game::switchFlashOn() {
	flashOn_ = !flashOn_;
}

int Game::getLinesCleared() {
	return linesCleared_;
}

bool Game::isPaused() {
	return paused_;
}

void Game::switchPaused() {
	paused_ = !paused_;
}

int Game::getTimer() {
	return timer_;
}

void Game::setTimer(int timer) {
	timer_ = timer;
}

int Game::getNextBlock() {
	return nextBlock_;
}

void Game::setNextBlock(int nextBlock) {
	nextBlock_ = nextBlock;
}

int Game::getCurrentBlock() {
	return currentBlock_;
}

int Game::getOrientation() {
	return orientation_;
}

int Game::getNumTimes(int numTimesTag) {
	return numTimes_[numTimesTag];
}

int Game::getGamePoint() {
	return gamePoint_;
}

int Game::getLevel() {
	return level_;
}



// функция очищает стакан или находит ряд для очистки
void Game::_clearGrid(bool clearRow) {
	if (!clearRow) {
		for (int r = 0; r < ROWS; r++) {
			for (int c = 0; c < COLS; c++) {
				grid_[r][c] = -1;
			}
		}
	}
	else {
		for (int r = 0; r < ROWS; r++) {
			bool flag = true;
			for (int c = 0; c < COLS - 1; c++) {
				if (grid_[r][c] == -1) {
					flag = false;
				}
			}

			if (flag) {
				clearedRowTag_ = r;
				rowCleared_ = true;
				flashOn_ = true;
			}
		}
	}
}


// функция перемещает всю кучу блоков вниз
void Game::_update(int rowCleared) {
	for (int r = rowCleared; r < ROWS - 2; r++) {
		for (int c = 0; c < COLS; c++) {
			grid_[r][c] = grid_[r + 1][c];
			this->_clearGrid(true);
		}
	}
	this->_addGamePoint(kClearRowPoint);
}


// функция добавляет блок в стакан
void Game::_blockToGrid() {
	BrickBlock piece = blockTemplates[currentBlock_][orientation_];
	for (int i = 0; i < NUM_POS; i++) {
		for (int j = 0; j < NUM_POS; j++) {
			if (piece.grid[i][j] == 'X') {
				grid_[row_ - i - 1][pos_ + j - 1] = currentBlock_;
			}
		}
	}
}


// функция проверяет проиграл игрок или нет
void Game::_checkDeath() {
	if (grid_[ROWS - 1][COLS / 2] != -1) {
		killed_ = true;
	}
}

// функция прибавляет очки, увеличивает уровень и скорость
void Game::_addGamePoint(int point) {
	if (gamePoint_ / kLevelStep  < (gamePoint_ + point) / kLevelStep) {
		level_++;
		timerStart_ -= kTimerStep;
		if (timerStart_ < 1)
			timerStart_ = 1;
	}
	gamePoint_ += point;
}