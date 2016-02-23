// main.cpp

#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "game.h"
#include "template.h"
#include "drawing.h"

using namespace std;

const int windowWidth = COLS * BLOCKSIZE;
const int windowHeight = ROWS * BLOCKSIZE - BLOCKSIZE;
Game game;
Drawing drawing;


// таймер
void timer(int id)
{
	if (!game.isPaused()) {
		// проигрыш или удаление строки
		if (game.isKilled() || game.isRowCleared()) {
			game.switchFlashOn();
			if (id < 3) {
				glutTimerFunc(100, timer, id + 1);
			}
			else {
				if (game.isRowCleared()) {
					game.clearRow();
				}
				else if (game.isKilled()) {
					game.restart();
				}
				glutTimerFunc(game.getTimer(), timer, 0);
			}
			glutPostRedisplay();
		}
		else {
			// обычный режим
			if (game.isKilled()) {
				glutTimerFunc(100, timer, 1);
			}
			else if (id == 0) {
				glutTimerFunc(game.getTimer(), timer, 0);
				if (game.checkCollision(true, false, false, game.getOrientation())) {
					game.switchBlock();
				}
				else if (!game.checkCollision(true, false, false, game.getOrientation())) {
					game.removeRow();
				}
				else if (game.isRowCleared()) {
					glutTimerFunc(100, timer, 1);
				}
				glutPostRedisplay();
			}
		}
	}
}

// init
void init() {
	glLineWidth(2.0);
	glClearColor(255, 255, 255, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

// функция отрисовки паузы
void pause() {
	glViewport(80, 0, windowWidth, windowHeight);
	init();
	gluOrtho2D(-1, COLS - 1, 0, ROWS);
	drawing.setColor(Drawing::kGray);
	glRectd(0, 0, COLS - 1, ROWS);

	drawing.setColor(Drawing::kWhite);
	drawing.displayText("Pause", 4, 10);
	glutSwapBuffers();
}

// функция обработки паузы и выхода из игры
void keyboard(unsigned char key, int x, int y) {
	if (key == 'p') {
		game.switchPaused();
		pause();
		if (!game.isPaused()) {
			glutTimerFunc(game.getTimer(), timer, 0);
			glutSwapBuffers();
		}
	}
	else if (key == ' ') {
		game.setTimer(TIMER_FAST);
	}
	else if (key == 'x') {
		exit(0);
	}
}

// функция обработки клавиатуры (движение вращение)
void special(int key, int x, int y)
{
	if (!game.isPaused() && !game.isKilled()) {
		if (key == GLUT_KEY_LEFT) {
			game.move(-1, 0);
		}
		else if (key == GLUT_KEY_RIGHT) {
			game.move(+1, 0);
		}
		else if (key == GLUT_KEY_DOWN) {
			game.move(0, -1);
		}
		else if (key == GLUT_KEY_UP) {
			game.move(0, 1);
		}
		else if (key == GLUT_KEY_F1) {
			game.setNextBlock(1);
		}
		glutPostRedisplay();
	}
}


// функция отрисовки блоков
void displayTetriminos(BrickBlock tetrimino, int x, int y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tetrimino.grid[i][j] == 'X') {
				drawing.drawTeramino(x, y, j, i, tetrimino.color);
			}
		}
	}
}

// функция отрисовки блоков лежащих на земле
void displayGrid() {
	for (int r = 0; r<ROWS; r++) {
		for (int c = 0; c<COLS; c++) {
			if (game.getGrid(r, c) > -1) {
				int grid = game.getGrid(r, c);
				int color = blockTemplates[grid][0].color;
				drawing.drawTeramino(c, r, 1, -1, color);
			}
		}
	}
}

//функция выводит анимацию при очистке строки
void displayAnimation() {
	if (game.isRowCleared()) {
		if (game.isFlashOn() == true) {
			drawing.setColor(Drawing::kGray);
		}
		else {
			drawing.setColor(Drawing::kWhite);
		} for (int c = 0; c < COLS; c++) {
			if (game.getGrid(game.getClearedRow(), c) > -1)
				glRectd(c, game.getClearedRow(), c + 1, game.getClearedRow() + 1);
		}
	}
}


void display(void){
	init();
	glClear(GL_COLOR_BUFFER_BIT);

	//отрисовка следующего блока
	glViewport(0, 0, 110, windowHeight);
	init();
	gluOrtho2D(0, COLS - 1, 0, ROWS);
	drawing.setColor(Drawing::kGray);
	drawing.drawAll(0, 0, COLS, ROWS, GL_QUADS);

	glViewport(80, 0, windowWidth, windowHeight);
	init();
	glOrtho(-1, COLS - 1, 0, ROWS, -1, 1);

	// полоска
	drawing.setColor(Drawing::kBlack);
	drawing.drawLine(0, 0, 0, ROWS);

	// отрисовать сетку
	drawing.setColor(Drawing::kGray);
	for (int r = 0; r < COLS; r++) {
		drawing.drawLine(r, 0, r, ROWS);
	}
	for (int c = 0; c < ROWS; c++) {
		drawing.drawLine(0, c, COLS, c);
	}

	displayGrid();
	displayAnimation();

	//отрисовка блоков
	BrickBlock currBlock = blockTemplates[game.getCurrentBlock()][game.getOrientation()];
	displayTetriminos(currBlock, game.getPos(), game.getRow());

	//отрисовка следующего блока
	glViewport(5, 350, windowWidth - 60, windowHeight - 60);
	init();
	gluOrtho2D(-2, COLS - 3, 0, ROWS - 3);

	BrickBlock nextBlock = blockTemplates[game.getNextBlock()][0];
	displayTetriminos(nextBlock, 0, (ROWS - 8) / 2);

	//отрисовка информации
	glViewport(10, 55, 125, 350);
	init();
	gluOrtho2D(-2, COLS, 0, ROWS + 11);
	//нарисовать маленькие блоки
	for (int i = 0; i < NUM_BLOCK_TYPES; i++) {
		BrickBlock smallBlock = blockTemplates[i][0];
		if (i == 1)
			displayTetriminos(smallBlock, 0, ROWS + 10 - i * 4 + 1);
		else
			displayTetriminos(smallBlock, 0, ROWS + 10 - i * 4);
	}

	//вывод надписей с количеством блоков
	glViewport(30, 55, 125, 350);
	init();
	gluOrtho2D(-2, COLS, 0, ROWS + 10);
	char m[100];
	drawing.setColor(Drawing::kBlack);
	for (int i = 0; i < NUM_BLOCK_TYPES; i++) {
		sprintf_s(m, "x %d", game.getNumTimes(i));
		drawing.displayText(m, 0, ROWS + 10 - i * 4 - 2);
	}

	//вывод надписей 
	init();
	glViewport(5, 10, windowWidth, 50);
	gluOrtho2D(0, 100, 0, 600);

	char msg[100];
	sprintf_s(msg, "Lines: %d", game.getLinesCleared());
	drawing.setColor(Drawing::kBlack);
	drawing.displayText(msg, 1, 50);

	sprintf_s(msg, "Points: %d", game.getGamePoint());
	drawing.displayText(msg, 1, 300);

	sprintf_s(msg, "Level: %d", game.getLevel());
	drawing.displayText(msg, 1, 600);

	glutSwapBuffers();
}


// main
void main(int argc, char *argv[]) {
	srand(time(NULL));
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowWidth + 80, windowHeight - 60);

	glutCreateWindow("Tetris OpenGL");

	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(game.getTimer(), timer, 0);

	glutMainLoop();
}
