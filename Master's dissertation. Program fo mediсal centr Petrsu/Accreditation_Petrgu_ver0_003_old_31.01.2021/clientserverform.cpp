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
/*
ClientForm * ClientServerForm::createClientForm(QMdiArea * mdi)
{
    this->CF = new ClientForm(mdi);

    return this->CF;
}

ServerForm * ClientServerForm::createServerForm(QMdiArea * mdi)
{
    this->SF = new ServerForm(mdi);

    return this->SF;
}

void ClientServerForm::openClientForm(QMdiSubWindow *subW)
{
    this->subCF = subW;
    //subW->show();
}

void ClientServerForm::openServerForm(QMdiSubWindow *subW)
{
    this->subSF = subW;
}
*/

void ClientServerForm::selectClientOfServerslot()
{
   qDebug() << "Нажата кнопка selectClientOfServerslot() ";

   bool ClientRole = ui->clientRole->isChecked();
   bool ServerRole = ui->serverRole->isChecked();

   emit openClientOrServer(ClientRole, ServerRole);

   /*Если нажата serverRole, и не нажата clientRole, то открываем окно Server*/
   //if ( (ui->clientRole->isChecked() == true) && (this->SF->isVisible() == false) )
   //{
   //    qDebug() << "Нажата clientRole ";
//
  //     this->CF->show();
  //     //emit openClient();
   //}
   /*Если наоборот, то окрываем Client*/
   /*Следует учесть, открыто ли уже одно из окон*/
   //else if  ( (ui->serverRole->isChecked() == true) && (this->CF->isVisible() == false) )
   //{
   //    qDebug() << "Нажата serverRole ";
//
  //     this->SF->show();
  //     //emit openServer();
  // }
}


