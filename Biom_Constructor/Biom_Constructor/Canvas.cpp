#include "Canvas.h"
#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(Canvas, wxHVScrolledWindow)
	EVT_PAINT(Canvas::OnPaint)
	EVT_LEFT_DOWN(Canvas::OnMouseLeftDown)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow* parent) : wxHVScrolledWindow(parent, wxID_ANY)
{
	//SetRowColumnCount(40, 40);
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	
	elem.push_back(wxColour(64, 164, 223));
	elem.push_back(wxColour(161, 64, 43));
	elem.push_back(wxColour(80, 80, 80));
	elem.push_back(wxColour(237, 201, 175));
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
	//delete[] sprite;
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
	sprite[(evt.GetY() / pixelSize + s.GetRow()) * this->GetColumnCount() + (evt.GetX() / pixelSize + s.GetCol())] = colour;
	this->Refresh(false);
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

			int colour = sprite[y * this->GetColumnCount() + x];

			brush.SetColour(elem[colour]);
			brush.SetStyle(wxBRUSHSTYLE_SOLID);
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
