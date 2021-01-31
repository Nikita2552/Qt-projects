#include "clientserverform_old.h"
#include "ui_clientserverform.h"

ClientServerForm::ClientServerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientServerForm)
{
    ui->setupUi(this);
}

ClientServerForm::~ClientServerForm()
{
    delete ui;
}
