#include "shumform1.h"
#include "ui_shumform1.h"
#include <QDebug>
#include <QVector>
#include <QtMath>
#include <QImage>
#include <QCheckBox>
#include <complex>
#include <math.h>
#include <cmath>

#define PI 3.14159265
//Т.к. функция atan выдаёт значение угла в радианах, требуется конвертация в градусы.
// 1(радиана) = 57.2958(градусов)
#define grad 57.3

shumForm1::shumForm1(QWidget *parent) :
    QWidget(parent),
     ui(new Ui::shumForm1)
{
    ui->setupUi(this);

    //Присвоение адреса объекта дочернего окна ссылке
    SF2 = new shumForm2();

    connect(this, SIGNAL(for_form2_signal(QImage, QImage, QImage, QImage, QImage, QImage, QImage, QImage, QImage) ), SF2, SLOT(process_for_seen_images(QImage, QImage, QImage, QImage, QImage, QImage, QImage, QImage, QImage) ) );

   // connect(this, SIGNAL( clicked() ), this, SLOT( saveText() ) );
    connect(this, SIGNAL( forSave_images(QString) ), SF2, SLOT( saveImages(QString) ) );
}

shumForm1::~shumForm1()
{
    delete ui;
}

void shumForm1::SeeImages(QImage image, shumForm1::Images im)
{

    QSize labelSize;
    QImage imageSmall;

    switch (im)
    {
    case IMAGE_CLONE:
            qDebug() << "image CLONE";
            labelSize = ui->label->size();

            imageSmall = image.scaled(labelSize.width(), labelSize.height(), Qt::KeepAspectRatio);

            ui->label->setPixmap(QPixmap::fromImage(imageSmall));
            break;
    case IMAGE_SPEKTR:
            qDebug() << "image SPEKTR";
            labelSize = ui->label_2->size();

            imageSmall = image.scaled(labelSize.width(), labelSize.height(), Qt::KeepAspectRatio);

            ui->label_2->setPixmap(QPixmap::fromImage(imageSmall));
            break;
    case IMAGE_CLONE1:
            qDebug() << "image CLONE1";
            labelSize = ui->label_3->size();

            imageSmall = image.scaled(labelSize.width(), labelSize.height(), Qt::KeepAspectRatio);

            ui->label_3->setPixmap(QPixmap::fromImage(imageSmall));
            break;
    case IMAGE_R:
            qDebug() << "image R";
            labelSize = ui->label_4->size();

            imageSmall = image.scaled(labelSize.width(), labelSize.height(), Qt::KeepAspectRatio);

            ui->label_4->setPixmap(QPixmap::fromImage(imageSmall));
            break;
    case IMAGE_G:
            qDebug() << "image G";
            labelSize = ui->label_5->size();

            imageSmall = image.scaled(labelSize.width(), labelSize.height(), Qt::KeepAspectRatio);

            ui->label_5->setPixmap(QPixmap::fromImage(imageSmall));
             break;
    case IMAGE_B:
            qDebug() << "image B";
            labelSize = ui->label_6->size();

            imageSmall = image.scaled(labelSize.width(), labelSize.height(), Qt::KeepAspectRatio);

            ui->label_6->setPixmap(QPixmap::fromImage(imageSmall));
             break;
    case IMAGE_ST1:
           qDebug() << "image ST1";
           labelSize = ui->label_7->size();
           imageSmall = image.scaled(labelSize.width(), labelSize.height(), Qt::KeepAspectRatio);

           ui->label_7->setPixmap(QPixmap::fromImage(imageSmall));
           break;
    case IMAGE_ST2:
           qDebug() << "image ST2";
           labelSize = ui->label_8->size();
           imageSmall = image.scaled(labelSize.width(), labelSize.height(), Qt::KeepAspectRatio);

           ui->label_8->setPixmap(QPixmap::fromImage(imageSmall));
           break;
    case IMAGE_ST3:
           qDebug() << "image ST3";
           labelSize = ui->label_9->size();
           imageSmall = image.scaled(labelSize.width(), labelSize.height(), Qt::KeepAspectRatio);

           ui->label_9->setPixmap(QPixmap::fromImage(imageSmall));
           break;


    }
}

QImage shumForm1::CentrImage(QImage image)
{
    //Создание объекта точка
    QPoint p;
    QColor iRgb, iredd, igreenn, ibluee;
    float ired, igreen, iblue;

    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;


    int step;

    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            p = QPoint(j, i);
            iRgb = image.pixelColor(p);
            step = one_with_N(i + j);

            ired = float( iRgb.red() ); //qDebug() << "[] ired = " << ired;
            ired = ired * step;

            igreen = iRgb.green();
            igreen = igreen * step;

            iblue = iRgb.blue();
            iblue = iblue * step;

            iRgb = QColor( int(ired), int(igreen), int(iblue), 0);

            image.setPixelColor(p, iRgb);
        }
    }

    return image;
}

QVector<QVector<float> > shumForm1::CentrImage(QImage image, shumForm1::Images im)
{
    //Создание объекта точка
    QPoint p;
    QColor iRgb;
    float icolor;

    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;


    /*Двумерный массив яркостей точек*/
    QVector < QVector <float> > complex_image;
    /*Временный массив для строки массива яркостей точек */
    QVector <float> complex_str;
    /*Переменная для хранения центрирующего коэффициента */
    int step;

    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            p = QPoint(j, i);
            iRgb = image.pixelColor(p);
            step = one_with_N(i + j);

            switch (im)
                {
                case IMAGE_R:
                        //qDebug() << "complex R";
                        icolor = float( iRgb.red() );
                        break;
                case IMAGE_G:
                        //qDebug() << "complex G";
                        icolor = float( iRgb.green() );
                        break;
                case IMAGE_B:
                        //qDebug() << "complex B";
                        icolor = float( iRgb.blue() );
                        break;
                } qDebug() << "! icolor = " << icolor;

             icolor = icolor * step; qDebug() << "step = " << step << ";icolor = " << icolor;

             complex_str.append(icolor);
          }
            complex_image.append(complex_str);
            complex_str.clear();
    }

    return complex_image;
}

/*Образец для вставки: D:\Obrazets\1test.bmp */
/*Образец для вставки: D:\Obrazets\1testcut.bmp */

QVector<QVector<complex<float> > > shumForm1::PryamoeFurieStroki(QVector<QVector<float> > image)
{
    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    /*Двумерный массив из комплексных чисел*/
    QVector < QVector < complex <float> > > complex_image;
    /*Временный массив для строки массива комплексных чисел */
    QVector < complex <float> > complex_str;
    QVector <float> image_str;
    /*Временная переменная для элменента массива из комплексных чиел */
    complex <float> complex_el_sum, complex_el;

    /*Переделать для двумерного массива комплексных чисел*/
    //complex <float> * complex_image = new complex <float> [iwidth][iheight];

    float icolor, real_part, imag_part;

    /*Меняем номер столбца*/
    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            /*j - в данном случае частота, k - отсчёт*/

            for (int k = 0; k < iwidth; k++)
            {
             image_str = image.at(i);
             icolor = image_str.at(k); //qDebug() << "----"; qDebug() << "i=" << i <<", j=" << j << ", k=" << k << "; iwidth= " << iwidth << ";[]icolor = " << icolor;

            /*Создание комплексного значения F(u, y)*/
            real_part = icolor * qCos( (2 * PI * j * k) / iwidth ); //qDebug() << "real_part = " << real_part;
            imag_part = icolor * qSin( (2 * PI * j * k) / iwidth ); //qDebug() << "imag_part = " << imag_part; qDebug() << "----";
            complex_el = complex <float> ( real_part, imag_part );

            complex_el_sum += complex_el;

            }
            /* добавление данных в строку массива */
            complex_str.append( complex_el_sum ); qDebug() << complex_el_sum.real() << " + " << complex_el_sum.imag() << " * i";

            complex_el_sum = 0 + 0 * i;
            complex_el = 0 + 0 * i;
        }
            complex_image.append( complex_str );
            complex_str.clear();
    }
    qDebug() << "return complex_image!";
    return complex_image;
}


QVector<QVector<complex<float> > > shumForm1::PryamoeFurieStolbtsyi(QVector<QVector<complex<float> > > image)
{
    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    int isize;

    /*Двумерный массив из комплексных чисел*/
    QVector < QVector < complex <float> > > complex_image;
    /*Временный массив для строки массива комплексных чисел */
    QVector < complex <float> > complex_str, image_str;
    /*Временная переменная для элменента массива из комплексных чиел */
    complex <float> image_el, complex_el_sum, complex_el;

    float image_real_part, image_imag_part;
    float complex_real_part, complex_imag_part;
    float icos, isin;

    /*Проходим по всем элементам строки*/
    for (int i = 0; i < iwidth; i++)
    {
        /*Меняем номер столбца*/
        for (int j = 0; j < iheight; j++)
        {
            /*Суммирование элементов массива по столбцам*/
            for (int k = 0; k < iheight; k++)
            {
                /*Считывание элемента из image*/
                image_str = image.at(k);
                image_el = image_str.at(i);
                /*__*/
                image_real_part = image_el.real();
                image_imag_part = image_el.imag();

                icos = qCos( (2 * PI * j * k) / iheight );
                isin = qSin( (2 * PI * j * k) / iheight );

                complex_real_part = image_real_part * icos - image_imag_part * isin;  //qDebug() << "----"; qDebug() << "complex_real_part = " << complex_real_part;
                complex_imag_part = image_real_part * isin + image_imag_part * icos;  //qDebug() << "complex_imag_part = " << complex_imag_part; qDebug() << "----";

                /*Запись элемента в complex_image*/
                complex_el = complex <float> ( complex_real_part, complex_imag_part );
                /*Суммирование всех элементов*/
                complex_el_sum += complex_el;
            }

            /*Проверка, создан ли текущий строковый вектор*/
            isize = complex_image.size(); //qDebug() << complex_el_sum.real() << " + " << complex_el_sum.imag() << " * i";

            if(j < isize)
                {
                complex_str = complex_image.at(j);
                /*complex_str.insert(i, complex_el_sum); */ complex_str.append(complex_el_sum);

                //complex_image.remove(j);
                //complex_image.insert(j, complex_str);
                complex_image.replace(j, complex_str);
                }
             else
                {
                complex_str.append(complex_el_sum);
                complex_image.append(complex_str);
                }
            /*__*/

            complex_el_sum = complex <float> ( 0, 0 );
            complex_str.clear();
        }
    }

    return complex_image;
}

QVector<QVector<float> > shumForm1::toVectorF(QVector<QVector<complex<float> > > image)
{
    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    QVector < complex <float> > image_str;
    /*Временная переменная для элменента массива из комплексных чиел */
    complex <float> image_el;

    QVector <QVector <float> > complex_image;
    QVector <float> complex_image_str;

    float real, imag, el;

    /*Меняем номер столбца*/
    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            image_str = image.at(i);
            image_el = image_str.at(j); // qDebug() << "----"; //qDebug() << "i=" << i <<", j=" << j << ", k=" << j << "; iwidth= " << iwidth << ";[]icolor = " << icolor;

            //Получаем точку спектра
            real = image_el.real();
            imag = image_el.imag();

            el = qSqrt ( qPow(real, 2) + qPow(imag, 2) );
            complex_image_str.append(el);
        }
        complex_image.append(complex_image_str);
        complex_image_str.clear();
    }

    return complex_image;
}

QVector<QVector<float> > shumForm1::toVectorFlog(QVector<QVector<float> > image)
{
    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    QVector<QVector<float> > complex_image;

    QVector <float> image_str, complex_str;
    /*Временная переменная для элменента массива из комплексных чиел */
    float image_el, complex_el, image_el0;

    float max, min;


    /*Меняем номер столбца*/
    for (int i = 0; i < iheight; i++)
    {
        //image_str = image.at(i);
        //image_el0 = image_str.at(0);

        for(int j = 0; j < iwidth; j++)
        {
            image_str = image.at(i);
            image_el = image_str.at(j); //qDebug() << "----"; //qDebug() << "i=" << i <<", j=" << j << ", k=" << j << "; iwidth= " << iwidth << ";[]icolor = " << icolor;

            complex_el = log2( image_el / (iheight * iwidth) ); //qDebug() << "!!! - " << complex_el;

           complex_str.append(complex_el);
        }
        complex_image.append(complex_str);
        complex_str.clear();
    }

    return complex_image;
}

QVector<QVector<float> > shumForm1::toVectorFshkala(QVector<QVector<float> > image)
{
    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;


    QVector<QVector<float> > complex_image;
    QVector <float> image_str, complex_str;
    float image_el, complex_el;
    float min, max;

    image_str = image.at(0);
    min = image_str.at(0);
    max = min;

    /*Меняем номер столбца*/
    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            image_str = image.at(i);
            image_el = image_str.at(j);

            if (image_el > max)
                max = image_el;
            if (image_el < min)
                min = image_el;
        }
    }

    /*Меняем номер столбца*/
    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            image_str = image.at(i);
            image_el = image_str.at(j);

            complex_el = (image_el - min) / (max - min) * 255;
            complex_str.append(complex_el); qDebug() << "[toVectorFshkala] complex_el = " << complex_el;
        }
        complex_image.append(complex_str);
        complex_str.clear();
    }
    return complex_image;
}

QImage shumForm1::toMonoImage(QVector<QVector<float> > image, Images im)
{
    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    QImage complex_image(iwidth, iheight, QImage::Format_RGB32);
    QVector <float> image_str, complex_str;
    float image_el, complex_el;

    QPoint p;
    QColor icolor;
    int ired, igreen, iblue;

    /*Меняем номер столбца*/
    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            image_str = image.at(i);
            image_el = image_str.at(j);

            p = QPoint(j, i);

            switch (im)
                {
                case IMAGE_R:
                        ired = int(image_el); //qDebug() << "[] ired = " << ired;
                        icolor = QColor(ired, 0, 0, 0);
                         break;
                case IMAGE_G:
                        igreen = int(image_el);
                        icolor = QColor(0, igreen, 0, 0);
                         break;
                case IMAGE_B:
                        iblue = int(image_el);
                        icolor = QColor(0, 0, iblue, 0);
                         break;
                }

            complex_image.setPixelColor(p, icolor);
        }
    }

    return complex_image;
}

QImage shumForm1::toStereoImage(QVector<QVector<float> > R_image, QVector<QVector<float> > G_image, QVector<QVector<float> > B_image)
{
    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    QImage complex_image(iwidth, iheight, QImage::Format_RGB32);
    QVector <float> R_image_str, G_image_str, B_image_str, complex_str;
    float R_image_el, G_image_el, B_image_el, complex_el;

    QPoint p;
    QColor icolor;
    int ired, igreen, iblue;

    /*Меняем номер столбца*/
    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            R_image_str = R_image.at(i);
            R_image_el = R_image_str.at(j);

            G_image_str = G_image.at(i);
            G_image_el = G_image_str.at(j);

            B_image_str = B_image.at(i);
            B_image_el = B_image_str.at(j);

            p = QPoint(j, i);

            ired = int(R_image_el);
            igreen = int(G_image_el);
            iblue = int(B_image_el);

            icolor = QColor(ired, igreen, iblue, 0); qDebug() << "ired=" << ired << ",igreen=" << igreen << ",iblue="<<iblue;

            complex_image.setPixelColor(p, icolor);
        }
    }

    return complex_image;
}

QVector<QVector<float> > shumForm1::Mask(QVector<QVector<float> > image, float D0, maskType Type)
{
    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    QVector<QVector< float > > mask;
    QVector <float> mask_str;
    /*Временная переменная для элеменента массива */
    float H_uv;

    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            switch (Type)
                {
                case Ideal:
                     H_uv = H_u_v_ideal(D0, j, i, iwidth, iheight);
                     break;
                case Gauss:
                     H_uv = H_u_v_gauss(D0, j, i, iwidth, iheight);
                     break;
                }
            mask_str.append(H_uv);
       }
        mask.append(mask_str);
        mask_str.clear();
    }

    return mask;
}

QImage shumForm1::toMonoMask(QVector<QVector<float> > image, shumForm1::Images im)
{
    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    QImage complex_image(iwidth, iheight, QImage::Format_RGB32);
    QVector <float> image_str, complex_str;
    float image_el, complex_el;

    QPoint p;
    QColor icolor;
    int ired, igreen, iblue;

    /*Меняем номер столбца*/
    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            image_str = image.at(i);
            image_el = image_str.at(j);

            p = QPoint(j, i);

            switch (im)
                {
                case IMAGE_R:
                        ired = 255 * int(image_el); //qDebug() << "[] ired = " << ired;
                        icolor = QColor(ired, 0, 0, 0);
                         break;
                case IMAGE_G:
                        igreen = 255 * int(image_el);
                        icolor = QColor(0, igreen, 0, 0);
                         break;
                case IMAGE_B:
                        iblue = 255 * int(image_el);
                        icolor = QColor(0, 0, iblue, 0);
                         break;
                }

            complex_image.setPixelColor(p, icolor);
        }
    }

    return complex_image;
}

QImage shumForm1::toStereoMask(QVector<QVector<float> > R_image, QVector<QVector<float> > G_image, QVector<QVector<float> > B_image)
{
    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    QImage complex_image(iwidth, iheight, QImage::Format_RGB32);
    QVector <float> R_image_str, G_image_str, B_image_str, complex_str;
    float R_image_el, G_image_el, B_image_el, complex_el;

    QPoint p;
    QColor icolor;
    int ired, igreen, iblue;

    /*Меняем номер столбца*/
    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            R_image_str = R_image.at(i);
            R_image_el = R_image_str.at(j);

            G_image_str = G_image.at(i);
            G_image_el = G_image_str.at(j);

            B_image_str = B_image.at(i);
            B_image_el = B_image_str.at(j);

            p = QPoint(j, i);

            ired = 255 * int(R_image_el);
            igreen = 255 * int(G_image_el);
            iblue = 255 * int(B_image_el);

            icolor = QColor(ired, igreen, iblue, 0);

            complex_image.setPixelColor(p, icolor);
        }
    }

    return complex_image;
}

QVector<QVector<float> > shumForm1::idealFilter(QVector<QVector<float> > spektr, QVector<QVector<float> > mask)
{

    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    /*Добавить выбор фильтра*/
    //float D0 = 5;
    QVector<QVector<float> > filtered_spektr;

    QVector <float> spektr_str, mask_str, filtered_spekr_str;
    /*Временная переменная для элменента массива из комплексных чиел */
    float F_uv, H_uv, G_uv;

    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            spektr_str = spektr.at(i);
            F_uv = spektr_str.at(j);

            mask_str = mask.at(i);
            H_uv = mask_str.at(j);

            /*Сделать конвертацию*/
            G_uv = H_uv * F_uv; //qDebug() << "G_uv = " << G_uv.real() << " + " << G_uv.imag() << "*i";

            filtered_spekr_str.append(G_uv);
       }
        filtered_spektr.append(filtered_spekr_str);
        filtered_spekr_str.clear();
    }

    return filtered_spektr;
}

QVector<QVector<complex<float> > > shumForm1::idealFilterComplex(QVector<QVector<complex<float> > > spektr, QVector<QVector<float> > mask)
{
    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    /*Добавить выбор фильтра*/
    //float D0 = 5;
    QVector<QVector<complex<float> > > filtered_spektr;

    QVector < complex<float> > spektr_str, filtered_spekr_str;
    QVector <float> mask_str;
    complex <float> spektr_el;
    float mask_el;
    /*Временная переменная для элменента массива из комплексных чиел */
    //float H_uv;

    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            spektr_str = spektr.at(i);
            spektr_el = spektr_str.at(j);

            mask_str = mask.at(i);
            mask_el = mask_str.at(j);

            if (mask_el == 1)
            {
                filtered_spekr_str.append(spektr_el);
            }
            else
            {
               filtered_spekr_str.append( complex <float> (0, 0) );
            }

       }
        filtered_spektr.append(filtered_spekr_str);
        filtered_spekr_str.clear();
    }

    return filtered_spektr;
}

QVector<QVector<complex<float> > > shumForm1::ObratnoyeFurieStroki(QVector<QVector<complex<float> > > image)
{
    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    /*Двумерный массив из комплексных чисел*/
    QVector < QVector < complex <float> > > complex_image;
    /*Временный массив для строки массива комплексных чисел */
    QVector < complex <float> > complex_str, image_str;
    /*Временная переменная для элменента массива из комплексных чиел */
    complex <float> image_el, complex_el_sum, complex_el;

    float icolor, real_part, imag_part, image_real_part, image_imag_part, complex_real_part, complex_imag_part, icos, isin;

    /*Меняем номер столбца*/
    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            /*j - в данном случае частота, k - отсчёт*/

            for (int k = 0; k < iwidth; k++)
            {
             //image_str = image.at(i);
             //icolor = image_str.at(k); //qDebug() << "----"; qDebug() << "i=" << i <<", j=" << j << ", k=" << k << "; iwidth= " << iwidth << ";[]icolor = " << icolor;

            /*Создание комплексного значения F(u, y)*/
            //real_part = icolor * qCos( (2 * PI * j * k) / iwidth ); //qDebug() << "real_part = " << real_part;
            //imag_part = icolor * qSin( (2 * PI * j * k) / iwidth ); //qDebug() << "imag_part = " << imag_part; qDebug() << "----";
            //complex_el = complex <float> ( real_part, imag_part );

            //complex_el_sum += complex_el;

            /*Считывание элемента из image*/
            image_str = image.at(i);
            image_el = image_str.at(k);
            /*__*/
            image_real_part = image_el.real();
            image_imag_part = image_el.imag();

            icos = qCos( (2 * PI * j * k) / iwidth );
            isin = qSin( (2 * PI * j * k) / iwidth );

            complex_real_part = image_real_part * icos + image_imag_part * isin;  //qDebug() << "----"; qDebug() << "complex_real_part = " << complex_real_part;
            complex_imag_part = image_real_part * isin - image_imag_part * icos;  //qDebug() << "complex_imag_part = " << complex_imag_part; qDebug() << "----";

            /*Запись элемента в complex_image*/
            complex_el = complex <float> ( complex_real_part, complex_imag_part );
            /*Суммирование всех элементов*/
            complex_el_sum += complex_el;

            }
            /* добавление данных в строку массива */
            complex_str.append( complex_el_sum ); //qDebug() << complex_el_sum.real() << " + " << complex_el_sum.imag() << " * i";

            complex_el_sum = 0 + 0 * i;
            complex_el = 0 + 0 * i;
        }
            complex_image.append( complex_str );
            complex_str.clear();
    }
    qDebug() << "ObratnoyeFurieStroki!";
    return complex_image;
}

QVector<QVector<complex<float> > > shumForm1::ObratnoyeFurieStolbtsyi(QVector<QVector<complex<float> > > image)
{
    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;
    int isize;

    QVector<QVector<complex<float> > > complex_image;
    QVector<complex<float> > image_str, complex_image_str;
    complex <float> image_el, complex_image_el, complex_image_el_current;

    float image_real_part, image_imag_part;
    float complex_real_part, complex_imag_part;
    float icos, isin;


    for (int i = 0; i < iwidth; i++)
    {
        /*Меняем номер столбца*/
        for(int j = 0; j < iheight; j++)
        {
            /*k - в данном случае частота, j - отсчёт*/

            for (int k = 0; k < iheight; k++)
            {
                image_str = image.at(k);
                image_el = image_str.at(i);

                image_real_part = image_el.real();
                image_imag_part = image_el.imag();

                icos = qCos( ( 2 * PI * j * k) / iheight  );
                isin = qSin( ( 2 * PI * j * k) / iheight );

                complex_real_part = image_real_part * icos + image_imag_part * isin; //qDebug() << "----"; qDebug() << "complex_real_part1 = " << complex_real_part;
                complex_imag_part = image_real_part * isin - image_imag_part * icos; //qDebug() << "complex_imag_part1 = " << complex_imag_part; qDebug() << "----";

                /*Запись элемента в complex_image*/
                complex_image_el_current = complex <float> ( complex_real_part, complex_imag_part );
                /*Суммирование всех элементов*/
                complex_image_el += complex_image_el_current;
            }
            /*Проверка, создан ли текущий строковый вектор*/
            isize = complex_image.size(); //qDebug() << "OBR real=" << complex_image_el.real() << ", imag=" << complex_image_el.imag();
            if(j < isize)
                {
                complex_image_str = complex_image.at(j);
                /*complex_image_str.insert(i, complex_image_el);*/complex_image_str.append(complex_image_el);

                complex_image.replace(j, complex_image_str);
                }
             else
                {
                complex_image_str.append(complex_image_el);
                complex_image.append(complex_image_str);
                }
            /*__*/
           complex_image_el = complex <float> ( 0, 0 );
           complex_image_str.clear();
       }
    }
    qDebug() << "ObratnoyeFurieStolbtsyi!";
    return complex_image;
}

QVector<QVector<float> > shumForm1::RealVector(QVector<QVector<complex<float> > > image)
{
    QVector<QVector<float> >  complex_image;

    QVector <complex <float> > image_str;
    complex <float> image_el;
    QVector<float > complex_image_str;
    float real, imag, complex_image_el;

    float icolor;

    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    int step;

    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            image_str = image.at(i);
            image_el = image_str.at(j);

            real = image_el.real();
            imag = image_el.imag();

            complex_image_el = (real + imag) / (iheight * iwidth);

            complex_image_str.append(complex_image_el);
        }
        complex_image.append(complex_image_str);
        complex_image_str.clear();

    }

    return complex_image;
}

QVector<QVector<float> > shumForm1::CentrVector(QVector<QVector<float> > image)
{
    QVector<QVector<float> >  complex_image;

    QVector<float > image_str, complex_image_str;
    float image_el, complex_image_el, complex_image_el_current;

    float icolor;

    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    int step;

    for (int i = 0; i < iheight; i++)
    {
        for(int j = 0; j < iwidth; j++)
        {
            image_str = image.at(i);
            image_el = image_str.at(j);

            step = one_with_N(i + j);
            icolor = image_el * step; qDebug() << "[CentrVector icolor] = " << icolor;

            complex_image_str.append(icolor);
        }
        complex_image.append(complex_image_str);
        complex_image_str.clear();

    }

    return complex_image;
}

QVector<QVector<float> > shumForm1::Warning_fix(QVector<QVector<float> > image)
{
    QVector<QVector<float> >  complex_image;

    QVector<float > image_str, complex_image_str;
    float image_el, complex_image_el, complex_image_el_current;

    int iwidth = this->imageWidth;
    int iheight = this->imageHeight;

    for (int i = 0; i < iheight; i++)
    {
        for(int j = iwidth - 1; j >= 0; j--)
        {
            image_str = image.at(i);
            image_el = image_str.at(j);

            complex_image_str.append(image_el);
        }
        complex_image.append(complex_image_str);
        complex_image_str.clear();

    }

    return complex_image;
}

float shumForm1::D_u_v(float u, float v, float iwidth, float iheight)
{
    float D = qSqrt( qPow(u - iwidth/2, 2) + qPow(v - iheight/2, 2)  );

    return D;
}

float shumForm1::H_u_v_ideal(float D0, float u, float v, float iwidth, float iheight)
{
    float D = D_u_v(u,v,iwidth,iheight); //qDebug() << "[!] D = " << D;
    float H;

    if ( D <= D0)
        H = 1;
    else
        H = 0;

    return H;
}

float shumForm1::H_u_v_gauss(float D0, float u, float v, float iwidth, float iheight)
{
    float D = D_u_v(u,v,iwidth,iheight); //qDebug() << "[!] D = " << D;
    float H;

    H = 1 - qExp(  - qPow(D, 2) / qPow(D0, 2) );

    return H;
}

float shumForm1::one_with_N(int n)
{
    float m;
    n = n % 2;
    /*Если остаток существует, то число нечетное*/
    if (n)
        m = -1;
    else
        m = 1;

    return m;
}

//D:\Obrazets\teatbwcut.bmp
/*Образец для вставки: D:\Obrazets\1test.bmp */
/*Образец для вставки: D:\Obrazets\1testcut.bmp */
void shumForm1::process_of_ideal_RGBsignal(QImage Ishodnoe, QImage RIshodnoe, QImage GIshodnoe, QImage BIshodnoe, float D0, int width, int height)
{
    imageWidth = width;
    imageHeight = height;

    qDebug() << "This is process_of_ideal_RGBsignal; D0=" << D0;

    /*Прямое*/
    QVector <QVector <float> > r = CentrImage(RIshodnoe, IMAGE_R); //() << r; //SeeImages(Ishodnoe, IMAGE_CLONE);
    QVector <QVector <complex <float> > > r_complex = PryamoeFurieStroki(r);
    QVector <QVector <complex <float> > > r_complex_1 = PryamoeFurieStolbtsyi(r_complex);

    QVector <QVector <float> > g = CentrImage(GIshodnoe, IMAGE_G); //qDebug() << g; //SeeImages(GIshodnoe, IMAGE_CLONE);
    QVector <QVector <complex <float> > > g_complex = PryamoeFurieStroki(g);
    QVector <QVector <complex <float> > > g_complex_1 = PryamoeFurieStolbtsyi(g_complex);

    QVector <QVector <float> > b = CentrImage(BIshodnoe, IMAGE_B); //qDebug() << r; //SeeImages(Ishodnoe, IMAGE_CLONE);
    QVector <QVector <complex <float> > > b_complex = PryamoeFurieStroki(b);
    QVector <QVector <complex <float> > > b_complex_1 = PryamoeFurieStolbtsyi(b_complex);

    /*Фильтрация*/
    /*D0 = 100;*/

    QVector<QVector<float> > r_mask = Mask(r, D0, Ideal);
    QVector<QVector<float> > g_mask = Mask(g, D0, Ideal);
    QVector<QVector<float> > b_mask = Mask(b, D0, Ideal);

    QVector <QVector <complex <float> > > r_G = idealFilterComplex(r_complex_1, r_mask);
    QVector <QVector <complex <float> > > g_G = idealFilterComplex(g_complex_1, g_mask);
    QVector <QVector <complex <float> > > b_G = idealFilterComplex(b_complex_1, b_mask);

    /*Обратное*/
    QVector <QVector <complex <float> > > r_obr = ObratnoyeFurieStolbtsyi(r_G);
    QVector <QVector <complex <float> > > r_obr_1 = ObratnoyeFurieStroki(r_obr);
    QVector <QVector <float> > r_obr_2 = RealVector(r_obr_1);
    QVector <QVector <float> > r_obr_3 = CentrVector(r_obr_2);

    QVector <QVector <complex <float> > > g_obr = ObratnoyeFurieStolbtsyi(g_G);
    QVector <QVector <complex <float> > > g_obr_1 = ObratnoyeFurieStroki(g_obr);
    QVector <QVector <float> > g_obr_2 = RealVector(g_obr_1);
    QVector <QVector <float> > g_obr_3 = CentrVector(g_obr_2);

    QVector <QVector <complex <float> > > b_obr = ObratnoyeFurieStolbtsyi(b_G);
    QVector <QVector <complex <float> > > b_obr_1 = ObratnoyeFurieStroki(b_obr);
    QVector <QVector <float> > b_obr_2 = RealVector(b_obr_1);
    QVector <QVector <float> > b_obr_3 = CentrVector(b_obr_2);

    /*Преобразование к виду, удобному для показа*/
    /*Прямое*/
    QVector <QVector <float> > r_after = toVectorF(r_complex_1); //qDebug() << r_after;
    QVector <QVector<float> > r_after_log = toVectorFlog(r_after); //qDebug() << r_after_log;
    QVector<QVector<float> > r_shkala = toVectorFshkala(r_after_log); //qDebug() << r_shkala;
    QVector<QVector<float> > r_G_sh = idealFilter(r_shkala, r_mask);

    QVector <QVector <float> > g_after = toVectorF(g_complex_1); //qDebug() << g_after;
    QVector <QVector<float> > g_after_log = toVectorFlog(g_after); //qDebug() << g_after_log;
    QVector<QVector<float> > g_shkala = toVectorFshkala(g_after_log); //qDebug() << g_shkala;
    QVector<QVector<float> > g_G_sh = idealFilter(g_shkala, g_mask);

    QVector <QVector <float> > b_after = toVectorF(b_complex_1); //qDebug() << b_after;
    QVector <QVector<float> > b_after_log = toVectorFlog(b_after); //qDebug() << b_after_log;
    QVector<QVector<float> > b_shkala = toVectorFshkala(b_after_log); //qDebug() << b_shkala;
    QVector<QVector<float> > b_G_sh = idealFilter(b_shkala, b_mask);

    /*Обратное*/
    QVector<QVector<float> > r_obr_shkala = toVectorFshkala(r_obr_3); //qDebug() << r_obr_shkala;
    QVector<QVector<float> > r_obr_shkala_1 = Warning_fix(r_obr_shkala);

    QVector<QVector<float> > g_obr_shkala = toVectorFshkala(g_obr_3); //qDebug() << r_obr_shkala;
    QVector<QVector<float> > g_obr_shkala_1 = Warning_fix(g_obr_shkala);

    QVector<QVector<float> > b_obr_shkala = toVectorFshkala(b_obr_3); //qDebug() << r_obr_shkala;
    QVector<QVector<float> > b_obr_shkala_1 = Warning_fix(b_obr_shkala);

    /*Преобразование некоторых изображений из массивов в картинки*/
    QImage RGB_SPEKTR = toStereoImage(r_shkala, g_shkala, b_shkala);
    QImage R_SPEKTR = toMonoImage(r_shkala, IMAGE_R);
    QImage G_SPEKTR = toMonoImage(g_shkala, IMAGE_G);
    QImage B_SPEKTR = toMonoImage(b_shkala, IMAGE_B);

    QImage RGB_FILTER = toStereoMask(r_mask, g_mask, b_mask);
    QImage R_FILTER = toMonoMask(r_mask, IMAGE_R);
    QImage G_FILTER = toMonoMask(g_mask, IMAGE_G);
    QImage B_FILTER = toMonoMask(b_mask, IMAGE_B);

    QImage RGB_G = toStereoImage(r_G_sh, g_G_sh, b_G_sh);
    QImage R_RG = toMonoImage(r_G_sh, IMAGE_R);
    QImage G_GG = toMonoImage(g_G_sh, IMAGE_G);
    QImage B_BG = toMonoImage(b_G_sh, IMAGE_B);

    QImage RGB_AFTER_FILTER = toStereoImage(r_obr_shkala_1, g_obr_shkala_1, b_obr_shkala_1);
    QImage R_AFTER_FILTER = toMonoImage(r_obr_shkala_1, IMAGE_R);
    QImage G_AFTER_FILTER = toMonoImage(g_obr_shkala_1, IMAGE_G);
    QImage B_AFTER_FILTER = toMonoImage(b_obr_shkala_1, IMAGE_B);


    /*Показать изображения*/
    SeeImages(Ishodnoe, IMAGE_CLONE);
    SeeImages(RIshodnoe, IMAGE_R);
    SeeImages(GIshodnoe, IMAGE_G);
    SeeImages(BIshodnoe, IMAGE_B);

    SeeImages(RGB_SPEKTR, IMAGE_SPEKTR);
    //SeeImages(R_SPEKTR, IMAGE_ST1);
    //SeeImages(G_SPEKTR, IMAGE_ST2);
    //SeeImages(B_SPEKTR, IMAGE_ST3);

    SeeImages(RGB_FILTER, IMAGE_CLONE1);
    //SeeImages(R_FILTER, IMAGE_ST1);
    //SeeImages(G_FILTER, IMAGE_ST2);
    //SeeImages(B_FILTER, IMAGE_ST3);

    SeeImages(RGB_G, IMAGE_ST1);
    //SeeImages(R_RG, IMAGE_ST1);
    //SeeImages(G_GG, IMAGE_ST2);
    //SeeImages(B_BG, IMAGE_ST3);

    SeeImages(RGB_AFTER_FILTER, IMAGE_ST2);
    //SeeImages(R_AFTER_FILTER, IMAGE_ST1);
    //SeeImages(G_AFTER_FILTER, IMAGE_ST2);
    //SeeImages(B_AFTER_FILTER, IMAGE_ST3);

    /*Сохранить изображения*/
    iImage.append(Ishodnoe);
    iImage.append(RIshodnoe);
    iImage.append(GIshodnoe);
    iImage.append(BIshodnoe);
    iImage.append(RGB_SPEKTR);
    iImage.append(RGB_FILTER);
    iImage.append(RGB_G);
    iImage.append(RGB_AFTER_FILTER);

    emit for_form2_signal(R_SPEKTR, G_SPEKTR, B_SPEKTR, R_FILTER, G_FILTER, B_FILTER, R_AFTER_FILTER, G_AFTER_FILTER, B_AFTER_FILTER);

    SF2->show();


}

void shumForm1::process_of_gauss_RGBsignal(QImage Ishodnoe, QImage RIshodnoe, QImage GIshodnoe, QImage BIshodnoe, float D0, int width, int height)
{
    imageWidth = width;
    imageHeight = height;

    qDebug() << "This is process_of_gauss_RGBsignal;";

    /*Прямое*/
    QVector <QVector <float> > r = CentrImage(RIshodnoe, IMAGE_R); //() << r; //SeeImages(Ishodnoe, IMAGE_CLONE);
    QVector <QVector <complex <float> > > r_complex = PryamoeFurieStroki(r);
    QVector <QVector <complex <float> > > r_complex_1 = PryamoeFurieStolbtsyi(r_complex);

    QVector <QVector <float> > g = CentrImage(GIshodnoe, IMAGE_G); //qDebug() << g; //SeeImages(GIshodnoe, IMAGE_CLONE);
    QVector <QVector <complex <float> > > g_complex = PryamoeFurieStroki(g);
    QVector <QVector <complex <float> > > g_complex_1 = PryamoeFurieStolbtsyi(g_complex);

    QVector <QVector <float> > b = CentrImage(BIshodnoe, IMAGE_B); //qDebug() << r; //SeeImages(Ishodnoe, IMAGE_CLONE);
    QVector <QVector <complex <float> > > b_complex = PryamoeFurieStroki(b);
    QVector <QVector <complex <float> > > b_complex_1 = PryamoeFurieStolbtsyi(b_complex);

    /*Фильтрация*/
    /*D0 = 100;*/

    QVector<QVector<float> > r_mask = Mask(r, D0, Gauss);
    QVector<QVector<float> > g_mask = Mask(g, D0, Gauss);
    QVector<QVector<float> > b_mask = Mask(b, D0, Gauss);

    QVector <QVector <complex <float> > > r_G = idealFilterComplex(r_complex_1, r_mask);
    QVector <QVector <complex <float> > > g_G = idealFilterComplex(g_complex_1, g_mask);
    QVector <QVector <complex <float> > > b_G = idealFilterComplex(b_complex_1, b_mask);

    /*Обратное*/
    QVector <QVector <complex <float> > > r_obr = ObratnoyeFurieStolbtsyi(r_G);
    QVector <QVector <complex <float> > > r_obr_1 = ObratnoyeFurieStroki(r_obr);
    QVector <QVector <float> > r_obr_2 = RealVector(r_obr_1);
    QVector <QVector <float> > r_obr_3 = CentrVector(r_obr_2);

    QVector <QVector <complex <float> > > g_obr = ObratnoyeFurieStolbtsyi(g_G);
    QVector <QVector <complex <float> > > g_obr_1 = ObratnoyeFurieStroki(g_obr);
    QVector <QVector <float> > g_obr_2 = RealVector(g_obr_1);
    QVector <QVector <float> > g_obr_3 = CentrVector(g_obr_2);

    QVector <QVector <complex <float> > > b_obr = ObratnoyeFurieStolbtsyi(b_G);
    QVector <QVector <complex <float> > > b_obr_1 = ObratnoyeFurieStroki(b_obr);
    QVector <QVector <float> > b_obr_2 = RealVector(b_obr_1);
    QVector <QVector <float> > b_obr_3 = CentrVector(b_obr_2);

    /*Преобразование к виду, удобному для показа*/
    /*Прямое*/
    QVector <QVector <float> > r_after = toVectorF(r_complex_1); //qDebug() << r_after;
    QVector <QVector<float> > r_after_log = toVectorFlog(r_after); //qDebug() << r_after_log;
    QVector<QVector<float> > r_shkala = toVectorFshkala(r_after_log); //qDebug() << r_shkala;
    QVector<QVector<float> > r_G_sh = idealFilter(r_shkala, r_mask);

    QVector <QVector <float> > g_after = toVectorF(g_complex_1); //qDebug() << g_after;
    QVector <QVector<float> > g_after_log = toVectorFlog(g_after); //qDebug() << g_after_log;
    QVector<QVector<float> > g_shkala = toVectorFshkala(g_after_log); //qDebug() << g_shkala;
    QVector<QVector<float> > g_G_sh = idealFilter(g_shkala, g_mask);

    QVector <QVector <float> > b_after = toVectorF(b_complex_1); //qDebug() << b_after;
    QVector <QVector<float> > b_after_log = toVectorFlog(b_after); //qDebug() << b_after_log;
    QVector<QVector<float> > b_shkala = toVectorFshkala(b_after_log); //qDebug() << b_shkala;
    QVector<QVector<float> > b_G_sh = idealFilter(b_shkala, b_mask);

    /*Обратное*/
    QVector<QVector<float> > r_obr_shkala = toVectorFshkala(r_obr_3); //qDebug() << r_obr_shkala;
    QVector<QVector<float> > r_obr_shkala_1 = Warning_fix(r_obr_shkala);

    QVector<QVector<float> > g_obr_shkala = toVectorFshkala(g_obr_3); //qDebug() << r_obr_shkala;
    QVector<QVector<float> > g_obr_shkala_1 = Warning_fix(g_obr_shkala);

    QVector<QVector<float> > b_obr_shkala = toVectorFshkala(b_obr_3); //qDebug() << r_obr_shkala;
    QVector<QVector<float> > b_obr_shkala_1 = Warning_fix(b_obr_shkala);

    /*Преобразование некоторых изображений из массивов в картинки*/
    QImage RGB_SPEKTR = toStereoImage(r_shkala, g_shkala, b_shkala);
    QImage R_SPEKTR = toMonoImage(r_shkala, IMAGE_R);
    QImage G_SPEKTR = toMonoImage(g_shkala, IMAGE_G);
    QImage B_SPEKTR = toMonoImage(b_shkala, IMAGE_B);

    QImage RGB_FILTER = toStereoMask(r_mask, g_mask, b_mask);
    QImage R_FILTER = toMonoMask(r_mask, IMAGE_R);
    QImage G_FILTER = toMonoMask(g_mask, IMAGE_G);
    QImage B_FILTER = toMonoMask(b_mask, IMAGE_B);

    QImage RGB_G = toStereoImage(r_G_sh, g_G_sh, b_G_sh);
    QImage R_RG = toMonoImage(r_G_sh, IMAGE_R);
    QImage G_GG = toMonoImage(g_G_sh, IMAGE_G);
    QImage B_BG = toMonoImage(b_G_sh, IMAGE_B);

    QImage RGB_AFTER_FILTER = toStereoImage(r_obr_shkala_1, g_obr_shkala_1, b_obr_shkala_1);
    QImage R_AFTER_FILTER = toMonoImage(r_obr_shkala_1, IMAGE_R);
    QImage G_AFTER_FILTER = toMonoImage(g_obr_shkala_1, IMAGE_G);
    QImage B_AFTER_FILTER = toMonoImage(b_obr_shkala_1, IMAGE_B);


    /*Показать изображения*/
    SeeImages(Ishodnoe, IMAGE_CLONE);
    SeeImages(RIshodnoe, IMAGE_R);
    SeeImages(GIshodnoe, IMAGE_G);
    SeeImages(BIshodnoe, IMAGE_B);

    SeeImages(RGB_SPEKTR, IMAGE_SPEKTR);
    //SeeImages(R_SPEKTR, IMAGE_ST1);
    //SeeImages(G_SPEKTR, IMAGE_ST2);
    //SeeImages(B_SPEKTR, IMAGE_ST3);

    SeeImages(RGB_FILTER, IMAGE_CLONE1);
    //SeeImages(R_FILTER, IMAGE_ST1);
    //SeeImages(G_FILTER, IMAGE_ST2);
    //SeeImages(B_FILTER, IMAGE_ST3);

    SeeImages(RGB_G, IMAGE_ST1);
    //SeeImages(R_RG, IMAGE_ST1);
    //SeeImages(G_GG, IMAGE_ST2);
    //SeeImages(B_BG, IMAGE_ST3);

    SeeImages(RGB_AFTER_FILTER, IMAGE_ST2);
    //SeeImages(R_AFTER_FILTER, IMAGE_ST1);
    //SeeImages(G_AFTER_FILTER, IMAGE_ST2);
    //SeeImages(B_AFTER_FILTER, IMAGE_ST3);

    /*Сохранить изображения*/
    iImage.append(Ishodnoe);
    iImage.append(RIshodnoe);
    iImage.append(GIshodnoe);
    iImage.append(BIshodnoe);
    iImage.append(RGB_SPEKTR);
    iImage.append(RGB_FILTER);
    iImage.append(RGB_G);
    iImage.append(RGB_AFTER_FILTER);

    emit for_form2_signal(R_SPEKTR, G_SPEKTR, B_SPEKTR, R_FILTER, G_FILTER, B_FILTER, R_AFTER_FILTER, G_AFTER_FILTER, B_AFTER_FILTER);

    SF2->show();
}

void shumForm1::saveImages(QString saveway)
{
    /*QString saveWay = ui->lineEdit->text();*/ qDebug() << "[] saveWay = " << saveway;

    QVector <bool> checkboxState;

    //Создание массива значение чекбоксов
    checkboxState.append(ui->checkBox->isChecked() );
    checkboxState.append(ui->checkBox_2->isChecked() );
    checkboxState.append(ui->checkBox_4->isChecked() );
    checkboxState.append(ui->checkBox_5->isChecked() );
    checkboxState.append(ui->checkBox_6->isChecked() );
    checkboxState.append(ui->checkBox_7->isChecked() );
    checkboxState.append(ui->checkBox_8->isChecked() );
    checkboxState.append(ui->checkBox_9->isChecked() );
    /*checkboxState.append(ui->checkBox_3->isChecked() );*/qDebug() << "[] Состояние чекбоксов = " << checkboxState;

    bool currentCheckbox = false;
    QString str = "AfterProgram-";
    QString currentStr, status;
    //Перебор массива и сохранение отмеченных картинок
    for (int i = 0; i < 8; i++)
    {
        currentCheckbox = checkboxState.at(i);
        if (currentCheckbox == true)
        {
            currentStr = saveway + str + QString::number(i) + ".bmp";
            iImage.at(i).save( currentStr, "BMP" );
            status = status + currentStr + "\n"; qDebug() << status;


        }
    }

    ui->label_15->setText(status);

    emit forSave_images(saveway);

    qDebug() << "Проверка, кнопка сохранения нажата!";
}
