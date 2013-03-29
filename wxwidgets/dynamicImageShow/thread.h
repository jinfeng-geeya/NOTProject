#include "wx/thread.h"
#include "gui.h"

class Thread : public wxThread
{
 public:
    Thread(GUI * gui){this->gui = gui;};
    virtual void * Entry();
 private:
    GUI * gui;
};
