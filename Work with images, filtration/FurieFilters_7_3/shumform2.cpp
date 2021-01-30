#include "shumform2.h"
#include "ui_shumform2.h"
#include <QDebug>

shumForm2::shumForm2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shumForm2)
{
    ui->setupUi(this);
}

shumForm2::~shumForm2()
{
    delete ui;
}

void shumForm2::SeeImages(QImage image, shumForm2::Images im)
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

void shumForm2::process_for_seen_images(QImage R_SPEKTR, QImage G_SPEKTR, QImage B_SPEKTR, QImage R_FILTER, QImage G_FILTER, QImage B_FILTER, QImage R_RG, QImage G_RG, QImage B_RG)
{
    qDebug() << "show images!!!";

    SeeImages(R_SPEKTR, IMAGE_CLONE);
    SeeImages(G_SPEKTR, IMAGE_SPEKTR);
    SeeImages(B_SPEKTR, IMAGE_CLONE1);

    SeeImages(R_FILTER, IMAGE_R);
    SeeImages(G_FILTER, IMAGE_G);
    SeeImages(B_FILTER, IMAGE_B);

    SeeImages(R_RG, IMAGE_ST1);
    SeeImages(G_RG, IMAGE_ST2);
    SeeImages(B_RG, IMAGE_ST3);

    /*Сохранить изображения*/
    iImage.append(R_SPEKTR);
    iImage.append(G_SPEKTR);
    iImage.append(B_SPEKTR);
    iImage.append(R_FILTER);
    iImage.append(G_FILTER);
    iImage.append(B_FILTER);
    iImage.append(R_RG);
    iImage.append(G_RG);
    iImage.append(B_RG);


}

void shumForm2::saveImages(QString saveway)
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
            currentStr = saveway + str + QString::number(i + 9) + ".bmp";
            iImage.at(i).save( currentStr, "BMP" );
            status = status + currentStr + "\n"; qDebug() << status;


        }
    }

    ui->label_15->setText(status);

    qDebug() << "Проверка, кнопка сохранения нажата!";

}
