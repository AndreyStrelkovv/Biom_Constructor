#include "Menu.h"

wxBEGIN_EVENT_TABLE(Menu, wxMDIParentFrame)
	EVT_MENU(10001, Menu::menuNew)
	EVT_MENU(10002, Menu::menuOpen)
	EVT_MENU(10003, Menu::menuSave)
	EVT_MENU(10004, Menu::menuExit)
wxEND_EVENT_TABLE()


Menu::Menu() : wxMDIParentFrame(nullptr, wxID_ANY, "ANDY", wxPoint(100, 100), wxSize(800, 600))
{
	menuBar = new wxMenuBar();
	this->SetMenuBar(menuBar);

	wxMenu* menuFile = new wxMenu();
	menuFile->Append(10001, "New");
	menuFile->Append(10002, "Open");
	menuFile->Append(10003, "Save");
	menuFile->Append(10004, "Exit");

	menuBar->Append(menuFile, "File");

	toolBar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);

	wxColour palette[16];
	palette[0] = wxColour(0, 0, 0);
	palette[1] = wxColour(0, 0, 128);
	palette[2] = wxColour(0, 128, 0);
	palette[3] = wxColour(0, 128, 128);
	palette[4] = wxColour(128, 0, 0);
	palette[5] = wxColour(128, 0, 128);
	palette[6] = wxColour(128, 128, 0);
	palette[7] = wxColour(192, 192, 192);
	palette[8] = wxColour(128, 128, 128);
	palette[9] = wxColour(0, 0, 255);
	palette[10] = wxColour(0, 255, 0);
	palette[11] = wxColour(0, 255, 255);
	palette[12] = wxColour(255, 0, 0);
	palette[13] = wxColour(255, 0, 255);
	palette[14] = wxColour(255, 255, 0);
	palette[15] = wxColour(255, 255, 255);

	for (int i = 0; i < 16; i++) {
		wxButton* b = new wxButton(toolBar, 10100 + i, "", wxDefaultPosition, wxSize(40, 24), 0);
		b->SetBackgroundColour(palette[i]);
		b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Menu::selectColour), nullptr, this);
		toolBar->AddControl(b);
	}

	wxButton* b = new wxButton(toolBar, 10100 + 16, "Alpha", wxDefaultPosition, wxDefaultSize, 0);
	b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Menu::selectColour), nullptr, this);
	toolBar->AddControl(b);
	toolBar->Realize();
}

Menu::~Menu()
{
}

void Menu::menuNew(wxCommandEvent& evt)
{
}

void Menu::menuOpen(wxCommandEvent& evt)
{
}

void Menu::menuSave(wxCommandEvent& evt)
{
}

void Menu::menuExit(wxCommandEvent& evt)
{
}

void Menu::selectColour(wxCommandEvent& evt)
{
}
