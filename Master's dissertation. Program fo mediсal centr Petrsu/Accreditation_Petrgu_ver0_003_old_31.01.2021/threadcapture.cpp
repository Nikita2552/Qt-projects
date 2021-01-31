#include "threadcapture.h"

threadCapture::threadCapture()
{
    this->cickleFlag = true;
}

threadCapture::~threadCapture()
{
    this->cickleFlag = false;
}

/* метод слот, содержащий инструкции для потока */
void threadCapture::process()
{
     qDebug() << "Class [threadCapture]: process is started!";

     VideoCapture vcap;
     Mat image, imageMin, imageMinNum;

     int numberFrame = 0;

     //const string videoStreamAddress = "http://USER:PWD@IPADDRESS:8088/mjpeg.cgi?user=USERNAME&password=PWD&channel=0&.mjpg";
     const string videoStreamAddress = "rtsp://operator:Cvjnhbntkm12@172.20.141.15/";
        //open the video stream and make sure it's opened
     if(!vcap.open(videoStreamAddress)) {
         qDebug() << "Class [threadCapture]: Error opening video stream or file";
         return;
     }

     while(this->cickleFlag) {    //for(;;) {
         if(!vcap.read(image)) {
             qDebug() << "Class [threadCapture]: No frame";
             waitKey();
         }
         //imshow("Output Window", image);

         /* Разреживание по кадрам */
        if (numberFrame < 4) {

            //resize( image, imageMin, Size(), 0.5, 0.5, INTER_AREA); /* Уменьшение размера */
            //imshow("small Window before", imageMin);

            /* Сигнал, испускающий кадр для помещения в label0 */
            emit CaptureToLabel(&image);

            numberFrame++;
        } else if (numberFrame == 4) {

            //resize( image, imageMinNum, Size(), 0.3, 0.3, INTER_AREA); /* Уменьшение размера */
            //imshow("small Window after", imageMinNum);

            /* Сигнал, испускающий кадр для анализа */
            emit CaptureToAnalyze(&image);

            numberFrame = 0;
        }

        if(waitKey(1) >= 0) break;
     }

     return;
}
