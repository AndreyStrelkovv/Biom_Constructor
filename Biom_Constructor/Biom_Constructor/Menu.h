#pragma once
#include "wx/wx.h"
#include "wx/vscroll.h"
#include "Canvas.h"

class Menu : public wxMDIParentFrame
{
public:
	Menu();
	~Menu();

private:
	Canvas* canvas = nullptr;
	wxStatusBar* statusBar = nullptr;
	wxSlider* zoomSlider = nullptr;

private:
	wxToolBar* toolBar = nullptr;
	wxMenuBar* menuBar = nullptr;

	void OnZoomChange(wxCommandEvent& evt);

	void menuNew(wxCommandEvent& evt);
	void menuOpen(wxCommandEvent& evt);
	void menuSave(wxCommandEvent& evt);
	void menuExit(wxCommandEvent& evt);

	void selectColour(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};