#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <shumform.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(UniImage()) );
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(BiImage()) );

    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(MedUniImage()) );
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(MedBiImage()) );

    //connect(SF1, SIGNAL(signalBack(QImage) ), this, SLOT(BackFromSignalShum(QImage) ));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UniImage()
{
    qDebug() << "ShumImage";

    QString imageWay = ui->lineEdit->text(); qDebug() << "imageWay = " << imageWay;
    QString imageSigma1 = ui->lineEdit_2->text(); //qDebug() << "imageSigma = " << imageSigma1;
    QString imageMask1 = ui->lineEdit_3->text(); //qDebug() << "imageMask = " << imageMask1;

    double imageSigma = imageSigma1.toDouble(); qDebug() << "imageSigma = " << imageSigma;
    int imageMask = imageMask1.toInt(); qDebug() << "imageMask = " << imageMask;
    bool flag = false; //???
    bool flag1 = false; //???

    //Присвоение адреса объекта дочернего окна ссылке
    SF1 = new ShumForm(nullptr, imageWay, imageSigma, imageMask, flag, flag1);

    SF1->show();

}


void MainWindow::BiImage()
{
    qDebug() << "BiImage";

    QString imageWay = ui->lineEdit->text(); qDebug() << "imageWay = " << imageWay;
    QString imageSigma1 = ui->lineEdit_2->text(); //qDebug() << "imageSigma = " << imageSigma1;
    QString imageMask1 = ui->lineEdit_3->text(); //qDebug() << "imageMask = " << imageMask1;

    double imageSigma = imageSigma1.toDouble(); qDebug() << "imageSigma = " << imageSigma;
    int imageMask = imageMask1.toInt(); qDebug() << "imageMask = " << imageMask;
    bool flag = true; //???
    bool flag1 = false; //Включение фильтра среднего контргармонического

    //Присвоение адреса объекта дочернего окна ссылке
    SF1 = new ShumForm(nullptr, imageWay, imageSigma, imageMask, flag, flag1);

    SF1->show();
}

void MainWindow::MedUniImage()
{
    qDebug() << "MedUniImage";

    QString imageWay = ui->lineEdit->text(); qDebug() << "imageWay = " << imageWay;
    QString imageMask1 = ui->lineEdit_4->text(); //qDebug() << "Med imageMask = " << imageMask1;

    double imageSigma = 0; //imageSigma1.toDouble(); qDebug() << "imageSigma = " << imageSigma;
    int imageMask = imageMask1.toInt(); qDebug() << "imageMask = " << imageMask;
    bool flag = false; //???
    bool flag1 = true; //Включение медианного фильтра

    //Присвоение адреса объекта дочернего окна ссылке
    SF1 = new ShumForm(nullptr, imageWay, imageSigma, imageMask, flag, flag1);

    SF1->show();

}

void MainWindow::MedBiImage()
{
    qDebug() << "MedUniImage";

    QString imageWay = ui->lineEdit->text(); qDebug() << "imageWay = " << imageWay;
    QString imageMask1 = ui->lineEdit_4->text(); //qDebug() << "Med imageMask = " << imageMask1;

    double imageSigma = 0; //imageSigma1.toDouble(); qDebug() << "imageSigma = " << imageSigma;
    int imageMask = imageMask1.toInt(); qDebug() << "imageMask = " << imageMask;
    bool flag = true;  //???
    bool flag1 = true; //Включение медианного фильтра

    //Присвоение адреса объекта дочернего окна ссылке
    SF1 = new ShumForm(nullptr, imageWay, imageSigma, imageMask, flag, flag1);

    SF1->show();
}
/*
void MainWindow::NonShumImage()
{
    qDebug() << "NonShumImage";
}


void MainWindow::BackFromSignalShum(QImage Ishodnoe2)//, QImage Zashumlennoye_one2, QImage Zashumlennoye_two2)
{
    Ishodnoe = Ishodnoe2; qDebug() << "Ishodnoe - сохранено!";
    Zashumlennoye_one = Zashumlennoye_one2; qDebug() << "Zashumlennoye_one - сохранено!";
    Zashumlennoye_two = Zashumlennoye_two2; qDebug() << "Zashumlennoye_two - сохранено!";
}

void MainWindow::testslot()
{

}

*/
