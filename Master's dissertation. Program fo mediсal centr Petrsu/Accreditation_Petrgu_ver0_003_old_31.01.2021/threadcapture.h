#ifndef THREADCAPTURE_H
#define THREADCAPTURE_H

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/* Коласс-обёртка в Qt для потока threadCapture */
class threadCapture : public QObject
{
    Q_OBJECT

public:
    threadCapture();
    ~threadCapture();

private:

    bool cickleFlag;

    Mat *Image;    

public slots:
    void process();

signals:
    void CaptureToAnalyze(Mat *image);

    void CaptureToLabel(Mat *image);

};

#endif // THREADCAPTURE_H
