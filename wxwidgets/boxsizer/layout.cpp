#include "wx/wx.h"
#include "wx/mediactrl.h"

class App;
class GUI;
class Media;
class Information;
class Log;

class App : public wxApp
{
public:
    virtual bool OnInit();
};

class GUI : public wxFrame
{
public:
    GUI();

    void OnRightDown(wxMouseEvent &event)
    {
        wxFileDialog *fileDlg = new wxFileDialog(this);
        if(wxID_OK == fileDlg->ShowModal())
        {
            wxString fileName = fileDlg->GetFilename();
        }
    }

protected:
    DECLARE_EVENT_TABLE()
};

class Log : public wxPanel
{
public:
    Log(wxWindow *parent, wxWindowID id)
        : wxPanel(parent,id)
    {
        log = new wxTextCtrl(this,-1,"Welcome!\n", wxPoint(-1,-1),
                                          wxSize(-1,-1),wxTE_MULTILINE);
        //======================================================================
        wxBoxSizer * sizeH = new wxBoxSizer(wxHORIZONTAL);
        sizeH->Add(log,1,wxEXPAND|wxALL,1);
        SetSizer(sizeH);
    }

    void Note(wxString & text)
    {
        log->AppendText(text);
    }

private:
    wxTextCtrl * log;

protected:
    DECLARE_EVENT_TABLE()
};

enum
{
    ID_MEDIA = 100,
};

class Media : public wxPanel
{
public:
    Media(wxWindow *parent, wxWindowID id)
        : wxPanel(parent,id)
    {
        mediaCtrl = new wxMediaCtrl(this, ID_MEDIA, wxT(""),
                                                  wxPoint(-1,-1), wxSize(-1,-1),
                                                  0, wxMEDIABACKEND_DIRECTSHOW);
        mediaCtrl->Connect(ID_MEDIA,wxEVT_MEDIA_LOADED,
                           wxMediaEventHandler(Media::OnLoaded), NULL, this);
        //======================================================================
        wxBoxSizer * sizeH = new wxBoxSizer(wxHORIZONTAL);
        sizeH->Add(mediaCtrl,1,wxEXPAND|wxALL,1);
        SetSizer(sizeH);
    }

    void OnLoaded(wxMediaEvent &event)
    {
        mediaCtrl->Play();
    }

    void OnRightDown(wxMouseEvent &event)
    {
        wxFileDialog *fileDlg = new wxFileDialog(this);
        if(wxID_OK == fileDlg->ShowModal())
        {
            wxString fileName = fileDlg->GetFilename();
            mediaCtrl->Load(fileName);
        }
    }

private:
    wxMediaCtrl * mediaCtrl;

protected:
    DECLARE_EVENT_TABLE()
};

enum
{
    ID_AVATAR = 200,
    ID_TEXT,

};

class Information : public wxPanel
{
public:
    Information(wxWindow *parent, wxWindowID id, Log * log)
        : wxPanel(parent,id)
    {
        wxString msg;

        if(false == avatar.LoadFile("test.bmp", wxBITMAP_TYPE_BMP))
        {
            msg.Printf("Cannot load image!");
            log->Note(msg);
        }

        msg.Printf("image size: %d x %d\n", avatar.GetWidth(),
                     avatar.GetHeight());
        log->Note(msg);

        if(avatar.GetWidth()!=128 || avatar.GetHeight()!=128)
        {
            wxImage image = avatar.ConvertToImage();
            avatar = wxBitmap(image.Scale(128,128));
        }

        wxStaticBitmap *winAvatar = new wxStaticBitmap(this,-1,avatar);

        wxStaticText * name = new wxStaticText(this, -1, wxT("James"));
        wxStaticText * sex = new wxStaticText(this, -1, wxT("Male"));
        //======================================================================
        wxBoxSizer * sizeAll = new wxBoxSizer(wxVERTICAL);

        wxStaticBoxSizer * sizeInfo = new wxStaticBoxSizer(new wxStaticBox(this,
                                        -1,wxT("Information:")), wxVERTICAL);
        sizeInfo->Add(name,1,wxEXPAND|wxALIGN_CENTER|wxALL,10);
        sizeInfo->Add(sex,1,wxEXPAND|wxALIGN_CENTER|wxALL,10);

        sizeAll->Add(winAvatar,1,wxALL|wxALIGN_CENTER,15);
        sizeAll->Add(sizeInfo,0,wxALL|wxEXPAND|wxALIGN_CENTER,15);

        SetSizer(sizeAll);
        Centre();
    }
private:
    wxBitmap avatar;
    Log * log;

protected:
    DECLARE_EVENT_TABLE()
};

IMPLEMENT_APP(App);

BEGIN_EVENT_TABLE(GUI, wxFrame)
    EVT_RIGHT_DOWN(GUI::OnRightDown)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(Media, wxPanel)
    EVT_RIGHT_DOWN(Media::OnRightDown)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(Information, wxPanel)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(Log, wxPanel)
END_EVENT_TABLE()

bool App::OnInit()
{
    GUI * gui = new GUI();
    gui->Show();
    SetTopWindow(gui);

    return true;
}

GUI::GUI()
: wxFrame(NULL, -1, "Layout", wxPoint(-1,-1), wxSize(600,400))
{
    SetBackgroundColour(*wxBLACK);

    wxPanel * main = new wxPanel(this, -1);
    main->SetBackgroundColour(wxColor(255,200,0));

    Media * a = new Media(main, -1);
    a->SetBackgroundColour(*wxBLACK);
    Log * b = new Log(main, -1);
    b->SetBackgroundColour(*wxWHITE);
    Information * c = new Information(main, -1, b);
    c->SetBackgroundColour(*wxLIGHT_GREY);

//==============================================================================
    wxBoxSizer * sizeLeft = new wxBoxSizer(wxVERTICAL);
    sizeLeft->Add(a,3,wxEXPAND|wxALL,5);
    sizeLeft->Add(b,1,wxEXPAND|wxALL,5);

    wxBoxSizer * sizeMain = new wxBoxSizer(wxHORIZONTAL);
    sizeMain->Add(sizeLeft,3,wxEXPAND|wxALL,5);
    sizeMain->Add(c,1,wxEXPAND|wxALL,5);

    main->SetSizer(sizeMain);

    wxBoxSizer * sizeAll = new wxBoxSizer(wxVERTICAL);
    sizeAll->Add(main,1,wxEXPAND|wxALL,0);

    wxBoxSizer * sizeFrame = new wxBoxSizer(wxVERTICAL);
    sizeFrame->Add(sizeAll,1,wxEXPAND|wxALL,0);
    SetSizer(sizeFrame);
}
