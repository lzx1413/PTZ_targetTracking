#include "FaceDetection.h"
#include<QDebug>
static CvMemStorage *storage = 0;
static CvHaarClassifierCascade *cascade = 0;
static const char *cascade_name = "D:/E/work/QT/TargetTracking_PTZ/cascade/haarcascade_frontalface_alt2.xml";

void CascadeInit()
{
    cascade = (CvHaarClassifierCascade*)cvLoad(cascade_name, 0, 0, 0);
    if (!cascade)
    {
        fprintf(stderr, "ERROR:没有文件\n");

    }
}

CvSeq* FaceDetect(IplImage *img) //检测和画出人脸的函数体
{
    storage = cvCreateMemStorage(0);
    double scale = 1.3;
    IplImage* gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);
    IplImage* small_img = cvCreateImage(cvSize(cvRound(img->width / scale), cvRound(img->height / scale)), 8, 1);
    cvCvtColor(img, gray, CV_BGR2GRAY);
    cvResize(gray, small_img, CV_INTER_LINEAR);
    cvEqualizeHist(small_img, small_img);
    cvClearMemStorage(storage);
    if (cascade)
    {
        CvSeq *faces = cvHaarDetectObjects(small_img, cascade, storage, 1.1, 2, 0, cvSize(30, 30));
        cvReleaseImage(&small_img);
        cvReleaseImage(&gray);
        return faces;
    }
    return NULL;

}

CvRect GetFaceRoi(IplImage *frame,CvRect rect)
{
    cvSetImageROI(frame, rect);
    IplImage* frame_copy = cvCreateImage(cvGetSize(frame),frame->depth,3);
    if (!frame_copy)
    {
        frame_copy = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_8U, frame->nChannels);
    }

    if (frame->origin == IPL_ORIGIN_TL)
    {
        cvCopy(frame, frame_copy, 0);
    }
    else
    {

        cvFlip(frame, frame_copy, 0);//反转图像
    }
    CvSeq* faces = FaceDetect(frame_copy);
    CvRect r = {0};
    if (faces->total)
     {
       r = *(CvRect*)cvGetSeqElem(faces, 0);

     }
    cvReleaseMemStorage(&(faces->storage));
    cvReleaseImage(&frame_copy);
    float scale = 1.3f;
    Point pt1,pt2;
    pt1.x = r.x*scale;
    pt2.x = (r.x + r.width)*scale;
    pt1.y = r.y*scale;
    pt2.y = (r.y + r.height)*scale;
    CvRect face = cvRect(pt1.x,pt1.y,pt2.x-pt1.x,pt2.y-pt1.y);
    cvResetImageROI(frame);
    return face;
}

