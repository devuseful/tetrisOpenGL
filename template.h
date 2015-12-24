// template.h

#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include "constants.h"


struct BrickBlock {
	int w, h, color;
	char *grid[4];
};

// ������ ������ ��� ������� ���������
// ������, ������, ����, �������� (������ ��� X)
const BrickBlock blockTemplates[NUM_BLOCK_TYPES][NUM_POS] =
{
	{
		{ 2, 2, 1, "XX  ",
		"XX  ",
		"    ",
		"    " },
		{ 2, 2, 1, "XX  ",
		"XX  ",
		"    ",
		"    " },
		{ 2, 2, 1, "XX  ",
		"XX  ",
		"    ",
		"    " },
		{ 2, 2, 1, "XX  ",
		"XX  ",
		"    ",
		"    " }
	},
	{
		{ 1, 4, 2, "X   ",
		"X   ",
		"X   ",
		"X   " },
		{ 4, 1, 2, "XXXX",
		"    ",
		"    ",
		"    " },
		{ 1, 4, 2, "X   ",
		"X   ",
		"X   ",
		"X   " },
		{ 4, 1, 2, "XXXX",
		"    ",
		"    ",
		"    " }
	},
	{
		{ 2, 3, 3, "X   ",
		"XX  ",
		"X   ",
		"    " },
		{ 3, 2, 3, " X  ",
		"XXX ",
		"    ",
		"    " },
		{ 2, 3, 3, " X  ",
		"XX  ",
		" X  ",
		"    " },
		{ 3, 2, 3, "XXX ",
		" X  ",
		"    ",
		"    " }
	},
	{
		{ 2, 3, 4, "X   ",
		"XX  ",
		" X  ",
		"    " },
		{ 3, 2, 4, " XX ",
		"XX  ",
		"    ",
		"    " },
		{ 2, 3, 4, "X   ",
		"XX  ",
		" X  ",
		"    " },
		{ 3, 2, 4, " XX ",
		"XX  ",
		"    ",
		"    " }
	},
	{
		{ 2, 3, 5, "XX  ",
		"X   ",
		"X   ",
		"    " },
		{ 3, 2, 5, "X   ",
		"XXX ",
		"    ",
		"    " },
		{ 2, 3, 5, " X  ",
		" X  ",
		"XX  ",
		"    " },
		{ 3, 2, 5, "XXX ",
		"  X ",
		"    ",
		"    " }
	},
	{
		{ 2, 3, 6, "XX  ",
		" X  ",
		" X  ",
		"    " },
		{ 3, 2, 6, "XXX ",
		"X   ",
		"    ",
		"    " },
		{ 2, 3, 6, "X   ",
		"X   ",
		"XX  ",
		"    " },
		{ 3, 2, 6, "  X ",
		"XXX ",
		"    ",
		"    " }
	},
	{
		{ 2, 3, 7, " X  ",
		"XX  ",
		"X   ",
		"    " },
		{ 3, 2, 7, "XX ",
		" XX ",
		"    ",
		"    " },
		{ 2, 3, 7, " X  ",
		"XX  ",
		"X   ",
		"    " },
		{ 3, 2, 7, "XX  ",
		" XX ",
		"    ",
		"    " }
	}
};

#endif