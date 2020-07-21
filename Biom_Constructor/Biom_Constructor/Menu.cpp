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
