#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <shumform.h>

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

    QImage Ishodnoe;
    QImage Zashumlennoye_one;
    QImage Zashumlennoye_two;
    QImage RShum;
    QImage GShum;
    QImage BShum;
    QImage Obrabotannoye;

    ShumForm *SF1;

public slots:
    void UniImage();
    void BiImage();

    void MedUniImage();
    void MedBiImage();
    //void NonShumImage();
    //void BackFromSignalShum(QImage Ishodnoe2); //, QImage Zashumlennoye_one2, QImage Zashumlennoye_two2);

    //void testslot();
};

#endif // MAINWINDOW_H
