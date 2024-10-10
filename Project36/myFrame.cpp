#include"myFrame.h"
#include"draw.h"
#include <wx/splitter.h>
MyFrame::MyFrame(const wxString& title) :wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)) {
	wxSplitterWindow* splitter = new wxSplitterWindow(this);
	wxPanel* controlPanel = new wxPanel(splitter);
	Draw* drawPanel = new Draw(splitter);
	splitter->SplitVertically(controlPanel, drawPanel, 100);
	Bind(wxEVT_SIZE, &MyFrame::OnResize, this);
}
void MyFrame::OnResize(wxSizeEvent& event) {
	Layout();
	event.Skip();
}