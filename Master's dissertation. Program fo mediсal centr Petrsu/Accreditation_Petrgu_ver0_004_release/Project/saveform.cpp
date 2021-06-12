#include "saveform.h"
#include "ui_saveform.h"
#include <QDebug>

saveForm::saveForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::saveForm)
{
    ui->setupUi(this);

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveSlot()) );
    connect(ui->downButton, SIGNAL(clicked()), this, SLOT(downSlot()) );

    //??? Каков источник при получении параметров из родительского окна?
    //Дочернее окно ничего не знает о родительском. Ему нужно передать ссылку на дочернее окно!
    //connect( parentWidget(), SIGNAL(statusDSsignal(QString)), this, SLOT(statusSlot(QString)) );
}

saveForm::~saveForm()
{
    delete ui;
}

QString saveForm::dsEditOut ()
{
    //Получить строчку из текстового поля Wayline
    QString text1 = ui -> dsEdit -> text();
    return text1;
}

void saveForm::saveSlot()
{
    QString saveWay;

    saveWay = dsEditOut (); qDebug() << "HI FTHREE!";

    emit saveSignal(saveWay);
}

void saveForm::downSlot()
{
    QString downWay;

    downWay = dsEditOut ();

    emit downSignal(downWay);
}

void saveForm::statusSlot(QString status)
{
    ui->statusLabel->setText(status);
}
