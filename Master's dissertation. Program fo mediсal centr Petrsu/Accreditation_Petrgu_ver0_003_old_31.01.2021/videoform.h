#ifndef VIDEOFORM_H
#define VIDEOFORM_H

#include <QWidget>
#include <cmdform.h>
#include <saveform.h>

namespace Ui {
class VideoForm;
}

class VideoForm : public QWidget
{
    Q_OBJECT

public:
    explicit VideoForm(QWidget *parent = nullptr);
    ~VideoForm();

    //Получить текст из текстового поля Wayline
    //QString строчка
    QString WaylineOut ();

    //Вставить текст в текстовое поле Wayline
    //QString строчка
    void WaylineIn (QString waylilestr);

    //Получить текст из текстового поля ffmpegLine
    QString ffmpegLineOut ();

    //Вставить текст в текстовое поле ffmpegLine
    void ffmpegLineIn (QString ffmpeglinestr);

    //Проверка, соответствует ли этот текст абсолютному пути в Windows
    bool TrueWay(QString text1, QString format1);

    //Проверка, соответствует ли этот текст абсолютному пути в Windows
    bool TrueWay(QString text1, QString format1, QString filename1);

    //Проверка, имеюся ли строчки в таблице tableWidget
    bool TrueWay();

    //Удаление строк из таблицы
    void DeleteTable();

    //Прочитать текст из файла и выдать его массивом строчек
    //QList массив строчек QString
    QStringList ReadFileTxt (QString text1);

    //Нахождение всех файлов .mp4 в заданном каталоге и подкаталогах
    QStringList Dirmp4files (QString text1);

    //Заполнение таблицы по информации из двух массивов
    void WayBoxInit (QStringList txtmass, QStringList mp4mass);

    //Создание родительского каталога для нарезанных файлов
    void NarezCatalog();

    //Создание дочерних каталогов для нарезанных файлов по названию родительского файла
    void NarezdaughterCatalog();

    //Нарезка строки с названиями и временем файлов и пересчёт времени
    QVector <QVector <QString>> NarezTimeFile (QString filetime);

    //Создание массива-вектора из параметров:
                //- название выходного файла
                //- путь к входному файлу
                //- путь к выходному файлу
                //- время начала обрезки
                //- длительность обрезаемого файла
    QVector <QVector <QString>> ArrayTimeFile ();

    //Склейка строки "путь с именем входного файла" входного файла
    QString SkleyTimeFile(QString AbsoluteWayStr, QString NameInFile);

    //Получить в многомерный векторный массив все данные из элементов программы
    QVector <QVector <QString>> saveTableSettings();

    bool tableSettingstoFile(QString strway, QVector <QVector <QString>> parameters);

    bool saveLabelSettings(QString savelabel);

    //Получить в многомерный векторный массив все данные из элементов программы
   QVector <QVector <QString>> downAllSettings(QString strway);

   bool fileSettingstoTable(QVector <QVector <QString>> parameters);


private:
    Ui::VideoForm *ui;

    //Ссылка на окно класса дочернего окна для того, чтобы оно не исчезало
   //cmdForm *cmdF1;

    //Ссылка на окно класса окна сохранения/загрузки
    //saveForm *saveF1;

    //Строка с проверенным абсолютным путём к разбираемоемому файлу .txt, при
    //помощи которого создана таблица
    QString WayStr;

    //Строка с абсолютным путём к файлу ffmpeg.exe
    QString WayExe;

public slots:
    void WayTable();
    void WayNarez();
    //Ловить сообщения о завершении процесса контрал - нарезка не завершена процесс окончен  - завершена
    void WayPered(QVector <QVector <QString> > parameters);
    //Меню для сохранения, либо загрузки текущего состояния приложения
    void saveORdown();
    //Возврат из меню сохранения/загрузки для проведения действий
    void saveSettings(QString strway);
    void downSettings(QString strway);

    void mainWindows_cmdF1_show();

    void mainWindows_recieveData_show(QVector<QVector<QString> > parameters, QString parameter);

    void mainWindows_WayPered(QVector<QVector<QString> >);

    void mainWindows_cmdF1_close();


signals:
  //Создание своего собственного сигнала с параметрами. При помощи этого
  //сигнала данные поступают в дочернюю форму и обрабатываются в ней:
  void sendData(QVector <QVector <QString>> parameters, QString ffmpegstr);

  //Создание своего собственного сигнала с параметрами. При помощи этого
  //сигнала данные поступают в форму сохранения и обрабатываются в ней:
  void saveData(QVector <QVector <QString>> parameters);

  //Сигнал передачи статуса!
  void statusDSsignal(QString status);

  //Сигнал открытия формы cmdF1:
  void cmdF1_open();

  //Сигнал передачи данных во внешнее окно для cmdF1
  void mainWindows_sendData(QVector <QVector <QString>> parameters, QString ffmpegstr);

  //Сигнал открытия формы saveF1:
  void saveF1_open();

  void videoForm_peredTableFiles (QVector <QVector <QString> > parameters);

  //Сигнал закрытия формы cmdF1:
  void cmdF1_close();


//void clicked();
//Иcпользуется предусмотренный для кнопки сигнал
//В отличие от слотов сигналы описываются в заголовочном файле, но не реализуются в .cpp

};

#endif // VIDEOFORM_H
