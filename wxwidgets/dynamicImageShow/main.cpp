#include "app.h"
#include "wx/wx.h"
#include "common.h"
#include "gui.h"
#include "thread.h"

IMPLEMENT_APP(App);

bool App::OnInit()
{
    wxImage::AddHandler(new wxJPEGHandler);
    wxImage::AddHandler(new wxPNGHandler);

    GUI * gui = new GUI;
    gui->Show();
    SetTopWindow(gui);

    Thread * work = new Thread(gui);
    if(wxTHREAD_NO_ERROR != work->Create())
        return false;
    if(wxTHREAD_NO_ERROR != work->Run())
        return false;

    return true;
}
