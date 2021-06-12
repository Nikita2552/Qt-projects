#ifndef VIDEOREGISTRATORFORM_H
#define VIDEOREGISTRATORFORM_H

#include <QWidget>

namespace Ui {
class VideoRegistratorForm;
}

class VideoRegistratorForm : public QWidget
{
    Q_OBJECT

public:
    explicit VideoRegistratorForm(QWidget *parent = nullptr);
    ~VideoRegistratorForm();

private:
    Ui::VideoRegistratorForm *ui;
};

#endif // VIDEOREGISTRATORFORM_H
