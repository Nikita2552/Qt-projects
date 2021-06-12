#include "serverform.h"
#include "ui_serverform.h"

ServerForm::ServerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerForm)
{
    ui->setupUi(this);

    tableInit(this->count);

    QVector <QString> ipOptions = CheckLabelsCS::localIpAddress();
    ui->label_4->setText(ipOptions[1]);

    connect(ui->conndisconButton, SIGNAL(clicked()), this, SLOT(ConnectDisconnectSlot()) );
    connect(ui->testButton, SIGNAL(clicked()), this, SLOT(TestSlot()) );
    connect(this, SIGNAL(TransmitterSignal(int, QString, QVector <QString>)), this, SLOT(TransmitterSlot(int, QString, QVector <QString>)) );
}

ServerForm::~ServerForm()
{
    delete ui;
}

void ServerForm::tableInit(int rowcount)
{
    // Указываем число колонок
    int columncount = 3;
    ui->tableIPadress->setColumnCount(columncount);
    // Указываем число строк
    ui->tableIPadress->setRowCount(rowcount);
    // Устанавливаем заголовки колонок
    QStringList headers;
    headers << "IP-адрес" << "Порт" << "Управлять";
    ui->tableIPadress->setHorizontalHeaderLabels(headers);
    // Включаем сетку
    ui->tableIPadress->setShowGrid(true);
    // Разрешаем выделение только одного элемента. ??? Смотреть доки
    //ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tableIPadress->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->tableIPadress->horizontalHeader()->setStretchLastSection(true);
    // Скрываем колонку под номером 5
    //ui->tableWidget->hideColumn(4);
    //Запрет редактирования строк
    //ui->tableIPadress->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // выделяем память под все ячейки таблицы
    for(int row = 0; row < rowcount; row++)
    {
      for(int column = 0; column < columncount; column++)
      {
          ui->tableIPadress->setItem(row, column, new QTableWidgetItem());

          if (column == columncount - 1)
          {
              //Создание объекта чекбокс
              QTableWidgetItem *itemcheck = new QTableWidgetItem();
              //Установка чекбокса в состояние "не нажат"
              itemcheck->setCheckState(Qt::Checked); //Unchecked);
              //Добавление чекбокса в таблицу
              ui->tableIPadress->setItem(row, column, itemcheck);
          }

      }
    }
}

void ServerForm::getIPtabletoArray(int count)
{
    QVector <QString> strItem;
    int rowcount = 32;

    for(int row = 0; row < rowcount; row++)
    {
      // Правльно ли введен ip
      // Правильно ли введён вх порт
      // Правильно ли введён вых порт
      // Всё ли заполнено?
        QString test0 = ui->tableIPadress->item(row, 0)->text(); qDebug() << "test0 = " << test0;
        bool testVector0 = CheckLabelsCS::corrIpSplit(test0); qDebug() << "testVector0 = " << testVector0;

        QString test1 = ui->tableIPadress->item(row, 1)->text(); qDebug() << "test1 = " << test1;
        bool testVector1 = CheckLabelsCS::corrPortSplit(test1); qDebug() << "testVector1 = " << testVector1;

        bool testVector2 = ui->tableIPadress->item(row, 2)->checkState();

        if ( (testVector0 == true) && (testVector1 == true) && (testVector2 == true) )
        {
            strItem.push_back(test0);
            strItem.push_back(test1);

            this->ipAdressesArray.push_back(strItem);
          //qDebug() << strItem;
        }
        strItem.clear();
    }
    qDebug() << this->ipAdressesArray;

}

void ServerForm::setVectorSockets()
{
       qDebug() << "Открываются соответствующие сокеты!";

       int ipCount = this->ipAdressesArray.count();
       QVector <QString> currentStr;

       for (int i = 0; i < ipCount; i++)
       {
           QTcpSocket *newSock = new QTcpSocket();

           currentStr = this->ipAdressesArray[i]; qDebug() << currentStr;

           newSock->connectToHost(currentStr[0], currentStr[1].toInt()); /* Соединение соккетов из таблицы с хостами */

           if (newSock->waitForConnected(1000))
           {
            this->MedSock.push_back(newSock);
           //this->MedSock.append(new QTcpSocket());
            qDebug() << "Коннект создан";
           }
           else
           {
             qDebug() << "Коннект не создан";
           }
       }
}

void ServerForm::closeConnections()
{
    int ipCount = this->MedSock.count();

    for (int i = 0; i < ipCount; i++)
    {
        this->MedSock[i]->close();
    }

    this->MedSock.clear();
}

void ServerForm::ConnectDisconnectSlot()
{
    /* Создать соединение, либо прекратить соединение */
    if (this->connectFlag == false)
    {
    qDebug() << "Создать соединение";

    this->outputPort = ui->outputPort->text().toInt();
    qDebug() << "outputPort = " << this->outputPort;

    /*Поместить строки таблицы в вектор адресов*/
    this->ipAdressesArray.clear();
    getIPtabletoArray(this->count);

    /*Заполнить массив сокетов открытыми сокетами из созданного вектора адресов*/
    setVectorSockets();

    this->connectFlag = true;
    }
    else {
    qDebug() << "Прекратить соединение";
    this->connectFlag = false;
    closeConnections();
    }
}

void ServerForm::ServerInterface(int number, QVector <QString> parameters)
{
    QString status;

    //LogFile newLog;

    switch (number)
    {
        case 6: /*Параметры от модуля воспроизведения звука*/
        {
            qDebug() << "Сообщение!!!";
            status = "Воспроизведение сообщения";

            int count = parameters.count();

            QString strParameters = parameters[0] + "<<";

            if (count == 3) /* временный костыль, требует более красивого решения */
                strParameters += parameters[2];

            strParameters += ">>" + parameters[1];

            bool debugflag = this->newLog.WriteStrInLog(strParameters);
            break;
        }
        case 1:
        {
            qDebug() << "Начать воспроизведение";
            status = "Начало цикла вопроизведения сообщений";
            QString nameLog = this->newLog.CreateNameOfLog(); qDebug() << "nameLog = " << nameLog;
            this->newLog.InitLogFile("./LOGFILES/" + nameLog + ".txt"); //Не создаёт файл!!!
            bool debugflag = this->newLog.WriteStrInLog("Role: Server");
            bool debugflag1 = this->newLog.WriteStrInLog("ip-address: 0.0.0.0");
            bool debugflag2 = this->newLog.WriteStrInLog("camera ip-address: 0.0.0.0");
            bool debugflag3 = this->newLog.WriteStrInLog("");
            bool debugflag4 = this->newLog.WriteStrInLog(parameters[0] + "<<" + status + ">>" + parameters[1]);
            break;
        }
        case 2:
        {
            qDebug() << "Прервать воспроизведение";
            status = "Прерывание цикла вопроизведения сообщений";
            bool debugflag = this->newLog.WriteStrInLog(parameters[0] + "<<" + status + ">>" + parameters[1]);
            break;
        }
        case 3:
        {
            qDebug() << "Продолжить воспроизведение";
            status = "Продолжение цикла вопроизведения сообщений";
            bool debugflag = this->newLog.WriteStrInLog(parameters[0] + "<<" + status + ">>" + parameters[1]);
            break;
        }
        case 4: /* параметры для модуля воспроиведения видео. Должен быть уже введён ip-адрес камеры */
        {
            qDebug() << "Прекратить вопроизведение";
            status = "Прекращение цикла вопроизведения сообщений";
            bool debugflag = this->newLog.WriteStrInLog(parameters[0] + "<<" + status + ">>" + parameters[1]);
            break;
        }
        case 5: /* параметры для модуля воспроиведения видео. Должен быть уже введён ip-адрес камеры */
        {
            qDebug() << "Включить автоматику = " << parameters[0];

            status = "Включение автоматики для распознавания лиц";

            if (parameters[0] == "true")
                status += ": включено";
            else
                status += ": выключено";

            bool debugflag = this->newLog.WriteStrInLog("-<<" + status);
            break;
        }
    }

    emit TransmitterSignal(number, status, parameters);
}

void ServerForm::TestSlot()
{
        qDebug() << "Отправка тестового сообщения";

        QString str = "Тестовое сообщение"; qDebug() << str;

        QByteArray array;
        array.append(str);

        int socketCount = this->MedSock.count(); qDebug() << socketCount;

        if (socketCount > 0)
        {
            for (int i = 0; i < socketCount; i++)
            {
                this->MedSock[i]->write(array); qDebug() << "!!!"; /* Выслать сообщение всем адресатам в таблице */
            }

            ui->textEdit->append(str);
         }
}

void ServerForm::TransmitterSlot(int number, QString status, QVector<QString> parameters)
{
    qDebug() << "Отправка сообщений из таблицы адресов";

    QByteArray array;

    array.append(QString::number(number)+"_");
    array.append(status+"_");

    int countParameters = parameters.count();

    //status = status + " ";

    for (int i = 0; i < countParameters; i++)
    {
        array.append(parameters[i]+"_");
        status = status + +"_" + parameters[i];
    }

    qDebug() << "[TransmitterSlot] " + status;

    //QString str = "Тестовое сообщение1"; qDebug() << str;

    int socketCount = this->MedSock.count(); qDebug() << "[TransmitterSlot] " << socketCount;

    if (socketCount > 0)
    {
        for (int i = 0; i < socketCount; i++)
        {
            this->MedSock[i]->write(array); //Выслать сообщение всем адресатам в таблице
        }

        ui->textEdit->append(status);
     }
}
