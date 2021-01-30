#ifndef MEDIANFORM_H
#define MEDIANFORM_H

#include <QWidget>

namespace Ui {
class medianForm;
}

class medianForm : public QWidget
{
    Q_OBJECT

public:
    explicit medianForm(QWidget *parent = nullptr,
                        QString imageWay = "",
                        double imageSigma = 0,
                        int imageMask = 0,
                        bool noise_flag = false);
    ~medianForm();

private:
    Ui::medianForm *ui;


    QString imageWay;
    double imageSigma;
    int imageMask;
/*
    QImage iImage;
    QImage iNoise;
    QImage iRedNoise;
    QImage iGreenNoise;
    QImage iBlueNoise;
    QImage iRedAfter;
    QImage iGreenAfter;
    QImage iBlueAfter;
    QImage iAfter;
*/
    QVector <QImage> iImage;
public slots:
    //Сохранее отмеченных изображений
    void saveImages();

};

#endif // SHUMFORM_H

