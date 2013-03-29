#include "thread.h"
#include <vector>

using namespace std;

void * Thread::Entry()
{
    vector<wxImage> image;

    wxImage image1("1.jpg",wxBITMAP_TYPE_JPEG);
    wxImage image2("2.jpg",wxBITMAP_TYPE_JPEG);
    wxImage image3("3.jpg",wxBITMAP_TYPE_JPEG);
    wxImage image4("4.jpg",wxBITMAP_TYPE_JPEG);
    wxImage image5("5.jpg",wxBITMAP_TYPE_JPEG);

    image.push_back(image1);
    image.push_back(image2);
    image.push_back(image3);
    image.push_back(image4);
    image.push_back(image5);

    int i=0;

    while(1)
    {
        gui->Notify(&image[i]);
        i++; if(i>4) i =0;
        Sleep(200);
    }
    return NULL;
}
