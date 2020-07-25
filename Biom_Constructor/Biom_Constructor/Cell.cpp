#include "Cell.h"

Cell::Cell(int t, int h, int tp)
{
	temp = t;
	height = h;
	type = tp;
}

Cell::~Cell()
{
}

void Cell::setTemp()
{
}

void Cell::setHeight(int h)
{
	if (h < 10) {
		height = h;
	}
}

void Cell::setType(int t)
{
	type = t;
}

void Cell::setParameters()
{
}

int Cell::getHeight()
{
	return height;
}

int Cell::getType()
{
	return type;
}

string Cell::toString()
{
	string str = "height = " + to_string(height) + "; temp = " + to_string(temp) + "; type = " + to_string(type);
	return str;
}
