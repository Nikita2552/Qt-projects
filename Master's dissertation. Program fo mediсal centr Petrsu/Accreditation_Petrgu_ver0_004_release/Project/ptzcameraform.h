#ifndef PTZCAMERAFORM_H
#define PTZCAMERAFORM_H

#include <QWidget>
#include <QDebug>
#include <QTimer>

#include "checklabels.h"
#include "checklabelscs.h"
#include "ipcamera.h"
#include "detectfaces.h"

#include <opencv2/opencv.hpp>

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

    QTimer *timer;

    DWORD dwPTZCommand;

    /*
      InputData:
      0-3 - ip-аддресс
      4 - порт
      5 - логин
      6 - пароль
    */

    QVector <QString> InputData;

    QString status;

    ipCamera *ipCam;

    detectFaces *defFace;

    void ReadInputData();

    void WriteStatusData(QString status);

    void ConvertToLabel(QImage Image);

    void Convert2ToLabel(QImage Image);

    void Convert3ToLabel(double Tilt, double Pan);

    QImage WriteToLabelData(Mat *Image);

    bool CheckInvertBox();

public slots:

    void ConnectSlot();

    void DisconnectSlot();

    void UpSlot();

    void LeftSlot();

    void DownSlot();

    void RightSlot();

    void LeftUpSlot();

    void LeftDownSlot();

    void RightDownSlot();

    void RightUpSlot();

    void TimerInitOneMove();

    void TimerInit(int time);

    void StopSlot();

    void ConnectAutoSlot();

    void DisconnectAutoSlot();

    void WriteImageData(Mat *Image);

    void Write2ImageData(Mat *Image);

    void Write3ImageData(double Tilt, double Pan);

    void setOrunsetAutomateSlot(QString Automate);

signals:

    void TimerSignal(int time);

    void setAutomateSignal(int number, QVector <QString> setAutomate);

    void ConnectAutoSignal();

    void DisconnectAutoSignal();

};
#endif // PTZCAMERAFORM_H
