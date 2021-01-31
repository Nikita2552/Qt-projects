#ifndef THREADANGLE_H
#define THREADANGLE_H

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QtMath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/* Коласс-обёртка в Qt для потока threadAngle */
class threadAngle: public QObject
{
    Q_OBJECT

public:
    threadAngle();
    ~threadAngle();
private:
    int X;
    int Y;

    bool cickleFlag;    

public slots:

    void XYToProcess(int X, int Y);

signals:
    void AngleToLabel(double X, double Y);

    /* сигналы, испускаемыйе для корректировки камеры */
    /*
    void UpAuto();
    void LeftUpAuto();
    void LeftAuto();
    void LeftDownAuto();
    void DownAuto();
    void RightDownAuto();
    void RightAuto();
    void RightUpAuto();

    void SignalTimeAuto(int time);
    */

};

#endif // THREADANGLE_H
