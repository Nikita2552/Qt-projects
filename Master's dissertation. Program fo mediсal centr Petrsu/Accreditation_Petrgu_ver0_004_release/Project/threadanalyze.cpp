#include "threadanalyze.h"

threadAnalyze::threadAnalyze(bool invertFlag)
{
    this->cickleFlag = true;

    this->invertFlag = invertFlag;

    //-- 1. Load the cascade
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); }; //return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); }; //return -1; };

}

threadAnalyze::~threadAnalyze()
{
    //this->cickleFlag = false;
}

void threadAnalyze::imageToProcess(Mat *image)
{
    this->image = *image;

    //imshow("small Window after", this->image);

    /* Координаты центра кадра для отсчёта. Так как отсчёт, изначально, начинается с левой верхней точки,
       смещаем её в центр.
    */

    int testX = this->image.cols;
    int testY = this->image.rows;

    int center_X = this->image.cols / 2;
    int center_Y = this->image.rows / 2; //cout << "center_x = " << center_x << ", " << "center_y = " << center_y << ";" << endl

    int X = center_X; /*координата x*/
    int Y = center_Y; /*координата y*/

    detectAndDisplay( this->image, "test window", X, Y );    

    int delta_center_X =  X - center_X;
    int delta_center_Y = center_Y - Y;
    /* Учёт инфертирования осей */
    if (this->invertFlag) {
        delta_center_X *= -1;
        delta_center_Y *= -1;
    }

    //qDebug() << "Class [threadAnalyze]: imageToProcess X=" << delta_center_X << "; Y=" << delta_center_Y;

    emit AnalyzeToAngle(delta_center_X, delta_center_Y);
    //emit AnalyzeToAngle(X, Y);

    emit AnalyzeToLabel(&this->image);
}

/* применение Алгоритма Хаара для распознавания лица */

void threadAnalyze::detectAndDisplay( Mat frame, String window_name, int &x, int &y )
{
   std::vector<Rect> faces;
   Mat frame_gray, frame_min_gray;

   cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
   equalizeHist( frame_gray, frame_gray );

   //Уменьшение размера кадра
   resize( frame_gray, frame_gray, Size(), 0.3, 0.3, INTER_AREA);
   //Бинаризация
   //threshold(frame_gray, frame_gray, 100, 250, CV_THRESH_BINARY);

   //-- Detect faces
   face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(15, 15) );

   for( int i = 0; i < faces.size(); i++ )
    {
      Point center( (faces[i].x  + faces[i].width*0.5)*3.33, (faces[i].y + faces[i].height*0.5)*3.33 );
      ellipse( frame, center, Size( (faces[i].width*0.5)*3.33, (faces[i].height*0.5)*3.33 ), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );

      //cout << "--||--" << endl;
      //cout << window_name << " => :"  << endl;
      //cout << "x - " << faces[i].x + faces[i].width*0.5 << endl;
      //cout << "y - " << faces[i].y + faces[i].height*0.5 << endl;
      //cout << "--||--" << endl;

      x = (faces[i].x  + faces[i].width*0.5)*3.33;
      y = (faces[i].y + faces[i].height*0.5)*3.33;


      Mat faceROI = frame_gray( faces[i] );
      std::vector<Rect> eyes;

      //-- In each face, detect eyes
      eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

      for( int j = 0; j < eyes.size(); j++ )
       {
         Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
         int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
         circle( frame, center, radius, Scalar( 255, 0, 0 ), 3, 8, 0 );
       }
    }
   //-- Show what you got
   //imshow( window_name, frame );
    //cout << "finish" << endl;
}
