#include "videoregistratorform.h"
#include "ui_videoregistratorform.h"

VideoRegistratorForm::VideoRegistratorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoRegistratorForm)
{
    ui->setupUi(this);
}

VideoRegistratorForm::~VideoRegistratorForm()
{
    delete ui;
}
