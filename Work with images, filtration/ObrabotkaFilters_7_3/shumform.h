#ifndef SHUMFORM_H
#define SHUMFORM_H

#include <QWidget>
#include <QImage>
#include <QVector>

namespace Ui {
class ShumForm;
}

class ShumForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShumForm(QWidget *parent = nullptr,
                      QString imageWay = "",
                      double imageSigma = 0,
                      int imageMask = 0,
                      bool noise_flag = false,
                      bool filter_flag = false);
    ~ShumForm();

private:
    Ui::ShumForm *ui;

    QString imageWay;
    double imageSigma;
    int imageMask;

    QVector <QImage> iImage;
public slots:
    //Сохранее отмеченных изображений
    void saveImages();

};

#endif // SHUMFORM_H
