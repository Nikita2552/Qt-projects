#ifndef THREADANALYZE_H
#define THREADANALYZE_H

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/* Коласс-обёртка в Qt для потока threadCapture */
class threadAnalyze : public QObject
{
    Q_OBJECT

public:
    threadAnalyze(bool invertFlag);
    ~threadAnalyze();

private:
    Mat image;

    Mat *Image;

    bool cickleFlag;

    bool invertFlag;

    String face_cascade_name = "D:/opencv4/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
    String eyes_cascade_name = "D:/opencv4/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    //RNG rng(12345);

    void detectAndDisplay( Mat frame, String window_name, int &x, int &y );

public slots:

    void imageToProcess(Mat *image);

signals:
    void AnalyzeToAngle(int X, int Y);

    void AnalyzeToLabel(Mat *image);
};

#endif // THREADANALYZE_H
