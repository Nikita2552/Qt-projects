#include "logfile.h"

LogFile::LogFile()
{

}

LogFile::~LogFile()
{

}

void LogFile::InitLogFile(QString address)
{
    //QFile file(address);
    //this->file = &file;
    //filePointer = &file;

    //
    //QString fname = "file"+QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".txt";
    //QFile file(fname);
    //if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
    //    file.write("blablabla");
    //    file.close();
    //}
    //else
    //    qDebug() << "НЕ УДАЛОСЬ СОЗДАТЬ ФАЙЛ!!!";
            // else не удалось создать/открыть файл
    //

    this->address = address;

    this->file.setFileName(this->address);
    //address = "test_add.txt";

    //QFile file(address);

    bool open_flag = this->file.open(QIODevice::WriteOnly|QIODevice::Append);

    if (!open_flag)
    {
        qDebug() << "Ошибка открытия для записи";
    }
    else
    {
        qDebug() << "Файл для успешно открыт";
        //file.write("blablabla");
        file.close();
    }

    //return open_flag;
}

bool LogFile::WriteStrInLog(QString str)
{
    this->file.setFileName(this->address);

    bool open_flag = this->file.open(QIODevice::ReadWrite|QIODevice::Append);

    if (!open_flag)
    {
        qDebug() << "Ошибка открытия для чтения";
    }
    else
    {
        QTextStream writeStream(&this->file);
        writeStream.setCodec("utf-8");
        writeStream << str + "\r\n";

        this->file.close();
    }

    return open_flag;

}

QString LogFile::CreateNameOfLog()
{
    QString nameOfLog = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");

    return nameOfLog;
}

