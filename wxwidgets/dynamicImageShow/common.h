#ifndef common_h
#define common_h

#include "wx/wx.h"

//Derived by GUI
class NotifyGUI
{
public:
    virtual void Notify(wxImage * frame) = 0;
};

/*
// Derived by Work Thread
class FaceTracker()
{
public:
    FaceTracker(){frame = new IplImage;}
    ~FaceTracker(){delete frame;}

    // Be Called by Work thread
    wxImage& TrackNewFrame(IplImage &frame);

private:
     void FaceDectect(IplImage &frame, vector<Rect> &headlist);
     void FaceTrack(IplImage &frame);
     wxImage& Ipl2wxImage(IplImage &frame);

private:
    IplImage *frame;
    vector<Rect> headlist;
};
*/

#endif // common_h
