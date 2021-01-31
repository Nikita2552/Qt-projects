#include "videoform.h"
#include "ui_videoform.h"

#include <QLabel>
#include <QHBoxLayout>

#include <QFile>
#include <QDebug>
#include <QDir>
#include <QObject>
#include <QTextCodec>
#include <QTextStream>
#include <QListWidget>
#include <QString>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QHeaderView>
#include <QtMath>
#include <QProcess>
#include <QVector>
#include <QStringList>

#include <QMdiSubWindow>

//Включение заголовочного файла cmd формы
#include <cmdform.h>
//#include <saveform.h>

VideoForm::VideoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoForm)
{
    ui->setupUi(this);

    //Создание формы для сохранения или загрузки текущего состояния
    //saveF1 = new saveForm();

    //connect(ui -> WayButton, SIGNAL (clicked()), this, SLOT (WayInWayOut()));
    //Здесь:
    //"ui -> WayButton" объект, из которого исходит сигнал
    //"clicked()" типовой сигнал с кнопки
    //"this" после подачи сигнала объектом данного класса возвращаемся к нему же
    //"WayInWayOut()" слот, которому адресован данный сигнал
    //connect(ui -> ProvButton, SIGNAL (clicked()), this, SLOT (WayProv()));
    connect(ui -> tableButton, SIGNAL (clicked()), this, SLOT (WayTable()));

    //Событие открытия дочернего окна cmdF1 по нажатию кнопки: (просто показать окно, без действий)
    connect(ui -> rezButton, SIGNAL (clicked()), this, SLOT (mainWindows_cmdF1_show()) );
    //Событие запуска открытия слота, который отправляет данные в
    //внешнее окно cmdF1 через сигнал
    connect(ui -> rezButton, SIGNAL (clicked()), this, SLOT (WayNarez()) );
    //Передача параметров в другое окно по сигналу из слота WayNarez()
    connect(this, SIGNAL(sendData(QVector<QVector<QString> >, QString)), this, SLOT (mainWindows_recieveData_show(QVector<QVector<QString> >, QString)) );

    //Передача параметров из другого окна по сигналу
    //connect(cmdF1, SIGNAL(peredTableFiles (QVector <QVector <QString> >)), this, SLOT(WayPered(QVector<QVector<QString> >)));
    //Событие закрытия дочернего окна по нажатию кнопки: (просто закрыть окно, без действий)
    //connect(cmdF1, SIGNAL (peredTableFiles (QVector <QVector <QString> >)), cmdF1, SLOT (close()));
    //Передача параметров из другого окна по сигналу
    connect(this, SIGNAL(videoForm_peredTableFiles (QVector <QVector <QString> >)), this, SLOT(WayPered(QVector<QVector<QString> >)));
    //Событие закрытия дочернего окна по нажатию кнопки: (просто закрыть окно, без действий)
    connect(this, SIGNAL (videoForm_peredTableFiles (QVector <QVector <QString> >)), this, SLOT (mainWindows_cmdF1_close()));

    //дочернее окно сохранения/загрузки через сигнал
   connect(ui -> sdButton, SIGNAL (clicked()), this, SLOT (saveORdown()));

   //connect(saveF1, SIGNAL(saveSignal(QString)), this, SLOT(saveSettings(QString)));
   //connect(this, SIGNAL(statusDSsignal(QString)), saveF1, SLOT(statusSlot(QString)));

   //connect(saveF1, SIGNAL(downSignal(QString)), this, SLOT(downSettings(QString)));
   //connect(this, SIGNAL(statusDSsignal(QString)), saveF1, SLOT(statusSlot(QString)));

   //connect(this, SIGNAL(saveData(QVector <QVector <QString>>)), saveF1, SLOT(downSettings(QString)));

}

VideoForm::~VideoForm()
{
    delete ui;
}

QString VideoForm::WaylineOut ()
{
    //Получить строчку из текстового поля Wayline
 QString text1 = ui -> Wayline -> text();
 return text1;
}

void VideoForm::WaylineIn(QString waylilestr)
{
    ui -> Wayline -> setText(waylilestr);
}

QString VideoForm::ffmpegLineOut ()
{
    //Получить строчку из текстового поля Wayline
 QString text1 = ui -> ffmpegLine -> text();
 return text1;
}

void VideoForm::ffmpegLineIn (QString ffmpeglinestr)
{
    ui -> ffmpegLine -> setText(ffmpeglinestr);
}

bool VideoForm::TrueWay(QString text1, QString format1)
{
    bool Flag;
    //Flag = true;

    QFileInfo text1info(text1);

    bool file1bool = text1info.isFile();
    QString file1string = text1info.completeSuffix();

    if ((file1bool == true) && (file1string == format1))
        {
        Flag = true;
        }
    else
        {
        Flag = false;
        }
    //Проверка, имеетлся ли файл по этому пути и формата ли он format1
    return Flag;

}

bool VideoForm::TrueWay(QString text1, QString format1, QString filename1)
{
    bool Flag;
    //Flag = true;

    QFileInfo text1info(text1);

    filename1.append(".");
    filename1.append(format1);

    bool file1bool = text1info.isFile();
    QString file1string = text1info.fileName();

    if ((file1bool == true) && (file1string == filename1))
        {
        Flag = true;
        }
    else
        {
        Flag = false;
        }
    return Flag;
}

bool VideoForm::TrueWay()
{
    bool Flag;

    int TabWigRows = ui->tableWidget->rowCount();

    if (TabWigRows > 0)
        {
        Flag = true;
        }
    else
        {
        Flag = false;
        }
    return Flag;

}

void VideoForm::DeleteTable()
{
    ui->tableWidget->setRowCount(0);
}

QStringList VideoForm::ReadFileTxt(QString text1)
{
    //Чтение содержимого файла txt
    QStringList FileList;
    // Пробная строка
    //FileList << "one" << "two" << "three";
    //Создание объекта файл для извлечения строк
    QFile textFile (text1);
    //Открытие файла для чтения и проверка
    bool flag = textFile.open(QIODevice::ReadOnly|QIODevice::Text);
    if (!flag)
        {
            qDebug() << "Ошибка открытия для чтения";
        }
    else
        {
        //Создание массива строк из файла
        QString fileLine;

        //QTextStream in(&fileLine);
         //in.setCodec("UTF-8");
         //Считывать построчно, пока не достигли конца файла
        while(!textFile.atEnd())
        {
            //Чтение из файла как строки построчно
            fileLine = textFile.readLine(); //Считывание строки
            fileLine = fileLine.simplified(); //Удаление \t и \n из текста ASCII, чтобы все пути и строки были корректными
            //Русская кодировка в названии файла отображается только если кодировка .txt файла UTF-8
            FileList.append(fileLine); //Запись в конец списка
        }
        //Закрытие файла после чтения
        textFile.close();
        //Выдача созданного массива
        }
    return FileList;
}

QStringList VideoForm::Dirmp4files(QString text1)
{
    QFileInfoList text3;
    QStringList text2;
    QDir dir(text1);
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
        dir.setFilter(QDir::Files | QDir::AllDirs|QDir::NoDotAndDotDot);
        //Установка фильтра по названию файла. В данном случае маска берётся по формату
        QStringList nameFilter;
        nameFilter << "*.mp4";
        dir.setNameFilters(nameFilter);
        //Указание по сортировке
        //QDir::DirsLast позволяет сначала прочитать файлы, затем уже каталоги
        dir.setSorting(QDir::DirsLast);

        QString str, str1, str_size, text1_size;
        text1_size = text1.size();

        //Проверка, в правильном ли каталоге находимся
        //QString text3;
        //text3 = dir.path();
        //Возвращает массив  строк с именами файлов и названиями дирректорий
        //text2 = dir.entryList(); //QStringList("*.mp4")
        //Это лучше. Возвращает массив объектов с информацией о файлах и дирректориях
        text3 = dir.entryInfoList();
        //Получить массив файлов
        //Получить массив директорий
        for (QFileInfo number : text3)
        {
          //Перебор объектов полученных в массиве и выяснение, файл это или каталог
            if (number.isFile())
                {
                //Добавление в массив text2 названия файла
                str = number.fileName();
                text2.append(str);
                //Добавление в массив text2 абсолютного пути к файлу
                str1 = number.absoluteFilePath();
                text2.append(str1);
                }
            else if (number.isDir())
                {
                //Получение абсолютного пути к папке, но, так как кроме нужных путей
                //в массиве имеются пути в верхнем папкам, мы их удаляем.
                str = number.absoluteFilePath();
                //Сравниваем две строки по содержанию и размеру
                //bool flag_str = str.contains(text1, Qt::CaseInsensitive);
                str_size = str.size();
                //Рекурсивный вызов метода для прохода по всем каталогам:
                QStringList answer = Dirmp4files(str);
                //Организовать корректный возврат из рекурсии!!!
                for (QString number_answer : answer)
                    text2.append(number_answer);
                }
        }

        //Выход на директорию выше!
        dir.cdUp();
     }
    return text2;
}

void VideoForm::WayBoxInit(QStringList txtmass, QStringList mp4mass)
{
        // Удаляем предыдущее содержание таблицы
    //При этом при смене пути к файлу удаляются только строчки, а не их содержимое. Исправить!!!
    //При выставлении количества строк в 1 осталась только одна строка. Что ещё можно сделать?
    //Из-за появления дополнительной строки не запускается дочернее окно!!!
        //ui->tableWidget->clear();
        //ui->tableWidget->setRowCount(1);
        //ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

        // Указываем число колонок
        ui->tableWidget->setColumnCount(5);
        // Указываем число строк
        //ui->tableWidget->setRowCount(5);
        // Устанавливаем заголовки колонок
        QStringList headers;
        headers << "Отметка" << "Имя" << "Расположение" << "Статус" << "Фрагменты";
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        // Включаем сетку
        ui->tableWidget->setShowGrid(true);
        // Разрешаем выделение только одного элемента. ??? Смотреть доки
        //ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        // Разрешаем выделение построчно
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        // Растягиваем последнюю колонку на всё доступное пространство
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        // Скрываем колонку под номером 5
        //ui->tableWidget->hideColumn(4);
        //Запрет редактирования строк
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        QStringList thisrow;
        QString it;
        thisrow << "one" << "two" << "three" << "four" << "five";
        //Количество строк в таблице или количество строк в массиве
        QRegExp reg1("^[\\D\\d]+.mp4$"); //"^*.mp4$"
        //QRegExp reg1("^*.mp4$");
        //\D - символ нецифры
        //\d - символ цифры
        //[ ] - в каком диапазоне будут лежать символы
        // + - символов может быть сколько угодно
        QRegExp reg2("^[\\D\\d]+.mp4\\s[0-6][0-9]:[0-6][0-9]:[0-6][0-9]\\s[0-6][0-9]:[0-6][0-9]:[0-6][0-9]$");
        //^,$ - символы начала и конца строки, с ними сравниваемая строка должна
        //точно соответствовать маске
        //\s - символ пробела
        //Первый элемент, с которого ищутся сопадения
        int regsize = 22; //длина регулярного выражения
        int zero_element = 0;
        //int txtflag = 0;
        int sizeRows = txtmass.size();
        QString txtelement_one, txtelement_two, mp4timestring, textWay;
        //txtelement_one первое совпадение по регулярному выражению reg1
        //txtelement_two второе совпадение по регулярному выражению reg1
        //mp4timestring переменная для записи результирующей строки из
        //названий и временных отрезков
        int txtnumber_one, txtnumber_two, mp4size, mp4timesize;

        QStringList mp4number, mp4timelist;
        // Создаём строку!!!
        ui->tableWidget->insertRow(0);
        txtelement_one = txtmass.at(0);
        txtelement_two = txtmass.at(1);

        //Папка, откуда берётся видео
        QTableWidgetItem *item5 = new QTableWidgetItem(txtelement_one);
        // вставляем ячейку
        ui->tableWidget->setItem(0, 2, item5);
        //Папка, где будет нарезанное видео
        QTableWidgetItem *item6 = new QTableWidgetItem(txtelement_two);
        // вставляем ячейку
        ui->tableWidget->setItem(0, 3, item6);

        // Скрываем строку под номером 0
        //ui->tableWidget->hideRow(0);

        for (int i = 1; i < sizeRows; i++)
            {
            //Заполняем созданную строку
            //Находим первое вхождение "*.mp4" в массиве строк
            txtnumber_one = txtmass.indexOf(reg1, zero_element);
            //Находим второе вхождение "*.mp4" в массиве строк
            txtnumber_two = txtmass.indexOf(reg1, txtnumber_one + 1);
            if (txtnumber_one == -1)
                {
          //Если первое совпадение не находится, то выход из цикла.
                break;
                }
            else
                {
                txtelement_one = txtmass.at(txtnumber_one);
                mp4number = mp4mass.filter(txtelement_one);
                //Если совпадений в первом и втором массиве не находится
                textWay = "null";
                //Возвращает true, если массив пуст
                if (!mp4number.isEmpty())
                    {
                    textWay = mp4number.at(1);
                    }
                }
            if (txtnumber_two > -1)
               {
               mp4size = txtnumber_two;
               }
            else
               {
               mp4size = sizeRows;
               }
            for (int j = txtnumber_one + 1; j < mp4size; j++)
                {
              //Создание строки из названий и времени обрезков
                mp4timestring = txtmass.at(j);
                mp4timesize = mp4timestring.size();
              //Проверка, является ли количество символов в рассмативаемой строке большимм,
              //чем количество символов в регулярном вырожении. Без неё indexOf выдаёт ошибку!!!
                if (mp4timesize > regsize)
                    {
                    int txtflag = mp4timestring.indexOf(reg2, 0);
                    if (txtflag > -1)
                        {
                        mp4timelist.append(mp4timestring);
                        }
                    }
               }
            //Создание из массива строк названий файлов и отрезков времени единой строки
                QString textString = mp4timelist.join(";");
            //Обнудение массива
                mp4timelist.clear();
                zero_element = txtnumber_two;

            // Создаём строку!!!
            ui->tableWidget->insertRow(i); //i);

            //Создание объекта чекбокс
            QTableWidgetItem *itemcheck = new QTableWidgetItem();
            //Установка чекбокса в состояние "не нажат"
            itemcheck->setCheckState(Qt::Unchecked);
            //Добавление чекбокса в таблицу
            ui->tableWidget->setItem(i, 0, itemcheck);

            // выделяем память под ячейку вставляем строку
            QTableWidgetItem *item1 = new QTableWidgetItem(txtelement_one);
            // вставляем ячейку
            ui->tableWidget->setItem(i, 1, item1);
            // выделяем память под ячейку вставляем строку
            QTableWidgetItem *item2 = new QTableWidgetItem(textWay);
            // вставляем ячейку
            ui->tableWidget->setItem(i, 2, item2);
            //Выставляем статус
            QString textStatus = "Целый";
            // выделяем память под ячейку вставляем строку
            QTableWidgetItem *item3 = new QTableWidgetItem(textStatus);
            // вставляем ячейку
            ui->tableWidget->setItem(i, 3, item3);
            // выделяем память под ячейку вставляем строку
            QTableWidgetItem *item4 = new QTableWidgetItem(textString);
            // вставляем ячейку
            ui->tableWidget->setItem(i, 4, item4);

        }
}

void VideoForm::NarezCatalog()
{
    //qDebug() << "Hi";
    QString text = ui->tableWidget->item(0,3)->text();
    //qDebug() << text;
    QString razdel = "/";
    //qDebug() << razdel;
    int num;
    //Получение последнего вхождения подстроки для создания папки, если её нет
    //lastIndexOf(razdel) - получение последнего вхождения
    num = text.lastIndexOf(razdel);
    QString numb  = QString::number(num); qDebug() << numb;
    //Получение абсолютного пути к создаваемой папке с нарезанным видео
    //left(num) - вырезание подстроки слева от последнего вхождения
    QString absoluteWay = text.left(num); qDebug() << absoluteWay;
    //Получение названия создаваемой папки
    //mid(num + 1) - вырезание подстроки справа от последнего вхождения
    QString nameOfcatalog = text.mid(num + 1); qDebug() << nameOfcatalog;
    QDir dir(absoluteWay);
    bool flag_absoluteWay = dir.exists();
    if (!flag_absoluteWay)
        qWarning("absoluteWay - Данную директорию невозможно найти!");
    //mkdir(nameOfcatalog) - создание каталога по указанному пути
    bool flag_nameOfcatalog = dir.mkdir(nameOfcatalog);
    if (!flag_nameOfcatalog)
        qWarning("nameOfcatalog - Данную директорию создать не удалось!");

}

void VideoForm::NarezdaughterCatalog()
{
     qDebug() << "Hi";
     QString oldnameOffile, oldwayOffile;
     QString razdel = ".mp4";
     QString textStatus = "Нет источника";
     QString absoluteWay = ui->tableWidget->item(0,3)->text();
     QString way_check;
     QDir dir(absoluteWay);
     bool flag_absoluteWay = dir.exists();
     if (!flag_absoluteWay)
         qWarning("absoluteWay 1 - Данную директорию невозможно найти!");
    //Получение общего колличества строк
    int rows = ui->tableWidget->rowCount();
    //Перебор таблицы построчно
    for (int i = 1; i < rows; i++)
    {
     /*   QString numb  = QString::number(i);
        //Вывод сообщений в консоль
        qDebug() << numb;
        //Получение скрытого элемента с путём, где нужно создавать файлы.
        qDebug() << absoluteWay;
*/
        //Извлечение статуса чекбокса: нажат/не нажат
        bool flag_check = ui->tableWidget->item(i,0)->checkState(); qDebug() << flag_check;
        //Получение названия файла с форматом
        oldnameOffile = ui->tableWidget->item(i,1)->text(); qDebug() << oldnameOffile;
        way_check = ui->tableWidget->item(i,2)->text(); qDebug() << way_check;
        if ((flag_check == true) && (way_check != "null"))
        {
            int num = oldnameOffile.lastIndexOf(razdel);
            QString newcatalogOfflile = oldnameOffile.left(num);
        //Создание дочерних каталогов с именами файлов
            bool flag_newcatalogOfflile = dir.mkdir(newcatalogOfflile);
            if (!flag_newcatalogOfflile)
                qWarning("newcatalogOfflile - Данную директорию создать не удалось!");
        }
        else if (way_check == "null")
            ui->tableWidget->item(i,3)->setText(textStatus);
    }
}

QVector <QVector <QString>> VideoForm::NarezTimeFile(QString filetime)
{
    int t1, t2, t3, a, b, sect1, sect2, sec1, sec2;
    QStringList sectime1, sectime2; qDebug() << filetime;
    QString spl1 = ";";
    QString spl2 = " ";
    QString spl3 = ":";
    QString Time1, Time2, Nartime, sect01, sect02, t3str, t2str, t1str;
    //Создание двумерного вектора - двумерного массива из векторов (массивов) строк
    QVector <QVector <QString>> NarezTime;
    QVector<QString> NarezTimeStr;
    //Поделить по "; "
    QStringList oneFiletime = filetime.split (spl1);

    for (QString number_oneFiletime : oneFiletime)
    {
        //qDebug() << number_oneFiletime;
    //Поделить по " "
        QStringList oneTime = number_oneFiletime.split (spl2);

        //показать созданный массив
        //for (QString number_oneTime : oneTime)
        //      qDebug() << number_oneTime;

    //Поделить каждое время на ":"
        Time1 = oneTime.at(1); //qDebug() << Time1;
        Time2 = oneTime.at(2); //qDebug() << Time2;
        sectime1 = Time1.split (spl3);
        sectime2 = Time2.split (spl3);
        sec1 = 0;
        sec2 = 0;
        Nartime = "";
        for (int i = 0; i < 3; i++)
        {
        //Получение секунды\минуты\часа первого отрезка и преобразование из строки в число
        sect01 = sectime1.at(i); //qDebug() << sect01;
        sect1 = sect01.toInt(); //qDebug() << sect1;
        //Получение секунды\минуты\часа второго отрезка и преобразование из строки в число
        sect02 = sectime2.at(i); //qDebug() << sect02;
        sect2 = sect02.toInt(); //qDebug() << sect2;
        sec1 = sec1 + sect1 * qPow(60,2 - i); //qDebug() << sec1;
        sec2 = sec2 + sect2 * qPow(60,2 - i); //qDebug() << sec2;
        }
        //Получение разницы первого и второго отрезка
        int sectreg = sec2 - sec1; //qDebug() << sectreg;
        //Вычисление секунд
        a = sectreg / 60;
        t1 = sectreg - a * 60; //qDebug() << t1;
        //Вычисление минут
        b = a / 60;
        t2 = a - b * 60; //qDebug() << t2;
        //Получение часов
        t3 = b; //qDebug() << t3;

        t3str  = QString::number(t3);
        Nartime.append(t3str);
        Nartime.append(":");
        t2str  = QString::number(t2);
        Nartime.append(t2str);
        Nartime.append(":");
        t1str  = QString::number(t1);
        Nartime.append(t1str); //qDebug() << Nartime;

        //Создание массива-вектора из строк с имя нарезанного файла/начальное время/конечное время
        //push_back() - аналог append() для вектора
        NarezTimeStr.push_back(oneTime.at(0));
        NarezTimeStr.push_back(oneTime.at(1));
        NarezTimeStr.push_back(Nartime);

        //Добавление созданного массива строк к двумерному массиву
        NarezTime.push_back(NarezTimeStr);
        NarezTimeStr.clear();

        //переменные, в которых хранится информация:
        //oneTime имя нарезанного файла/начальное время/конечное время
        //Nartime длина создаваемого отрезка по времени

    }

    return NarezTime;
}

QVector<QVector<QString> > VideoForm::ArrayTimeFile()
{
    QVector <QVector <QString>> arrayTimevect, arrayNarezTime;
    QVector <QString> arrayTimevectStr, arrayNarezka;
    QString iString1, iString2, iString3, iString4, iString5, iString6, iString7, iString8, Status;
    bool flag_check;
    flag_check = false;

    //В цикле:
    //Извлечение строки из таблицы:
    int i, j, tableCount, row4Count; //номер строки/номер элемента в строке/количество строк таблицы
    tableCount = ui->tableWidget->rowCount(); qDebug() << "!! - " << tableCount;
    for (i = 1; i < tableCount; i++)
        {
        Status = ui->tableWidget->item(i,3)->text();
        flag_check = ui->tableWidget->item(i,0)->checkState(); qDebug() << flag_check;
        if ( ((Status == "Целый") || (Status == "Нарезается")) && (flag_check == true) )
            {
            //-название файла
            iString1 = ui->tableWidget->item(i,1)->text(); qDebug() << iString1;
            //arrayTimevectStr.push_back(iString);// qDebug() << arrayTimevectStr;

            //-строка с фрагментами через ; (названиефайла/время начала обрезки/длительность обрезаемого файла)
            iString2 = ui->tableWidget->item(i,4)->text(); qDebug() << iString2;
            //Превращение последней строки в массив строчек:
            //-Название выходного файла
            //-время начала обрезки
            //-длина обрезаемого файла
            arrayNarezTime = NarezTimeFile(iString2); qDebug() << arrayNarezTime;
            //вычислить длину массива и создать строчки с дибликатами общих записей
            //-путь к исходному файлу с именем файла
            iString3 = ui->tableWidget->item(i,2)->text(); qDebug() << iString3;
            //arrayTimevectStr.push_back(iString3); qDebug() << arrayTimevectStr;

            //-путь к выходному файлу с именем файла
            //Получение пути к папке, в которой будут нарезанные файлы
            iString4 = ui->tableWidget->item(0,3)->text();
            //Получение пути к папке, где будут нарезанные из конкретного файла файлы
            iString5 = SkleyTimeFile (iString4, iString1); qDebug() << iString5 << " -- !!";

            row4Count = arrayNarezTime.count();
            for (j = 0; j < row4Count; j++)
            {
              //Получение названиефайла/время начала обрезки/длительность обрезаемого файла
              arrayNarezka = arrayNarezTime.at(j); qDebug() << arrayNarezka;
              //-время начала обрезки
              arrayTimevectStr.push_back(arrayNarezka.at(1));
              //-длина обрезаемого файла
              arrayTimevectStr.push_back(arrayNarezka.at(2));
              //-путь к исходному файлу с именем файла
              arrayTimevectStr.push_back(iString3);
              //-путь к выходному файлу с именем файла
              iString6.append(iString5);
              //Название выходного файла
              iString7 = arrayNarezka.at(0);
              //Название входного файла
              iString8 = ui->tableWidget->item(i,1)->text();
              iString6.append(iString7);
              arrayTimevectStr.push_back(iString6);
              arrayTimevectStr.push_back(iString7);
              arrayTimevectStr.push_back(iString8);
              arrayTimevect.push_back(arrayTimevectStr); qDebug() << arrayTimevectStr;
              arrayTimevectStr.clear();
              iString6.clear();
            }

          }

        //Создание массива:
        //-название файла
        //-время начала обрезки
        //-длина обрезаемого файла
        //-путь к исходному файлу с именем файла
        //-путь к выходному файлу с именем файла
        //Все файлы должны быть со статусом "Целый"

        }

    return arrayTimevect;
}

QString VideoForm::SkleyTimeFile(QString AbsoluteWayStr, QString NameInFile) //, QString NameOutFile)
{
    QString Outputstr, catalogOutFile;
    int index;

    QString reg = ".mp4";
    index = NameInFile.indexOf(reg);
    if (index >= 0)
    {
        catalogOutFile = NameInFile.left(index);
        Outputstr.append(AbsoluteWayStr);
        Outputstr.append("/");
        Outputstr.append(catalogOutFile);
        Outputstr.append("/");
        //Outputstr.append(NameOutFile);
    }

    return Outputstr;
}

QVector<QVector<QString> > VideoForm::saveTableSettings()
{

    int tableCount = ui->tableWidget->rowCount(); qDebug() << "tableCount - saveAllSettings" << tableCount;
    QVector <QString> elements;
    QVector <QVector <QString>> array_of_elements;
    QString str;
    bool flag_check = false;

    str = "***";
    elements.push_back(str);
    elements.push_back(str);
    str = ui->tableWidget->item(0,2)->text(); qDebug() << "TW1 - " << str;
    elements.push_back(str);
    str = ui->tableWidget->item(0,3)->text(); qDebug() << "TW1 - " << str;
    elements.push_back(str);
    str = "***";
    elements.push_back(str);
    array_of_elements.push_back(elements);
    elements.clear();

    for (int i = 1; i < tableCount; i++)
    { //qDebug() << "i - saveAllSettings" << i;

        //Проверить, есть ли чекбокс в ячейке???
        if (ui->tableWidget->item(i,0) != 0)
        {
        flag_check = ui->tableWidget->item(i,0)->checkState();// qDebug() << flag_check;
        if (flag_check)
        {
            str = "true";
        }
        else
        {
            str  = "false";
        }
        elements.push_back(str);
        }

        for (int j = 1; j < 5; j++)
        {
            if (ui->tableWidget->item(i,j) != 0)
            {
                str = ui->tableWidget->item(i,j)->text();
            }
            else
            {
                str = "***";
            }
            elements.push_back(str);
        }
        array_of_elements.push_back(elements);
        elements.clear();
    } //qDebug() << array_of_elements;
/*
    QVector <QString> one;
    one << "one" << "two";
    QVector <QVector<QString> > parameters;
    parameters.push_back(one);
    parameters.push_back(one);

    return parameters;
*/
    return array_of_elements;
}

bool VideoForm::tableSettingstoFile(QString strway, QVector <QVector <QString>> parameters)
{
    qDebug() << parameters;
    qDebug() << strway;

    QVector <QString> str_paremeter;
    QString str, way, ffmpeg;
    int iCount;

    QFile textFile (strway);
    //Открытие файла для чтения и проверка
    bool open_flag = textFile.open(QIODevice::WriteOnly|QIODevice::Text);
    if (!open_flag)
    {
        qDebug() << "Ошибка открытия для чтения";
    }
    else
    {
        iCount = parameters.count();

        QTextStream writeStream(&textFile);
        writeStream.setCodec("utf-8");

        for (int i = 0; i < iCount; i++)
        {
            str_paremeter = parameters.at(i);

            for (int j = 0; j < 5; j++)
            {
                str = str_paremeter.at(j); qDebug() << str;
                writeStream << str;
                writeStream << "|"; //qDebug() << "|";
                //?? textFile.write(str.arg(i).arg(total).arg(fileName).toUtf8());
                //str = "HI!";
                //textFile.write("HI!");
            }
            writeStream << "\n";// qDebug() << "|";
            str.clear();
            //iCount = 0;

        }
        way = WaylineOut ();
        ffmpeg = ffmpegLineOut ();

        writeStream << "\n\n" << way << "\n" << ffmpeg << "\n" << strway;
    }
    textFile.close();

    bool flag = true;
    return flag;
}

bool VideoForm::saveLabelSettings(QString savelabel)
{
    QString way, ffmpeg;
    way = WaylineOut ();
    ffmpeg = ffmpegLineOut ();
    QFile textFile (savelabel);
    //Открытие файла для чтения и проверка
    bool open_flag = textFile.open(QIODevice::WriteOnly|QIODevice::Text);
    if (!open_flag)
    {
        qDebug() << "Ошибка открытия для чтения";
    }
    else
    {
        QTextStream writeStream(&textFile);
        writeStream << "\n\n" << way << "\n" << ffmpeg << "\n" << savelabel;
    }

    bool flag = true;
    return flag;
}

QVector<QVector<QString> > VideoForm::downAllSettings(QString strway)
{
 /*   QVector <QString> one;
    one << "one" << "two";
    QVector <QVector<QString> > parameters;
    parameters.push_back(one);
    parameters.push_back(one);
*/
    //Чтение содержимого файла txt
    QVector<QVector<QString> > FileVect;
    QVector<QString> vectStr;
    //Создание объекта файл для извлечения строк
    QFile textFile (strway);
    //Открытие файла для чтения и проверка
    bool flag = textFile.open(QIODevice::ReadOnly|QIODevice::Text);
    if (!flag)
        {
            qDebug() << "Ошибка открытия для чтения";
        }
    else
        {
        //Создание массива строк из файла
        QString fileLine;
        QStringList fileLineList, fileLineSPL;
        int iCount = 0;

        //QTextStream in(&fileLine);
         //in.setCodec("UTF-8");
        //Узнать, сколько строк в файле
        while(!textFile.atEnd())
        {
        fileLine = textFile.readLine(); //Считывание строки
        fileLine = fileLine.simplified(); //Удаление \t и \n из текста ASCII, чтобы все пути и строки были корректными
        //Русская кодировка в названии файла отображается только если кодировка .txt файла UTF-8
        fileLineList.append(fileLine);
        iCount++;
        } qDebug() << "iCount - " << iCount; qDebug() << "iCount - " << fileLineList; qDebug() << "_______ ";

        for (int i = 0; i < iCount - 5; i++)
        {
            fileLine = fileLineList.at(i);
            fileLineSPL = fileLine.split("|");
            fileLineSPL.removeLast();
            int jCount = fileLineSPL.count();
            for (int j = 0; j < jCount; j++)
            {
                vectStr.push_back(fileLineSPL.at(j));
            }
            FileVect.push_back(vectStr);
            vectStr.clear();
        }

        for (int i = iCount - 3; i < iCount; i++)
        { qDebug() << i;
            vectStr.push_back(fileLineList.at(i)); qDebug() << fileLineList.at(i);
            FileVect.push_back(vectStr);
            vectStr.clear();
        }
        //Закрытие файла после чтения
        textFile.close();
        //Выдача созданного массива
        }

    return FileVect;
}

bool VideoForm::fileSettingstoTable(QVector<QVector<QString> > parameters)
{
    // Указываем число колонок
    ui->tableWidget->setColumnCount(5);
    // Указываем число строк
    //ui->tableWidget->setRowCount(5);
    // Устанавливаем заголовки колонок
    QStringList headers;
    headers << "Отметка" << "Имя" << "Расположение" << "Статус" << "Фрагменты";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    // Включаем сетку
    ui->tableWidget->setShowGrid(true);
    // Разрешаем выделение только одного элемента. ??? Смотреть доки
    //ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    // Скрываем колонку под номером 5
    //ui->tableWidget->hideColumn(4);
    //Запрет редактирования строк
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    qDebug() << parameters;

    QVector<QString> parameter = parameters.at(0);
    QString folderway2, folderway3;
    folderway2 = parameter.at(2);
    folderway3 = parameter.at(3);

    // Создаём строку!!!
    ui->tableWidget->insertRow(0);

    // выделяем память под ячейку вставляем строку
    QTableWidgetItem *item02 = new QTableWidgetItem(folderway2);
    // вставляем ячейку
    ui->tableWidget->setItem(0, 2, item02);
    // выделяем память под ячейку вставляем строку
    QTableWidgetItem *item03 = new QTableWidgetItem(folderway3);
    // вставляем ячейку
    ui->tableWidget->setItem(0, 3, item03);

    int arrayCount = parameters.count();

    for (int i = 1; i < (arrayCount - 3); i++)
    {
        // Создаём строку!!!
        ui->tableWidget->insertRow(i);
        parameter = parameters.at(i);
        QString iCheckbox = parameter.at(0);
        //Создание объекта чекбокс
        QTableWidgetItem *itemcheck = new QTableWidgetItem();
        if (iCheckbox == "true")
        {
            //Установка чекбокса в состояние "нажат"
            itemcheck->setCheckState(Qt::Checked);
        }
        else
        {
            //Установка чекбокса в состояние "не нажат"
            itemcheck->setCheckState(Qt::Unchecked);
        }
        //Добавление чекбокса в таблицу
        ui->tableWidget->setItem(i, 0, itemcheck);
    }

    for (int i = 1; i < (arrayCount - 3); i++)
    {
        parameter = parameters.at(i);
        int parCount = parameter.count();
        for (int j = 1; j < parCount; j++)
        {
            // выделяем память под ячейку вставляем строку
            QTableWidgetItem *item = new QTableWidgetItem(parameter.at(j));
            // вставляем ячейку
            ui->tableWidget->setItem(i, j, item);
        }
    }

    parameter = parameters.at(arrayCount - 3);
    WaylineIn(parameter.at(0));
    this->WayStr = parameter.at(0);
    parameter = parameters.at(arrayCount - 2);
    ffmpegLineIn(parameter.at(0));
    this->WayExe = parameter.at(0);

    bool flag = true;
    return flag;
}


void VideoForm::WayTable()
{
    //Реализация слота. Получение строчки из текстового поля и вставка в список
    QString text1 = WaylineOut();
    QString text0 = ffmpegLineOut();
    //Проверка, соответствует ли полученный текст абсолютному пути к файлу
    QString format1 = "txt";
    bool truewayFlag1 = TrueWay(text1, format1);
    //Проверка, соответствует ли полученный текст абсолютному пути к файлу
    QString format0 = "exe";
    QString filename0 = "ffmpeg";
    bool truewayFlag0 = TrueWay(text0, format0, filename0);
    //Проверка, имеется ли в пути к ffmpeg название самой утилиты,
    //Существует ли такой файл по заданному пути!!!
    //Если соответствует, совершаем следующие действия
    //Проверка, имеются ли строки в таблице
    bool truewayFlag2 = TrueWay();
    //Если строки в таблице имеются
    if (truewayFlag2 == true)
        {
        DeleteTable(); qDebug() << "Удаление строк из таблицы!!!";
        }
    if ((truewayFlag0 == true) && (truewayFlag1 == true) && (WayStr != text1))
        {
        //Получение массива строчек из файла .txt и вставка в список
        QStringList listtext1 = ReadFileTxt(text1);
        //Вернуть элемент 0 - путь к исходным файлам .mp4
        QString text2, text3;
        text2 = listtext1.at(0);
        //Получение массива из названий найденных .mp4 и абсолютных путей
        QStringList listtext2 = Dirmp4files(text2);
        //Создание таблицы по полученным данным
        WayBoxInit(listtext1, listtext2);
        //Сохранение проверенного полного пути к файлу .txt в переменную WayStr
        this->WayStr = text1;
        //Сохранение проверенного полного пути к файлу ffmpeg.exe в переменную WayExe
        this->WayExe = text0;
        ui->errorLabel->setText("УСПЕХ! Оба пути введены\n верно.");
        }
    //Если
        //-это не путь,
        //или такого файла .exe не существует,
        //или таблица по этому пути уже создана,
    //вызываем окно с сообщением
    else
        {
        //Реализация окна с сообщением
        qDebug() << "ОШИБКА!!!!";
        ui->errorLabel->setText("ОШИБКА! Не верно введён\n один из путей\n к файлам.");
        }
}

void VideoForm::WayNarez()
{
    //Проверка, имеются ли строки в таблице
    bool truewayFlag2 = TrueWay();
    //Если строки в таблице имеются
    if (truewayFlag2 == true)
    {
    //Создание родительского каталога
    NarezCatalog();
    //Создание дочерних каталогов файлов, которые помечены
    NarezdaughterCatalog();
    //Перебор всех помеченных строчек, вычисление разницы по времени и нарезка файлов
    //Получение списка массивов названиефайла/время начала обрезки/длительность обрезаемого файла
    //Получение массива время начала обрезки/длительность обрезаемого файла/путь к обрезаемому
    //файлу/путь к обрезанному файлу в массиве вектор
    //Для всех обрезаемых файлов
    QVector <QVector <QString>> arraytimeList;
    arraytimeList = ArrayTimeFile(); qDebug() << arraytimeList;
    //Строка для примера
    //QString param = "-codecs";
    //Запуск процесса ffmpeg
    //NarezFfmpegProcess(param);

    //Вызов сигнала, в который передаются введённые данные (полученный массив),
    //которые потом должны будут переданы в форму
    QString ffmpegstr;
    //ffmpegstr = "D:/OOP/NarezkaFailov/ffmpeg/bin/ffmpeg.exe";
    ffmpegstr = this->WayExe;
    //Открытие окна сразу по событию, а не через сигнал.
    //cmdF1->show();
    emit cmdF1_open();
    //Параметры из одного окна в другое лучше передавать только через сигнально-слотовое
    //соединение, так как это потокобезопасно!
    emit sendData(arraytimeList, ffmpegstr);
    }
}

//Ловить сообщения о завершении процесса контрал - нарезка не завершена процесс окончен  - завершена
void VideoForm::WayPered(QVector<QVector<QString> > parameters)
{
    qDebug() << parameters;
    //Нахождение количества строк в таблице
    int rows = ui->tableWidget->rowCount();
    //Нахождение количества строк в массиве обработанных строк
    int iparameters = parameters.count(); qDebug() << "iparameters" << iparameters;
    bool StatusFlag = false;
    //Перебор всех строк в таблице и удаление из их списков нарезаемых файлов
    //уже нарезанных
    for (int i = 1; i < rows; i++)
    {
        //Название исходного файла
        QString nameOfOldfile = ui->tableWidget->item(i,1)->text(); qDebug() << i << " - " << nameOfOldfile;
        //Извлечение строки с названиями порезаемых файлов через ;
        QString strOfOldfile = ui->tableWidget->item(i,4)->text(); qDebug() << i << " - " << strOfOldfile;

        //Разбиение строки на массив
        QString spl1 = ";";
        QStringList listOfOldfile = strOfOldfile.split (spl1); qDebug() << listOfOldfile;

        int strFlag = listOfOldfile.count();

        QStringList filterOfOldFile;
        QVector <QString> strparameters;
        QString Status;
        //Перебор массива с нарезанными файлами и их сравнения с массивом
        //строчек
        for (int j = 0; j < iparameters; j++)
        {
            qDebug() << j;
            strparameters = parameters.at(j); qDebug() << strparameters;
            if (strparameters.at(0) == nameOfOldfile)
            {
            QString nameOfNewfile = strparameters.at(1);

            filterOfOldFile = listOfOldfile.filter(nameOfNewfile); qDebug() << "HI" << filterOfOldFile << " - HI";
            //Всё верно, так как filterOfOldFile массив строк, в котором всего
            //один элемент - 0. Его и берём.
            listOfOldfile.removeOne(filterOfOldFile.at(0));
            }
        }
        //filterOfOldFile.clear();
        int ilist = listOfOldfile.count(); qDebug() << "ilist - " << ilist << "strFlag - " << strFlag;
        if ((ilist > 0) && (ilist < strFlag))
        {
            strOfOldfile = listOfOldfile.join(";"); qDebug() << "IlistIF" << strOfOldfile << " - IlistIF";
            Status = "Нарезается";
            StatusFlag  = true;
        }
        else if (ilist == 0)
        {
            strOfOldfile = "0"; qDebug() << "IlistELSE" << strOfOldfile << " - IlistELSE";
            Status = "Нарезан";
            StatusFlag  = true;
        }

        if (StatusFlag == true)
        {
        // выделяем память под ячейку вставляем строку
        QTableWidgetItem *item3 = new QTableWidgetItem(Status);
        // вставляем ячейку
        ui->tableWidget->setItem(i, 3, item3);
        // выделяем память под ячейку вставляем строку
        QTableWidgetItem *item4 = new QTableWidgetItem(strOfOldfile);
        // вставляем ячейку
        ui->tableWidget->setItem(i, 4, item4);
        }
        StatusFlag = false;
    }

}

//Показать подменю с сохранением.загрузкой настроек
void VideoForm::saveORdown()
{
    //cmdF1->show();
    //emit cmdF1_open();
}

//Открываем меню сохранения и отправляем ему данные.
void VideoForm::saveSettings(QString strway)
{
    QString format1, status;
    format1 = "txt";
    bool truewayFlag1 = TrueWay(strway, format1);
    if (truewayFlag1 == true)
    {
    QVector <QVector<QString> > parameters;
    parameters = saveTableSettings(); //qDebug() << parameters; qDebug() << strway;
    bool flag1 = tableSettingstoFile(strway, parameters);
    //bool flag2 = saveLabelSettings(strway);
    status = "Сохранено"; qDebug() << status;
    }
    else
    {
    status = "Ошибка в пути сохранения"; qDebug() << status;
    }

    emit statusDSsignal(status);
}

void VideoForm::downSettings(QString strway)
{
    QString format1, status;
    format1 = "txt";
    bool truewayFlag1 = TrueWay(strway, format1);
    //Проверка, имеются ли строки в таблице
    bool truewayFlag2 = TrueWay();
    //Если строки в таблице имеются
    if (truewayFlag2 == true)
    {
        DeleteTable(); qDebug() << "Удаление строк из таблицы!!!";
    }
    if (truewayFlag1 == true)
    {
    QVector <QVector<QString> > parameters;
    parameters = downAllSettings(strway); //qDebug() << parameters; qDebug() << strway;
    bool flag1 = fileSettingstoTable(parameters);
    status = "Загружено"; qDebug() << status;
    }
    else
    {
    status = "Ошибка в пути загрузки"; qDebug() << status;
    }


    emit statusDSsignal(status);
}

//Обращение к родительскому окну для показа окна cmdF1
void VideoForm::mainWindows_cmdF1_show()
{
    emit cmdF1_open();
}

void VideoForm::mainWindows_recieveData_show(QVector<QVector<QString> > parameters, QString parameter)
{
    emit mainWindows_sendData(parameters, parameter);
}

void VideoForm::mainWindows_WayPered(QVector<QVector<QString> > parameters)
{
    qDebug() << "videoForm_peredTableFiles!!!";

    emit videoForm_peredTableFiles (parameters);
}

void VideoForm::mainWindows_cmdF1_close()
{
    qDebug() << "mainWindows_cmdF1_close!!!";

    emit cmdF1_close();
}
