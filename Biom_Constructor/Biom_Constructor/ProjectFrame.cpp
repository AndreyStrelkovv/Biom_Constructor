#include "ProjectFrame.h"

wxBEGIN_EVENT_TABLE(ProjectFrame, wxMDIChildFrame)
	EVT_SLIDER(20001, ProjectFrame::OnZoomChange)
wxEND_EVENT_TABLE()

ProjectFrame::ProjectFrame(wxMDIParentFrame* parent, wxString name) : wxMDIChildFrame(parent, wxID_ANY, name)
{
	canvas = new Canvas(this);
	statusBar = this->CreateStatusBar(2, wxSTB_DEFAULT_STYLE, wxID_ANY);
	zoomSlider = new wxSlider(statusBar, 20001, 8, 1, 32);
}

ProjectFrame::~ProjectFrame()
{
}

void ProjectFrame::SetColour(int c)
{
	canvas->SetColour(c);
}

bool ProjectFrame::Save(wxString sFileName)
{
	return false;
}

bool ProjectFrame::Open(wxString sFileName)
{
	return false;
}

bool ProjectFrame::New(int r, int c)
{
	delete[] m_pSprite;
	m_pSprite = new unsigned char[r * c]{ 0 };
	canvas->SetSpriteData(r, c, m_pSprite);
	//sprBase = olcSprite(c, r);
	return false;
}

void ProjectFrame::OnZoomChange(wxCommandEvent& evt)
{
	statusBar->SetStatusText(wxString("Zoom: ") << zoomSlider->GetValue(), 1);
	canvas->SetPixelSize(zoomSlider->GetValue());
	evt.Skip();
}
