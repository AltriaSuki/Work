#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/menu.h>
#endif
#ifndef WX_PRECOMP
#include "wx/app.h"
#include "wx/bitmap.h"
#include "wx/frame.h"
#include "wx/image.h"
#include "wx/menu.h"
#include "wx/msgdlg.h"
#include "wx/log.h"
#include "wx/textctrl.h"
#include "wx/textdlg.h"
#endif

#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "../sample.xpm"
#endif


class SubMenu : public wxFrame

{

public:

    SubMenu(const wxString& title);



    void OnQuit(wxCommandEvent& event);



    wxMenuBar* menubar;

    wxMenu* file;

    wxMenu* imp;

    wxMenuItem* quit;

};
class MyFrame : public wxFrame
{
public:
    //创建菜单和工具栏
    explicit MyFrame(const wxString& title)
        : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 800))
    {
       //菜单
        // 创建一个面板
        auto* panel = new wxPanel(this, wxID_ANY);

        //创建一个菜单条
        wxMenuBar* menubar = new wxMenuBar();

        //创建一个菜单项

        wxMenu* file = new wxMenu;
        

        // 添加“关于”菜单项
        file->Append(wxID_NEW, wxT("&NEW"),
            wxT("Quit this program"));
        file->Append(wxID_OPEN, wxT("&open"),
            wxT("Quit this program"));
        file->Append(wxID_EXIT, wxT("E&xit\tAlt-X"),
            wxT("Quit this program"));
        file->AppendSeparator();

        //菜单项的子菜单
       wxMenu* subm = new wxMenu;
       subm->Append(wxID_ANY, wxT("&app"));

        // 将菜单项添加到菜单条中
       file->AppendSubMenu(subm, _T("I&mport"));

        // ...然后将菜单条放置在主窗口上
       menubar->Append(file, _T("&File"));

        SetMenuBar(menubar);

        // 创建一个状态条来让一切更有趣些。
        CreateStatusBar(2);
        SetStatusText(wxT("Welcome to wxWidgets!"));

        // 创建一个按钮
        auto* button = new wxButton(panel, 20, wxT("Click me!"),
            wxPoint(10, 40), wxSize(100, 30));
        auto* button2 = new wxButton(panel, 30, wxT("dont Click me!"),
            wxPoint(10, 70), wxSize(100, 30));

        //工具栏
        wxImage::AddHandler(new wxPNGHandler);

        wxBitmap exit(_T("copy.png"), wxBITMAP_TYPE_PNG);

        wxToolBar* toolbar = CreateToolBar();

        toolbar->AddTool(wxID_EXIT, _T("Exit application"), exit);

        toolbar->Realize();

        Connect(wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MyFrame::OnQuit));



        Centre();

        // 绑定按钮点击事件
        button->Bind(wxEVT_LEFT_DOWN, &MyFrame::OnButtonClicked,this,10,40);
        button2->Bind(wxEVT_LEFT_DOWN, &MyFrame::OnButtonClicked, this);
    }
    //点击open打开文件
 void OnOpenFileClick(wxCommandEvent& event)
         {
     wxTextCtrl* text1=NULL;
             wxFileDialog dlg(this, wxT("打开C++源程序"), wxT(""), wxT(""),
                                  wxT("C++源程序(*.cpp)|*.cpp"),
                                  wxFD_OPEN | wxFD_FILE_MUST_EXIST);
          if (dlg.ShowModal() == wxID_CANCEL)
                  return;
          text1->LoadFile(dlg.GetPath());
       
           }
 void OnSaveClick(wxCommandEvent& enent)
 {

 }

 //点击new新建窗口
 void OnNewClick(wxCommandEvent& event)
 {
     auto* frame = new MyFrame(wxT("Hello wxWidgets!"));
     frame->Show(true);
 }
private:
    void OnButtonClicked(wxMouseEvent& event)
    {
        wxUnusedVar(event);
        if (event.GetId() == 30) {
            wxMessageBox(wxT("not good"), wxT("Hello"), wxOK | wxICON_INFORMATION);
        }
        else
            wxMessageBox(wxT("good"), wxT("Hello"), wxOK | wxICON_INFORMATION);
    }
    void OnQuit(wxCommandEvent& event)
    {
        Close();
    }


    wxDECLARE_EVENT_TABLE();
};
class Toolbar : public wxFrame

{

 public:
     explicit Toolbar(const wxString& title)

        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(280, 180))

    {

        wxImage::AddHandler(new wxPNGHandler);



        wxBitmap exit(_T("copy.png"), wxBITMAP_TYPE_PNG);



        wxToolBar* toolbar = CreateToolBar();

        toolbar->AddTool(wxID_EXIT, _T("Exit application"), exit);

        toolbar->Realize();



        Connect(wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Toolbar::OnQuit));



        Centre();

    }
    

    void OnQuit(wxCommandEvent& event);

};




void Toolbar::OnQuit(wxCommandEvent& WXUNUSED(event))

{

    Close(true);

}



wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
    EVT_MENU(wxID_OPEN, MyFrame::OnOpenFileClick)
    EVT_MENU(wxID_NEW, MyFrame::OnNewClick)
wxEND_EVENT_TABLE()

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        auto* frame = new MyFrame(wxT("Hello wxWidgets!"));
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp); // NOLINT
