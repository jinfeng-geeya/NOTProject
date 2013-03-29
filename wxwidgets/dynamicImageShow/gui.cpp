#include "gui.h"

BEGIN_EVENT_TABLE(GUI,wxFrame)
    EVT_PAINT(GUI::OnPaint)
    EVT_SIZE(GUI::OnSize)
END_EVENT_TABLE()

GUI::GUI()
: wxFrame(NULL,-1,"",wxPoint(-1,-1),wxSize(800,600))
{
    width = GetClientSize().GetWidth();
    height = GetClientSize().GetHeight();

    frame = wxBitmap(800,600);  // All Members Must be Inited!

    SetBackgroundColour(wxColor(0xe9,0xc2,0xa6));
}

void GUI::Notify(wxImage * frame)
{
    this->frame = wxBitmap(frame->Scale(width,height));
    Refresh(true);
}

void GUI::OnPaint(wxPaintEvent &event)
{
    wxPaintDC dc(this);
    dc.DrawBitmap(frame,wxPoint(-1,-1));
}

void GUI::OnSize(wxSizeEvent &event)
{
    width = GetClientSize().GetWidth();
    height = GetClientSize().GetHeight();
}
