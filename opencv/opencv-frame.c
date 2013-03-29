////////////////////////////////////////////////////////////////////////
//
// test3.cpp
//
// 该程序实现视频和图片的相互转换.
// Image_to_video()函数将一组图片合成AVI视频文件.
// Video_to_image()函数将AVI视频文件读入，将每一帧存储为jpg文件.
//
////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#define NUM_FRAME 300 //只处理前300帧，根据视频帧数可修改

void Video_to_image(char* filename)
{
printf("------------- video to image ... ----------------\n");
//初始化一个视频文件捕捉器
CvCapture* capture = cvCaptureFromAVI(filename);
//获取视频信息
cvQueryFrame(capture);
int frameH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
int frameW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
int fps       = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
int numFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
printf("\tvideo height : %d\n\tvideo width : %d\n\tfps : %d\n\tframe numbers : %d\n", frameH, frameW, fps, numFrames);
//定义和初始化变量
int i = 0;
IplImage* img = 0;
char image_name[13];

cvNamedWindow( "mainWin", CV_WINDOW_AUTOSIZE );
//读取和显示
while(1)
{
  
   img = cvQueryFrame(capture); //获取一帧图片
   cvShowImage( "mainWin", img ); //将其显示
   char key = cvWaitKey(20);
  
   sprintf(image_name, "%s%d%s", "image", ++i, ".jpg");//保存的图片名
  
   cvSaveImage( image_name, img);   //保存一帧图片

   if(i == NUM_FRAME) break;
}
cvReleaseCapture(&capture);
cvDestroyWindow("mainWin");
}