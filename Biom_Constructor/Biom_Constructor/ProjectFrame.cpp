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
	for (int i = 0; i < biomf.nWidth; i++) {
		for (int j = 0; j < biomf.nHeight; j++) {
			short colour = sprite[j * biomf.nWidth + i];

			if (colour == 16) {
				biomf.SetColour(i, j, 0);
				biomf.SetGlyph(i, j, L' ');
			}
			else {
				biomf.SetColour(i, j, colour);
				biomf.SetGlyph(i, j, 0x2588);
			}
		}
	}
	return biomf.Save(sFileName.wc_str());
}

bool ProjectFrame::Open(wxString sFileName)
{
	if (!biomf.Load(sFileName.wc_str())) {
		return false;
	}
	else {

		delete[] sprite;
		sprite = new unsigned char[biomf.nWidth * biomf.nHeight]{ 0 };

		for (int i = 0; i < biomf.nWidth; i++) {
			for (int j = 0; j < biomf.nHeight; j++) {
				wchar_t glyph = biomf.GetGlyph(i, j);
				short colour = biomf.GetColour(i, j);

				if (glyph == L' ') {
					sprite[j * biomf.nWidth + i] = 16;
				}
				else {
					sprite[j * biomf.nWidth + i] = colour & 0x000F;
				}
			}
		}
	}
	canvas->SetSpriteData(biomf.nHeight, biomf.nWidth, sprite);
	return true;
}

bool ProjectFrame::New(int r, int c)
{
	delete[] sprite;
	sprite = new unsigned char[r * c]{ 0 };
	canvas->SetSpriteData(r, c, sprite);
	biomf = BiomFile(c, r);
	return false;
}

void ProjectFrame::OnZoomChange(wxCommandEvent& evt)
{
	statusBar->SetStatusText(wxString("Zoom: ") << zoomSlider->GetValue(), 1);
	canvas->SetPixelSize(zoomSlider->GetValue());
	evt.Skip();
}
