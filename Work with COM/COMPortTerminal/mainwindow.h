#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void StartOrStopConnectSlot();
    void serialTransmit();
    void cleanTerminal();
    void serialRecieve();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    bool ConnectFlag = false;
    QStringList ComPorts;

    void programInit();

    void programReInit();
};
#endif // MAINWINDOW_H
