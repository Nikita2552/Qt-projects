#ifndef CLIENTSERVERFORM_H
#define CLIENTSERVERFORM_H

#include <QWidget>

namespace Ui {
class ClientServerForm;
}

class ClientServerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientServerForm(QWidget *parent = nullptr);
    ~ClientServerForm();

private:
    Ui::ClientServerForm *ui;
};

#endif // CLIENTSERVERFORM_H
