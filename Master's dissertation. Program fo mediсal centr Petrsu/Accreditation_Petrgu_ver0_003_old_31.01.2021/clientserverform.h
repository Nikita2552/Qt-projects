#ifndef CLIENTSERVERFORM_H
#define CLIENTSERVERFORM_H

#include <QMainWindow>
#include <QDebug>
#include <QMdiArea> //Для добаления подокон внутрь родительского окна

#include "clientform.h"
#include "serverform.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ClientServerForm;
}
QT_END_NAMESPACE

class ClientServerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientServerForm(QWidget *parent = nullptr);
    ~ClientServerForm();

private:
    Ui::ClientServerForm *ui;

    ClientForm *CF; /*Указатель на клиентскую форму*/
    ServerForm *SF; /*Указатель на серверную форму*/

    QMdiSubWindow *subCF;
    QMdiSubWindow *subSF;

public:
    ClientForm * createClientForm(QMdiArea * mdi);
    ServerForm * createServerForm(QMdiArea * mdi);

    void openClientForm(QMdiSubWindow * subW);
    void openServerForm(QMdiSubWindow * subW);

public slots:
    void selectClientOfServerslot();

signals:
    void openClientOrServer(bool ClientRole, bool ServerRole);
    //void openServer();

};
#endif // CLIENTSERVERFORM_H
