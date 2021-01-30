#ifndef SHUMFORM1_H
#define SHUMFORM1_H

#include <QWidget>
#include <QImage>
#include <complex>
#include <shumform2.h>
using namespace std;

namespace Ui {
class shumForm1;
}

class shumForm1 : public QWidget
{
    Q_OBJECT

public:
    explicit shumForm1(QWidget *parent = nullptr);
    ~shumForm1();

private:
    Ui::shumForm1 *ui;

    shumForm2 *SF2;

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

    enum maskType
    {
        Ideal,
        Gauss
    };

    int imageWidth;
    int imageHeight;

    QVector <QImage> iImage;

    void SeeImages(QImage image, Images im);

    QImage CentrImage(QImage image);

    QVector<QVector<float> > CentrImage(QImage image, Images im);

    QVector<QVector<complex<float> > > PryamoeFurieStroki(QVector<QVector<float> > image);

    QVector<QVector<complex<float> > > PryamoeFurieStolbtsyi(QVector<QVector<complex<float> > > image);

    QVector <QVector <float> >  toVectorF(QVector<QVector<complex<float> > > image);

    QVector <QVector <float> >  toVectorFlog(QVector<QVector<float> > image);

    QVector <QVector <float> >  toVectorFshkala(QVector<QVector<float> > image);

    QImage  toMonoImage(QVector<QVector<float> > image, Images im);

    QImage  toStereoImage(QVector<QVector<float> > R_image, QVector<QVector<float> > G_image, QVector<QVector<float> > B_image);

    QVector <QVector <float> > Mask(QVector <QVector <float> > image, float D0, maskType Type);

    QImage  toMonoMask(QVector<QVector<float> > image, Images im);

    QImage  toStereoMask(QVector<QVector<float> > R_image, QVector<QVector<float> > G_image, QVector<QVector<float> > B_image);

    QVector<QVector<float> > idealFilter(QVector<QVector<float> > spektr, QVector<QVector<float> > mask);

    QVector<QVector<complex<float> > > idealFilterComplex (QVector<QVector<complex<float> > > spektr, QVector<QVector<float> > mask);

    QVector<QVector<complex<float> > > ObratnoyeFurieStroki(QVector<QVector<complex<float> > > image);

    QVector<QVector<complex<float> > > ObratnoyeFurieStolbtsyi(QVector<QVector<complex<float> > > image);

    QVector<QVector<float> > RealVector(QVector<QVector<complex<float> > > image);

    QVector<QVector<float> > CentrVector(QVector<QVector<float > > image);

    QVector<QVector<float> > Warning_fix(QVector<QVector<float> > image);

    float D_u_v(float u, float v, float iwidth, float iheight);

    float H_u_v_ideal(float D0, float u, float v, float iwidth, float iheight);

    float H_u_v_gauss(float D0, float u, float v, float iwidth, float iheight);

    float one_with_N(int n);

public slots:
    void process_of_ideal_RGBsignal(QImage Ishodnoe, QImage RIshodnoe, QImage GIshodnoe, QImage BIshodnoe, float D0, int width, int height);

    void process_of_gauss_RGBsignal(QImage Ishodnoe, QImage RIshodnoe, QImage GIshodnoe, QImage BIshodnoe, float D0, int width, int height);

    void saveImages(QString saveway);

signals:
    void for_form2_signal(QImage R_SPEKTR, QImage G_SPEKTR, QImage B_SPEKTR, QImage R_FILTER, QImage G_FILTER, QImage B_FILTER, QImage R_RG, QImage G_RG, QImage B_RG);
    void forSave_images(QString saveway);
};

#endif // SHUMFORM1_H
