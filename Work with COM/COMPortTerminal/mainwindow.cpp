#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    /*
    serial->setPortName("com4");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open((QIODevice::ReadWrite));
    serial->write("Привет!");
    */

    programInit();

    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(StartOrStopConnectSlot()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(serialTransmit()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(cleanTerminal()));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete serial;
}

void MainWindow::StartOrStopConnectSlot()
{
    if (ConnectFlag == false)
    {
        QString ComName = ui->lineEdit->text();

        if ((ComName != "" ) && (this->ComPorts.indexOf(ComName) > -1))
        {
            qDebug() << "Название порта: " << ComName;
            serial->setPortName(ComName);
        }

        bool ComSpeed = ui->radioButton->isChecked();

        if (ComSpeed == true)
        {
            qDebug() << "Скорость: 9600";
            serial->setBaudRate(QSerialPort::Baud9600);
        }

        bool NumberOfBits = ui->radioButton->isChecked();

        if (NumberOfBits == true)
        {
            qDebug() << "Количество бит в посылке: 8";
            serial->setDataBits(QSerialPort::Data8);
        }

        bool Polarity = ui->radioButton->isChecked();

        if (Polarity == true)
        {
            qDebug() << "Чётность: no";
            serial->setParity(QSerialPort::NoParity);
        }

        bool NumberOfStopbits = ui->radioButton->isChecked();

        if (NumberOfStopbits == true)
        {
           qDebug() << "Количество стоп-бит: 1";
           serial->setStopBits(QSerialPort::OneStop);
        }

        bool FlowControl = ui->radioButton->isChecked();

        if (FlowControl == true)
        {
            qDebug() << "Управление потоком: no";
            serial->setFlowControl(QSerialPort::NoFlowControl);
        }

        serial->open((QIODevice::ReadWrite));

        ui->label_10->setText("Статус: Соединение произошло");

        ConnectFlag = true;
    }
    else
    {
        ui->label_10->setText("Статус: Соединение разорвано");

        serial->close();

        ConnectFlag = false;
    }
}

void MainWindow::serialTransmit()
{
    if (ConnectFlag == true)
    {
        qDebug() << "Обмен начат";

        QString str = ui->textEdit_2->toPlainText();
        QStringList strList=str.split('\n');
        //str=strList.at(1);

        qDebug() << strList;

        ui->textEdit->append("Начало обмена");

        for (int i = 0; i < strList.count(); i++)
        {
            str = strList.at(i);
            qDebug() << str; //Добавить перевод в хекс формат !!!

            QByteArray strByte = str.toUtf8();
            char *strOut = strByte.data();

            if (serial->write(strOut) > -1)
            {
                ui->textEdit->append("Отправляем: " + str);

                QByteArray ba;
                ba = serial->readAll();
                ui->textEdit->append("Получаем: " + ba.toHex());
            }
            else
            {
                ui->textEdit->append("Отправляем: " + str + " неудача");
            }
        }

        ui->textEdit->append("Конец обмена");
    }

}

void MainWindow::cleanTerminal()
{
    programReInit();
}

void MainWindow::serialRecieve()
{
    QByteArray ba;
    ba = serial->readAll();
    ui->textEdit->setText(ba.toHex());
}

void MainWindow::programInit()
{
    ui->textEdit->setText("Приветствую! Вы находитесь в терминале, который программировал Новохатько Никита Юрьевич в мае 2021 года.");
    ui->textEdit->append("Список портов, к которым Вы можете подключиться:");
    ui->textEdit_2->setText("0x01");
    ui->lineEdit->setText("COM1");

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort port;
        port.setPort(info);
        if (port.open(QIODevice::ReadWrite))
        {
            QString str = "Название: " + info.portName(); // + " " + info.description() + info.manufacturer();
            this->ComPorts.append(str);
            ui->textEdit->append(str);
        }
    }

    ui->label_10->setText("Статус: Соединение разорвано");
}

void MainWindow::programReInit()
{
    ui->textEdit->setText("Приветствую! Вы находитесь в терминале, который программировал Новохатько Никита Юрьевич в мае 2021 года.");
    ui->textEdit->append("Список портов, к которым Вы можете подключиться:");
    ui->textEdit_2->setText("0x01");
    ui->lineEdit->setText("COM1");

    for (int i = 0; i < this->ComPorts.count(); i++ )
    {
        ui->textEdit->append(this->ComPorts[i]);
    }

    ui->label_10->setText("Статус: Соединение разорвано");
}

