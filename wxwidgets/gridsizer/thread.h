#ifndef thread_h
#define thread_h

#include "wx/wx.h"
#include "wx/thread.h"
#include "layout.h"

class WorkThread : public wxThread
{
public:
    WorkThread(GUI *gui);
    virtual void * Entry();
private:
    Log * log;
    Media * media;
    Info * info;
    Extra * extra;
};

#endif // thread_h
