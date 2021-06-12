#include "cickletimerform.h"
#include "ui_cickletimerform.h"
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QVector>
#include <QtMath>

CickleTimerForm::CickleTimerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CickleTimerForm)
{
    ui->setupUi(this);
    //showTime();
    //Создал новый объект для этого окна
    QTimer *timerObsh = new QTimer(this);
    //Когда объект таймер сигнализирует о прохождении секунды,
    //вызывается слот вывода времени в окно
    connect(timerObsh, SIGNAL (timeout()), this, SLOT(showTime()) );
    //вызывается слот для таймера одиночного цикла!
    connect(timerObsh, SIGNAL (timeout()), this, SLOT(mp3OdinTimer()) );

    //вызывается слот для таймера множественного цикла!
    connect(timerObsh, SIGNAL (timeout()), this, SLOT(mp3MnogoTimer()) );


    //Переменная состояния кнопки "Начать одиночный цикл"
    this->NachOdinCikleBool = false;
    //Переменная состояния кнопки "Приостановить одиночный цикл"
    this->PriosOdinCikleBool = false;
    //Переменная состояния кнопки "Возобновить одиночный цикл"
    this->VozobOdinCikleBool = false;
    //Переменная состояния кнопки "Прервать одиночный цикл"
    this->PrervOdinCikleBool = false;
    //Переменная положения в таблице mp3 файлов
    this->CurrentOdinCount = 0;
    //Время начала одиночного цикла в милисекундах
    this->StartOdinTime = 0;
    //Время окончания одиночного цикла в милисекундах
    this->FinishOdinTime = 0;
    //текущее время в милисекундах
    this->CurrentOdinTime = 0;
    //Текущая строка строкового вектора
    this->CurrentOdinRow = 0;
    //количество строк строкового вектора
    this->CurrentOdinMany = 0;
    //Время до следующего воспроизведения сообщения
    this->CurrentOdinPart = 0;

    this->TableFlag = false;

    timerObsh->start(1000);

    connect(ui->mp3Button, SIGNAL(clicked()), this, SLOT(mp3VTable()) );

    connect(ui->NachOdinButton, SIGNAL(clicked()), this, SLOT(NachOdinCikle()) );
    connect(ui->PriosOdinButton, SIGNAL(clicked()), this, SLOT(PriosOdinCikle()) );
    connect(ui->VozobOdinButton, SIGNAL(clicked()), this, SLOT(VozobOdinCikle()) );
    connect(ui->PrervOdinButton, SIGNAL(clicked()), this, SLOT(PrervOdinCikle()) );

    connect(ui->NachMnogoButton, SIGNAL(clicked()), this, SLOT(NachMnogoCikle()) );
    connect(ui->PriosMnogoButton, SIGNAL(clicked()), this, SLOT(PriosMnogoCikle()) );
    connect(ui->VozobMnogoButton, SIGNAL(clicked()), this, SLOT(VozobMnogoCikle()) );
    connect(ui->PrervMnogoButton, SIGNAL(clicked()), this, SLOT(PrervMnogoCikle()) );

    player = new QMediaPlayer;

    connect(this, SIGNAL(doubleOne()), this, SLOT(NachOdinCikle()) );
    connect(this, SIGNAL(doubleMany()), this, SLOT(NachMnogoCikle()) );
}

CickleTimerForm::~CickleTimerForm()
{
    delete ui;
}

QString CickleTimerForm::mp3Way()
{
    QString mp3W = ui->mp3Line->text();
    return mp3W;
}

QVector <QVector<QString> > CickleTimerForm::mp3Dir(QString mp3W)
{
    QFileInfoList text3;
    QStringList text2;
    QVector <QVector<QString> > mp3Files;
    QVector<QString> mp3Files_str;
    QDir dir(mp3W);
    //QDir::setCurrent(text1);
    bool flag = dir.exists();
    if (!flag)
        {
        qWarning("text1 - Данную директорию невозможно найти!");
        }
    else
       {
        //Установка фильтров при поиске файлов
        //QDir::Files позволяет увидеть файлы
        //QDir::AllDirs позволяет увидеть все каталоги, в том числе не соответсутвующие маске
        //QDir::NoDotAndDotDot удаляет из полученного списка каталоги "." и ".."
        dir.setFilter(QDir::Files); // | QDir::AllDirs|QDir::NoDotAndDotDot);
        //Установка фильтра по названию файла. В данном случае маска берётся по формату
        QStringList nameFilter;
        nameFilter << "*.mp3";
        dir.setNameFilters(nameFilter);

        QString str, str1, str_size, text1_size;

        //Возвращает массив объектов с информацией о файлах и дирректориях
        text3 = dir.entryInfoList(); qDebug() << "text3 - " << text3;
        //Получить массив файлов
        //Получить массив директорий
        for (QFileInfo number : text3)
        {
          //Перебор объектов полученных в массиве и выяснение, файл это или каталог
            if (number.isFile())
                {
                //Добавление в массив mp3Files_str названия файла
                mp3Files_str.push_back(number.fileName());
                //mp3Files.append(str);
                //Добавление в массив mp3Files_str абсолютного пути к файлу
                 mp3Files_str.push_back(number.absoluteFilePath());
                 mp3Files.push_back(mp3Files_str);
                 mp3Files_str.clear();
                }
        }
     }

        //QVector <QString> mp3Files;
        //mp3Files << "one.mp3" << "two.mp3";
    return mp3Files;
}

void CickleTimerForm::mp3TableHeaders()
{
    // Удаляем предыдущее содержание таблицы
//При этом при смене пути к файлу удаляются только строчки, а не их содержимое. Исправить!!!
//При выставлении количества строк в 1 осталась только одна строка. Что ещё можно сделать?
//Из-за появления дополнительной строки не запускается дочернее окно!!!
    ui->mp3TimeTable->clear();
    ui->mp3TimeTable->setRowCount(0);
    //ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    // Указываем число колонок
    ui->mp3TimeTable->setColumnCount(7);
    // Указываем число строк
    //ui->tableWidget->setRowCount(5);
    // Устанавливаем заголовки колонок
    QStringList headers;
    headers << "Метка" << "Название файла" << "Расположение" << "Время проигрывания" << "Статус" << "Камера1" << "Камера2";
    ui->mp3TimeTable->setHorizontalHeaderLabels(headers);
    // Включаем сетку
    ui->mp3TimeTable->setShowGrid(true);
    // Разрешаем выделение только одного элемента. ??? Смотреть доки
    //ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->mp3TimeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->mp3TimeTable->horizontalHeader()->setStretchLastSection(true);
    // Скрываем колонку под номером 5
    //ui->tableWidget->hideColumn(4);
    //Запрет редактирования строк
    //ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->mp3TimeTable->setColumnCount(3);
}

void CickleTimerForm::mp3TableInfo(QVector<QVector<QString> > mp3Info)
{
    qDebug() << "Заполнение таблицы!!!";

    int sizeRows = mp3Info.size();
    QVector <QString> mp3Info_str;
    QStringList FirstLast;
    FirstLast << "Точка отсчёта" << "Последняя точка";
    //int FirstLastRow = 0;
    //int iFirstLast = 0;

    ui->mp3TimeTable->insertRow(0); //i);

    //Создание объекта чекбокс
    QTableWidgetItem *itemcheck = new QTableWidgetItem();
    //Установка чекбокса в состояние "не нажат"
    itemcheck->setCheckState(Qt::Checked); //Unchecked);
    //Добавление чекбокса в таблицу
    ui->mp3TimeTable->setItem(0, 0, itemcheck);

    QString FirstTime = FirstLast.at(0); //"hh:mm:ss";
    // выделяем память под ячейку вставляем строку
    QTableWidgetItem *item4 = new QTableWidgetItem(FirstTime);
    // вставляем ячейку
    ui->mp3TimeTable->setItem(0, 1, item4);

    QString FirsTimeExample1 = "***"; //"hh:mm:ss";
    // выделяем память под ячейку вставляем строку
    QTableWidgetItem *item5a = new QTableWidgetItem(FirsTimeExample1);
    // вставляем ячейку
    ui->mp3TimeTable->setItem(0, 2, item5a);

    QString FirsTimeExample = "00:00:00"; //"hh:mm:ss";
    // выделяем память под ячейку вставляем строку
    QTableWidgetItem *item5 = new QTableWidgetItem(FirsTimeExample);
    // вставляем ячейку
    ui->mp3TimeTable->setItem(0, 3, item5);

    QString Status = "Не проигран";
    // выделяем память под ячейку вставляем строку
    QTableWidgetItem *item2 = new QTableWidgetItem(Status);
    // вставляем ячейку
    ui->mp3TimeTable->setItem(0, 4, item2);

    //QString Pologenie = "Внутри";
    // выделяем память под ячейку вставляем строку
    //QTableWidgetItem *item3 = new QTableWidgetItem(Pologenie);
    // вставляем ячейку
    //ui->mp3TimeTable->setItem(0, 5, item3);

    //Создание объекта чекбокс
    QTableWidgetItem *cameracheck1 = new QTableWidgetItem();
    //Установка чекбокса в состояние "не нажат"
    cameracheck1->setCheckState(Qt::Checked); //Unchecked);
    //Добавление чекбокса в таблицу
    ui->mp3TimeTable->setItem(0, 5, cameracheck1);

    //Создание объекта чекбокс
    QTableWidgetItem *cameracheck2 = new QTableWidgetItem();
    //Установка чекбокса в состояние "не нажат"
    cameracheck2->setCheckState(Qt::Unchecked); //Unchecked);
    //Добавление чекбокса в таблицу
    ui->mp3TimeTable->setItem(0, 6, cameracheck2);

    for (int i = 1; i < sizeRows; i++)
    {
        mp3Info_str = mp3Info.at(i);
        //int strRows = mp3Info_str.size();
        // Создаём строку!!!
        ui->mp3TimeTable->insertRow(i); //i);
        //Создание объекта чекбокс
        QTableWidgetItem *itemcheck = new QTableWidgetItem();
        //Установка чекбокса в состояние "не нажат"
        itemcheck->setCheckState(Qt::Checked); //Unchecked);
        //Добавление чекбокса в таблицу
        ui->mp3TimeTable->setItem(i, 0, itemcheck);
        for (int j = 0; j < 2; j++)
        {
            // выделяем память под ячейку вставляем строку
            QTableWidgetItem *item1 = new QTableWidgetItem(mp3Info_str.at(j));
            // вставляем ячейку
            ui->mp3TimeTable->setItem(i, (j + 1), item1);
        }
        QString Example = "00:00:10"; //"hh:mm:ss";
        // выделяем память под ячейку вставляем строку
        QTableWidgetItem *item0 = new QTableWidgetItem(Example);
        // вставляем ячейку
        ui->mp3TimeTable->setItem(i, 3, item0);


        QString Status = "Не проигран";
        // выделяем память под ячейку вставляем строку
        QTableWidgetItem *item2 = new QTableWidgetItem(Status);
        // вставляем ячейку
        ui->mp3TimeTable->setItem(i, 4, item2);

        //QString Pologenie = "Внутри";
        // выделяем память под ячейку вставляем строку
        //QTableWidgetItem *item3 = new QTableWidgetItem(Pologenie);
        // вставляем ячейку
        //ui->mp3TimeTable->setItem(i, 5, item3);

        //Создание объекта чекбокс
        QTableWidgetItem *cameracheck1 = new QTableWidgetItem();
        //Установка чекбокса в состояние "не нажат"
        cameracheck1->setCheckState(Qt::Checked); //Unchecked);
        //Добавление чекбокса в таблицу
        ui->mp3TimeTable->setItem(i, 5, cameracheck1);

        //Создание объекта чекбокс
        QTableWidgetItem *cameracheck2 = new QTableWidgetItem();
        //Установка чекбокса в состояние "не нажат"
        cameracheck2->setCheckState(Qt::Unchecked); //Unchecked);
        //Добавление чекбокса в таблицу
        ui->mp3TimeTable->setItem(i, 6, cameracheck2);
    }

    int sizeRowsDop = sizeRows;

    ui->mp3TimeTable->insertRow(sizeRowsDop); //i);

    //Создание объекта чекбокс
    QTableWidgetItem *itemcheck1 = new QTableWidgetItem();
    //Установка чекбокса в состояние "не нажат"
    itemcheck1->setCheckState(Qt::Checked); //Unchecked);
    //Добавление чекбокса в таблицу
    ui->mp3TimeTable->setItem(sizeRowsDop, 0, itemcheck1);

    FirstTime = FirstLast.at(1); //"hh:mm:ss";
    // выделяем память под ячейку вставляем строку
    QTableWidgetItem *item7 = new QTableWidgetItem(FirstTime);
    // вставляем ячейку
    ui->mp3TimeTable->setItem(sizeRowsDop, 1, item7);

    QString FirsTimeExample2 = "***"; //"hh:mm:ss";
    // выделяем память под ячейку вставляем строку
    QTableWidgetItem *item5b = new QTableWidgetItem(FirsTimeExample2);
    // вставляем ячейку
    ui->mp3TimeTable->setItem(sizeRowsDop, 2, item5b);

    FirsTimeExample = "00:00:00"; //"hh:mm:ss";
    // выделяем память под ячейку вставляем строку
    QTableWidgetItem *item8 = new QTableWidgetItem(FirsTimeExample);
    // вставляем ячейку
    ui->mp3TimeTable->setItem(sizeRowsDop, 3, item8);

    Status = "Не проигран";
    // выделяем память под ячейку вставляем строку
    QTableWidgetItem *item9 = new QTableWidgetItem(Status);
    // вставляем ячейку
    ui->mp3TimeTable->setItem(sizeRowsDop, 4, item9);

    //Pologenie = "Внутри";
    // выделяем память под ячейку вставляем строку
    //QTableWidgetItem *item10 = new QTableWidgetItem(Pologenie);
    // вставляем ячейку
    //ui->mp3TimeTable->setItem(sizeRowsDop, 5, item10);

    //Создание объекта чекбокс
    QTableWidgetItem *cameracheck1_end = new QTableWidgetItem();
    //Установка чекбокса в состояние "не нажат"
    cameracheck1_end->setCheckState(Qt::Checked); //Unchecked);
    //Добавление чекбокса в таблицу
    ui->mp3TimeTable->setItem(sizeRowsDop, 5, cameracheck1_end);

    //Создание объекта чекбокс
    QTableWidgetItem *cameracheck2_end = new QTableWidgetItem();
    //Установка чекбокса в состояние "не нажат"
    cameracheck2_end->setCheckState(Qt::Unchecked); //Unchecked);
    //Добавление чекбокса в таблицу
    ui->mp3TimeTable->setItem(sizeRowsDop, 6, cameracheck2_end);

}

QVector <QVector<QString> > CickleTimerForm::mp3TableRead()
{
    QVector <QVector<QString> > mp3Tbl;
    QVector <QString> mp3Tbl_str;
    QString str;

    int iRowCount = ui->mp3TimeTable->rowCount();

    for (int i = 0; i < iRowCount; i++)
    {
        //Извлечение статуса чекбокса: нажат/не нажат
        bool flag_check = ui->mp3TimeTable->item(i,0)->checkState(); qDebug() << flag_check;
        if (flag_check == true)
        {
            for (int j = 1; j < 6; j++)
            {
                str = ui->mp3TimeTable->item(i,j)->text();
                mp3Tbl_str.push_back(str);
            }
            mp3Tbl.push_back(mp3Tbl_str);
            mp3Tbl_str.clear();
        }
    }

    return mp3Tbl;
}

void CickleTimerForm::mp3TableTimeRead(QVector <QVector<QString> > mp3Tbl)
{
    QVector <QString> mp3Tbl_str, mp3Tbl_str_new;
    QVector <QVector <QString> > mp3Tbl_new;
    QString mp3Tbl_str_el;
    int i_mp3Tbl = mp3Tbl.count();

    /*Символ разделитель ":" */
    QString spl3 = ":";
    QStringList sectime1, sectime2;
    int sect1, sec1, allsec1, FinishOdin, StartOdin, CurrentOdin;
    QString sect01;
    FinishOdin = 0;

    for (int i = 0; i < i_mp3Tbl; i++)
    {
        /*Получение элемента таблицы*/
        mp3Tbl_str = mp3Tbl.at(i);
        mp3Tbl_str_el = mp3Tbl_str.at(2);

        /*Разделение строки времени по разделителю ":" */
        sectime1 = mp3Tbl_str_el.split (spl3);
        sec1 = 0;
        allsec1 = 0;

        for (int j = 0; j < 3; j++)
        {
        /*Получение секунды\минуты\часа первого отрезка и преобразование из строки в число*/
        sect01 = sectime1.at(j);
        sect1 = sect01.toInt();
        sec1 = sec1 + sect1 * qPow(60,2 - j);
        allsec1 = allsec1 + sec1;
        sec1 = 0;
        }
        if (i > 0)
        {
            FinishOdin = FinishOdin + allsec1;
        }
        else
        {
            StartOdin = allsec1;
            CurrentOdin = allsec1;
        }

        QString allsec1_str = QString::number(allsec1 * 1000);
        mp3Tbl_str.replace(2, allsec1_str);
        mp3Tbl.replace(i, mp3Tbl_str);

        allsec1 = 0;
    }

    this->mp3Table = mp3Tbl; qDebug() << "mp3Tbl - " << mp3Tbl;

    this->StartOdinTime = StartOdin; // * 1000; //qDebug() << "StartOdin - " << StartOdin;
    //this->CurrentOdinTime = CurrentOdin; // * 1000; //qDebug() << "CurrentOdin - " << FinishOdin;
    this->FinishOdinTime = FinishOdin; // * 1000; //qDebug() << "FinishOdin - " << FinishOdin;
    this->CurrentOdinTime = 0;
    this->CurrentOdinRow = 0;
    this->CurrentOdinCount = mp3ArraySearch(this->CurrentOdinRow); //qDebug() << "this->mp3OdinCount - " << this->mp3OdinCount;
    this->CurrentOdinMany = this->mp3Table.count();
    this->Start_flag = false;
    this->Finish_flag = true;

}

QString CickleTimerForm::mp3Time(int time)
{
    int a, b, t1, t2, t3;
    QString t1str, t2str, t3str, Nartime;
    //Вычисление секунд
    a = time / 60;
    t1 = time - a * 60; //qDebug() << t1;
    //Вычисление минут
    b = a / 60;
    t2 = a - b * 60; //qDebug() << t2;
    //Получение часов
    t3 = b; //qDebug() << t3;

    if (t3 < 10)
    {
        t3str.append("0");
    }
    t3str  = t3str.append(QString::number(t3));
    Nartime.append(t3str);
    Nartime.append(":");
    if (t2 < 10)
    {
        t2str.append("0");
    }
    t2str  = t2str.append(QString::number(t2));
    Nartime.append(t2str);
    Nartime.append(":");
    if (t1 < 10)
    {
        t1str.append("0");
    }
    t1str  = t1str.append(QString::number(t1));
    Nartime.append(t1str);

    return Nartime;
}

void CickleTimerForm::mp3TimeLabels()
{
    int Start, Finish, Current, Negative;
    QString CurrentStr, NegativeStr, NegativeMin;
    qDebug() << "Единичный таймер включен!";
    Start = this->StartOdinTime;
    Finish = this->FinishOdinTime;
    Current = this->CurrentOdinTime;
    if ((Start <= Current) && (Current < Finish))
    {
        //Преобразование из секунд в 00:00:00 текущего времени
        CurrentStr = mp3Time(Current);

        NegativeStr.append(" - ");
        Negative = Finish - Current;
        //Преобразование из секунд в 00:00:00 обратного времени
        NegativeMin = mp3Time(Negative);
        NegativeStr.append(NegativeMin);

    }
    else
    {
        Current = - 1;
        CurrentStr = "00:00:00";
        NegativeStr = " - 00:00:00";
    }


    //Здесь должно быть преобразование в hh:mm:ss
    //Выдача в лэйбл
    ui->OneCikleTime->setText(CurrentStr); //QString::number(this->CurrentOdinTime) );
    ui->PoslCikleTime->setText(NegativeStr); //QString::number(this->CurrentOdinTime) );

    //return Current;
}

int CickleTimerForm::mp3TimeRow()
{
    int iRow = -1;

    //При условии, что совпадает момент времени с последним отрезком
    if ((this->CurrentOdinTime == this->CurrentOdinCount) && (this->CurrentOdinRow < this->CurrentOdinMany))
    {

        int mp3Search = mp3ArraySearch(this->CurrentOdinRow);
        //Если отрезок времени равен нулю
        if (mp3Search == 0)
        {
            this->CurrentOdinTime--;
        }

        this->CurrentOdinCount = this->CurrentOdinCount + mp3Search;

        iRow = this->CurrentOdinRow;

        this->CurrentOdinRow++;

    }

    return iRow;
}

int CickleTimerForm::mp3ArraySearch(int iRow)
{

    QVector<QString> mp3Table_str = this->mp3Table.at(iRow);
    QString mp3Table_el = mp3Table_str.at(2);
    int iTime = mp3Table_el.toInt() / 1000;

    return iTime;
}

void CickleTimerForm::mp3Play(int iRow)
{
    //Получение пути к нужному файлу, исключая первую и последнюю строку таблицы:
    if ( (iRow > 0) && (iRow < this->CurrentOdinMany - 1) )
    {
    QVector<QString> mp3Table_str = this->mp3Table.at(iRow);
    QString mp3Table_el = mp3Table_str.at(1);

    qDebug() << "Воспроизведение файла по пути: " << mp3Table_el;

    /* Функция воспроизведения файла mp3 */
    player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(mp3Table_el))); //"D:\\OOP\\CikleTimer\\Soobshenia2016\\2 Входите.mp3")));
    player->setVolume(50);
    player->play();

    } else if (iRow == this->CurrentOdinMany - 1)
    {
        this->NachOdinCikleBool = false;
    }

}

QString CickleTimerForm::mp3Name(int iRow)
{
    QVector<QString> mp3Table_str = this->mp3Table.at(iRow);
    QString mp3Table_el = mp3Table_str.at(0);

    qDebug() << "Воспроизведение файла по пути <<>> : " << mp3Table_el;

    return mp3Table_el;
}

void CickleTimerForm::mp3Status(int iRow, bool flag)
{
    QString Status;

    if (flag == true)
    {
        Status = "Проигран";
    }

    else
    {
        Status = "Не проигран";
    }

    // выделяем память под ячейку вставляем строку
    QTableWidgetItem *item2 = new QTableWidgetItem(Status);
    // вставляем ячейку
    ui->mp3TimeTable->setItem(iRow, 4, item2);
}

void CickleTimerForm::mp3TableStatus()
{
    int iRow = this->CurrentOdinMany;

    for (int i = 0; i < iRow; i++)
    {
        qDebug() << "Status";
        mp3Status(i, false);
    }
}

void CickleTimerForm::mp3Switch(int iRow)
{
    int DynamicNumber = 0b00;

    //Получение пути к нужному файлу, исключая первую и последнюю строку таблицы:
    if ( (iRow > 0) && (iRow < this->CurrentOdinMany - 1) )
    {
    //Извлечение статуса чекбокса для колонки 1: нажат/не нажат
    bool flag_check1 = ui->mp3TimeTable->item(iRow,5)->checkState(); //qDebug() << flag_check;
    bool flag_check2 = ui->mp3TimeTable->item(iRow,6)->checkState(); //qDebug() << flag_check;

    if ((flag_check1 == true) && (flag_check2 == false))
    {
        DynamicNumber = 0b01;
    }

    if ((flag_check1 == false) && (flag_check2 == true))
    {
        DynamicNumber = 0b10;
    }

    if ((flag_check1 == true) && (flag_check2 == true))
    {
        DynamicNumber = 0b11;
    }

    qDebug() << "Посылка сигнала по пути: " << DynamicNumber;

    /*
     * Посылка сигнала с параметром DynamicNumber:
     * 00 - не подавать сигнал на колонки //0
     * 01 - 1ая колонка (внутренняя)      //1
     * 10 - 1ая колонка (внешняя)         //2
     * 11 - подать сигнал на обе колонки  //3
   */
    emit SwitchSignal(DynamicNumber);

    } else if (iRow == this->CurrentOdinMany - 1)
    {
        this->NachOdinCikleBool = false;
    }


}

void CickleTimerForm::OdinCikleOptions()
{
    this->CickleCount = 0;
}

void CickleTimerForm::MnogoCikleOptions()
{
    QString Str_CickleCount = ui->KolvCikleLine->text();

    int CickleCount = Str_CickleCount.toInt();

    if (CickleCount > 0)
    {
        CickleCount--;
    }

    this->CickleCount = CickleCount;

}

void CickleTimerForm::mp3OdinTimer()
{

    if (this->NachOdinCikleBool == true)
    {
        mp3TimeLabels();

        int iRow = mp3TimeRow();

        if (iRow >= 0)
        {
          mp3Status(iRow, true); //Выставляем статус - сообщение проиграно

          mp3Play(iRow); //Воспроизводим сообщение строки с номером

          QString nameOfFile = mp3Name(iRow);

          mp3Switch(iRow); //Отсылаем сигнал переключателю

          QVector <QString> parameters;
          parameters.push_back(QString::number(this->CickleCount));
          parameters.push_back(ui->ObshTime->text());
          parameters.push_back(nameOfFile);

          emit TimerToServerSignal(06, parameters);
        }


        this->CurrentOdinTime++;
    }
}

void CickleTimerForm::mp3MnogoTimer()
{
    //qDebug() << "This is test for mp3MnogoTimer()";

    QString numberClk;

    if (this->NachOdinCikleBool == true)
    {
       int CK = this->CickleCount; //Извлекаем количество повторений
       int Finish = this->FinishOdinTime; //Время окончания одиночного цикла в милисекундах
       int Current = this->CurrentOdinTime; //текущее время в милисекундах

       if ( (CK > 0) && (Current == Finish) )  //Если количество повторений больше нуля и текущее время цикла равно времени окончания цикла,то:
       {
            this->CurrentOdinTime = 0;
            this->CurrentOdinRow = 0;
            this->CurrentOdinCount = mp3ArraySearch(this->CurrentOdinRow); //qDebug() << "this->mp3OdinCount - " << this->mp3OdinCount;

            mp3TableStatus();

            QVector <QString> parameters;
            parameters.push_back(QString::number(this->CickleCount));
            parameters.push_back(ui->ObshTime->text());

            emit TimerToServerSignal(00, parameters);

            CK--; //this->CickleCount--;
       }

       this->CickleCount = CK; qDebug() << "! - " << CK << " - !";

       ui->KolCikleTime->setText(QString::number(CK)); //this->CickleCount));
    }
}

void CickleTimerForm::textForNumberCickles(int numberCickles)
{
    //CickleCount = numberCickles;
    ui->KolvCikleLine->setText(QString::number(numberCickles));

    qDebug() << "textForNumberCickles";

    if (ui->mp3TimeTable->rowCount() > 2) //Если строчек в таблице больше 2, высылаем сигнал
        emit doubleOne();
}

void CickleTimerForm::textForNumberCicklesMany(int numberCickles)
{
    //CickleCount = numberCickles;
    ui->KolvCikleLine->setText(QString::number(numberCickles+1));

    qDebug() << "textForNumberCicklesMany";

   if (ui->mp3TimeTable->rowCount() > 2) //Если строчек в таблице больше 2, высылаем сигнал
       emit doubleMany();
}

void CickleTimerForm::showTime()
{
    //Получить текущее время
    QTime time = QTime::currentTime();
    //Преобразовать его в строку
    QString time_text = time.toString("hh:mm:ss");
    //Вывести в окно
    ui->ObshTime->setText(time_text);
}

void CickleTimerForm::mp3VTable()
{
    QString mp3W = mp3Way();
    QVector <QVector<QString> > mp3Files;
    mp3Files = mp3Dir(mp3W);
    mp3TableHeaders();
    mp3TableInfo(mp3Files);

    this->NachOdinCikleBool = false;
    this->PriosOdinCikleBool = false;
    this->VozobOdinCikleBool = false;
    this->PrervOdinCikleBool = false;

    this->TableFlag = true;

    //При этом все кнопки мноржественных циклов ставятся в true

}

/*
   По нажатию этой кнопки начинается одиночный цикл.
   Во время нажатия NachOdinCikleBool = 0.
   Создаётся массив mp3Tbl, в который из функции mp3TableRead() помещается массив строчек таблицы, состоящих из названий файлов и времени каждого цикла.
   В функции mp3TableTimeRead(mp3Tbl) отрезки времени из массива mp3Tbl преобразуются, хаполняя следующие переменные,
   в которых:
        StartOdinTime = StartOdin; - время начала отсчёта таймера
        FinishOdinTime = FinishOdin; - время окончания отсчёта таймера
        CurrentOdinTime = 0;  - текущее рвемя
        CurrentOdinRow = 0;
        mp3OdinCount = mp3ArraySearch(this->CurrentOdinRow);
        CurrentOdinMany = this->mp3Table.count();

   Для задейстования приостанавливающей и возобновляющей цикл кнопки нужно знать значения каждой глобальной переменной в каждый
   момент времени и обнулять какие то из них, запоминая их значения после нажатия "приостановить", или вставляю запомненные значения
   после "возобновить".

*/

void CickleTimerForm::NachOdinCikle()
{
    if ((this->NachOdinCikleBool == false) && (this->TableFlag == true))
    {
    //...
    QVector <QVector<QString> > mp3Tbl;
    mp3Tbl = mp3TableRead();
    mp3TableTimeRead(mp3Tbl);
    mp3TableStatus();

    //Для создания одноциклового прохода:
    OdinCikleOptions();

    this->NachOdinCikleBool = true;
    this->PriosOdinCikleBool = false;
    this->VozobOdinCikleBool = false;
    this->PrervOdinCikleBool = false;

    QVector <QString> parameters;
    parameters.push_back("0");
    parameters.push_back(ui->ObshTime->text());

    emit TimerToServerSignal(01, parameters);
    }
}

void CickleTimerForm::PriosOdinCikle()
{
    if ((this->PriosOdinCikleBool == false) && (this->NachOdinCikleBool == true))
    {

    //...
    qDebug() << "Приостановить единичный цикл!";
    qDebug() << "Состояние текущих системных переменных: CurrentOdinTime = " << this->CurrentOdinTime << "; CurrentOdinCount = " << this->CurrentOdinCount << "; CurrentOdinRow = " << this->CurrentOdinRow << ";";
    qDebug() << "Состояние неизменных системных переменных: StartOdinTime = " << this->StartOdinTime << "; FinishOdinTime = " << this->FinishOdinTime << "; CurrentOdinMany = " << this->CurrentOdinMany << ";";
    /*Сохранение текущего состояния изменяющегося переменных в бэкап переменных*/
    this->BackupOdinTime = this->CurrentOdinTime;
    this->BackupOdinCount = this->CurrentOdinCount;
    this->BackupOdinRow = this->CurrentOdinRow;
    qDebug() << "Состояние бэкап системных переменных: BackupOdinTime = " << this->BackupOdinTime << "; BackupOdinCount = " << this->BackupOdinCount << "; BackupOdinRow = " << this->BackupOdinRow << ";";
    /*Придание изменяющимся переменным граничных значений, чтобы цикл временнно перестал работать*/
    this->CurrentOdinTime = this->FinishOdinTime;
    this->CurrentOdinCount = this->FinishOdinTime;
    this->CurrentOdinRow = this->CurrentOdinMany;

    this->PriosOdinCikleBool = true;
    this->VozobOdinCikleBool = false;
    this->PrervOdinCikleBool = false;

    QVector <QString> parameters;
    parameters.push_back("0");
    parameters.push_back(ui->ObshTime->text());

    emit TimerToServerSignal(02, parameters);
    }
}

void CickleTimerForm::VozobOdinCikle()
{
    if ((this->PriosOdinCikleBool == true) && (this->NachOdinCikleBool == true) && (this->VozobOdinCikleBool == false))
    {

    //...
    qDebug() << "Возобновить единичный цикл!";
    qDebug() << "Состояние  текущих системных переменных: CurrentOdinTime = " << this->CurrentOdinTime << "; CurrentOdinCount = " << this->CurrentOdinCount << "; CurrentOdinRow = " << this->CurrentOdinRow << ";";
    qDebug() << "Состояние неизменных системных переменных: StartOdinTime = " << this->StartOdinTime << "; FinishOdinTime = " << this->FinishOdinTime << "; CurrentOdinMany = " << this->CurrentOdinMany << ";";
    this->CurrentOdinTime = this->BackupOdinTime;
    this->CurrentOdinCount = this->BackupOdinCount;
    this->CurrentOdinRow = this->BackupOdinRow;

    this->VozobOdinCikleBool = true;
    this->PriosOdinCikleBool = false;
    this->PrervOdinCikleBool = false;

    QVector <QString> parameters;
    parameters.push_back("0");
    parameters.push_back(ui->ObshTime->text());

    emit TimerToServerSignal(03, parameters);
    }
}

void CickleTimerForm::PrervOdinCikle()
{
    if (this->PrervOdinCikleBool == false)
    {

    //...

    this->NachOdinCikleBool = false; qDebug() << "Прервать единичный цикл!";
    this->PriosOdinCikleBool = false;
    this->VozobOdinCikleBool = false;
    this->PrervOdinCikleBool = true; //??? Додумать, почему не меняется флаг

    QVector <QString> parameters;
    parameters.push_back("0");
    parameters.push_back(ui->ObshTime->text());

    emit TimerToServerSignal(04, parameters);
    }

    /*mTranscodingProcess->kill();*/
}

/*------------------*/

void CickleTimerForm::NachMnogoCikle()
{
    if ((this->NachOdinCikleBool == false)  && (this->TableFlag == true))
    {
    //...
    QVector <QVector<QString> > mp3Tbl;
    mp3Tbl = mp3TableRead();
    mp3TableTimeRead(mp3Tbl);
    mp3TableStatus();

    //Для создания многоциклового прохода:
    MnogoCikleOptions();

    this->NachOdinCikleBool = true;
    this->PriosOdinCikleBool = false;
    this->VozobOdinCikleBool = false;
    this->PrervOdinCikleBool = false;


    QVector <QString> parameters;
    parameters.push_back(QString::number(this->CickleCount));
    parameters.push_back(ui->ObshTime->text());

    emit TimerToServerSignal(01, parameters);
    }
}

void CickleTimerForm::PriosMnogoCikle()
{
    if ((this->PriosOdinCikleBool == false) && (this->NachOdinCikleBool == true))
    {

    //...
    qDebug() << "Приостановить единичный цикл!";
    qDebug() << "Состояние текущих системных переменных: CurrentOdinTime = " << this->CurrentOdinTime << "; CurrentOdinCount = " << this->CurrentOdinCount << "; CurrentOdinRow = " << this->CurrentOdinRow << ";";
    qDebug() << "Состояние неизменных системных переменных: StartOdinTime = " << this->StartOdinTime << "; FinishOdinTime = " << this->FinishOdinTime << "; CurrentOdinMany = " << this->CurrentOdinMany << ";";
    /*Сохранение текущего состояния изменяющегося переменных в бэкап переменных*/
    this->BackupOdinTime = this->CurrentOdinTime;
    this->BackupOdinCount = this->CurrentOdinCount;
    this->BackupOdinRow = this->CurrentOdinRow;
    qDebug() << "Состояние бэкап системных переменных: BackupOdinTime = " << this->BackupOdinTime << "; BackupOdinCount = " << this->BackupOdinCount << "; BackupOdinRow = " << this->BackupOdinRow << ";";
    /*Придание изменяющимся переменным граничных значений, чтобы цикл временнно перестал работать*/
    this->CurrentOdinTime = this->FinishOdinTime;
    this->CurrentOdinCount = this->FinishOdinTime;
    this->CurrentOdinRow = this->CurrentOdinMany;

    this->PriosOdinCikleBool = true;
    this->VozobOdinCikleBool = false;
    this->PrervOdinCikleBool = false;

    QVector <QString> parameters;
    parameters.push_back(QString::number(this->CickleCount));
    parameters.push_back(ui->ObshTime->text());

    emit TimerToServerSignal(02, parameters);
    }
}

void CickleTimerForm::VozobMnogoCikle()
{
    if ((this->PriosOdinCikleBool == true) && (this->NachOdinCikleBool == true) && (this->VozobOdinCikleBool == false))
    {

    //...
    qDebug() << "Возобновить единичный цикл!";
    qDebug() << "Состояние  текущих системных переменных: CurrentOdinTime = " << this->CurrentOdinTime << "; CurrentOdinCount = " << this->CurrentOdinCount << "; CurrentOdinRow = " << this->CurrentOdinRow << ";";
    qDebug() << "Состояние неизменных системных переменных: StartOdinTime = " << this->StartOdinTime << "; FinishOdinTime = " << this->FinishOdinTime << "; CurrentOdinMany = " << this->CurrentOdinMany << ";";
    this->CurrentOdinTime = this->BackupOdinTime;
    this->CurrentOdinCount = this->BackupOdinCount;
    this->CurrentOdinRow = this->BackupOdinRow;

    this->VozobOdinCikleBool = true;
    this->PriosOdinCikleBool = false;
    this->PrervOdinCikleBool = false;

    QVector <QString> parameters;
    parameters.push_back(QString::number(this->CickleCount));
    parameters.push_back(ui->ObshTime->text());

    emit TimerToServerSignal(03, parameters);
    }
}

void CickleTimerForm::PrervMnogoCikle()
{
    if (this->PrervOdinCikleBool == false)
    {

    //...

    this->NachOdinCikleBool = false; qDebug() << "Прервать единичный цикл!";
    this->PriosOdinCikleBool = false;
    this->VozobOdinCikleBool = false;
    this->PrervOdinCikleBool = true; //??? Додумать, почему не меняется флаг

    QVector <QString> parameters;
    parameters.push_back(QString::number(this->CickleCount));
    parameters.push_back(ui->ObshTime->text());

    emit TimerToServerSignal(04, parameters);
    }
}
