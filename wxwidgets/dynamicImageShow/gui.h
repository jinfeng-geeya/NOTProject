#ifndef gui_h
#define gui_h

#include "common.h"
#include "wx/wx.h"

class GUI : public wxFrame, public NotifyGUI
{
public:
    virtual void Notify(wxImage * frame);

public:
    GUI();

    void OnPaint(wxPaintEvent &event);
    void OnSize(wxSizeEvent &event);
// Property
private:
    int width;
    int height;

private:
    wxBitmap frame;

protected:
    DECLARE_EVENT_TABLE()
};


#endif // gui_h
