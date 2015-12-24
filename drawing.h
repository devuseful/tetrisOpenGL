// drawing.h

#ifndef _DRAWING_H_
#define _DRAWING_H_

#include <GL/glut.h>

class Drawing
{
public:
	Drawing(void);
	~Drawing(void);

	enum enumColor {
		kWhite = 0,
		kRed,
		kYellow,
		kBlue,
		kPurple,
		kDarkBlue,
		kGreen,
		kBrown,
		kBlack,
		kGray,
	};

	void drawTeramino(int x1, int y1, int x2, int y2, int color);
	void drawAll(int x1, int y1, int x2, int y2, int typeDraw);
	void drawLine(int x1, int y1, int x2, int y2);
	void drawOutLine(int x1, int y1);

	void setColor(int color);
	void displayText(char *str, int wcx, int wcy);

private:

};

#endif