#include "clientform.h"
#include "ui_clientform.h"

ClientForm::ClientForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientForm)
{
    ui->setupUi(this);

    QVector <QString> ipOptions = CheckLabelsCS::localIpAddress();
    ui->label_6->setText(ipOptions[1]);

    /* Запуск сервера для принятия сообщений */
    this->MedServ = new QTcpServer();
    connect(this->MedServ, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ConnectDisconnectSlot()) );

    connect(this, SIGNAL(ToClientTimer(QString )), this, SLOT(ClientInterface(QString)) );

}

ClientForm::~ClientForm()
{
    delete ui;
}

void ClientForm::ClientInterface(QString parameters)
{
    qDebug() << "HELLO";

    QStringList param = parameters.split("_"); qDebug() << param;

    int number = param[0].toInt();

    switch (number)
    {
        case 1: /*Параметры от модуля воспроизведения звука*/
        {
            numCickles = param[2].toInt();
            qDebug() << "Начать воспроизведение, кол-во циклов = " << numCickles;

            if (numCickles == 0)
                emit StartTimer(numCickles);
            else
                emit StartTimerMany(numCickles);
            break;
        }
        case 2:
        {
            qDebug() << "Прервать воспроизведение";

            if (numCickles == 0)
               emit PauseTimer();
            else
                emit PauseTimerMany();
            break;
        }
        case 3:
        {
            qDebug() << "Возобновить воспроизведение";

            if (numCickles == 0)
               emit  UnpauseTimer();
            else
                emit  UnpauseTimerMany();
            break;
        }
        case 4:
        {
            qDebug() << "Закончить воспроизведение";

            if (numCickles == 0)
               emit  FinishTimer();
            else
                emit  FinishTimerMany();
            break;
        }
        case 5: /* параметры для модуля воспроиведения видео. Должен быть уже введён ip-адрес камеры */
        {
            qDebug() << "Включить/Отключить автоматический режим видеокамеры [0 - выкл, 1 - вкл] ";// << parameter[1];
            emit setAutomateSignal(param[2]);
            break;
        }        
    }
}

void ClientForm::ConnectDisconnectSlot()
{
    QString Status;
    /* Создать соединение, либо прекратить соединение */
    if (this->connectFlag == false)
    {
        qDebug() << "Создать соединение";

        //int portMaster;
        //static qint32 ipAdressMaster;

        //this->inputPort = ui->inputPort->text().toInt();
        //this->outputPort = ui->outputPort->text().toInt();
        //qDebug() << "inputPort = " << this->inputPort << "outputPort = " << this->outputPort;
        /*Поместить строки таблицы в массив векторов*/
        //this->ipAdressesArray.clear();
        //getIPtabletoArray(this->count);

        /*Считать данные из полей*/
        /*Проверить данные на правильность*/
        /*Вставить данные в нужные переменные*/

        bool checkFlag = checkLineEdits(); qDebug() << "checkFlag = " << checkFlag;

        if (checkFlag == true)
        {
            //const QString ipAdressMaster = "192.168.1.101";
            //quint16 portMaster = 4242;

            QHostAddress QHostAddr;
            //QHostAddr.setAddress(ipAdressMaster);

            /*Запуск сервера на прослушивание */
            bool startServerFlag = this->MedServ->listen(QHostAddress(ui->label_6->text()), ui->inputPort->text().toInt()); //2  *QHostAddr, portMaster
           // bool startServerFlag = this->MedServ->listen(QHostAddress::Any, 4242); //2  *QHostAddr, portMaster

            if (startServerFlag == true)
            {
                Status = "Клиент запущен"; qDebug() << Status;
                ui->label_3->setText(Status);
                this->connectFlag = true;
            }
            else
            {
                Status = "Ошибка запуска клиента"; qDebug() << Status;
                ui->label_3->setText(Status);
                this->connectFlag = false;
            }
        }
        else
        {
            Status = "Ошибка ввода"; qDebug() << Status;
            ui->label_3->setText(Status);
            this->connectFlag = false;
        }
    }
    else {
    qDebug() << "Прекратить соединение";

    /*Закрытие сервера от прослушивание */
    this->MedServ->close();

    Status = "Отключён"; qDebug() << Status;
    ui->label_3->setText(Status);
    this->connectFlag = false;
    }
}

void ClientForm::onNewConnection()
{
    qDebug() << "Произошёл коннект!";

    /* Создание соккета для отправки или получения сообщений */
    this->MedSock = this->MedServ->nextPendingConnection();
    /* Даём возможность читать из соккета */
    connect(this->MedSock, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(this->MedSock, SIGNAL(disconnected()), this, SLOT(slotClientDisconnected()));
}

void ClientForm::onReadyRead()
{
    qDebug() << "Чтение!";

    while (this->MedSock->bytesAvailable()>0)
        {
            QString str = this->MedSock->readAll();
            str = str.simplified();

            QByteArray array;
            array.append(str);

            //this->MedSock->write(array);
            qDebug() << str;

            ui->textEdit->append(str);

            emit ToClientTimer(str);
    }
}

void ClientForm::slotClientDisconnected()
{
     this->MedSock->close();
}

bool ClientForm::checkLineEdits()
{
    bool flag;
    this->inputData.clear();

// Правильно ли введен ip
// Правильно ли введён вх порт
// Правильно ли введён вых порт
// Всё ли заполнено?
  QString test0 = ui->ipAddress->text(); qDebug() << "test0 = " << test0;
  bool testVector0 = CheckLabelsCS::corrIpSplit(test0); qDebug() << "testVector0 = " << testVector0;

  QString test1 = ui->outputPort->text(); qDebug() << "test1 = " << test1;
  bool testVector1 = CheckLabelsCS::corrPortSplit(test1); qDebug() << "testVector1 = " << testVector1;

  QString test2 = ui->inputPort->text(); qDebug() << "test2 = " << test2;
  bool testVector2 = CheckLabelsCS::corrPortSplit(test2); qDebug() << "testVector2 = " << testVector2;

  if ( (testVector0 == true) && (testVector1 == true) && (testVector2 == true) )
  {
      this->inputData.push_back(test0);
      this->inputData.push_back(test1);
      this->inputData.push_back(test2);
      qDebug() << this->inputData;

      flag = true;
  }
  else
  {
      this->inputData.clear();

      flag = false;
  }

  return flag;
}
