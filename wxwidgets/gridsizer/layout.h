#ifndef layout_h
#define layout_h

#include "wx/wx.h"

class App;
class GUI;

class Media;
class Info;
class Log;
class Extra;

class App : public wxApp
{
public:
    virtual bool OnInit();
};

class GUI : public wxFrame
{
public:
    GUI();
public:
    Log * log;
    Media * media;
    Info * info;
    Extra * extra;
protected:
    DECLARE_EVENT_TABLE()
};

class Media : public wxWindow
{
public:
    Media(wxWindow *parent,const wxSize &size, Log *log);
    void OnLeftDown(wxMouseEvent &event);
    void OnPaint(wxPaintEvent &event);
    void OnSize(wxSizeEvent &event);

private:
    Log *log;
private:
    // 0 - no frame, 1 - new, 2 - main menu show
    int flagNewFrame;
    wxBitmap frame;

private:
    wxSize clientSize;
    wxBitmap bmpCamera;
    wxBitmap bmpMovie;
    wxPoint posCamera;
    wxPoint posMovie;
    void AdjustIconPosition()
    {
        clientSize = GetClientSize();
        posCamera.x = clientSize.GetWidth()/2 - 90;
        posCamera.y = clientSize.GetHeight()/2 - 30;
        posMovie.x = clientSize.GetWidth()/2 + 30;
        posMovie.y = clientSize.GetHeight()/2 - 30;
    }

protected:
    DECLARE_EVENT_TABLE();
};

class Info : public wxPanel
{
public:
    Info(wxWindow *parent,const wxSize &size, Log *log);
private:
    Log *log;
private:
    wxBitmap avatar;
protected:
    DECLARE_EVENT_TABLE();
};

class Log : public wxTextCtrl
{
public:
    Log(wxWindow *parent,const wxSize &size);
    void Note(wxString &str)
    {
        this->AppendText(str);
    }
protected:
    DECLARE_EVENT_TABLE();
};

class Extra : public wxWindow
{
public:
    Extra(wxWindow *parent,const wxSize &size, Log *log);
private:
    Log *log;
protected:
    DECLARE_EVENT_TABLE()
};

#endif // layout_h
