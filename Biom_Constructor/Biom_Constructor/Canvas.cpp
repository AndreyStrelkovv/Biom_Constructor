#include "Canvas.h"
#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

#include "iostream"
using std::endl;
using std::cout;
using std::ostringstream;

#include "ProjectFrame.h"

wxBEGIN_EVENT_TABLE(Canvas, wxHVScrolledWindow)
	EVT_PAINT(Canvas::OnPaint)
	EVT_LEFT_DOWN(Canvas::OnMouseLeftDown)
	EVT_LEFT_UP(Canvas::OnMouseLeftUp)
	EVT_RIGHT_DOWN(Canvas::OnMouseRightDown)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow* p) : wxHVScrolledWindow(p, wxID_ANY)
{
	//SetRowColumnCount(40, 40);
	parent = p;
	//SetBackgroundStyle(wxBG_STYLE_PAINT);

	/*cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;*/
	OutputDebugStringA("Some random text");
	elem.push_back(wxColour(10, 108, 255));
	elem.push_back(wxColour(161, 64, 43));
	elem.push_back(wxColour(80, 80, 80));
	elem.push_back(wxColour(237, 201, 175));

	waterdepth.push_back(wxColour(10, 108, 255));
	waterdepth.push_back(wxColour(5, 101, 243));
	waterdepth.push_back(wxColour(7, 93, 220));
	waterdepth.push_back(wxColour(8, 84, 199));
	waterdepth.push_back(wxColour(7, 74, 175));
	waterdepth.push_back(wxColour(6, 64, 152));
	waterdepth.push_back(wxColour(5, 56, 132));
	waterdepth.push_back(wxColour(5, 49, 117));
	waterdepth.push_back(wxColour(3, 43, 102));
	waterdepth.push_back(wxColour(3, 36, 85));

	//palette[0] = wxColour(0, 0, 0);
	//palette[1] = wxColour(0, 0, 128);
	//palette[2] = wxColour(0, 128, 0);
	//palette[3] = wxColour(0, 128, 128);
	//palette[4] = wxColour(128, 0, 0);
	//palette[5] = wxColour(128, 0, 128);
	//palette[6] = wxColour(128, 128, 0);
	//palette[7] = wxColour(192, 192, 192);
	//palette[8] = wxColour(128, 128, 128);
	//palette[9] = wxColour(0, 0, 255);
	//palette[10] = wxColour(0, 255, 0);
	//palette[11] = wxColour(0, 255, 255);
	//palette[12] = wxColour(255, 0, 0);
	//palette[13] = wxColour(255, 0, 255);
	//palette[14] = wxColour(255, 255, 0);
	//palette[15] = wxColour(255, 255, 255);
}

Canvas::~Canvas()
{
	//if (sprite != nullptr) {
	//	delete sprite;
	//}
}

void Canvas::SetPixelSize(int n)
{
	pixelSize = n;
	wxVarHScrollHelper::RefreshAll();
	wxVarVScrollHelper::RefreshAll();
	Refresh();
}

void Canvas::SetSpriteData(int rows, int columns, unsigned char* pSprite)
{
	sprite = pSprite;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cells.push_back(Cell(0, 1, sprite[j * this->GetColumnCount() + i]));
		}
	}
	this->SetRowColumnCount(rows, columns);
}

void Canvas::SetColour(int c)
{
	colour = c;
}

wxCoord Canvas::OnGetRowHeight(size_t row) const
{
	return wxCoord(pixelSize);
}

wxCoord Canvas::OnGetColumnWidth(size_t col) const
{
	return wxCoord(pixelSize);
}

void Canvas::OnMouseLeftDown(wxMouseEvent& evt)
{
	wxPosition s = GetVisibleBegin();

	x = evt.GetX() / pixelSize + s.GetCol();
	y = evt.GetY() / pixelSize + s.GetRow();
}

void Canvas::OnMouseLeftUp(wxMouseEvent& evt)
{
	wxPosition s = GetVisibleBegin();

	int x1 = evt.GetX() / pixelSize + s.GetCol();
	int y1 = evt.GetY() / pixelSize + s.GetRow();

	if (x1 <= x && y1 <= y) {
		for (int i = x1; i <= x; i++) {
			for (int j = y1; j <= y; j++) {
				changeCellData(i, j);
			}
		}
	}
	else if (x1 >= x && y1 <= y) {
		for (int i = x; i <= x1; i++) {
			for (int j = y1; j <= y; j++) {
				changeCellData(i, j);
			}
		}
	}
	else if (x1 <= x && y1 >= y) {
		for (int i = x1; i <= x; i++) {
			for (int j = y; j <= y1; j++) {
				changeCellData(i, j);
			}
		}
	}
	else if (x1 >= x && y1 >= y) {
		for (int i = x; i <= x1; i++) {
			for (int j = y; j <= y1; j++) {
				changeCellData(i, j);
			}
		}
	}

	this->Refresh(false);
	evt.Skip();
}

void Canvas::changeCellData(int i, int j)
{
	int p = j * this->GetColumnCount() + i;

	sprite[p] = colour;

	if (cells[p].getType() == colour) {
		cells[p].setHeight(cells[p].getHeight() + 1);
	}
	else {
		cells[p].setHeight(1);
		cells[p].setType(colour);
	}
}

void Canvas::OnMouseRightDown(wxMouseEvent& evt)
{
	wxPosition s = GetVisibleBegin();
	int p = (evt.GetY() / pixelSize + s.GetRow()) * this->GetColumnCount() + (evt.GetX() / pixelSize + s.GetCol());

	((ProjectFrame*)parent)->setStatusBar(cells[p].toString());
	evt.Skip();
}

void Canvas::OnDraw(wxDC& dc)
{
	dc.Clear();
	wxBrush brush = dc.GetBrush();
	wxPen pen = dc.GetPen();

	wxPosition s = GetVisibleBegin();
	wxPosition e = GetVisibleEnd();

	pen.SetStyle(wxPENSTYLE_LONG_DASH);
	pen.SetColour(wxColour(200, 200, 200));
	dc.SetPen(pen);

	//dc.SetBrush(brush);
	//dc.DrawRectangle(20, 20, 200, 200);
	if (pixelSize <= 8) dc.SetPen(*wxTRANSPARENT_PEN);

	for (int y = s.GetRow(); y < e.GetRow(); y++)
		for (int x = s.GetCol(); x < e.GetCol(); x++) {

			int p = y * this->GetColumnCount() + x;

			int colour = sprite[p];

			if (cells[p].getType() == 0 && colour == 0) {
				brush.SetColour(waterdepth[cells[p].getHeight()]);
				brush.SetStyle(wxBRUSHSTYLE_SOLID);
			}
			else {
				brush.SetColour(elem[colour]);
				brush.SetStyle(wxBRUSHSTYLE_SOLID);
			}

			//brush.SetColour(elem[colour]);
			//brush.SetStyle(wxBRUSHSTYLE_SOLID);
			//if (colour < 16) {
			//	brush.SetColour(elem[colour]);
			//	brush.SetStyle(wxBRUSHSTYLE_SOLID);
			//}
			//else {
			//	brush.SetStyle(wxBrushStyle::wxBRUSHSTYLE_CROSSDIAG_HATCH);
			//	brush.SetColour(wxColour(0, 0, 0));
			//}

			dc.SetBrush(brush);
			dc.DrawRectangle(x * pixelSize, y * pixelSize, pixelSize, pixelSize);
		}

}


void Canvas::OnPaint(wxPaintEvent& evt)
{
	wxBufferedPaintDC dc(this);
	this->PrepareDC(dc);
	this->OnDraw(dc);
}
