#include "cmdform.h"
#include "ui_cmdform.h"

#include <QTextCodec>
#include <QDir>
#include <QDebug>
#include <QLabel>
#include <QScrollBar>
#include <QListWidget>
#include <QListWidgetItem>

cmdForm::cmdForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cmdForm)
{
    ui->setupUi(this);

    mTranscodingProcess = new QProcess(this);

    //connect(ui->ButtonVVod, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()) );
    connect(mTranscodingProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readyReadStandardOutput()) );
    //Проверка, завершен ли процесс ffmpeg, для нового его запуска
    connect(mTranscodingProcess,SIGNAL(finished(int, QProcess::ExitStatus)),this,SLOT(startButton_clicked()) );
    //Отправка строки с данными для нарезки файла
    connect(this, SIGNAL(sendDataCMD()),this,SLOT(startButton_clicked()));

    connect(ui->ButtonPrerv, SIGNAL(clicked()),this,SLOT(PrervatData()));
}

cmdForm::~cmdForm()
{
    delete ui;
}

void cmdForm::startButton_clicked()
{

    //Заменить на относительный путь!!!
    //QString program = "D:/OOP/NarezkaFailov/ffmpeg/bin/ffmpeg.exe";
    //QString program = "ffmpeg/bin/ffmpeg.exe";
    QString program = this->iWay;

    QStringList arguments;
    QString inputFile, outputFile, startTime, Time, InnameFile, OutnameFile;
    QVector <QVector <QString>> jparameters;
    QVector <QString> parametersSTR, jparamstr;
    int j, jtableCount;

    //inputFile = "D:/OOP/Videos/KastaMetla.mp4";
    //outputFile = "D:/OOP/Videos/Kasta1-1.mp4";
    //startTime = "00:01:00";
    //Time = "00:01:00";
    //Если строка в i больше 0, но меньше количества строк
    if ( (0 <= i) && (this->i < iCount) )
    {
    parametersSTR = this->parameters.at(i); qDebug() << parametersSTR;
    startTime = parametersSTR.at(0);
    Time = parametersSTR.at(1);
    inputFile = parametersSTR.at(2);
    outputFile = parametersSTR.at(3);
    OutnameFile = parametersSTR.at(4);
    InnameFile = parametersSTR.at(5);

    arguments << "-ss" << "-t" << "-i";
    //Вставка начала отсчёта отрезка
    arguments.insert(1, startTime);
    //Вставка продолжительности отрезка
    arguments.insert(3, Time);
    //Вставка пути и названия к обрезаемому файлу
    arguments.insert(5, inputFile);
    //Вставка  пути и названия отрезка
    arguments.insert(6, outputFile);

    //arguments << "-ss" << "00:01:00" << "-t" << "00:01:00" << "-i" << "D:/OOP/Videos/KastaMetla.mp4" << "D:/OOP/Videos/Kasta1-1.mp4";
    qDebug() << arguments;

    //Запуск процесса ffmpeg с аргументами в стандартный поток вывода
    mTranscodingProcess->setProcessChannelMode(QProcess::MergedChannels);
    mTranscodingProcess->start(program, arguments);

    // Создаём строку!!!
    ui->tableSpis->insertRow(this->i);

    // выделяем память под ячейку вставляем строку
    QTableWidgetItem *item1 = new QTableWidgetItem(InnameFile);
    // вставляем ячейку
    ui->tableSpis->setItem(this->i, 0, item1);
    // выделяем память под ячейку вставляем строку
    QTableWidgetItem *item2 = new QTableWidgetItem(OutnameFile);
    // вставляем ячейку
    ui->tableSpis->setItem(this->i, 1, item2);

    this->i++; qDebug() << "this-i - " << this->i;
    }
    //Если эти условия не выполняются. при этом нажата кнопка "Прервать",
    //то закрываем окно
    else if ((this->iFinish == "true") || (this->i == iCount))
    {
    qDebug() << "Окно cmdForm закрыто!!!";

    //Для примера
    //paramstr << "one" << "two";
    //parameters.push_back(paramstr);
    //parameters.push_back(paramstr);
    //parameters.push_back(paramstr);

    //Создание таблицы строк таблицы "входной-выходной"
    jtableCount = ui->tableSpis->rowCount(); qDebug() << "tableSpis - " << jtableCount;
    for (j = 0; j < jtableCount; j++)
        {
        jparamstr.push_back(ui->tableSpis->item(j,0)->text()); //qDebug() << "jparamstr0 - " << jparamstr;
        jparamstr.push_back(ui->tableSpis->item(j,1)->text()); qDebug() << "jparamstr - " << jparamstr;
        jparameters.push_back(jparamstr);
        jparamstr.clear();
        }


    qDebug() << jparameters;

    qDebug() << "emit peredTableFiles!!!";

    emit peredTableFiles (jparameters);
    }
}

void cmdForm::readyReadStandardOutput()
{
    //Чтение данных из потока вывода процесса ffmpeg и их вывод
    QString mOutputString;
    mOutputString.append(mTranscodingProcess->readAllStandardOutput());
    ui->textCMD->append(mOutputString);
    //Строка окончания
    //QString iReg = "Qavg";
}

void cmdForm::recieveData(QVector<QVector<QString> > parameters, QString ffmpegstr)
{
    qDebug() << "cmdForm parameters:";
    qDebug() << parameters;

    //Заполнение переменных массивом строчек параметров и начальным номером строки
    this->parameters = parameters; qDebug() << this->parameters;
    this->i = 0; qDebug() <<this->i;
    this->iCount = parameters.count(); qDebug() << this->iCount;
    //Заполнение переменной нажатия кнопки "Прервать"
    //для отложенного закрытия окна
    this->iFinish = "false";
    //Заполнение переменной пути к файлу ffmpeg;
    //ffmpegstr.append("/ffmpeg.exe");
    this->iWay = ffmpegstr; qDebug() << "this->iWay - " << this->iWay;
    ui->LabelFinish->setText(this->iFinish);

    // Указываем число колонок
    ui->tableSpis->setColumnCount(2);
    // Указываем число строк, для заполнения таблицы с нуля нужно каждый раз
    //указывать, что число строк - 0
    ui->tableSpis->setRowCount(0);
    // Устанавливаем заголовки колонок
    QStringList headers;
    headers << "Входной" << "Выходной";
    ui->tableSpis->setHorizontalHeaderLabels(headers);
    // Включаем сетку
    ui->tableSpis->setShowGrid(true);
    // Разрешаем выделение только одного элемента. ??? Смотреть доки
    //ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tableSpis->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->tableSpis->horizontalHeader()->setStretchLastSection(true);
    // Скрываем колонку под номером 5
    //ui->tableSpis->hideColumn(4);
    //Запрет рдактирования строк
    ui->tableSpis->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Сигнал для передачи слоту on_startButton_clicked()
    emit sendDataCMD ();
}

void cmdForm::PrervatData()
{
    //Если нужно прервать, то кнопку из false в true
    if (this->iFinish == "false")
    {
    //Сохранение i в промежуточную переменную
    //Приравнивание i к общему количеству строк. Тем самым прерывание цикла
    this->iBeta = i;
    this->i = iCount; qDebug() << "this-i = iCount - " << this->i;

    this->iFinish = "true";
    ui->LabelFinish->setText(this->iFinish);
    }
    //Если нужно отменить, то из true в false
    else
    {
    //Возврат i из промежуточной переменной
    this->i = this->iBeta;
    this->iFinish = "false";
    ui->LabelFinish->setText(this->iFinish);
    }
}
