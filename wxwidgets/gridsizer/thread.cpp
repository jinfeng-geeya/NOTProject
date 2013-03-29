#include "thread.h"
#include "wx/wx.h"
//#include <cv.h>

WorkThread::WorkThread(GUI *gui)
{
    //TMP
    wxString str;

    //Init
    log = gui->log;
    media = gui->media;
    info = gui->info;
    extra = gui->extra;

    // Note
    str.Printf("Work Thread Started!\n");
    log->Note(str);
}

void * WorkThread::Entry()
{
    wxString str("WorkThread wakes up.\n");

    while(1)
    {
        Sleep(1000);
        log->Note(str);
    }
    return NULL;
}

/*
void * WorkThread::Entry()
{
    CvCapture * capture = cvCaptureFromAVI("test.avi");
    cvQueryFrame(capture);

    int frameH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    int frameW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    int fps       = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
    int numFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);

    wxString str;
    str.Printf("AVI file(test.avi)\nSize: %d x %d\nFPS: %d\nFrameNum: %d\n",
               frameH,frameW,fps,numFrames);
    log->Note(str);

    IplImage * ipl = 0;
    wxBitmap * bmp = 0;

    int i = 0;

    while(1)
    {
        ipl = cvQueryFrame(capture);
        bmp = Ipl2Bitmap(ipl);
        media->frame = bmp;
        media->flagNewFrame = 1;
        media->Refresh(true);

        Sleep(20ms);

        if(numFrames == i++) break;
    }

    return NULL;
}
*/
