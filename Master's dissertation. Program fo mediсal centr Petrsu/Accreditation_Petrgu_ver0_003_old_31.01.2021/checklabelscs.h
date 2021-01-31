#ifndef CHECKLABELSCS_H
#define CHECKLABELSCS_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QDebug>
#include <QNetworkInterface>
#include <QHostInfo>

class CheckLabelsCS
{
public:
    CheckLabelsCS();

    static int corrIpAddress(QString ipForCorr, int startSegment, int endSegment);

    static bool corrIpSplit(QString stringIpSplit); /* static - для вызова метода не создавая объекта */

    static bool corrPortSplit(QString stringPortSplit);

    static QVector <QString> localIpAddress();
};

#endif // CHECKLABELSCS_H
