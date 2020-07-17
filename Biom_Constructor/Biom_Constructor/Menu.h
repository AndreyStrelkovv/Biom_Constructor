#pragma once
#include "wx/wx.h"

class Menu : public wxMDIParentFrame
{
public:
	Menu();
	~Menu();

private:
	wxToolBar* toolBar = nullptr;
	wxMenuBar* menuBar = nullptr;

	void menuNew(wxCommandEvent& evt);
	void menuOpen(wxCommandEvent& evt);
	void menuSave(wxCommandEvent& evt);
	void menuExit(wxCommandEvent& evt);

	void selectColour(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};