#ifndef SERVERFORM_H
#define SERVERFORM_H

#include <QWidget>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QAbstractSocket>

#include "checklabelscs.h"
#include "logfile.h"

namespace Ui {
class ServerForm;
}

class ServerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ServerForm(QWidget *parent = nullptr);
    ~ServerForm();

private:
    Ui::ServerForm *ui;

    QVector <QTcpSocket *> MedSock;

    bool connectFlag;
    int count = 32;
    int inputPort;
    int outputPort;

    LogFile newLog;

    QVector <QVector <QString>> ipAdressesArray;

    void tableInit(int count);

    void getIPtabletoArray(int count);

    void setVectorSockets();

    void closeConnections();

public slots:
    void ConnectDisconnectSlot();

    void ServerInterface(int number, QVector <QString> parameters); /* Метод, принимающий сигналы отдругих модулей */

    void TestSlot();

    void TransmitterSlot(int number, QString status, QVector <QString> parameters);

signals:
    void TransmitterSignal(int number, QString status, QVector <QString> parameters);


};

#endif // SERVERFORM_H
