#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include <QWidget>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QAbstractSocket>

#include "checklabelscs.h"

namespace Ui {
class ClientForm;
}

class ClientForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientForm(QWidget *parent = nullptr);
    ~ClientForm();

private:
    Ui::ClientForm *ui;

    QTcpServer *MedServ;
    QTcpSocket *MedSock;

    bool connectFlag;

    QVector <QString> inputData;

    bool checkLineEdits();

    int numCickles;

public slots:
    void ConnectDisconnectSlot();

    void onNewConnection();

    void onReadyRead();

    void slotClientDisconnected();

    void ClientInterface(QString parameters);

signals:
 void ToClientTimer(QString parameters);

 void StartTimer(int number);
 void PauseTimer();
 void UnpauseTimer();
 void FinishTimer();

 void StartTimerMany(int number);
 void PauseTimerMany();
 void UnpauseTimerMany();
 void FinishTimerMany();

 void setAutomateSignal(QString setAutomate);
};

#endif // CLIENTFORM_H
