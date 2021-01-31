#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QLabel>
#include <QAction>

#include <QTextEdit>
#include <QMdiSubWindow>

#include <videoform.h>
#include <cmdform.h>
#include <saveform.h>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mdiArea = new QMdiArea(this);  // инициализируем QMdiArea
    // Настраиваем скроллбары
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // Устанавливаем Mdi Area в качестве центрального виджета
    setCentralWidget(mdiArea);

    // Добавляем его в область
    //subWindow_cmdF1 = mdiArea -> addSubWindow(cmdF1);
    //Присвоение адреса объекта дочернего окна ссылке
    //saveF1 = new saveForm(mdiArea);
    // Добавляем его в область
    //subWindow_saveF1 = mdiArea -> addSubWindow(saveF1);

    //Открытие окна cmdForm
    //connect(cmdF1, SIGNAL( cmdF1_open() ), this, SLOT( cmdForm_open() ));
}

void MainWindow::on_actionAddVideo_triggered()
{
    //Присвоение адреса объекта дочернего окна ссылке
    vd1 = new VideoForm(mdiArea);
    // Добавляем его в область
    subWindow_vd1 = mdiArea -> addSubWindow(vd1);
    // Set the geometry of Child widget.
    vd1->parentWidget()->setGeometry(0,0,525,560);
    subWindow_vd1->show();

    //Присвоение адреса объекта дочернего окна ссылке
    cmdF1 = new cmdForm(mdiArea);
    subWindow_cmdF1 = mdiArea -> addSubWindow(cmdF1);
    // Set the geometry of Child widget.
    cmdF1->parentWidget()->setGeometry(0,0,525,560);

    connect(vd1, SIGNAL( cmdF1_open() ), this, SLOT( cmdForm_open() ));

    //Передача параметров из другого окна по сигналу
    connect(cmdF1, SIGNAL(peredTableFiles (QVector <QVector <QString> >)), vd1, SLOT(mainWindows_WayPered(QVector<QVector<QString> >)));
    //Событие закрытия дочернего окна по нажатию кнопки: (просто закрыть окно, без действий)
    connect(cmdF1, SIGNAL (peredTableFiles (QVector <QVector <QString> >)), vd1, SLOT (mainWindows_cmdF1_close()));
    connect(vd1, SIGNAL (cmdF1_close()), this, SLOT (cmdForm_Close()));

}

void MainWindow::on_actionAddTimer_triggered()
{
    //Присвоение адреса объекта дочернего окна ссылке
    cid1 = new CickleTimerForm(mdiArea);
    // Добавляем его в область
    subWindow_cid1 = mdiArea -> addSubWindow(cid1);
    // Set the geometry of Child widget.
    cid1->parentWidget()->setGeometry(0,0,600,800);
    subWindow_cid1->show();
}

void MainWindow::on_actionAddCamera_triggered()
{

    //Присвоение адреса объекта дочернего окна ссылке
    ptzid1 = new PTZcameraForm(mdiArea);
    // Добавляем его в область
    subWindow_ptzid1 = mdiArea -> addSubWindow(ptzid1);
    // Set the geometry of Child widget.
    ptzid1->parentWidget()->setGeometry(0,0,747,765);
    subWindow_ptzid1->show();

}

void MainWindow::on_actionAddUsb_triggered()
{
    //Присвоение адреса объекта дочернего окна ссылке
    usbid1 = new ModuleUsbForm(mdiArea);
    // Добавляем его в область
    subWindow_usbid1 = mdiArea -> addSubWindow(usbid1);
    // Set the geometry of Child widget.
    usbid1->parentWidget()->setGeometry(0,0,350,350);
    subWindow_usbid1->show();
}

void MainWindow::on_actionAddEthernet_triggered()
{
    //Присвоение адреса объекта дочернего окна ссылке
    clservid1 = new ClientServerForm(mdiArea);
    // Добавляем его в область
    subWindow_clservid1 = mdiArea -> addSubWindow(clservid1);
    // Set the geometry of Child widget.
    clservid1->parentWidget()->setGeometry(0,0,200,120);
    subWindow_clservid1->show();

    //clid1 = clservid1->createClientForm(mdiArea);
    clid1 = new ClientForm(mdiArea);
    // Добавляем его в область
    subWindow_clid1 = mdiArea -> addSubWindow(clid1);
    // Set the geometry of Child widget.
    clid1->parentWidget()->setGeometry(0,0,410,465);
    //subWindow_clid1->show();
    //clservid1->openClientForm(subWindow_clid1); //????
    //connect(clservid1, SIGNAL( openClient() ), this, SLOT( openClientForm() ));

    //servid1 = clservid1->createServerForm(mdiArea);
    servid1 = new ServerForm(mdiArea);
    // Добавляем его в область
    subWindow_servid1 = mdiArea -> addSubWindow(servid1);
    // Set the geometry of Child widget.
    servid1->parentWidget()->setGeometry(0,0,700,590);
    //subWindow_servid1->show();
    //connect(clservid1, SIGNAL( openServer() ), this, SLOT( openServerForm() ));

    connect(clservid1, SIGNAL( openClientOrServer(bool, bool) ), this, SLOT( selectClientOrServerslot(bool, bool) ));


}

void MainWindow::on_actionAddLogs_triggered()
{
    //Присвоение адреса объекта дочернего окна ссылке
    regid1 = new VideoRegistratorForm(mdiArea);
    // Добавляем его в область
    subWindow_regid1 = mdiArea -> addSubWindow(regid1);
    // Set the geometry of Child widget.
    regid1->parentWidget()->setGeometry(0,0,525,560);
    subWindow_regid1->show();
}

void MainWindow::on_actionAddOptions_triggered()
{   /*
    // Создаём виджет, который будет окном
    QWidget *widget = new QWidget(mdiArea);
    // Добавляем в него размещение
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Добавляем на виджет надпись
    QLabel *label = new QLabel("actionAddOptions!!!", widget);
    gridLayout->addWidget(label);

    // Добавляем виджет в качестве подокна в Mdi Area
    mdiArea->addSubWindow(widget);
    // Устанавливаем заголовок окна
    widget->setWindowTitle("Sub Window");
    // и показываем виджет
    widget->show();
    */
    //Присвоение адреса объекта дочернего окна ссылке
    optid1 = new OptionsForm(mdiArea);
    // Добавляем его в область
    subWindow_optid1 = mdiArea -> addSubWindow(optid1);
    // Set the geometry of Child widget.
    optid1->parentWidget()->setGeometry(0,0,525,560);
    subWindow_optid1->show();
}

void MainWindow::cmdForm_open()
{
    subWindow_cmdF1->show();
    //Создание соединения для отправки из окна vd1 в окно cmdF1
    connect(vd1, SIGNAL(mainWindows_sendData(QVector<QVector<QString> >, QString) ), this, SLOT(mainWindows_recieveData(QVector<QVector<QString> >, QString)) );
    connect(this, SIGNAL(out_recieveData(QVector<QVector<QString> >, QString) ), cmdF1, SLOT(recieveData(QVector<QVector<QString> >, QString)) );
    //Создание соединения для отправки из окна cmdF1 в окно vd1
    //Передача параметров из другого окна по сигналу
    connect(cmdF1, SIGNAL(peredTableFiles (QVector <QVector <QString> >)), this, SLOT(mainWindows_WayPered(QVector<QVector<QString> >)));
    //connect(this, SIGNAL(out_WayPered (QVector <QVector <QString> >)), vd1, SLOT(WayPered(QVector<QVector<QString> >)));
    //Событие закрытия дочернего окна по нажатию кнопки: (просто закрыть окно, без действий)
    //connect(cmdF1, SIGNAL (peredTableFiles (QVector <QVector <QString> >)), this, SLOT (vd1_Close()));
    //connect(this, SIGNAL (vd1_peredTableFiles ()), cmdF1, SLOT (close()));

}

void MainWindow::saveForm_open()
{
    /*
    //Создание формы для сохранения или загрузки текущего состояния
    saveF1 = new saveForm(mdiArea);

    // Добавляем его в область
    subWindow_saveF1 = mdiArea -> addSubWindow(saveF1);

    saveF1->parentWidget()->setGeometry(0,0,525,560);
    subWindow_saveF1->show();
    */
}

void MainWindow::mainWindows_recieveData(QVector<QVector<QString> > parameters, QString ffmpegstr)
{
    qDebug() << "out_recieveData!!!";
    emit out_recieveData(parameters, ffmpegstr);
}

void MainWindow::mainWindows_WayPered(QVector<QVector<QString> > parameters)
{
    qDebug() << "out_WayPered!!!";
    emit out_WayPered(parameters);
}

void MainWindow::vd1_Close()
{
    qDebug() << "vd1_Close!!!";
    emit vd1_peredTableFiles();
}

/*Закрыть окно cmdForm*/
void MainWindow::cmdForm_Close()
{
    qDebug() << "cmdForm_Close!!!";

    subWindow_cmdF1->hide();//subWindow_cmdF1->close();//parentWidget()->deleteLater();
}

void MainWindow::selectClientOrServerslot(bool ClientRole, bool ServerRole)
{
    qDebug() << ClientRole << " --- " << ServerRole;

    /*Если нажата serverRole, и не нажата clientRole, то открываем окно Server*/
    if ( (ClientRole == true) && (this->servid1->isVisible() == false) )
    {
        qDebug() << "Нажата clientRole ";

        this->clid1->show();
   //     //emit openClient();
    }
    /*Если наоборот, то окрываем Client*/
    /*Следует учесть, открыто ли уже одно из окон*/
    else if  ( (ServerRole == true) && (this->clid1->isVisible() == false) )
    {
        qDebug() << "Нажата serverRole ";

        this->servid1->show();
    //    //emit openServer();
    }
}

/*
void MainWindow::openClientForm()
{
    subWindow_clid1->show();
}

void MainWindow::openServerForm()
{
    subWindow_servid1->show();
}
*/

MainWindow::~MainWindow()
{
    delete ui;
}
