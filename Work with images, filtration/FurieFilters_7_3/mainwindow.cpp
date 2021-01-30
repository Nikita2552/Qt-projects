#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <shumform1.h>
#include <shumform2.h>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Присвоение адреса объекта дочернего окна ссылке
    SF1 = new shumForm1();

    /*Коннекты*/
    connect(ui->pushButton, SIGNAL(clicked() ), this, SLOT(IdealSlot() ) );
    connect(ui->pushButton_2, SIGNAL(clicked() ), this, SLOT(GaussSlot() ) );

    connect(this, SIGNAL(forRGB_ideal_signal() ), this, SLOT(showRGBVariablesForIdeal() ) );
    connect(this, SIGNAL(RGB_ideal_signal(QImage, QImage, QImage, QImage, float, int, int) ), SF1, SLOT(process_of_ideal_RGBsignal(QImage, QImage, QImage, QImage, float, int, int) ) );

    connect(this, SIGNAL(forRGB_gauss_signal() ), this, SLOT(showRGBVariablesForGauss() ) );
    connect(this, SIGNAL(RGB_gauss_signal(QImage, QImage, QImage, QImage, float, int, int) ), SF1, SLOT(process_of_gauss_RGBsignal(QImage, QImage, QImage, QImage, float, int, int) ) );

    connect(ui->pushButton_3, SIGNAL( clicked() ), this, SLOT( saveText() ) );
    connect(this, SIGNAL( forSave_images(QString) ), SF1, SLOT( saveImages(QString) ) );
    /*--*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveText()
{
    QString saveway = ui->lineEdit_3->text();

    emit forSave_images(saveway);
}

/*Создание объекта "Исходное изображение"*/
void MainWindow::CreateIshodnoe()
{
   qDebug() << "This is CreateIshodnoe();";

   QString imageWay = ui->lineEdit->text(); qDebug() << "imageWay = " << imageWay;
   QString mask = ui->lineEdit_2->text(); qDebug() << "mask = " << mask;

/*Проверка пуста ли картинка, и её загрузка. Образец для вставки: D:\Obrazets\1test.bmp */
   if (!imageWay.isEmpty())
   {
       QImage image(imageWay);

       if (image.isNull())
       {
           qDebug() << "Error load image";
       }
       else
       {
           qDebug() << "Sucsessfull load image";
           Ishodnoe = image;
           iwidth = image.width();
           iheight = image.height();
       }
  }

   /*Проверка пуста ли картинка, и её загрузка. Образец для вставки: D:\Obrazets\1test.bmp */
      if (!mask.isEmpty())
      {
          qDebug() << "Sucsessfull load mask";
          D0 = mask.toFloat();
      }
      else
      {
          qDebug() << "Error load mask";
      }


}

/* Разбиение изображения на каналы*/
void MainWindow::CreateGRB(Colors color)
{
    int iwidth = Ishodnoe.width(); qDebug() << "[ширина] width = " << iwidth;
    int iheight = Ishodnoe.height(); qDebug() << "[высота] iheight = " << iheight;

    //Создание объекта точка
    QPoint p;

    QColor iRgb, iclonee;
    int ired, igreen, iblue;
    QImage clone_oneside = Ishodnoe;
    QImage clone_oneside_clone = Ishodnoe;

    switch (color)
    {
        case COLOR_R:
            qDebug() << "chosed R";

            for (int i = 0; i < iheight; i++)
            {
                for(int j = 0; j < iwidth; j++)
                {
                    p = QPoint(j, i);
                    iRgb = clone_oneside.pixelColor(p);

                    ired = iRgb.red(); //qDebug() << "[] ired = " << ired;
                    iclonee = QColor(ired, 0, 0, 0);
                    clone_oneside_clone.setPixelColor(p, iclonee);

                }
            }

            RIshodnoe = clone_oneside_clone;
            qDebug() << "Created RIshodnoe";

            break;
        case COLOR_G:
            qDebug() << "chosed G";

            for (int i = 0; i < iheight; i++)
            {
                for(int j = 0; j < iwidth; j++)
                {
                    p = QPoint(j, i);
                    iRgb = clone_oneside.pixelColor(p);

                    igreen = iRgb.green();
                    iclonee = QColor(0, igreen, 0, 0);
                    clone_oneside_clone.setPixelColor(p, iclonee);

                }
            }

            GIshodnoe = clone_oneside_clone;
            qDebug() << "Created GIshodnoe";

            break;
        case COLOR_B:
            qDebug() << "chosed B";

            for (int i = 0; i < iheight; i++)
            {
                for(int j = 0; j < iwidth; j++)
                {
                    p = QPoint(j, i);
                    iRgb = clone_oneside.pixelColor(p);

                    iblue = iRgb.blue();
                    iclonee = QColor(0, 0, iblue, 0);
                    clone_oneside_clone.setPixelColor(p, iclonee);
                }
            }

            BIshodnoe = clone_oneside_clone;
            qDebug() << "Created BIshodnoe";

            break;
    }
}

void MainWindow::CreateImages()
{
    CreateIshodnoe();

    CreateGRB(COLOR_R);
    CreateGRB(COLOR_G);
    CreateGRB(COLOR_B);
}

void MainWindow::IdealSlot()
{
    qDebug() << "This is IdeaSlot();";

    CreateImages();

    SF1->show();

    emit forRGB_ideal_signal();
}

void MainWindow::GaussSlot()
{
    qDebug() << "This is GaussSlot();";

    CreateImages();

    SF1->show();

    emit forRGB_gauss_signal();


}

void MainWindow::showRGBVariablesForIdeal()
{
    qDebug() << "This is showRGBVariablesForIdeal;";

    QImage Ishodnoe1 = this->Ishodnoe;

    QImage RIshodnoe1 = this->RIshodnoe;
    QImage GIshodnoe1 = this->GIshodnoe;
    QImage BIshodnoe1 = this->BIshodnoe;

    float D0 = this->D0;
    int width = this->iwidth;
    int height = this->iheight;

    emit RGB_ideal_signal(Ishodnoe1, RIshodnoe1, GIshodnoe1, BIshodnoe1, D0, width, height);
}

void MainWindow::showRGBVariablesForGauss()
{
    qDebug() << "This is showRGBVariablesForGauss;";

    QImage Ishodnoe1 = this->Ishodnoe;

    QImage RIshodnoe1 = this->RIshodnoe;
    QImage GIshodnoe1 = this->GIshodnoe;
    QImage BIshodnoe1 = this->BIshodnoe;

    float D0 = this->D0;
    int width = this->iwidth;
    int height = this->iheight;

    emit RGB_gauss_signal(Ishodnoe1, RIshodnoe1, GIshodnoe1, BIshodnoe1, D0, width, height);
}
