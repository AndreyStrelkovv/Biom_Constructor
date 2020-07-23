#pragma once
#include "wx/wx.h"
#include "ProjectFrame.h"

#include "vector"
using std::vector;

class Main : public wxMDIParentFrame
{
public:
	Main();
	~Main();

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