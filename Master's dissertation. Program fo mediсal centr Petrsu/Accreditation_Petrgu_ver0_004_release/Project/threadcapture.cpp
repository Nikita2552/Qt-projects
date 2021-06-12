#include "threadcapture.h"

threadCapture::threadCapture(QVector<QString> ForCameraData)
{
    this->InputData = ForCameraData;

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

     QString strIn;
     strIn.append(this->InputData[0]);
     strIn.append(".");
     strIn.append(this->InputData[1]);
     strIn.append(".");
     strIn.append(this->InputData[2]);
     strIn.append(".");
     strIn.append(this->InputData[3]);

     QByteArray strByte = strIn.toUtf8();
     char *strOut = strByte.data();

     QString portIn;
     portIn.append(this->InputData[4]);

     QByteArray portByte = portIn.toUtf8();
     char *portOut = portByte.data();

     QString loginIn;
     loginIn.append(this->InputData[5]);

     QByteArray loginByte = loginIn.toUtf8();
     char *loginOut = loginByte.data();

     QString passwordIn;
     passwordIn.append(this->InputData[6]);

     QByteArray passwordByte = passwordIn.toUtf8();
     char *passwordOut = passwordByte.data();

     // This works on a D-Link CDS-932L

      char videoStreamAddressChar[] = "rtsp://";

      strcat(videoStreamAddressChar, loginOut);
      strcat(videoStreamAddressChar, ":");
      strcat(videoStreamAddressChar, passwordOut);
      strcat(videoStreamAddressChar, "@");
      strcat(videoStreamAddressChar, strOut);
      strcat(videoStreamAddressChar, "/");

      //string videoStreamAddress = "rtsp://operator:Cvjnhbntkm12@172.20.141.15/";
       string videoStreamAddress = string(videoStreamAddressChar);


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
         //else { //Попытка устранить ошибку runtime error - не сработала.
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
         //}
     }

     return;
}
