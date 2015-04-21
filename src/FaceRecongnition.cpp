#include"FaceRecognition.h"
#include"FaceDetection.h"
#include"information_feedback_class.h"
static InformationFeedback information_feedback;
static const int num_of_template = 2;
static const string path_of_model = "D:\\E\\work\\QT\\TargetTracking_PTZ\\FaceLib\\facereco.xml";
const static 	string dir = "D:\\E\\work\\QT\\TargetTracking_PTZ\\";
Ptr<FaceRecognizer> model;
Mat face;
void FaceRecognitionInit()
{
    model =createLBPHFaceRecognizer();
    cout << "Loading Model" << endl;
    information_feedback.InfoDisplay("Loading Model\n");
    model->load(path_of_model);
    cout << "Model Loaded" << endl;
    information_feedback.InfoDisplay("Model Loaded\n");
    face = Mat::zeros(92,112,CV_8UC3);
}
void TrainingModle( int FaceNum )
{
    vector<Mat> images;
    vector<int> labels;
    string cur_dir;
    char id[2];
    int j;

    for (int i = 1; i <= FaceNum; i++)
    {
        cur_dir = dir;
        cur_dir.append("FaceLib\\");
        _itoa(i, id, 10);
        cur_dir.append(id);
        const char* dd = cur_dir.c_str();
        CStatDir statdir;
        if (!statdir.SetInitDir(dd))
        {
            puts("Dir not exist");
            break;
        }
        cout << "Processing samples in Class " << i << endl;
        information_feedback.InfoDisplay("Processing samples in Class"+QString::number(i,10)+"\n");
        vector<char*>file_vec = statdir.BeginBrowseFilenames("*.*");
        Mat image;
        if(file_vec.size()>=0)
        {
          for (j = 0; j < file_vec.size(); j++)
            {
                image = imread(file_vec[j],0);
                imshow("11",image);
                waitKey(20);

                labels.push_back(i);
                images.push_back(image);

            }
         }
        cout << images.size() << " images." << endl;
    }
    Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
    cout << "train" << endl;
    information_feedback.InfoDisplay("training the samples\n");
    model->train(images, labels);
    model->save(path_of_model);
    cout <<"model train finished"<<endl;
    information_feedback.InfoDisplay("model trian finished\n");
}

LabelOfFace FaceRecognition(Mat& frame, Rect rec)
{
    int predicted_label = -1;
    double predicted_confidence = 0.0;
    resize(frame(rec),face,face.size(),0,0,INTER_LINEAR);
    cvtColor(face,face, CV_RGB2GRAY);
    model->predict(face, predicted_label, predicted_confidence);
    LabelOfFace label;
    label.confidence = predicted_confidence;
    label.label = predicted_label;
    return label;
}
