#include "wx/wx.h"
#include "layout.h"
#include "thread.h"

IMPLEMENT_APP(App);

bool App::OnInit()
{
    // TMP
    wxString str;

    // Init
    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);

    // Allocate
    GUI * gui = new GUI();
    gui->Show();
    SetTopWindow(gui);

    // create a working thread
    WorkThread * thread = new WorkThread(gui);
    if(thread->Create() != wxTHREAD_NO_ERROR)
    {
        str.Printf("Thread Create Error.\n");
        gui->log->Note(str);
        return false;
    }
    if(thread->Run() != wxTHREAD_NO_ERROR)
    {
        str.Printf("Thread Run Error.\n");
        gui->log->Note(str);
        return false;
    }

    return true;
}

//==============================================================================

BEGIN_EVENT_TABLE(GUI, wxFrame)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(Media, wxWindow)
    EVT_LEFT_DOWN(Media::OnLeftDown)
    EVT_PAINT(Media::OnPaint)
    EVT_SIZE(Media::OnSize)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(Info, wxPanel)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(Log, wxTextCtrl)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(Extra, wxWindow)
END_EVENT_TABLE()

GUI::GUI()
:wxFrame(NULL,-1,"grid box layout",wxPoint(-1,-1),wxSize(700,470))
{
    // Settings
    SetBackgroundColour(wxColor(0xcd,0x7f,0x32));

    // Allocate
    log = new Log(this,wxSize(500,100));
    media = new Media(this,wxSize(500,300),log);
    info = new Info(this,wxSize(180,300),log);
    extra = new Extra(this,wxSize(180,100),log);

    // Layout
    wxFlexGridSizer * s1 = new wxFlexGridSizer(2,2,2,2);
    s1->Add(media,1,wxEXPAND|wxALL,2);
    s1->Add(info,1,wxEXPAND|wxALL,2);
    s1->Add(log,1,wxEXPAND|wxALL,2);
    s1->Add(extra,0,wxALL,2);
    s1->AddGrowableCol(0,1);
    s1->AddGrowableRow(0,1);
    SetSizer(s1);
}


Media::Media(wxWindow *parent,const wxSize &size, Log *log)
:wxWindow(parent,wxID_ANY,wxPoint(-1,-1),size)
{
    // Init
    this->log = log;

    this->flagNewFrame = 2;

    wxImage image;
    image.LoadFile("camera.png", wxBITMAP_TYPE_PNG);
    bmpCamera = wxBitmap(image.Scale(60,60));
    image.LoadFile("movie.png", wxBITMAP_TYPE_PNG);
    bmpMovie = wxBitmap(image.Scale(60,60));

    AdjustIconPosition();

    // Settings
    SetBackgroundColour(wxColor(0xe9,0xc2,0xa6));

    // Note
    wxString str;
    str.Printf("Media has been constructed.\n");
    log->Note(str);
}

void Media::OnLeftDown(wxMouseEvent &event)
{
    int x = event.GetX(), y = event.GetY();
    wxString str;

    if((abs(x-posCamera.x-30)<20) && (abs(y-posCamera.y-30)<20))
    {
        str.Printf("Open Camera.\n");
        log->Note(str);
    }
    else if((abs(x-posMovie.x-30)<20) && (abs(y-posMovie.y-30)<20))
    {
        str.Printf("Open Movie file.\n");
        log->Note(str);
    }

    Refresh(true);  // Important
}

void Media::OnPaint(wxPaintEvent &event)
{
    wxPaintDC dc(this);

    switch(flagNewFrame)
    {
    case 0:
        dc.DrawBitmap(bmpMovie, wxPoint(-1,-1));
        flagNewFrame = 1;
        break;
    case 1:
        dc.DrawBitmap(bmpCamera, wxPoint(-1,-1));
        flagNewFrame = 2;
        break;
    case 2:
        dc.DrawBitmap(bmpCamera,posCamera);
        dc.DrawBitmap(bmpMovie,posMovie);
        flagNewFrame = 0;
    default:
        break;
    }
}

void Media::OnSize(wxSizeEvent &event)
{
    AdjustIconPosition();
    Refresh(true);
}

Info::Info(wxWindow *parent,const wxSize &size, Log *log)
:wxPanel(parent,-1,wxPoint(-1,-1),size)
{
    // Init
    this->log = log;

    wxImage image("avatar.jpg", wxBITMAP_TYPE_JPEG);
    avatar = wxBitmap(image.Scale(150, 150));

    // Allocate
    wxStaticBitmap *winAvatar = new wxStaticBitmap(this,-1,avatar);
    wxStaticBox *winInfo = new wxStaticBox(this, -1, "What I know", wxPoint(15,170), wxSize(150,100));
    //wxStaticBox *winInfo = new wxStaticBox(this, -1, "What I know");
    wxStaticText *winName = new wxStaticText(this,-1,"She is a beautyful lady !");
    wxStaticText *winSex = new wxStaticText(this,-1,"What she think about ?");

    // Layout
    wxStaticBoxSizer *infoSizer = new wxStaticBoxSizer(winInfo, wxVERTICAL);
    infoSizer->Add(winName,0,wxALIGN_CENTER|wxALL,2);
    infoSizer->AddSpacer(5);
    infoSizer->Add(winSex,0,wxALIGN_CENTER|wxALL,2);

    wxBoxSizer * topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(winAvatar,0,wxALIGN_CENTER|wxALL,5);
    topSizer->Add(infoSizer,1,wxEXPAND|wxALL,5);

     // Settings
    SetBackgroundColour(wxColor(204,232,207));
    SetSizer(topSizer);

    // Note
    wxString str;
    str.Printf("Info has been constructed.\n");
    log->Note(str);
}

Log::Log(wxWindow *parent,const wxSize &size)
:wxTextCtrl(parent,-1,"",wxPoint(-1,-1),size,wxTE_MULTILINE)
{
    // settings
    SetBackgroundColour(wxColor(0xe9,0x96,0x7a));
    // Note
    wxString str;
    str.Printf("Log has been constructed.\n");
    this->Note(str);
}

Extra::Extra(wxWindow *parent,const wxSize &size, Log *log)
:wxWindow(parent,-1,wxPoint(-1,-1),size)
{
    this->log = log;

    SetBackgroundColour(wxColor(0xa6,0x80,0x64));

    // Note
    wxString str;
    str.Printf("Extra has been constructed.\n");
    log->Note(str);
}
