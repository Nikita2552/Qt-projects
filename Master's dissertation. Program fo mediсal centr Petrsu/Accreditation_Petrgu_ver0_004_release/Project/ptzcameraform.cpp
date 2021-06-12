#include "ptzcameraform.h"
#include "ui_ptzcameraform.h"

PTZcameraForm::PTZcameraForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PTZcameraForm)
{
    ui->setupUi(this);

    /* Создал объект таймер */
    this->timer = new QTimer(this);

    /* Кнопка "Подключиться" активна, кнопка "Отключиться" деактивирована */
    ui->Connect->setEnabled(true);
    ui->Disconnect->setEnabled(false);

    ui->Up->setEnabled(false);
    ui->Left->setEnabled(false);
    ui->Down->setEnabled(false);
    ui->Right->setEnabled(false);
    ui->LeftUp->setEnabled(false);
    ui->LeftDown->setEnabled(false);
    ui->RightDown->setEnabled(false);
    ui->RightUp->setEnabled(false);
    ui->ConnectAutomatic->setEnabled(false);
    ui->DisconnectAutomatic->setEnabled(false);

    connect(ui->Connect, SIGNAL(clicked()), this, SLOT(ConnectSlot()) );
    connect(ui->Disconnect, SIGNAL(clicked()), this, SLOT(DisconnectSlot()) );
    connect(ui->Up, SIGNAL(clicked()), this, SLOT(UpSlot()) );
    connect(ui->Left, SIGNAL(clicked()), this, SLOT(LeftSlot()) );
    connect(ui->Down, SIGNAL(clicked()), this, SLOT(DownSlot()) );
    connect(ui->Right, SIGNAL(clicked()), this, SLOT(RightSlot()) );
    connect(ui->LeftUp, SIGNAL(clicked()), this, SLOT(LeftUpSlot()) );
    connect(ui->LeftDown, SIGNAL(clicked()), this, SLOT(LeftDownSlot()) );
    connect(ui->RightDown, SIGNAL(clicked()), this, SLOT(RightDownSlot()) );
    connect(ui->RightUp, SIGNAL(clicked()), this, SLOT(RightUpSlot()) );

    connect(ui->Up, SIGNAL(clicked()), this, SLOT(TimerInitOneMove()) );
    connect(ui->Left, SIGNAL(clicked()), this, SLOT(TimerInitOneMove()) );
    connect(ui->Down, SIGNAL(clicked()), this, SLOT(TimerInitOneMove()) );
    connect(ui->Right, SIGNAL(clicked()), this, SLOT(TimerInitOneMove()) );
    connect(ui->LeftUp, SIGNAL(clicked()), this, SLOT(TimerInitOneMove()) );
    connect(ui->LeftDown, SIGNAL(clicked()), this, SLOT(TimerInitOneMove()) );
    connect(ui->RightDown, SIGNAL(clicked()), this, SLOT(TimerInitOneMove()) );
    connect(ui->RightUp, SIGNAL(clicked()), this, SLOT(TimerInitOneMove()) );

    connect(ui->ConnectAutomatic, SIGNAL(clicked()), this, SLOT(ConnectAutoSlot()) );
    connect(ui->DisconnectAutomatic, SIGNAL(clicked()), this, SLOT(DisconnectAutoSlot()) );

    /* вызывается слот для таймера */
    connect(this, SIGNAL(TimerSignal(int )), this, SLOT(TimerInit(int )) );
    connect(timer, SIGNAL (timeout()), this, SLOT(StopSlot()) );

    /* Подключение сигналов из клиента по сети */
    connect(this, SIGNAL(ConnectAutoSignal()), this, SLOT(ConnectAutoSlot()) );
    connect(this, SIGNAL(DisconnectAutoSignal()), this, SLOT(DisconnectAutoSlot()) );
}

PTZcameraForm::~PTZcameraForm()
{
    delete ui;
}

void PTZcameraForm::ReadInputData()
{
    this->InputData.clear();
    /* Получить части ip-адреса из входных полей */
    this->InputData.append(ui -> TetraAddressOne -> text() );
    this->InputData.append(ui -> TetraAddressTwo -> text() );
    this->InputData.append(ui -> TetraAddressThree -> text() );
    this->InputData.append(ui -> TetraAddressFour -> text() );

    /* Получить номер порта */
    this->InputData.append(ui -> Port -> text() );

    /* Получить логин */
    this->InputData.append(ui -> Login -> text() );

    /* Получить пароль */
    this->InputData.append(ui -> Password -> text() );

    /* Получить пароль */
    this->InputData.append(ui -> PortRTSP -> text() );
}

void PTZcameraForm::WriteStatusData(QString status)
{
    ui -> Status -> setText(status);
}

void PTZcameraForm::ConvertToLabel(QImage Image)
{
    /* создать Qpixmap из Qimage */
    QPixmap pix = QPixmap::fromImage(Image);

    /* Изменение размера исходного изображения */
    int width = ui->testPicture->width();
    int height = ui->testPicture->height();

    QSize PicSize(width, height);

    pix = pix.scaled(PicSize,Qt::KeepAspectRatio);

    /* показать pixmap на label */
    ui->testPicture->setPixmap(pix);
}

void PTZcameraForm::Convert2ToLabel(QImage Image)
{
    /* создать Qpixmap из Qimage */
    QPixmap pix = QPixmap::fromImage(Image);

    /* Изменение размера исходного изображения */
    int width = ui->filterPicture->width();
    int height = ui->filterPicture->height();

    QSize PicSize(width, height);

    pix = pix.scaled(PicSize,Qt::KeepAspectRatio);

    /* показать pixmap на label */
    ui->filterPicture->setPixmap(pix);
}

void PTZcameraForm::Convert3ToLabel(double Tilt, double Pan)
{
    ui -> Tilt -> setText(QString::number(Tilt) );
    ui -> Pan -> setText(QString::number(Pan) );
}

QImage PTZcameraForm::WriteToLabelData(Mat *Image)
{
    Mat Im = *Image;
    /* пробегаемся по всем пикселям изображения */
    QImage ImageL(Im.cols, Im.rows, QImage::Format_ARGB32);
            for (int y = 0; y < Im.rows; ++y) {
                    const Vec3b *srcrow = Im.ptr<Vec3b>(y);
                    QRgb *destrow = (QRgb*)ImageL.scanLine(y);
                    for (int x = 0; x < Im.cols; ++x) {
                            destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
                    }
            }

   return ImageL;

}

bool PTZcameraForm::CheckInvertBox()
{
 bool invertBox = false;

 invertBox = ui->invertBox->checkState(); /* проверка состояния чекбокса инвертации осей */

 return invertBox;
}

void PTZcameraForm::ConnectSlot()
{
    qDebug() << "Open: ConnectSlot()";

    ReadInputData();

    qDebug() << "Open [ConnectSlot]: " << this->InputData;

    CheckLabels CheckLab(this->InputData); /* создать объект для проверки */
    CheckLabelsCS CheckLabCS; /* создать объект для проверки портов */

    string ipAddress = CheckLab.getIpAddress();
    bool checkServerPort = CheckLabCS.corrPortSplit(this->InputData[4]); /* Проверка корректности ввода порта Сервера */
    bool checkRTSPPort = CheckLabCS.corrPortSplit(this->InputData[7]); /* Проверка корректности ввода порта RTSP */

    bool loginNotNull = false;
    if (this->InputData[5] != "")
    {
        loginNotNull = true;
    }

    bool passwordNotNull = false;
    if (this->InputData[6] != "")
    {
        passwordNotNull = true;
    }

    if ((ipAddress == "") || (checkServerPort == false) || (checkRTSPPort == false) || (loginNotNull == false)  || (passwordNotNull == false))
    {
        qDebug() << "Open [ConnectSlot]: IP adress is uncorrect!";

        this->status = "Camera is not connected";
        WriteStatusData(this->status);
    }
    else
    {
        qDebug() << "Open [ConnectSlot]: IP adress is correct! Connection!";

        this->ipCam = new ipCamera(this->InputData); /* Присвоение значения объекту камера */

        this->ipCam->ipCameraConnect();

        this->defFace = new detectFaces(this->InputData);
        //defFace.detectTest();
        this->defFace->startThreadCapture();

        //Кнопка "Подключиться" деактивирована, кнопка "Отключиться" активна
        ui->Connect->setEnabled(false);
        ui->Disconnect->setEnabled(true);

        ui->invertBox->setEnabled(true);

        ui->Up->setEnabled(true);
        ui->Left->setEnabled(true);
        ui->Down->setEnabled(true);
        ui->Right->setEnabled(true);
        ui->LeftUp->setEnabled(true);
        ui->LeftDown->setEnabled(true);
        ui->RightDown->setEnabled(true);
        ui->RightUp->setEnabled(true);
        ui->ConnectAutomatic->setEnabled(true);
        ui->DisconnectAutomatic->setEnabled(true);

        connect(this->defFace, SIGNAL(ImageToLabel(Mat *)), this, SLOT(WriteImageData(Mat *)) );

        this->status = "Camera is connected";
        WriteStatusData(this->status);
    }

    //CheckLab.~CheckLabels(); /* уничтожить объект для проверки */
}

void PTZcameraForm::DisconnectSlot()
{
    qDebug() << "Open: DisconnectSlot()";

    this->ipCam->ipCameraDisconnect();

    this->defFace->stopThreadCapture();

    //Кнопка "Подключиться" активна, кнопка "Отключиться" деактивирована
    ui->Connect->setEnabled(true);
    ui->Disconnect->setEnabled(false);

    ui->Up->setEnabled(false);
    ui->Left->setEnabled(false);
    ui->Down->setEnabled(false);
    ui->Right->setEnabled(false);
    ui->LeftUp->setEnabled(false);
    ui->LeftDown->setEnabled(false);
    ui->RightDown->setEnabled(false);
    ui->RightUp->setEnabled(false);
    ui->ConnectAutomatic->setEnabled(false);
    ui->DisconnectAutomatic->setEnabled(false);

    this->InputData.clear();
}

void PTZcameraForm::UpSlot()
{
    qDebug() << "Open: UpSlot()";

    this->dwPTZCommand = ipCam->ipCameraMoveUp();
}

void PTZcameraForm::LeftSlot()
{
    qDebug() << "Open: LeftSlot()";

    this->dwPTZCommand = ipCam->ipCameraMoveLeft();
}

void PTZcameraForm::DownSlot()
{
    qDebug() << "Open: DownSlot()";

    this->dwPTZCommand = ipCam->ipCameraMoveDown();
}

void PTZcameraForm::RightSlot()
{
    qDebug() << "Open: RightSlot()";

    this->dwPTZCommand = ipCam->ipCameraMoveRight();
}

void PTZcameraForm::LeftUpSlot()
{
    qDebug() << "Open: LeftUpSlot()";

    this->dwPTZCommand = ipCam->ipCameraMoveLeftUp();
}

void PTZcameraForm::LeftDownSlot()
{
    qDebug() << "Open: LeftDownSlot()";

    this->dwPTZCommand = ipCam->ipCameraMoveLeftDown();
}

void PTZcameraForm::RightDownSlot()
{
    qDebug() << "Open: RightDownSlot()";

    this->dwPTZCommand = ipCam->ipCameraMoveRightDown(); 
}

void PTZcameraForm::RightUpSlot()
{
    qDebug() << "Open: RightUpSlot()";

    this->dwPTZCommand = ipCam->ipCameraMoveRightUp();
}

void PTZcameraForm::TimerInitOneMove()
{
     /* 100 - задержка перед посылкой сигнала для прекращения движения */
    int time = 100;
    emit TimerSignal(time);
}

/* Запуск таймера. Параметр - время отсчёта в мс */
void PTZcameraForm::TimerInit(int time)
{
    this->timer->start(time);
}

void PTZcameraForm::StopSlot()
{
    qDebug() << "Open: StopSlot()";

    ipCam->ipCameraMoveStop(this->dwPTZCommand);

    this->timer->stop();
}

void PTZcameraForm::ConnectAutoSlot()
{
    qDebug() << "Open: ConnectAutoSlot()";

    bool invertFlag;
    invertFlag = CheckInvertBox();

    ui->invertBox->setEnabled(false);

    this->defFace->startAutoDetect(invertFlag);

    connect(this->defFace, SIGNAL(Image2ToLabel(Mat *)), this, SLOT(Write2ImageData(Mat *)) );
    connect(this->defFace, SIGNAL(Image3ToLabel(double, double)), this, SLOT(Write3ImageData(double, double)) );
    /* Написать код для установки направления движения:
    void UpAuto();
    void LeftUpAuto();
    void LeftAuto();
    void LeftDownAuto();
    void DownAuto();
    void RightDownAuto();
    void RightAuto();
    void RightUpAuto();
    */
    connect(defFace, SIGNAL(UpAuto()), this, SLOT(UpSlot()) );
    connect(defFace, SIGNAL(LeftAuto()), this, SLOT(LeftSlot()) );
    connect(defFace, SIGNAL(DownAuto()), this, SLOT(DownSlot()) );
    connect(defFace, SIGNAL(RightAuto()), this, SLOT(RightSlot()) );
    connect(defFace, SIGNAL(LeftUpAuto()), this, SLOT(LeftUpSlot()) );
    connect(defFace, SIGNAL(LeftDownAuto()), this, SLOT(LeftDownSlot()) );
    connect(defFace, SIGNAL(RightDownAuto()), this, SLOT(RightDownSlot()) );
    connect(defFace, SIGNAL(RightUpAuto()), this, SLOT(RightUpSlot()) );

    connect(defFace, SIGNAL(SignalTimeAuto(int )), this, SLOT(TimerInit(int )) );

    QVector <QString> setAutomate;
    setAutomate.push_back("true");
    emit setAutomateSignal(05, setAutomate);
}

void PTZcameraForm::DisconnectAutoSlot()
{
    qDebug() << "Open: DisconnectAutoSlot()";

    ui->invertBox->setEnabled(true);

    this->defFace->stopAutoDetect();

    QVector <QString> setAutomate;
    setAutomate.push_back("false");
    emit setAutomateSignal(05, setAutomate);
}
/* Слот для показа картинке в Label0 */
void PTZcameraForm::WriteImageData(Mat *Image)
{
    //qDebug() << "Open [ConnectSlot]: WriteImageData";

    QImage ImageL;

    ImageL = WriteToLabelData(Image);

    ConvertToLabel(ImageL);
}

void PTZcameraForm::Write2ImageData(Mat *Image)
{
    //qDebug() << "Open [ConnectSlot]: Write2ImageData";

    QImage ImageL;

    ImageL = WriteToLabelData(Image);

    Convert2ToLabel(ImageL);
}

void PTZcameraForm::Write3ImageData(double Tilt, double Pan)
{
    //qDebug() << "Open [ConnectSlot]: Write3ImageData";

    Convert3ToLabel(Tilt, Pan);
}

void PTZcameraForm::setOrunsetAutomateSlot(QString Automate)
{
    qDebug() << "Выбор сигнала!!!";

    if (this->status == "Camera is connected")
    {
        if (Automate == "true")
            emit ConnectAutoSignal();
        else
            emit DisconnectAutoSignal();
    }
    else
    {
        qDebug() << "Сигнал с удалённого пульта не посылается";
    }
}
