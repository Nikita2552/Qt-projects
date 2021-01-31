#ifndef CMDFORM_H
#define CMDFORM_H

#include <QWidget>
#include <QProcess>

namespace Ui {
class cmdForm;
}

class cmdForm : public QWidget
{
    Q_OBJECT

public:
    explicit cmdForm(QWidget *parent = nullptr);
    ~cmdForm();

private:
    Ui::cmdForm *ui;
    //QProcess *m_process;
    //Процесс, в который будет помещаться ffmpeg в окне
    QProcess *mTranscodingProcess;
    //Параметры процесса в вектор-массиве
    QVector <QVector <QString>> parameters;
    //Номер обрабатываемой строки массива
    int i;
    //Длина полученного массива строк:
    int iCount;
    //Промежуточная переменная:
    int iBeta;
    //Переменная прекращения работы окна
    QString iFinish;
    //Переменная пути к файлу ffmpeg.exe
    QString iWay;

public slots:
    //Пример для проверки работы обрезки утилиты ffmpeg:
    void startButton_clicked();
    //Получение данных из потока во время работы утилиты ffmpeg:
    void readyReadStandardOutput();
    //Получение данных из родительской формы и их обработка утилитой ffmpeg:
    void recieveData(QVector <QVector <QString>> parameters, QString ffmpegstr);
    //Слот нажатия кнопки прерывания
    void PrervatData();
/*
    void setStdout();
    void Command();
*/

signals:
    void sendDataCMD ();

    void peredTableFiles (QVector <QVector <QString>> parameters);

    //Сигнал открытия формы cmdF1:
    //void cmdF1_open();

};

#endif // CMDFORM_H
