#ifndef SAVEFORM_H
#define SAVEFORM_H

#include <QWidget>

namespace Ui {
class saveForm;
}

class saveForm : public QWidget
{
    Q_OBJECT

public:
    explicit saveForm(QWidget *parent = 0);
    ~saveForm();

    //Извлечение строки из поля ввода места сохранения/загрузки файла с состоянием
    QString dsEditOut();


private:
    Ui::saveForm *ui;
    //Строка с путём
    //QString strway;

public slots:
    //Отрабатывает по клику кнопки "Сохранить"
    void saveSlot();
    //Отрабатывает по клику кнопки "Загрузить"
    void downSlot();
    //Отрабатывает для изменения статуса
    void statusSlot(QString status);

signals:
    void saveSignal(QString str1);
    void downSignal(QString str1);

};

#endif // SAVEFORM_H
