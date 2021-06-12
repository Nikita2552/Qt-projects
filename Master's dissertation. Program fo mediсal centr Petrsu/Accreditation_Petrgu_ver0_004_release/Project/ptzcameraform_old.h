#ifndef PTZCAMERAFORM_H
#define PTZCAMERAFORM_H

#include <QWidget>
#include <QDebug>
#include "threadanalyze.h"
#include "threadangle.h"
#include "threadcapture.h"

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//#include "../"

using namespace cv;
using namespace std;

namespace Ui {
class PTZcameraForm;
}

class PTZcameraForm : public QWidget
{
    Q_OBJECT

public:
    explicit PTZcameraForm(QWidget *parent = nullptr);
    ~PTZcameraForm();

private:
    Ui::PTZcameraForm *ui;

    QString Status;

    String getIpAddress();

    int corrIpAddress(QString ipForCorr);

    void WaylineIn(QString waylilestr);

public slots:
    void ConnectSl(); /* Соединить */

    void DisconnectSl(); /* Отсоединить */

    void UpSl(); /* Вверх */

    void LeftSl(); /* Влево */

    void RightSl(); /* Вправо */

    void DownSl(); /* Вниз */

    void AutoConnectSl(); /* Включить автоматическую подстройку */

    void AutoDisconnectSl(); /* Выключить автоматическую подстройку */

};

#endif // PTZCAMERAFORM_H
