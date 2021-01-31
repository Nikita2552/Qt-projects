#include "detectfaces.h"

detectFaces::detectFaces()
{

}

detectFaces::~detectFaces()
{

}

int detectFaces::detectTest()
{
    //const string videoStreamAddress = "http://USER:PWD@IPADDRESS:8088/mjpeg.cgi?user=USERNAME&password=PWD&channel=0&.mjpg";

      VideoCapture vcap;
      Mat image, image_min;

     // This works on a D-Link CDS-932L

     //const string videoStreamAddress = "http://USER:PWD@IPADDRESS:80/mjpeg.cgi?user=USERNAME&password=PWD&channel=0&.mjpg";
     //const string videoStreamAddress = "http://operator:Cvjnhbntkm12@172.20.141.15:8000/mjpeg.cgi?user=operator&password=Cvjnhbntkm12&channel=1&.mjpg";
     const string videoStreamAddress = "rtsp://operator:Cvjnhbntkm12@172.20.141.15/";
        //open the video stream and make sure it's opened
     if(!vcap.open(videoStreamAddress)) {
         qDebug() << "Class [detectFaces]: Error opening video stream or file";
         return -1;
     }

     for(;;) {
         if(!vcap.read(image)) {
             qDebug() << "Class [detectFaces]: No frame";
             waitKey();
         }
         //imshow("Output Window", image);

         resize( image, image_min, Size(), 0.3, 0.3, INTER_AREA); /* Уменьшение размера */

         imshow("small Window before", image_min);
         imshow("small Window after", image_min);

         if(waitKey(1) >= 0) break;
     }

     return 0;
}

void detectFaces::startThreadCapture()
{
    // Создание потока
    this->threadCap = new QThread;
    this->workerCap = new threadCapture();

    // Передаем права владения "рабочим" классом, классу QThread.
    this->workerCap->moveToThread(this->threadCap);

    // Соединяем сигнал started потока, со слотом process "рабочего" класса, т.е. начинается выполнение нужной работы.
    connect(this->threadCap, SIGNAL(started()), this->workerCap, SLOT(process()));

    /* старт потока */
    this->threadCap->start();

    connect(this->workerCap, SIGNAL(CaptureToLabel(Mat *)), this, SLOT(MatToImage(Mat *)) );
}

void detectFaces::stopThreadCapture()
{
    /* завершение потока */
    //this->threadCap->terminate();
    this->workerCap->~threadCapture();
}

void detectFaces::startAutoDetect(bool invertFlag)
{
    /* Подключение метода анализа */
     this->workerAna = new threadAnalyze(invertFlag);

    /* Подключение метода угла */
    this->workerAng = new threadAngle();

    connect(this->workerCap, SIGNAL(CaptureToAnalyze(Mat *)), this->workerAna, SLOT(imageToProcess(Mat *)), Qt::DirectConnection);//, Qt::BlockingQueuedConnection );
    connect(this->workerAna, SIGNAL(AnalyzeToAngle(int, int)), this->workerAng, SLOT(XYToProcess(int, int)), Qt::DirectConnection);//, Qt::BlockingQueuedConnection );

    connect(this->workerAna, SIGNAL(AnalyzeToLabel(Mat *)), this, SLOT(Mat2ToImage(Mat *)) );
    connect(this->workerAng, SIGNAL(AngleToLabel(double, double)), this, SLOT(Mat3ToImage(double, double)) );
    connect(this->workerAng, SIGNAL(AngleToLabel(double, double)), this, SLOT(MoveAutoSlot(double, double)) );
}

void detectFaces::stopAutoDetect()
{
    disconnect(this->workerCap, SIGNAL(CaptureToAnalyze(Mat *)), this->workerAna, SLOT(imageToProcess(Mat *)));//, Qt::BlockingQueuedConnection );
    disconnect(this->workerAna, SIGNAL(AnalyzeToAngle(int, int)), this->workerAng, SLOT(XYToProcess(int, int)));//, Qt::BlockingQueuedConnection );
}

void detectFaces::MatToImage(Mat *Image)
{
    qDebug() << "Class [detectFaces]: MatToImage";

    /* Промежуточный сигнал */
    emit ImageToLabel(Image);
}

void detectFaces::Mat2ToImage(Mat *Image)
{
    qDebug() << "Class [detectFaces]: Mat2ToImage";

    /* Промежуточный сигнал */
    emit Image2ToLabel(Image);
}

void detectFaces::Mat3ToImage(double X, double Y)
{
    qDebug() << "Class [detectFaces]: Mat3ToImage";

    /* Промежуточный сигнал */
    emit Image3ToLabel(X, Y);
}

void detectFaces::MoveAutoSlot(double X, double Y)
{
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

    int D = qSqrt(pow(X, 2)+pow(Y, 2));

    if (D > 100) {

        /* (1,0) */

        if ((X > 0) && (Y == 0 )) {

            emit RightAuto();
            //emit LeftAuto();
        }

        /* (0,1) */

        else if ((X == 0) && (Y > 0 )) {

            emit UpAuto();
            //emit DownAuto();

        }

        /* (-1,0) */

        else if ((X < 0) && (Y == 0 )) {

            emit LeftAuto();
            //emit RightAuto();
        }

        /* (0,-1) */

        else if ((X == 0) && (Y < 0 )) {

            emit DownAuto();
            //emit UpAuto();
        }

        /* (1,1) */

        else if ((X > 0) && (Y > 0 )) {

            emit RightUpAuto();
            //emit LeftDownAuto();
        }

        /* (-1,1) */

        else if ((X < 0) && (Y > 0 )) {

            emit LeftUpAuto();
            //emit RightDownAuto();
        }

        /* (-1,-1) */

        else if ((X < 0) && (Y < 0 )) {

            emit LeftDownAuto();
            //emit RightUpAuto();
        }

        /* (1,-1) */

        else if ((X > 0) && (Y < 0 )) {

            emit RightDownAuto();
            //emit LeftUpAuto();
        }

        /* Выставляем сигналы с временем задержки */

        int time = 0;

        if (D <= 300) {

            time = 30;
        } else {

            time = 50;
        }

        emit SignalTimeAuto(time);
    }
}
