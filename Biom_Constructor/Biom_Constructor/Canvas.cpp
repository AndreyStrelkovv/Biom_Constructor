#include "Canvas.h"

wxBEGIN_EVENT_TABLE(Canvas, wxHVScrolledWindow)
//EVT_PAINT(cCanvas::OnPaint)
//EVT_LEFT_DOWN(cCanvas::OnMouseLeftDown)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow* parent) : wxHVScrolledWindow(parent, wxID_ANY)
{
	SetRowColumnCount(40, 40);
	SetBackgroundStyle(wxBG_STYLE_PAINT);
}

Canvas::~Canvas()
{
}

void Canvas::SetPixelSize(int n)
{
	pixelSize = n;
	wxVarHScrollHelper::RefreshAll();
	wxVarVScrollHelper::RefreshAll();
	Refresh();
}

wxCoord Canvas::OnGetRowHeight(size_t row) const
{
	return wxCoord(pixelSize);
}

wxCoord Canvas::OnGetColumnWidth(size_t col) const
{
	return wxCoord(pixelSize);
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

	dc.SetBrush(brush);
	dc.DrawRectangle(20, 20, 200, 200);
	//if (pixelSize <= 4) dc.SetPen(*wxTRANSPARENT_PEN);

	//for (int y = s.GetRow(); y < e.GetRow(); y++)
	//	for (int x = s.GetCol(); x < e.GetCol(); x++) {

	//		int colour = m_pSprite[y * this->GetColumnCount() + x];

	//		if (colour < 16) {
	//			brush.SetColour(palette[colour]);
	//			brush.SetStyle(wxBRUSHSTYLE_SOLID);
	//		}
	//		else {
	//			brush.SetStyle(wxBrushStyle::wxBRUSHSTYLE_CROSSDIAG_HATCH);
	//			brush.SetColour(wxColour(0, 0, 0));
	//		}

	//		dc.SetBrush(brush);
	//		dc.DrawRectangle(x * pixelSize, y * pixelSize, pixelSize, pixelSize);
	//	}

}


void Canvas::OnPaint(wxPaintEvent& evt)
{
	wxBufferedPaintDC dc(this);
	this->PrepareDC(dc);
	this->OnDraw(dc);
}
