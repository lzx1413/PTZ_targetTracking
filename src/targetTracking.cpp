#include "targetTracking.h"
#include  "FaceDetection.h"
#include"ImageController.h"
#include"windows.h"
static Rect g_selection;
static bool g_selectObject = false;
static Point g_origin;
static Mat g_image = Mat::zeros(640, 640, CV_8UC3);
static int g_trackObject = 0 ;
static int num_of_lost = 0;
vector<KeyPoint> keypoints_object;
  SurfFeatureDetector dector;
    SurfDescriptorExtractor extractor;
    FlannBasedMatcher matcher;




void TargetTracking::TestFunction()
{
    qDebug()<<face_name_list_.values();
    qDebug()<<num_of_template;
}
static void onMouse(int event, int x, int y, int, void*)  //用于鼠标选取目标的回调函数

{
    if (g_selectObject)
    {
        g_selection.x = MIN(x, g_origin.x);
        g_selection.y = MIN(y, g_origin.y);
        g_selection.width = std::abs(x - g_origin.x);
        g_selection.height = std::abs(y - g_origin.y);
        g_selection &= Rect(0, 0, g_image.cols, g_image.rows);
    }

    switch (event)
    {
    case CV_EVENT_LBUTTONDOWN:
        g_origin = Point(x, y);
        g_selection = Rect(x, y, 0, 0);
        g_selectObject = true;
        break;
    case CV_EVENT_LBUTTONUP:
        g_selectObject = false;
        if (g_selection.width > 0 && g_selection.height > 0)
            g_trackObject = -1;
        break;
    }
}


//区域的缩放
inline static Rect RectChange(Rect &rec ,float scale)
{
    Rect tem ;
    tem.x  = static_cast<int>(rec.x-rec.width*(scale-1)/2);
    tem.y  = static_cast<int>(rec.y-rec.height*(scale-1)/2);
    tem.width = static_cast<int>(rec.width*scale);
    tem.height = static_cast<int>(rec.height*scale);
   if(tem.x<0)
       tem.x = 0;
   if(tem.y<0)
       tem.y = 0;
   if(tem.x+tem.width>640)
       tem.width = 640-tem.x;
   if(tem.y+tem.height>480)
       tem.height = 480-tem.y;
    return tem;

}

TargetTracking::TargetTracking()
{
    ptz_command_ = new PTZCommand;
    FaceRecognitionInit();
    face_name_list_[1] = "LZXxxxx";
    face_name_list_[2] = "LT";
}

TargetTracking::~TargetTracking()
{
    delete ptz_command_;
}

void TargetTracking::DrawCross( Point center, Scalar color,int d )
{
  line(  g_image, Point( center.x - d, center.y - d ),
    Point( center.x + d, center.y + d ), color, 2, CV_AA, 0);
  line(  g_image, Point( center.x + d, center.y - d ),
    Point( center.x - d, center.y + d ), color, 2, CV_AA, 0 );
}

inline int TargetTracking:: iAbsolute(int a, int b)
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

//设置退出视频循环信号
void TargetTracking::set_exit_flag()
{
    if(exit_flag_ == false)
      exit_flag_ =true;

}

//用于判断跟踪是否失败
bool TargetTracking::target_miss_config()
{
    if( get_point_distace(new_point_,old_point_)> 640||((float)new_target_area_/(float)old_target_area_)>2||((float)new_target_area_/(float)old_target_area_)<0.8)
    {
        return false;
    }
    else
        return true;
}

//判断当前目标是否包含脸
bool TargetTracking::face_config(Mat& frame,Rect rect)
{
       Rect face_rect = RectChange(rect,1.3);
       Rect faces = GetFaceRoi(frame,face_rect);
       if(num_of_lost>10)
       {
           num_of_lost=0;
           return false;

       }
       else if(faces.height == 0)
            num_of_lost++;
       else
       {
           qDebug()<<target_rect_.x<<target_rect_.y<<target_rect_.width<<target_rect_.height;
           qDebug()<<faces.x<<faces.y<<faces.width<<faces.height;
           num_of_lost = 0;
           return true;
        }

}

void TargetTracking::PTZReposition()
{

        ptz_command_->Home();
        waitKey(20);
}

void TargetTracking::UpdateStablePoint()
{
    if(abs(new_point_.x-old_point_.x)<200&&abs(new_point_.y-old_point_.y)<200)
    {
        stable_point_ = new_point_;
    }
}

void TargetTracking::GetPredictPoint()
{
    int weight= 0.5 ;//预测的点所占的比重
    predict_pt_.x = weight*statePt_.x +(1-weight)*trackBox.center.x;
       predict_pt_.y = weight*statePt_.y +(1-weight)*trackBox.center.y;
}


int TargetTracking::tracking()
{

    qDebug()<<num_of_template<<"ge subdir";
    waitKey();
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cout << "***Could not initialize capturing...***\n";
        cout << "Current parameter's value: \n";
        return -1;
    }
    CascadeInit();
    Rect trackWindow;
    int hsize = 80;  //越大越准确，同时计算量也越大
    float hranges[] = { 0, 180 };
    const float* phranges = hranges;
    /*************粒子滤波初始化************************************/
    Mat_<float> measurement(2,1);
    measurement.setTo(cv::Scalar(0));
    int dim = 2;
    int nParticles = 200;
    float x_range = 640.0;
    float y_range = 480.0;

    float min_range[] = { 0, 0 };
    float max_range[] = { x_range, y_range };
    CvMat LB, UB;
    cvInitMatHeader(&LB, 2, 1, CV_32FC1, min_range);
    cvInitMatHeader(&UB, 2, 1, CV_32FC1, max_range);

    CvConDensation* condens = cvCreateConDensation(dim, dim, nParticles);

    cvConDensInitSampleSet(condens, &LB, &UB);
    condens->DynamMatr[0] = 1.0;
    condens->DynamMatr[1] = 0.0;
    condens->DynamMatr[2] = 0.0;
    condens->DynamMatr[3] = 1.0;

   namedWindow("Histogram", 0);
    namedWindow("TargetTracking", 0);
    //namedWindow("segmenter",CV_WINDOW_AUTOSIZE);
   // namedWindow("binary",0);
    setMouseCallback("TargetTracking", onMouse, 0);


    ImageControllerInit("D:/E/work/QT/TargetTracking_PTZ/image");

    Mat frame = Mat::zeros(640, 480, CV_8UC3);
    Mat hsv = Mat::zeros(640, 480, CV_8UC3);
    Mat hue = Mat::zeros(640, 480, CV_8UC3);
    Mat mask = Mat::zeros(640, 480, CV_8UC3);
    Mat hist = Mat::zeros(640, 480, CV_8UC3);
    Mat histimg = Mat::zeros(640, 480, CV_8UC3);
    Mat backproj;
    IplImage *face_frame = 0;
    bool paused = false;
    int frame_num = 0;
    int num_of_facedection = 0;
    flag_of_new_target_ = 0;


    for (;;)
    {

        double t = (double)cvGetTickCount();//精确测量函数的执行时间
        if (!paused)
        {
            cap>>frame;
        }

        if (!paused)
        {
            if(!g_trackObject)
            {
              Mat gray;
              cvtColor(frame,gray,CV_BGR2GRAY);
              Rect faces = GetFaceRoi(gray,Rect(0,0,640,480));
              if(faces.width>0)
            {
                  num_of_facedection++;
                  qDebug()<<"have a face"<<faces.x<<faces.y<<faces.height<<faces.width;
                  if(num_of_facedection>5)
                  {
                        g_trackObject = -1;
                        g_selection = RectChange(faces,1);
                        num_of_facedection=0;
                        rectangle(g_image,faces,Scalar(125,125,0));
                   }
           }
              else
              {
                  num_of_facedection = 0;

              }
            }
            rawframe = frame;
            GaussianBlur(frame,g_image,Size(1,1),0,0);
            cvtColor(g_image, hsv, COLOR_BGR2HSV);//转换到hsv空间

            if (g_trackObject)//已经选择好跟踪对象
           {
                frame_num++;
                int _vmin = vmin_, _vmax = vmax_;

                inRange(hsv, Scalar(0
                                    , smin_, MIN(_vmin, _vmax)),
                    Scalar(180, 256, MAX(_vmin, _vmax)), mask);
                imshow("mask", mask);
                int ch[] = { 0, 0 };
                hue.create(hsv.size(), hsv.depth());
                mixChannels(&hsv, 1, &hue, 1, ch, 1);           
                //提取出h 分量
                if (g_trackObject < 0)//计算选择目标的内的特征
                {
                    Mat roi(hue, g_selection), maskroi(mask, g_selection);
                    calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);//计算直方图
                    normalize(hist, hist, 0, 255, CV_MINMAX);//直方图归一化

                    trackWindow = g_selection;
                    g_trackObject = 1;

                    histimg = Scalar::all(0);
                    int binW = histimg.cols / hsize;
                    Mat buf(1, hsize, CV_8UC3);
                    for (int i = 0; i < hsize; i++)
                        buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180. / hsize), 255, 255);

                    for (int i = 0; i < hsize; i++)
                    {
                        int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows / 255);
                        rectangle(histimg, Point(i*binW, histimg.rows),
                            Point((i + 1)*binW, histimg.rows - val),
                            Scalar(buf.at<Vec3b>(i)), -1, 8);
                    }
                    new_target_area_ = g_selection.area();
                    old_target_area_ = g_selection.area();
                    origin_area_ = g_selection.area();
                    stable_point_ =Point( g_selection.x+g_selection.width/2,g_selection.y+g_selection.height/2);
                     CalculateKeyPoint(rawframe(g_selection),true);
                }

                calcBackProject(&hue, 1, 0, hist, backproj, &phranges);//计算反向投影图
                backproj &= mask;
                trackBox = CamShift(backproj, trackWindow, TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1));//camshift主函数，最后一个参数是迭代停止的标准
                cout<<trackBox.center.x<<" "<<trackBox.center.y<<endl;
                cout<<trackWindow.x<<" "<<trackWindow.y<<endl;
                /**********粒子滤波及其更新**********************/
                measurement(0)=trackBox.center.x;
                measurement(1)=trackBox.center.y;
                for (int i = 0; i < condens->SamplesNum; i++)//设置置信度
                {

                   float diffX = (measurement(0) - condens->flSamples[i][0])/x_range;
                   float diffY = (measurement(1) - condens->flSamples[i][1])/y_range;
                   condens->flConfidence[i] = 1.0 / (sqrt(diffX * diffX + diffY * diffY));
                   Point partPt(condens->flSamples[i][0], condens->flSamples[i][1]);
                   DrawCross(partPt , Scalar(255,0,255), 2);
                }
                cvConDensUpdateByTime(condens);
                statePt_ = Point(condens->State[0], condens->State[1]);


                GetPredictPoint();
                trackBox.center = predict_pt_;
                set_target_rect(trackBox.boundingRect().x,trackBox.boundingRect().y,trackBox.boundingRect().width,trackBox.boundingRect().height);
                if (trackWindow.area() <= 100)
                {
                    int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5) / 6;
                   trackWindow = Rect(trackWindow.x - r, trackWindow.y - r,
                       trackWindow.x + r, trackWindow.y + r) & Rect(0, 0, cols, rows);//赋值给下一次查找的
                }
                 target = target_rect_&Rect(0,0,640,480);
                 circle( g_image,statePt_,5,CV_RGB(0,0,255),3);
                 circle( g_image,trackBox.center,5,CV_RGB(0,255,0),3);
                 circle( g_image,Point(320,240),5,CV_RGB(255,0,0),3);


               GetTargetWithPoints(rawframe(target));
                if (backproj_mode_)
                cvtColor(backproj, g_image, COLOR_GRAY2BGR);
                 new_target_area_ = trackBox.size.area();
               // g_trackObject = target_miss_config();
                old_target_area_ = new_target_area_;
                new_point_ = trackBox.center;
                UpdateStablePoint();
                old_point_ = new_point_;
                ellipse(g_image, trackBox, Scalar(0, 0, 255), 3, CV_AA);//画出椭圆目标区域
                rectangle(g_image,target,Scalar(255,0,0),2,8);

                if(!(frame_num%10))
               {
                 //  g_trackObject = face_config(frame,target_rect_);
               }

                if(g_trackObject == 0)
                {
                    num_of_facedection = 0;
                }


                          if(!(frame_num%10))
                 {
                    if(!flag_of_train)
                  {
                       face = ImageControl(frame,flag_of_new_target_,target);
                       flag_of_new_target_= false;
                       face_labe_= FaceRecognition(frame,target);
                       if(face_labe_.label!=0)
                       {
                          emit GetFaceName();
                           QString result_text = face_name_list_[face_labe_.label];
                           putText(g_image,result_text.toStdString(),  Point(target.x,target.y),FONT_HERSHEY_PLAIN, 4.0, CV_RGB(0,255,0), 2.0);
                       }
                    }
                    else
                    {
                        SaveImageForTrain(frame,target,num_of_template,flag_of_train);
                        flag_of_new_target_  = true;
                        imshow("template",frame(target));

                    }
                 }
                // ImageWatersheds(target);
                 ptz_command_->PTZcontrol(Point(320,240),trackBox.center,frame_num);
                 trackWindow = target;
        }
        else if (g_trackObject < 0)
            paused = false;

        if (g_selectObject && g_selection.width > 0 && g_selection.height > 0)
        {
            Mat roi(g_image, g_selection);
            bitwise_not(roi, roi);//黑白反转
        }

        t = ((double)cvGetTickCount() - t)/10000; //计算检测到人脸所需时间
        char a[1];
        _itoa(t,a,10);
        string time =a;
        putText(g_image,time,Point(0,20),FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
        imshow("TargetTracking", g_image);
        imshow("Histogram", histimg);


        if(exit_flag_ == true)
        {
            exit_flag_ = false;
            break;
        }
        char c = (char)waitKey(3);
        if (c == 27)
            break;
        switch (c)
        {
        case 'b':
            backproj_mode_ = !backproj_mode_;
            break;
        case 'c':
            g_trackObject = 0;
            histimg = Scalar::all(0);
            break;
        case 'h':
            show_hist_ = !show_hist_;
            if (!show_hist_)
                destroyWindow("Histogram");
            else
                namedWindow("Histogram", 1);
            break;
        case 'p':
            paused = !paused;
            break;
        default:
            break;
        }
    }


}
  g_selectObject = false;
  destroyAllWindows();
  g_trackObject = 0 ;
return 0;
}


Mat TargetTracking::ReturnNoramlizedImage()
{

    return face;
}

void TargetTracking::set_flag_of_train()
{
    flag_of_train = !flag_of_train;
    if(flag_of_train)
    num_of_template++;
}

void TargetTracking::TrainingModelOfFace()
{
    TrainingModle(num_of_template);
}
void TargetTracking::set_num_of_template(int num)
{
    num_of_template = num;
}

void TargetTracking::AddFaceName(QString name)
{
    face_name_list_[num_of_template] = name;
}

QString TargetTracking::GetNameOfList()
{
    return face_name_list_[face_labe_.label];
}
void TargetTracking::set_target_rect(int x_,int y_,int width_,int height_)
{
    target_rect_ = Rect(x_,y_,width_,height_);
}

void TargetTracking::ImageWatersheds(Rect rec)

{
    Mat image,mask1,mask2,mask;
    rawframe(rec).copyTo(image);
    cvtColor(image,binary,COLOR_BGR2HSV);
    inRange(binary, Scalar(156,30,0), Scalar(180,170,256*0.9), mask1);
    inRange(binary, Scalar(0,40,20), Scalar(80,180,255), mask2);
    bitwise_or(mask1,mask2,binary);
    binary = opening(binary);
  //  imshow("binary",binary);
    Mat fImage;
    Mat bImage;
    dilate(binary,bImage,cv::Mat(),cv::Point(-1,-1),6);
    Mat marker(binary.size(),CV_8U,cv::Scalar(0));
    marker = fImage + bImage;  //创建标记图像
    segmenter.setMarkers(marker);
    segment = segmenter.process(image);
  //  imshow("segmenter",segment);
}

void TargetTracking::CalculateKeyPoint(Mat &img,bool flag)
{
    Mat gray_image;
    Mat image;
    resize(img,image,Size(92,112),0,0,CV_INTER_LINEAR);
    cvtColor(image,gray_image,CV_RGB2GRAY);
    if(flag)
    {
        dector.detect(gray_image,keypoints_object);
        extractor.compute(gray_image,keypoints_object,descriptors_object);
    }

 }
void  TargetTracking::GetTargetWithPoints(Mat &img)
{
    float width_raw = img.cols/92.0f;
    float height_raw = img.rows/112.0f;
    vector<KeyPoint> keypoints_scene;
    Mat image ;
    resize(img,image,Size(92,112),0,0,CV_INTER_LINEAR);
    Mat gray_image;
    cvtColor(image,gray_image,CV_RGB2GRAY);
    dector.detect(gray_image,keypoints_scene);
    extractor.compute(gray_image,keypoints_scene,descriptors_scene);
    vector<DMatch>matches;
     matcher.match(descriptors_object,descriptors_scene,matches);
        for (int i = 0; i <matches.size(); i++)
    {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }
        int n = matches.size();
         vector<DMatch> good_matches;
     for (int i = 0; i <matches.size(); i++)
    {
        if (matches[i].distance < 5*( min_dist))
        {
            good_matches.push_back(matches[i]);
        }
    }
     vector<Point2f> scene;
  int x_min=0,x_max=0;
  int y_min=0,y_max=0;
  int x = good_matches.size();
  for( int i = 0; i < good_matches.size(); i++ )
  {
         scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
         if(i==0)
         {
             x_min=scene[i].x;
             x_max=scene[i].x;
             y_min = scene[i].y;
             y_max=scene[i].y;
         }
         else
         {
            if(scene[i].x<x_min)
               x_min = scene[i].x;
            if(scene[i].x>x_max)
               x_max = scene[i].x;
            if(scene[i].y<y_min)
               y_min = scene[i].y;
            if(scene[i].y>y_max)
               y_max = scene[i].y;
         }
  }
  Rect rec(Point(x_min*width_raw+target.x,y_min*height_raw+target.y),Point(x_max*width_raw+target.x,y_max*height_raw+target.y));
  trackBox.center = Point(rec.x+rec.width/2,rec.y+rec.height/2);
  trackBox.size.width = rec.width;
  trackBox.size.height = rec.height;
 // target = Rect((rec.x+rec.width/2+target.x)/2,(rec.y+rec.height/2+target.y)/2,(rec.width+target.width)/2,(target.height+rec.height)/2);
 // target  = rec&Rect(0,0,640,480);
  cout<<rec.x<<' '<<rec.y<<' '<<rec.width<<' '<<rec.height<<endl;


}
