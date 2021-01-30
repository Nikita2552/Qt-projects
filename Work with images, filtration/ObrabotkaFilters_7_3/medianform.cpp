#include "medianform.h"
#include "ui_medianform.h"
#include <QPainter>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QColor>
#include <QRandomGenerator>
#include <QImage>
#include <QtMath>
#include <QCheckBox>

medianForm::medianForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::medianForm)
{
    {
        ui->setupUi(this);

        //QPixmap pix("D:/Obrazets/1.bmp");
        //QImage image("D:/Obrazets/1.bmp");
        //ui->label->setPixmap(pix);

        //QPixmap pix = QPixmap->fromImage(pix);

        //QString fileName = "D:/Obrazets/1test.bmp";

          QString fileName = imageWay;

             if (!fileName.isEmpty())
             {
                 QImage image(fileName);

                 if (image.isNull())
                 {
                     qDebug() << "Error load image";
                 }

                 ui->label->setPixmap(QPixmap::fromImage(image));
                 iImage.append(image);

                 int iwidth = image.width(); qDebug() << "[ширина] width = " << iwidth;
                 int iheight = image.height(); qDebug() << "[высота] iheight = " << iheight;
                 int w,h;
                 int s = int(iwidth*iheight*0.1); qDebug() << "[процент зашумлённых точек от общего их количества] s = " << s;

                 //Создание объекта "Цвет пикселя".
                 QColor white = QColor(255,255,255,0);
                 QColor black = QColor(0,0,0,0);

                 //Создание объекта точка
                 QPoint p, q;
                 bool flag = true;

                 QImage clone_oneside = image;

                 if (noise_flag == false)
                 {
                 //однополярный шум
                 for (int i = 0; i < s; i++)
                   {
                         w = int (QRandomGenerator::global()->generateDouble() * iwidth); //qDebug() << "[Произвольное положение по w] w = " << w;
                         h = int (QRandomGenerator::global()->generateDouble() * iheight); //qDebug() << "[Произвольное положение по h] h = " << h;
                         p = QPoint(w, h);
                         clone_oneside.setPixelColor(p, white);
                   }
                 }
                 else
                 {
                 //двуполярный шум
                for (int i = 0; i < s; i++)
                   {
                        w = int (QRandomGenerator::global()->generateDouble() * iwidth); //qDebug() << "[Произвольное положение по w] w = " << w;
                        h = int (QRandomGenerator::global()->generateDouble() * iheight); //qDebug() << "[Произвольное положение по h] h = " << h;
                        p = QPoint(w, h);
                        if (flag == true)
                            {
                            clone_oneside.setPixelColor(p, black);
                            flag = false;
                            }
                        else
                            {
                            clone_oneside.setPixelColor(p, white);
                            flag = true;
                            }
                   }

                     qDebug() << "двуполярный шум" ;
                 }
                ui->label_2->setPixmap(QPixmap::fromImage(clone_oneside));
                iImage.append(clone_oneside);

                QColor iRgb, iredd, igreenn, ibluee;
                int ired, igreen, iblue;
                QImage clone_oneside_red = image;
                QImage clone_oneside_green = image;
                QImage clone_oneside_blue = image;

                for (int i = 0; i < iheight; i++)
                {
                    for(int j = 0; j < iwidth; j++)
                    {
                        p = QPoint(j, i);
                        iRgb = clone_oneside.pixelColor(p);

                        ired = iRgb.red(); //qDebug() << "[] ired = " << ired;
                        iredd = QColor(ired, 0, 0, 0);
                        clone_oneside_red.setPixelColor(p, iredd);

                        igreen = iRgb.green();
                        igreenn = QColor(0, igreen, 0, 0);
                        clone_oneside_green.setPixelColor(p, igreenn);

                        iblue = iRgb.blue();
                        ibluee = QColor(0, 0, iblue, 0);
                        clone_oneside_blue.setPixelColor(p, ibluee);
                    }
                }

                ui->label_4->setPixmap(QPixmap::fromImage(clone_oneside_red));
                ui->label_5->setPixmap(QPixmap::fromImage(clone_oneside_green));
                ui->label_6->setPixmap(QPixmap::fromImage(clone_oneside_blue));
                iImage.append(clone_oneside_red);
                iImage.append(clone_oneside_green);
                iImage.append(clone_oneside_blue);

                //Ширина маски
                int mask_width = imageMask;
                //Высота маски
                int mask_height = imageMask;
                //радиус маски (если квадратная)
                int mask_radius_width, mask_radius_height;
                //Начальные положения для прохода по маске
                int i0, j0;

                mask_radius_width = (mask_width - 1) / 2; qDebug() << "[] mask_radius_width = " << mask_radius_width;
                mask_radius_height = (mask_height - 1) / 2; qDebug() << "[] mask_radius_height = " << mask_radius_height;

                //Коэффициент сигма
                double sigma;
                //Значение пикселя в маске, определяемое по ширине и высоте маски
                double pix_mask_red, pix_mask_green, pix_mask_blue;
                double pix_mask_red_0, pix_mask_green_0, pix_mask_blue_0;
                double pix_mask_red_1, pix_mask_green_1, pix_mask_blue_1;

                //Для примера:
                mask_width = 3;
                mask_height = 3;
                sigma = imageSigma;

                pix_mask_red = 0;
                pix_mask_green = 0;
                pix_mask_blue = 0;
                pix_mask_red_0 = 0;
                pix_mask_green_0 = 0;
                pix_mask_blue_0 = 0;
                pix_mask_red_1 = 0;
                pix_mask_green_1 = 0;
                pix_mask_blue_1 = 0;

                //Перебор с формированием маски, создание обработанных одноканальных изображений
                for (int i = mask_radius_height; i < (iheight - mask_radius_height); i++) //mask_radius_height; i < (iheight - mask_radius_height + 1); i++)
                            {
                                for(int j = mask_radius_width; j < (iwidth - mask_radius_width); j++) //mask_radius_width; j < (iwidth - mask_radius_width + 1); j++)
                                {
                                p = QPoint(j, i);
                                i0 = i - mask_radius_height; //qDebug() << "[Координата начала маски] i0 = " << i0;
                                j0 = j - mask_radius_width; //qDebug() << "[Координата начала маски] j0 = " << j0;

                                for (int k = i0; k < (i0 + mask_height); k++) //i0; k < mask_height; k++)
                                {
                                    for(int m = j0; m < (j0 + mask_width); m++) //j0; m < mask_width; m++)
                                    {
                                        q = QPoint(m, k); //qDebug() << "[Точка] q = " << q;

                                        iRgb = clone_oneside_red.pixelColor(q); //qDebug() << "[!!!] iRgb.red() = " << double(iRgb.red()); //qDebug() << "[!!!] iRgb = " << iRgb;
                                        if (iRgb.red() > 0)
                                        {
                                            pix_mask_red_0 += qPow(double(iRgb.red()), sigma); //qDebug() << "[QQQ] pix_mask_red_0 = " << pix_mask_red_0;
                                            pix_mask_red_1 += qPow(double(iRgb.red()), sigma + 1); //qDebug() << "[QQQ] pix_mask_red_1 = " << pix_mask_red_1;
                                        }

                                        iRgb = clone_oneside_green.pixelColor(q); //qDebug() << "[!!!] iRgb.green() = " << iRgb.green();// qDebug() << "[!!!] iRgb = " << iRgb;
                                        if (iRgb.green() > 0)
                                        {
                                            pix_mask_green_0 += qPow(double(iRgb.green()), sigma);
                                            pix_mask_green_1 += qPow(double(iRgb.green()), sigma + 1);
                                        }

                                        iRgb = clone_oneside_blue.pixelColor(q);

                                        if (iRgb.blue() > 0)
                                        {
                                            pix_mask_blue_0 += qPow(double(iRgb.blue()), sigma);
                                            pix_mask_blue_1 += qPow(double(iRgb.blue()), sigma + 1);
                                         }
                                    }
                                }

                                pix_mask_red = pix_mask_red_1 / pix_mask_red_0; //qDebug() << "[Результирующее значение в маске] pix_mask_red_1 / pix_mask_red_0 = " << pix_mask_red_1
                                                                                         //<< pix_mask_red_0;
                                pix_mask_green = pix_mask_green_1 / pix_mask_green_0; //qDebug() << "[Результирующее значение в маске] pix_mask_green = " << pix_mask_green;
                                pix_mask_blue = pix_mask_blue_1 / pix_mask_blue_0; //qDebug() << "[Результирующее значение в маске] pix_mask_blue = " << pix_mask_blue;

                                //Добавление точки в одноканальные изображения
                                //qDebug() << "[1]";
                                if ((0 <= pix_mask_red) && (pix_mask_red <= 256))
                                {
                                    iredd = QColor(int(pix_mask_red), 0, 0, 0); //qDebug() << "[] iredd = " << iredd;
                                    clone_oneside_red.setPixelColor(p, iredd);
                                }
                                //qDebug() << "[2]";
                                if ((0 <= pix_mask_green) && (pix_mask_green <= 256))
                                {
                                    igreenn = QColor(0, int(pix_mask_green), 0, 0); //qDebug() << "[] igreenn = " << igreenn;
                                    clone_oneside_green.setPixelColor(p, igreenn);
                                }
                                //qDebug() << "[3]";
                                if ((0 <= pix_mask_blue) && (pix_mask_blue <= 256))
                                {
                                    ibluee = QColor(0, 0, int(pix_mask_blue), 0); //qDebug() << "[] ibluee = " << ibluee;
                                    clone_oneside_blue.setPixelColor(p, ibluee);
                                }

                                pix_mask_red = 0;
                                pix_mask_green = 0;
                                pix_mask_blue = 0;
                                pix_mask_red_0 = 0;
                                pix_mask_green_0 = 0;
                                pix_mask_blue_0 = 0;
                                pix_mask_red_1 = 0;
                                pix_mask_green_1 = 0;
                                pix_mask_blue_1 = 0;
                                }
                             }

                ui->label_7->setPixmap(QPixmap::fromImage(clone_oneside_red));
                ui->label_8->setPixmap(QPixmap::fromImage(clone_oneside_green));
                ui->label_9->setPixmap(QPixmap::fromImage(clone_oneside_blue));
                iImage.append(clone_oneside_red);
                iImage.append(clone_oneside_green);
                iImage.append(clone_oneside_blue);


                //Перебираем три созданных изображения для формирования результирующего цветного
                for (int i = 0; i < iheight; i++)
                {
                    for(int j = 0; j < iwidth; j++)
                    {
                        p = QPoint(j, i);

                        iredd = clone_oneside_red.pixelColor(p);
                        ired = iredd.red(); //qDebug() << "[] ired = " << ired;

                        igreenn = clone_oneside_green.pixelColor(p);
                        igreen = igreenn.green(); //qDebug() << "[] ired = " << ired;

                        ibluee = clone_oneside_blue.pixelColor(p);
                        iblue = ibluee.blue(); //qDebug() << "[] ired = " << ired;

                        iRgb = QColor(ired, igreen, iblue, 0);
                        clone_oneside.setPixelColor(p, iRgb);
                    }
                }

                ui->label_3->setPixmap(QPixmap::fromImage(clone_oneside));
                iImage.append(clone_oneside);

                //Отработав, функция посылает сигнал с параметрами для родительскому окна
                //emit signalBack(image);//, clone_oneside, clone_twosides);

              }

             connect(ui->pushButton, SIGNAL(clicked() ), this, SLOT(saveImages() ));


    }

    ShumForm::~ShumForm()
    {
        delete ui;
    }

    void ShumForm::saveImages()
    {
        QString saveWay = ui->lineEdit->text(); qDebug() << "[] saveWay = " << saveWay;

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
        checkboxState.append(ui->checkBox_3->isChecked() );qDebug() << "[] Состояние чекбоксов = " << checkboxState;

        bool currentCheckbox = false;
        QString str = "AfterProgram-";
        QString currentStr, status;
        //Перебор массива и сохранение отмеченных картинок
        for (int i = 0; i < 9; i++)
        {
            currentCheckbox = checkboxState.at(i);
            if (currentCheckbox == true)
            {
                currentStr = saveWay + str + QString::number(i) + ".bmp";
                iImage.at(i).save( currentStr, "BMP" );
                status = status + currentStr + "\n"; qDebug() << status;


            }
        }

        ui->label_15->setText(status);

        qDebug() << "Проверка, кнопка сохранения нажата!";

    }



medianForm::~medianForm()
{
    delete ui;
}
