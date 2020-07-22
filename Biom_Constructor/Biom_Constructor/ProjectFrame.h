#pragma once
#include "wx/wx.h"
#include "Canvas.h"

class ProjectFrame : public wxMDIChildFrame
{
public:
	ProjectFrame(wxMDIParentFrame* parent, wxString name);
	~ProjectFrame();

	void SetColour(int c);
	bool Save(wxString sFileName);
	bool Open(wxString sFileName);
	bool New(int r, int c);

private:
	Canvas* canvas = nullptr;
	wxStatusBar* statusBar = nullptr;
	wxSlider* zoomSlider = nullptr;

	//olcSprite sprBase;
	unsigned char* m_pSprite = nullptr;

	void OnZoomChange(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

