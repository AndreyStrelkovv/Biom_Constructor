#include "Main.h"
#include "string"
using std::string;

wxBEGIN_EVENT_TABLE(Main, wxMDIParentFrame)
	EVT_MENU(10001, Main::menuNew)
	EVT_MENU(10002, Main::menuOpen)
	EVT_MENU(10003, Main::menuSave)
	EVT_MENU(10004, Main::menuExit)
wxEND_EVENT_TABLE()


Main::Main() : wxMDIParentFrame(nullptr, wxID_ANY, "ANDY", wxPoint(100, 100), wxSize(800, 600))
{
	menuBar = new wxMenuBar();
	this->SetMenuBar(menuBar);

	wxMenu* MenuFile = new wxMenu();
	MenuFile->Append(10001, "New");
	MenuFile->Append(10002, "Open");
	MenuFile->Append(10003, "Save");
	MenuFile->Append(10004, "Exit");

	menuBar->Append(MenuFile, "File");

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
		b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Main::selectColour), nullptr, this);
		toolBar->AddControl(b);
	}

	wxButton* b = new wxButton(toolBar, 10100 + 16, "Alpha", wxDefaultPosition, wxDefaultSize, 0);
	b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Main::selectColour), nullptr, this);
	toolBar->AddControl(b);
	toolBar->Realize();
}

Main::~Main()
{
}

void Main::menuNew(wxCommandEvent& evt)
{
	if (GetActiveChild() == nullptr) {
		ProjectFrame* p = new ProjectFrame(this, "Test");
		p->New(50, 75);
		p->Show();
	}
	evt.Skip();
}

void Main::menuOpen(wxCommandEvent& evt)
{
	if (GetActiveChild() == nullptr) {
		string spriteFolderPath = "C:\\Users\\andre\\Desktop\\GitHub\\Biom_Constructor\\biom_files";
		wxFileDialog dlg(this, "Open BiomFile File", spriteFolderPath, "", ".spr Files (*.spr)|*.spr", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
		if (dlg.ShowModal() == wxID_OK) {
			ProjectFrame* p = new ProjectFrame(this, dlg.GetPath());
			p->Open(dlg.GetPath());
			p->Show();
		}
	}
	evt.Skip();
}

void Main::menuSave(wxCommandEvent& evt)
{
	if (GetActiveChild() != nullptr) {
		string spriteFolderPath = "C:\\Users\\andre\\Desktop\\GitHub\\Biom_Constructor\\biom_files";
		wxFileDialog dlg(this, "Save BioM", spriteFolderPath, "", ".spr Files (*.spr)|*.spr", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (dlg.ShowModal() == wxID_OK) {
			((ProjectFrame*)GetActiveChild())->Save(dlg.GetPath());
		}
	}
	evt.Skip();
}

void Main::menuExit(wxCommandEvent& evt)
{
	Close();
	evt.Skip();
}

void Main::selectColour(wxCommandEvent& evt)
{
	int colour = evt.GetId() - 10100;
	if (GetActiveChild() != nullptr) {
		((ProjectFrame*)GetActiveChild())->SetColour(colour);
	}
}
