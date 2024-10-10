#pragma once
#include<wx/wx.h>
class MyFrame :public wxFrame {
public:
	MyFrame(const wxString& title);
	void OnResize(wxSizeEvent& event);
};