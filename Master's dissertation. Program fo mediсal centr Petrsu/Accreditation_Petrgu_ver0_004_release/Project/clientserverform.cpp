#include "clientserverform.h"
#include "ui_clientserverform.h"

ClientServerForm::ClientServerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientServerForm)
{
    ui->setupUi(this);

    //CF = new ClientForm();
    //SF = new ServerForm();

    connect(ui->selectRole, SIGNAL(clicked()), this, SLOT(selectClientOfServerslot()) );
}

ClientServerForm::~ClientServerForm()
{
    delete ui;
}

void ClientServerForm::selectClientOfServerslot()
{
   qDebug() << "Нажата кнопка selectClientOfServerslot() ";

   bool ClientRole = ui->clientRole->isChecked();
   bool ServerRole = ui->serverRole->isChecked();

   emit openClientOrServer(ClientRole, ServerRole);   
}


