#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea> //Для добаления подокон внутрь родительского окна

#include <videoform.h>
#include <cmdform.h>
#include <saveform.h>

#include <cickletimerform.h> /* Таймер */
#include <moduleusbform.h> /* Переключатель */
#include <videoregistratorform.h> /* звязь с видеорегистратором */
#include <ptzcameraform.h> /* работа с ПТЗ-камерой */
#include <clientserverform.h> /* клиент-сервер */
#include <clientform.h> /* клиент-сервер */
#include <serverform.h> /* клиент-сервер */
#include <optionsform.h> /* Опции */

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    cmdForm * cmdF1;

    saveForm * saveF1;

    CickleTimerForm * cikcleF1;

    QMdiArea * mdiArea;  // Область, в которую будут добавляться окна

    QMdiSubWindow * subWindow_cmdF1;

    QMdiSubWindow * subWindow_saveF1;

private slots:
    //Открытие дочерних окон
    void on_actionAddVideo_triggered();
    void on_actionAddTimer_triggered();
    void on_actionAddCamera_triggered();
    void on_actionAddUsb_triggered();
    void on_actionAddEthernet_triggered();
    void on_actionAddLogs_triggered();
    void on_actionAddOptions_triggered();

    //открутие окон для подприложений
    void cmdForm_open();
    void saveForm_open();

    void mainWindows_recieveData(QVector <QVector <QString>> parameters, QString ffmpegstr);

    void mainWindows_WayPered(QVector<QVector<QString> > parameters);

    void vd1_Close();
    void cmdForm_Close();

    //void openClientForm();
    //void openServerForm();
    void selectClientOrServerslot(bool ClientRole, bool ServerRole);

signals:
    //Сигнал, испускаемый для передачи начальных параметров в cmdF1
    void out_recieveData(QVector <QVector <QString>> parameters, QString ffmpegstr);
    //Сигнал, испускаемый при передаче массива результатов из cmdF1
    void out_WayPered(QVector<QVector<QString> > parameters);

    void vd1_peredTableFiles();

private:
    Ui::MainWindow *ui;

    VideoForm * vd1;

    CickleTimerForm * cid1;

    PTZcameraForm * ptzid1;

    ModuleUsbForm * usbid1;

    ClientServerForm * clservid1;

    ClientForm * clid1;
    ServerForm * servid1;

    VideoRegistratorForm * regid1;

    OptionsForm * optid1;

    QMdiSubWindow * subWindow_vd1;

    QMdiSubWindow * subWindow_cid1;

    QMdiSubWindow * subWindow_ptzid1;

    QMdiSubWindow * subWindow_usbid1;

    QMdiSubWindow * subWindow_clservid1;

    QMdiSubWindow * subWindow_clid1;

    QMdiSubWindow * subWindow_servid1;

    QMdiSubWindow * subWindow_regid1;

    QMdiSubWindow * subWindow_optid1;

};

#endif // MAINWINDOW_H
