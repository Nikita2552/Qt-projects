#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <shumform1.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    shumForm1 *SF1;

    QImage Ishodnoe;

    QImage RIshodnoe;
    QImage GIshodnoe;
    QImage BIshodnoe;

    float D0;
    int iwidth;
    int iheight;

    void CreateIshodnoe();

    enum Colors
    {
        COLOR_R,
        COLOR_G,
        COLOR_B,
    };

    /* Функция принимает три параметра COLOR_R, COLOR_G или COLOR_B.
     *  Заполняет переменные RIshodnoe,GIshodnoe,BIshodnoe
     *  В зависимости от параметра
     */
    void CreateGRB(Colors color);

    void CreateImages();

public slots:
    void IdealSlot();

    void GaussSlot();

    void showRGBVariablesForIdeal();

    void showRGBVariablesForGauss();

    void saveText();

signals:
    void RGB_ideal_signal(QImage clone, QImage cloneR, QImage cloneB, QImage cloneG, float D0, int width, int height);
    void RGB_gauss_signal(QImage clone, QImage cloneR, QImage cloneB, QImage cloneG, float D0, int width, int height);
    void forRGB_ideal_signal();
    void forRGB_gauss_signal();
    void forSave_images(QString saveway);


};

#endif // MAINWINDOW_H
