#ifndef SHUMFORM2_H
#define SHUMFORM2_H

#include <QWidget>

namespace Ui {
class shumForm2;
}

class shumForm2 : public QWidget
{
    Q_OBJECT

public:
    explicit shumForm2(QWidget *parent = nullptr);
    ~shumForm2();

private:
    Ui::shumForm2 *ui;

    enum Images
    {
        IMAGE_CLONE,
        IMAGE_SPEKTR,
        IMAGE_CLONE1,
        IMAGE_R,
        IMAGE_G,
        IMAGE_B,
        IMAGE_ST1,
        IMAGE_ST2,
        IMAGE_ST3
    };

    QVector <QImage> iImage;

    void SeeImages(QImage image, Images im);

public slots:
    void process_for_seen_images(QImage R_SPEKTR, QImage G_SPEKTR, QImage B_SPEKTR,
                                 QImage R_FILTER, QImage G_FILTER, QImage B_FILTER,
                                 QImage R_RG, QImage G_RG, QImage B_RG);
    void saveImages(QString saveway);
};

#endif // SHUMFORM2_H
