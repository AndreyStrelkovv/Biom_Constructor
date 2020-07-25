#pragma once
#include "wx/wx.h"
#include "wx/vscroll.h"
#include "Cell.h"

#include "vector"
using std::vector;

class Canvas : public wxHVScrolledWindow
{
public:
	Canvas(wxWindow* parent);
	~Canvas();

private:
	int pixelSize = 8;

public:
	void SetPixelSize(int n);
	void SetSpriteData(int rows, int columns, unsigned char *pSprite);
	void SetColour(int c);

private:

	unsigned char* sprite = nullptr;
	//wxColour palette[16];
	//vector<unsigned char*> sprite;
	vector<wxColour> elem;
	int colour;

private:
	//vector that contains information about every cell
	vector<Cell> cells;
	vector<wxColour> waterdepth;

private:
	virtual wxCoord OnGetRowHeight(size_t row) const;
	virtual wxCoord OnGetColumnWidth(size_t col) const;

	void OnMouseLeftDown(wxMouseEvent& evt);

	void OnDraw(wxDC& dc);
	void OnPaint(wxPaintEvent& evt);

	wxDECLARE_EVENT_TABLE();
};
