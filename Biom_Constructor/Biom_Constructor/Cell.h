#pragma once
#include "string"
using std::string;
using std::to_string;

class Cell
{
public:
	Cell(int temp, int height, int type);
	~Cell();

private:
	int temp;
	int height;
	int type;

public:
	void setTemp();
	void setHeight(int h);
	void setType(int t);
	void setParameters();

	int getHeight();
	int getType();

	string toString();
};

