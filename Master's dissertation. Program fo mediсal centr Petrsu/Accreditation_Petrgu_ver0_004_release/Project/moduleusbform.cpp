#include "moduleusbform.h"
#include "ui_moduleusbform.h"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>

ModuleUsbForm::ModuleUsbForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModuleUsbForm)
{
    ui->setupUi(this);

    //Установка кнопок манипуляции переключателем в состояние "деактивированы"
    ui->Tolkolevyivkl->setEnabled(false);
    ui->Tolkopravyivkl->setEnabled(false);
    ui->Obavkl->setEnabled(false);
    ui->Obavykl->setEnabled(false);

    //Создал новый объект для этого окна
    QTimer *timerObsh = new QTimer(this);
    timerObsh->start(200);
    USBflag = false;
    //Когда объект таймер сигнализирует о прохождении секунды,
    //вызывается слот вывода времени в окно
    connect(timerObsh, SIGNAL (timeout()), this, SLOT(showTime()) );

    //connect(ui->Dobavlev, SIGNAL(clicked()), this, SLOT(DobavLevyi()) );
    //connect(ui->Dobavprav, SIGNAL(clicked()), this, SLOT(DobavPravyi()) );
    connect(ui->Tolkolevyivkl, SIGNAL(clicked()), this, SLOT(TolkoVevyi()) );
    connect(ui->Tolkopravyivkl, SIGNAL(clicked()), this, SLOT(TolkoPravyi()) );
    connect(ui->Obavkl, SIGNAL(clicked()), this, SLOT(ObaVkl()) );
    connect(ui->Obavykl, SIGNAL(clicked()), this, SLOT(ObaVykl()) );
    connect(ui->Podklychitsia, SIGNAL(clicked()), this, SLOT(Podklychenie()) );
    connect(ui->Otklychitsia, SIGNAL(clicked()), this, SLOT(Otklychenie()) );

    /*обнуляем репорт*/
      memset(&report, 0, sizeof(report));
}

ModuleUsbForm::~ModuleUsbForm()
{
    delete ui;
}

void ModuleUsbForm::InReport()
{
    /*Вот самое интересное - отправка и приём репортов. Всё проще некуда :)*/
    if (hid_write(handle_device, (const unsigned char*)&report, sizeof(report))==-1)
      {
        QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка при отправке данных"));
      }
}

void ModuleUsbForm::OutReport()
{
    /*Вот самое интересное - отправка и приём репортов. Всё проще некуда :)*/
      uint8_t but = 0;

      if (hid_read(handle_device, &but, 1)==-1)
      {
       QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка при приёме данных"));
      }
      switch (but)
      {
           case 0b00001111:
                       ui->Sostoyanie_Perek->setText("Колонки выключены");
                       break;
           case 0b00001010:
                       ui->Sostoyanie_Perek->setText("Левая включена");
                       break;
           case 0b00000101:
                       ui->Sostoyanie_Perek->setText("Правая включена");
                       break;
           case 0b00000000:
                       ui->Sostoyanie_Perek->setText("Колонки включены");
                       break;
      }
}

void ModuleUsbForm::showTime()
{
    if (USBflag == true)
    {
    OutReport();
    }
}

/*
void ModuleUsbForm::DobavLevyi()
{
    qDebug() << "Добавить левую колонку!";

    //InReport();
}

void ModuleUsbForm::DobavPravyi()
{
    qDebug() << "Добавить правую колонку!";

    //InReport();
}
*/
void ModuleUsbForm::TolkoVevyi()
{
    qDebug() << "Включить только левую колонку!";

    report.screen[0] = 0b00001010;

    InReport();

    showTime();
}

void ModuleUsbForm::TolkoPravyi()
{
    qDebug() << "Включить только правую колонку!";

    report.screen[0] = 0b00000101;

    InReport();

    showTime();

    //OutReport();
}

void ModuleUsbForm::ObaVkl()
{
     qDebug() << "Включить обе колонки!";

     report.screen[0] = 0b00000000;

     InReport();

     showTime();

     //OutReport();
}

void ModuleUsbForm::ObaVykl()
{
     qDebug() << "Выключить обе колонки!";

     report.screen[0] = 0b00001111;

     InReport();

     showTime();

     //OutReport();
}

void ModuleUsbForm::Podklychenie()
{
 qDebug() << "Подключение, начало мониторинга модуля!";

 QString product_string("LUFA Generic HID Demo");

   struct hid_device_info *devs, *cur_dev;
   /* запускаем поиск hid-устройств*/
   devs = hid_enumerate(/*VID*/0x03EB, /*PID*/0x204F); qDebug() << devs;
   /*все найдённые устройства помещаются в динамический список*/
   cur_dev = devs;

   //qDebug() << devs;

   while (cur_dev)
     {
       /*пытаемся найти устройство с заданной строкой описания продукта*/
       if (QString::fromWCharArray(cur_dev->product_string) == product_string)
         break;
       cur_dev = cur_dev->next;
     }
     /*если нашли нужное устройство, и оно успешно открылось...*/
     if (cur_dev && (handle_device = hid_open_path(cur_dev->path)))
     {
       /*то активируем кнопку*/
       //ui->square_effect_button->setEnabled(true);
       //ui->connect_button->setEnabled(false);

         ui->Sostoyanie->setText("Модуль подключён");

         USBflag = true;

         //Установка кнопок манипуляции переключателем в состояние "деактивированы"
         ui->Tolkolevyivkl->setEnabled(true);
         ui->Tolkopravyivkl->setEnabled(true);
         ui->Obavkl->setEnabled(true);
         ui->Obavykl->setEnabled(true);


     }
     else
       QMessageBox::critical(this, tr("Ошибка"), tr("Невозможно подключиться к устройству"));

     /*удаляем список*/
     hid_free_enumeration(devs);

}

void ModuleUsbForm::Otklychenie()
{
 qDebug() << "Отключение, прекращение мониторинга модуля!";

 ui->Sostoyanie->setText("Модуль отключён");

 USBflag = false; /* Отключение приёма данных с переключателя. */

 //Установка кнопок манипуляции переключателем в состояние "деактивированы"
 ui->Tolkolevyivkl->setEnabled(false);
 ui->Tolkopravyivkl->setEnabled(false);
 ui->Obavkl->setEnabled(false);
 ui->Obavykl->setEnabled(false);
}
