#ifndef CICKLETIMERFORM_H
#define CICKLETIMERFORM_H

#include <QWidget>
#include <QMediaPlayer>
#include <QDir>
#include <QUrl>

namespace Ui {
class CickleTimerForm;
}

class CickleTimerForm : public QWidget
{
    Q_OBJECT

public:
    explicit CickleTimerForm(QWidget *parent = nullptr);
    ~CickleTimerForm();

private:
    Ui::CickleTimerForm *ui;
    //Переменная состояния кнопки "Начать одиночный цикл"
    bool NachOdinCikleBool;
    //Переменная состояния кнопки "Приостановить одиночный цикл"
    bool PriosOdinCikleBool;
    //Переменная состояния кнопки "Возобновить одиночный цикл"
    bool VozobOdinCikleBool;
    //Переменная состояния кнопки "Прервать одиночный цикл"
    bool PrervOdinCikleBool;
    //Переменная положения в таблице mp3 файлов
    int CurrentOdinCount;
    //Переменная состояния Задания для таймера
    //bool mp3OdinZadan;
    //Время начала одиночного цикла в милисекундах
    int StartOdinTime;
    //Время окончания одиночного цикла в милисекундах
    int FinishOdinTime;
    //текущее время в милисекундах
    int CurrentOdinTime;
    //Текущая строка строкового вектора
    int CurrentOdinRow;
    //количество строк строкового вектора
    int CurrentOdinMany;
    //Время до следующего воспроизведения сообщения
    int CurrentOdinPart;

    //Переменная количества запушенных циклов
    int CickleCount;

    //Переменные для временного хранения текущих значений
    int BackupOdinTime;
    int BackupOdinCount;
    int BackupOdinRow;

    bool TableFlag;

    QStringList output;

    bool Start_flag;
    bool Finish_flag;

    //Объект для проигрывания файлов mp3
    QMediaPlayer *player;

    //Параметры процесса в вектор-массиве
    QVector <QVector <QString>> parameters;

    //Создать слепок состояния таблицы, пригодный для операций
    QVector <QVector<QString> > mp3Table;

    //Получить строку с путём к папке с файлами .mp3
    QString mp3Way();

    //Найти все файлы в заданном каталоге
    QVector <QVector<QString> > mp3Dir (QString mp3W);

    //Создать заголовки для таблицы
    void mp3TableHeaders();

    //Записать в таблицу данные
    void mp3TableInfo(QVector <QVector<QString> > mp3Info);

    //Чтение таблицы в массив
    QVector <QVector <QString> > mp3TableRead();

    //Создание слепка состояния
    void mp3TableTimeRead(QVector <QVector <QString> > mp3Tbl);

    //Превращение количества секунд из числа в строку 00:00:00
    QString mp3Time (int time);

    //Выдача времени из таймеров в лэйблы
    void mp3TimeLabels();

    //Нахождение номера строки в массиве основной таблицы, сообщение которого нужно воспроизвести
    int mp3TimeRow();
    int mp3ArraySearch(int iRow);

    //Воспроизведение отрезка при помощи какого-либо плейера
    void mp3Play(int iRow);

    //Изменение статуса в строке таблицы при помощи номера строки и флага
    void mp3Status(int iRow, bool flag);
    //Изменение статуса во всех строках таблицы
    void mp3TableStatus();

    //Посылка сообщения с сигналом о включении нужной из колонок
    void mp3Switch(int iRow);

    //Задание опций для однопроходного цикла
    void OdinCikleOptions();

    //Задание опций для многопроходного цикла
    void MnogoCikleOptions();

public slots:
    //Показ текущего времени с ПК
    void showTime();
    //Найти все mp3 файлы и поместить их в таблицу
    void mp3VTable();

    //Начать единичный цикл
    void NachOdinCikle();
    //Приостановить единичный цикл
    void PriosOdinCikle();
    //Возобновить единичный цикл
    void VozobOdinCikle();
    //Прервать единичный цикл
    void PrervOdinCikle();

    //Начать единичный цикл
    void NachMnogoCikle();
    //Приостановить единичный цикл
    void PriosMnogoCikle();
    //Возобновить единичный цикл
    void VozobMnogoCikle();
    //Прервать единичный цикл
    void PrervMnogoCikle();

    //Функция запуска одиночного таймера
    void mp3OdinTimer();

    //Функция запуска одиночного таймера
    void mp3MnogoTimer();

signals:

    void SwitchSignal(int DynamicNumber);
};

#endif // CICKLETIMERFORM_H
