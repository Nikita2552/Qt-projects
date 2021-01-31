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

    void ClientInterface(QVector <QVector <int>> parameter);

    bool checkLineEdits();

public slots:
    void ConnectDisconnectSlot();

    void onNewConnection();

    void onReadyRead();

    void slotClientDisconnected();
};

#endif // CLIENTFORM_H
