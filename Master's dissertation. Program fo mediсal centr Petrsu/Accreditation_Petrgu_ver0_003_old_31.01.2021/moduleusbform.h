#ifndef MODULEUSBFORM_H
#define MODULEUSBFORM_H

#include <QWidget>
#include "hidapi.h"

#define SCREEN_SIZE 1
/*Размер выходного HID репорта*/

namespace Ui {
class ModuleUsbForm;
}

class ModuleUsbForm : public QWidget
{
    Q_OBJECT

public:
    explicit ModuleUsbForm(QWidget *parent = nullptr);
    ~ModuleUsbForm();

private:
    Ui::ModuleUsbForm *ui;

    hid_device *handle_device; /*указатель на структуру,
      описывающую HID-устройство в HIDAPI*/
      struct
      {
        uint8_t reportID;
        uint8_t screen[SCREEN_SIZE];
      } report;

      bool USBflag;
       /*Выходной репорт. HIDAPI функции требуют наличия байта
    ReportID, даже если устройство его не использует*/

    void InReport();
    void OutReport();

public slots:
    //void DobavLevyi();
    //void DobavPravyi();
    void TolkoVevyi();
    void TolkoPravyi();
    void ObaVkl();
    void ObaVykl();
    void Podklychenie();
    void Otklychenie();
    //Показ текущего времени с ПК
    void showTime();
};

#endif // MODULEUSBFORM_H
