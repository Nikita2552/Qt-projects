#ifndef SERVERFORM_H
#define SERVERFORM_H

#include <QWidget>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QAbstractSocket>

#include "checklabelscs.h"

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

    QVector <QVector <QString>> ipAdressesArray;

    void tableInit(int count);

    void getIPtabletoArray(int count);

    void setVectorSockets();

    void closeConnections();

public slots:
    void ConnectDisconnectSlot();

    void ServerInterface(QVector <QVector <int>> parameter); /* Метод, принимающий сигналы отдругих модулей */

    void TestSlot();
};

#endif // SERVERFORM_H
