// drawing.cpp

#include "Drawing.h"

Drawing::Drawing()
{
}

Drawing::~Drawing()
{
}

// �������� ������
void Drawing::drawTeramino(int x1, int y1, int x2, int y2, int color) {
	this->setColor(color);
	glRectd(x1 + x2, y1 - y2, x1 - 1 + x2, y1 - 1 - y2);
	this->drawOutLine(x1 - 1 + x2, y1 - 1 - y2);
}

// ������� ���������
void Drawing::drawAll(int x1, int y1, int x2, int y2, int typeDraw) {
	glBegin(typeDraw);
	glVertex2d(x1, y1);
	glVertex2d(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}


// ������� ��� ��������� �������
void Drawing::drawLine(int x1, int y1, int x2, int y2) {
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
}


// ������� ������ ��������� ������� ���������� ������� �
void Drawing::drawOutLine(int x1, int y1) {
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(x1, y1);
	glVertex2d(x1, y1 + 1);
	glVertex2d(x1 + 1, y1 + 1);
	glVertex2d(x1 + 1, y1);
	glEnd();
}



// ������� ������ ����
void Drawing::setColor(int color) {
	static const struct teraminoColor
	{
		float r, g, b;
	}
	colors[] = {
		{ 1, 1, 1 },			// �����
		{ 1, 0, 0 },			// �������
		{ 1, 1, 0 },			// ������
		{ 0, 1, 1 },			// �������
		{ 1, 0, 1 },			// ����������
		{ 0, 0, 1 },			// �����
		{ 0, 1, 0 },			// �������
		{ 0.5f, 0.5f, 0 },		// ����������
		{ 0, 0, 0 },			// ������
		{ 0.9f, 0.9f, 0.9f },	// �����
	};
	glColor3f(
		colors[color].r,
		colors[color].g,
		colors[color].b
		);
}


// ������� ��������� ������
void Drawing::displayText(char *str, int wcx, int wcy) {
	glRasterPos2i(wcx, wcy);
	for (int i = 0; str[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}