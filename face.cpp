#include "FaceDetection.h"
static CvScalar colors[] =
{
    { { 0, 0, 255 } },
    { { 0, 128, 255 } },
    { { 0, 255, 255 } },
    { { 0, 255, 0 } },
    { { 255, 128, 0 } },
    { { 255, 255, 0 } },
    { { 255, 0, 0 } },
    { { 255, 0, 255 } }
};

int main()
{
    CvCapture *capture = 0;
    IplImage *frame;
    capture = cvCaptureFromCAM(0);//获取摄像头
    cvNamedWindow("人脸识别", 1);//创建格式化窗口
    if (capture)
    {
        //循环从摄像头读出图片进行检测
        while (1)
        {

            if (!cvGrabFrame(capture))
            {
                break;
            }
            frame = cvRetrieveFrame(capture); //获得由cvGrabFrame函数抓取的图片
            if (!frame)
            {
                break;
            }
            CvRect faces = GetFaceRoi(frame); // 检测并且标识人脸
            if (cvWaitKey(10) >= 0)
                break;
            int i = 0;
            float scale = 1.3;

            if (faces.height)
            {
                CvPoint pt1, pt2;
                //找到画矩形的两个点
                pt1.x = faces.x*scale;
                pt2.x = (faces.x + faces.width)*scale;
                pt1.y = faces.y*scale;
                pt2.y = (faces.y + faces.height)*scale;
                //画出矩形
                cvRectangle(frame, pt1, pt2, colors[i % 8], 3, 8, 0);
            }
            //}

        cvShowImage("人脸识别", frame);
        }
        //释放指针
        cvReleaseImage(&frame);
        cvReleaseCapture(&capture);
    }

    cvDestroyWindow("人脸识别");
    return 0;
}


