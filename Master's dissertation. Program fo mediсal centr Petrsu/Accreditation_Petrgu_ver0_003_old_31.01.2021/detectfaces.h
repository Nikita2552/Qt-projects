#ifndef DETECTFACES_H
#define DETECTFACES_H

#include <QDebug>
#include <QThread>
#include <QObject>
#include <QMutex>

#include "threadcapture.h"
#include "threadanalyze.h"
#include "threadangle.h"

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class detectFaces : public QObject
{
    Q_OBJECT

public:
    detectFaces();
    ~detectFaces();

    int detectTest();

    void startThreadCapture();

    void stopThreadCapture();

    void startAutoDetect(bool invertFlag);

    void stopAutoDetect();

private:

    string window_name = "Capture - Face detection";

    QThread* threadCap;
    threadCapture* workerCap;

    QThread* threadAna;
    threadAnalyze* workerAna;

    QThread* threadAng;
    threadAngle* workerAng;

    /* Мьютексы для описанных потоков */

    QMutex	mutexCap;

    QMutex	mutexAna;

    QMutex	mutexAng;

    Mat imageCap;

    /* Переменные, которые требуется защитить мьютексами */

public slots:

    void MatToImage(Mat *Image);

    void Mat2ToImage(Mat *Image);

    void Mat3ToImage(double X, double Y);

    void MoveAutoSlot(double X, double Y);

signals:

    void ImageToLabel(Mat *Image);

    void Image2ToLabel(Mat *Image);

    void Image3ToLabel(double X, double Y);

    /* сигналы, испускаемыйе для корректировки камеры */

    void UpAuto();
    void LeftUpAuto();
    void LeftAuto();
    void LeftDownAuto();
    void DownAuto();
    void RightDownAuto();
    void RightAuto();
    void RightUpAuto();

    void SignalTimeAuto(int time);
};

#endif // DETECTFACES_H
