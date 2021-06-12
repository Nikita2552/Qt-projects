#include "ptzcameraform.h"
#include "ui_ptzcameraform.h"

PTZcameraForm::PTZcameraForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PTZcameraForm)
{
    ui->setupUi(this);

    Status = "Camera is not connected";
    WaylineIn(Status);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ConnectSl()) );
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(DisconnectSl()) );
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(UpSl()) );
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(LeftSl()) );
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(RightSl()) );
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(DownSl()) );
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(AutoConnectSl()) );
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(AutoDisconnectSl()) );

    /*

    void ConnectSl();

    void DisconnectSl();

    void UpSl();

    void LeftSl();

    void RightSl();

    void DownSl();

    void AutoConnectSl();

    void AutoDisconnectSl();

    */
}

PTZcameraForm::~PTZcameraForm()
{
    delete ui;
}

String PTZcameraForm::getIpAddress()
{
    String ipAddress;
    QString tetr1, tetr2, tetr3, tetr4;
    String tetr1s, tetr2s, tetr3s, tetr4s;
    int corrIp1, corrIp2, corrIp3, corrIp4;

    /* Получить части ip-адреса из входных полей */
    tetr1 = ui -> lineEdit -> text();
    tetr2 = ui -> lineEdit_2 -> text();
    tetr3 = ui -> lineEdit_3 -> text();
    tetr4 = ui -> lineEdit_4 -> text();

    /* Конвертировать QString в String */
    tetr1s = tetr1.toUtf8().constData();
    tetr2s = tetr2.toUtf8().constData();
    tetr3s = tetr3.toUtf8().constData();
    tetr4s = tetr4.toUtf8().constData();

    /* Преобразовать в int */
    corrIp1 = corrIpAddress(tetr1);
    corrIp2 = corrIpAddress(tetr2);
    corrIp3 = corrIpAddress(tetr3);
    corrIp4 = corrIpAddress(tetr4);

    if ((corrIp1 == -1) || (corrIp2 == -1) || (corrIp3 == -1) || (corrIp4 == -1))
        ipAddress = "";
    else
        ipAddress = tetr1s + "." + tetr2s + "." + tetr3s + "." + tetr4s;

    return ipAddress;
}

/* Если ip-адресс не число от 0 до 255, то возвращается -1 */
int PTZcameraForm::corrIpAddress(QString ipForCorr)
{
    int ipCorr;
    bool ok;

    ipCorr = ipForCorr.toInt(&ok, 10);

    if ((ok == false) || (ipCorr < 0) || (ipCorr > 255))
        ipCorr = -1;

    return ipCorr;
}

void PTZcameraForm::WaylineIn(QString waylilestr)
{
    ui -> label_3 -> setText(waylilestr);
}

void PTZcameraForm::ConnectSl()
{
    qDebug() << "ConnectSl";

    String ipAddress = getIpAddress();

    if (ipAddress == "")
    {
        qDebug() << "ConnectSl: IP adress is uncorrect!";

        Status = "Camera is not connected";
        WaylineIn(Status);
    }
    else
    {
        qDebug() << "ConnectSl: IP adress is correct! Connection!";

        Status = "Camera is connected";
        WaylineIn(Status);
    }
}

void PTZcameraForm::DisconnectSl()
{
    qDebug() << "DisconnectSl";

    Status = "Camera is not connected";
    WaylineIn(Status);
}

void PTZcameraForm::UpSl()
{
    qDebug() << "UpSl";
}

void PTZcameraForm::LeftSl()
{
    qDebug() << "LeftSl";
}

void PTZcameraForm::RightSl()
{
    qDebug() << "RightSl";
}

void PTZcameraForm::DownSl()
{
    qDebug() << "DownSl";
}

void PTZcameraForm::AutoConnectSl()
{
    qDebug() << "AutoConnectSl";
}

void PTZcameraForm::AutoDisconnectSl()
{
    qDebug() << "AutoDisconnectSl";
}
