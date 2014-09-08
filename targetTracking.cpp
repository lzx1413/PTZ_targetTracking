#include "targetTracking.h"
Rect selection;
bool selectObject = false;
Point origin;
Mat image;
int trackObject = 0 ;
void targetTracking::test()
{
    for(int i = 0;i<1000;i++)
    {
    ptzComm->Left();
    ptzComm->comm->msleep(50);
    ptzComm->Stop();
    ptzComm->comm->msleep(50);
    ptzComm->Right();
    ptzComm->comm->msleep(50);
    ptzComm->Stop();
    ptzComm->comm->msleep(50);
    }

}
static void onMouse(int event, int x, int y, int, void*)
{
    if (selectObject)
    {
        selection.x = MIN(x, origin.x);
        selection.y = MIN(y, origin.y);
        selection.width = std::abs(x - origin.x);
        selection.height = std::abs(y - origin.y);

        selection &= Rect(0, 0, image.cols, image.rows);
       // frameNum = -1;
      //  minWidth = selection.width;
        //minHeight = selection.height;
    }

    switch (event)
    {
    case CV_EVENT_LBUTTONDOWN:
        origin = Point(x, y);
        selection = Rect(x, y, 0, 0);
        selectObject = true;
        break;
    case CV_EVENT_LBUTTONUP:
        selectObject = false;
        if (selection.width > 0 && selection.height > 0)
            trackObject = -1;
        break;
    }
}

targetTracking::targetTracking()
{
    backprojMode = false;
    showHist = true;
    vmin = 10 ;
    vmax = 256;
    smin = 30;
    ptzComm = new PTZComm;
    oldPoint = Point(320,320);

}
targetTracking::~targetTracking()
{
    delete ptzComm;
}



void targetTracking::drawCross( Point center, Scalar color,int d )
{
  line(  image, Point( center.x - d, center.y - d ),
    Point( center.x + d, center.y + d ), color, 2, CV_AA, 0);
  line(  image, Point( center.x + d, center.y - d ),
    Point( center.x - d, center.y + d ), color, 2, CV_AA, 0 );
}

int targetTracking:: iAbsolute(int a, int b)
{
    int c = 0;
    if (a > b)
    {
        c = a - b;
    }
    else
    {
        c = b - a;
    }
    return	c;
}

void targetTracking::ptzControl(Point oldPt, Point newPt)
{
    if(((newPt.x-oldPt.x)<5)&((newPt.y-oldPt.y)<5))
        ptzComm->Stop();


}
int targetTracking::tracking()
{
    VideoCapture cap;
    Rect trackWindow;
    int hsize = 80;//越大越准确，同时计算量也越大
    float hranges[] = { 0, 180 };
    const float* phranges = hranges;

  //  CommandLineParser parser(argc, argv, keys);
    /*************Particle************************************/
    Mat_<float> measurement(2,1);
    measurement.setTo(cv::Scalar(0));
    int dim = 2;
    int nParticles = 200;
    float xRange = 640.0;
    float yRange = 640.0;

    float minRange[] = { 0, 0 };
    float maxRange[] = { xRange, yRange };
    CvMat LB, UB;
    cvInitMatHeader(&LB, 2, 1, CV_32FC1, minRange);
    cvInitMatHeader(&UB, 2, 1, CV_32FC1, maxRange);

    CvConDensation* condens = cvCreateConDensation(dim, dim, nParticles);

    cvConDensInitSampleSet(condens, &LB, &UB);
    condens->DynamMatr[0] = 1.0;
    condens->DynamMatr[1] = 0.0;
    condens->DynamMatr[2] = 0.0;
    condens->DynamMatr[3] = 1.0;
    cap.open(0);
    if (!cap.isOpened())
    {
        //help();
        cout << "***Could not initialize capturing...***\n";
        cout << "Current parameter's value: \n";
        //parser.printParams();
        return -1;
    }

    namedWindow("Histogram", 0);
    namedWindow("TargetTracking", 0);
    setMouseCallback("TargetTracking", onMouse, 0);
  //  createTrackbar("Vmin", "CamShift Demo", &vmin, 256, 0);
 //   createTrackbar("Vmax", "CamShift Demo", &vmax, 256, 0);
  //  createTrackbar("Smin", "CamShift Demo", &smin, 256, 0);

    Mat frame, hsv, hue, mask, hist, histimg = Mat::zeros(640, 640, CV_8UC3), backproj;
    bool paused = false;
    int frameNum = 0;
    for (;;)
    {

        if (!paused)
        {
            cap >> frame;
            if (frame.empty())
                break;
        }
        //if (frameNUm == 50)
        //	waitKey(0)
        //frame.copyTo(image);
        GaussianBlur(frame,image,Size(1,1),0,0);


        if (!paused)
        {
            cvtColor(image, hsv, COLOR_BGR2HSV);//转换到hsv空间

            if (trackObject)//已经选择好跟踪对象
            {
                frameNum++;
                int _vmin = vmin, _vmax = vmax;

                inRange(hsv, Scalar(0, smin, MIN(_vmin, _vmax)),
                    Scalar(180, 256, MAX(_vmin, _vmax)), mask);
                imshow("mask", mask);
                int ch[] = { 0, 0 };
                hue.create(hsv.size(), hsv.depth());
                mixChannels(&hsv, 1, &hue, 1, ch, 1);
                //提取出h 分量
                if (trackObject < 0)//计算选择目标的内的特征
                {
                    Mat roi(hue, selection), maskroi(mask, selection);
                    calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);//计算直方图
                    normalize(hist, hist, 0, 255, CV_MINMAX);//直方图归一化

                    trackWindow = selection;
                    trackObject = 1;

                    histimg = Scalar::all(0);
                    int binW = histimg.cols / hsize;
                    Mat buf(1, hsize, CV_8UC3);
                    for (int i = 0; i < hsize; i++)
                        buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180. / hsize), 255, 255);
                    cvtColor(buf, buf, CV_HSV2BGR);//画出直方图

                    for (int i = 0; i < hsize; i++)
                    {
                        int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows / 255);
                        rectangle(histimg, Point(i*binW, histimg.rows),
                            Point((i + 1)*binW, histimg.rows - val),
                            Scalar(buf.at<Vec3b>(i)), -1, 8);
                    }
                }

                calcBackProject(&hue, 1, 0, hist, backproj, &phranges);//计算反向投影图
                backproj &= mask;
                RotatedRect trackBox = CamShift(backproj, trackWindow,
                    TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1));//最后一个参数是迭代停止的标准
                cout<<trackBox.center.x<<" "<<trackBox.center.y<<endl;
                cout<<trackWindow.x<<" "<<trackWindow.y<<endl;
                //if(frameNum = -1 )
                  //  oldPoint = trackBox.center;
               // frameNum = frameNum + 2;
                if(frameNum ==40)
                {
                    frameNum = 0;
                    ptzComm->PTZcontrol(oldPoint,trackBox.center);
                }
                //oldPoint = trackBox.center;
                /**********Particle****************************************************/
                measurement(0)=trackBox.center.x;
                measurement(1)=trackBox.center.y;
                for (int i = 0; i < condens->SamplesNum; i++)
                {

                   float diffX = (measurement(0) - condens->flSamples[i][0])/xRange;
                   float diffY = (measurement(1) - condens->flSamples[i][1])/yRange;
                   condens->flConfidence[i] = 1.0 / (sqrt(diffX * diffX + diffY * diffY));
                   Point partPt(condens->flSamples[i][0], condens->flSamples[i][1]);
                   drawCross(partPt , Scalar(255,0,255), 2);
                }
                cvConDensUpdateByTime(condens);
                Point statePt(condens->State[0], condens->State[1]);
                circle( image,statePt,5,CV_RGB(0,0,255),3);


                if (trackWindow.area() <= 1)
                {
//                    int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5) / 6;
//                    trackWindow = Rect(trackWindow.x - r, trackWindow.y - r,
//                        trackWindow.x + r, trackWindow.y + r) &
//                        Rect(0, 0, cols, rows);//赋值给下一次查找的区域
                     trackWindow = Rect(statePt.x,statePt.y,100,100)&Rect(0,0,640,640);
                }
//                int iBetween = 0;
//                        //确保预测点 与 实际点之间 连线距离 在 本次 trackBox 的size 之内
//                 iBetween = sqrt(powf((statePt.x - trackBox.center.x),2)
//                            +
//                            powf((statePt.y - trackBox.center.y),2) );

//                        Point prePoint;//预测的点 相对于 实际点 的对称点



//                        if ( iBetween > 5)
//                        {
//                            //当实际点 在 预测点 右边
//                            if (trackBox.center.x > statePt.x)
//                            {
//                                //且，实际点在 预测点 下面
//                                if (trackBox.center.y > statePt.y)
//                                {
//                                    prePoint.x = trackBox.center.x + iAbsolute(trackBox.center.x,statePt.x);
//                                    prePoint.y = trackBox.center.y + iAbsolute(trackBox.center.y,statePt.y);
//                                }
//                                //且，实际点在 预测点 上面
//                                else
//                                {
//                                    prePoint.x = trackBox.center.x + iAbsolute(trackBox.center.x,statePt.x);
//                                    prePoint.y = trackBox.center.y - iAbsolute(trackBox.center.y,statePt.y);
//                                }
//                                //宽高
//                                if (trackWindow.width != 0)
//                                {
//                                    trackWindow.width += iBetween + iAbsolute(trackBox.center.x,statePt.x);
//                                }

//                                if (trackWindow.height != 0)
//                                {
//                                    trackWindow.height += iBetween + iAbsolute(trackBox.center.x,statePt.x);
//                                }
//                            }
//                            //当实际点 在 预测点 左边
//                            else
//                            {
//                                //且，实际点在 预测点 下面
//                                if (trackBox.center.y > statePt.y)
//                                {
//                                    prePoint.x = trackBox.center.x - iAbsolute(trackBox.center.x,statePt.x);
//                                    prePoint.y = trackBox.center.y + iAbsolute(trackBox.center.y,statePt.y);
//                                }
//                                //且，实际点在 预测点 上面
//                                else
//                                {
//                                    prePoint.x = trackBox.center.x - iAbsolute(trackBox.center.x,statePt.x);
//                                    prePoint.y = trackBox.center.y - iAbsolute(trackBox.center.y,statePt.y);
//                                }
//                                //宽高
//                                if (trackWindow.width != 0)
//                                {
//                                    trackWindow.width += iBetween + iAbsolute(trackBox.center.x,statePt.x);
//                                }

//                                if (trackWindow.height != 0)
//                                {
//                                    trackWindow.height += iBetween +iAbsolute(trackBox.center.x,statePt.x);
//                                }
//                            }

//                            trackWindow.x = prePoint.x - iBetween;
//                            trackWindow.y = prePoint.y - iBetween;
//                        }
//                        else
//                        {
//                            trackWindow.x -= iBetween;
//                            trackWindow.y -= iBetween;
//                            //宽高
//                            if (trackWindow.width != 0)
//                            {
//                                trackWindow.width += iBetween;
//                            }

//                            if (trackWindow.height != 0)
//                            {
//                                trackWindow.height += iBetween;
//                            }
//                        }

//                        //跟踪的矩形框不能小于初始化检测到的大小，当这个情况的时候，X 和 Y可以适当的在缩小
//                        if (trackWindow.width < minWidth)
//                        {
//                            trackWindow.width = minWidth;
//                            trackWindow.x -= iBetween;
//                        }
//                        if (trackWindow.height < minHeight)
//                        {
//                            trackWindow.height = minHeight;
//                            trackWindow.y -= iBetween;
//                        }

//                        //确保调整后的矩形大小在640 * 480之内
//                        if (trackWindow.x <= 0)
//                        {
//                            trackWindow.x = 0;
//                        }
//                        if (trackWindow.y <= 0)
//                        {
//                            trackWindow.y = 0;
//                        }
//                        if (trackWindow.x >= 600)
//                        {
//                            trackWindow.x = 600;
//                        }
//                        if (trackWindow.y >= 440)
//                        {
//                            trackWindow.y = 440;
//                        }

//                        if (trackWindow.width + trackWindow.x >= 640)
//                        {
//                            trackWindow.width = 640 - trackWindow.x;
//                        }
//                        if (trackWindow.height + trackWindow.y >= 480)
//                        {
//                            trackWindow.height = 480 - trackWindow.y;
//                        }
                if (backprojMode)
                    cvtColor(backproj, image, COLOR_GRAY2BGR);
                ellipse(image, trackBox, Scalar(0, 0, 255), 3, CV_AA);//画出椭圆目标区域

        }
        else if (trackObject < 0)
            paused = false;

        if (selectObject && selection.width > 0 && selection.height > 0)
        {
            Mat roi(image, selection);
            bitwise_not(roi, roi);//黑白反转
        }



        imshow("TargetTracking", image);
        imshow("Histogram", histimg);

        char c = (char)waitKey(10);
        if (c == 27)
            break;
        switch (c)
        {
        case 'b':
            backprojMode = !backprojMode;
            break;
        case 'c':
            trackObject = 0;
            histimg = Scalar::all(0);
            break;
        case 'h':
            showHist = !showHist;
            if (!showHist)
                destroyWindow("Histogram");
            else
                namedWindow("Histogram", 1);
            break;
        case 'p':
            paused = !paused;
            break;
        default:
            ;
        }
    }


}
return 0;
}
