#include "wx/wx.h"

class App : public wxApp
{
public:
    virtual bool OnInit();
};

class GUI : public wxFrame
{
public:
    GUI();
protected:
    DECLARE_EVENT_TABLE()
};

IMPLEMENT_APP(App);

bool App::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler);

    GUI * gui = new GUI();
    gui->Show();
    SetTopWindow(gui);

    return true;
}

BEGIN_EVENT_TABLE(GUI, wxFrame)
END_EVENT_TABLE()

GUI::GUI()
:wxFrame(NULL,-1,"grid box layout",wxPoint(-1,-1),wxSize(700,470))
{
    wxPanel * board = new wxPanel(this,-1);
    board->SetBackgroundColour(wxColor(0,80,60));

    wxWindow * w1 = new wxWindow(board,-1,wxPoint(-1,-1), wxSize(500,300));
    //w1->SetBackgroundColour(wxColor(255,255,255));
    wxWindow * w2 = new wxWindow(board,-1,wxPoint(-1,-1), wxSize(180,300));
    w2->SetBackgroundColour(wxColor(255,255,255));
    wxWindow * w3 = new wxWindow(board,-1,wxPoint(-1,-1), wxSize(500,100));
    w3->SetBackgroundColour(wxColor(255,255,255));
    wxWindow * w4 = new wxWindow(board,-1,wxPoint(-1,-1), wxSize(180,100));
    w4->SetBackgroundColour(wxColor(0,0,0));

    wxFlexGridSizer * s1 = new wxFlexGridSizer(2,2,2,2);
    board->SetSizer(s1);

    s1->Add(w1,1,wxEXPAND|wxALL,5);
    s1->Add(w2,1,wxEXPAND|wxALL,5);
    s1->Add(w3,1,wxEXPAND|wxALL,5);
    s1->Add(w4,0,wxALL,5);

    s1->AddGrowableCol(0,1);
    s1->AddGrowableRow(0,1);

    wxBoxSizer * s2 = new wxBoxSizer(wxVERTICAL);

    s2->Add(board,1,wxEXPAND|wxALL,1);

    SetSizer(s2);

    //==========================================================================


    wxImage image("camera.png", wxBITMAP_TYPE_PNG);
    wxBitmap bmp = wxBitmap(image.Scale(60,60));

    wxClientDC dc(this);
    dc.DrawText("OOOOOOOOOOOOOOO", wxPoint(100,100));
    dc.DrawBitmap(bmp, wxPoint(220,120));
}
