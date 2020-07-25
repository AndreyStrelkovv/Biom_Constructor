#pragma once
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
};

