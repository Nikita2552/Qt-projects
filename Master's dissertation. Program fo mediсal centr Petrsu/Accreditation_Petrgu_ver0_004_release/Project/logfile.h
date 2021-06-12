#ifndef LOGFILE_H
#define LOGFILE_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDate>
#include <QPointer>

class LogFile : public QObject
{
    Q_OBJECT
public:
    LogFile();
    ~LogFile();

    void InitLogFile(QString address);

    bool WriteStrInLog(QString str);

    QString CreateNameOfLog();

private:
    QFile file;

    QString address;

    //QPointer <QFile> filePointer;

};

#endif // LOGFILE_H




