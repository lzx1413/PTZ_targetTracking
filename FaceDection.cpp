#include "FaceDetection.h"
#include<QDebug>
static CvMemStorage *storage = 0;
static CvHaarClassifierCascade *cascade = 0;//harr 分类器级联的内部标识形式
static const char *cascade_name = "D:/E/work/QT/TargetTracking_PTZ/cascade/haarcascade_frontalface_alt2.xml";

void CascadeInit()
{
    cascade = (CvHaarClassifierCascade*)cvLoad(cascade_name, 0, 0, 0);
    if (!cascade)
    {
        fprintf(stderr, "ERROR:没有文件\n");

    }
}

CvSeq *FaceDetect(IplImage *img) //检测和画出人脸的函数体
{
    //随机颜色

    storage = cvCreateMemStorage(0);//创建内存块
    double scale = 1.3;
    IplImage* gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);//灰度图像
    IplImage* small_img = cvCreateImage(cvSize(cvRound(img->width / scale), cvRound(img->height / scale)), 8, 1);
    cvCvtColor(img, gray, CV_BGR2GRAY);//把输入的彩色图像转化为灰度图像
    cvResize(gray, small_img, CV_INTER_LINEAR);//缩小灰色图片
    cvEqualizeHist(small_img, small_img);//灰度图象直方图均衡化
    cvClearMemStorage(storage);//释放内存块
    if (cascade)
    {
        double t = (double)cvGetTickCount();//精确测量函数的执行时间
        //从目标图像small_img中检测出人脸
        CvSeq *faces = cvHaarDetectObjects(small_img, cascade, storage, 1.1, 2, 0, cvSize(30, 30));
        t = (double)cvGetTickCount() - t; //计算检测到人脸所需时间
        printf("face detection time = %gms\n", t / ((double)cvGetTickFrequency()*1000.));//打印到屏幕
        //画出检测到的人脸外框(可检测到多个人脸)
        cvReleaseImage(&small_img);
        cvReleaseImage(&gray);
        return faces;
    }
}

CvRect GetFaceRoi(IplImage *frame)
{
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
    float scale = 1.3;
    Point pt1,pt2;
    pt1.x = r.x*scale;
    pt2.x = (r.x + r.width)*scale;
    pt1.y = r.y*scale;
    pt2.y = (r.y + r.height)*scale;
    CvRect face = cvRect(pt1.x,pt1.y,pt2.x-pt1.x,pt2.y-pt1.y);
    return face;
}

