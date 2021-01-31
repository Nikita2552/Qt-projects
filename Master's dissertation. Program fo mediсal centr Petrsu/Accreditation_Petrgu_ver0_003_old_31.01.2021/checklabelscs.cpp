#include "checklabelscs.h"

CheckLabelsCS::CheckLabelsCS()
{

}

int CheckLabelsCS::corrIpAddress(QString ipForCorr, int startSegment, int endSegment)
{
    int ipCorr;
    bool ok;

    ipCorr = ipForCorr.toInt(&ok, 10);

    if ((ok == false) || (ipCorr < startSegment) || (ipCorr > endSegment))
        ipCorr = -1;

    return ipCorr;
}

bool CheckLabelsCS::corrIpSplit(QString stringIpSplit)
{
    QString sample = ".";
    bool segmentFlag = true;
    int segment = 0;

    QStringList afterSplit = stringIpSplit.split(sample); qDebug() << "afterSplit = " << afterSplit;
    int afterCount = afterSplit.count(); qDebug() << "afterCount = " << afterCount;
    /* В случае ip-дареса обязательно должно быть четыре сегмента через точку*/
    if (afterCount == 4)
    {
        for (int i = 0; i < afterCount; i++)
        {
            segment = corrIpAddress(afterSplit[i], 0, 255); qDebug() << "afterSplit[i] = " << afterSplit[i];
            if (segment == -1) /* Если в сегменте адреса не число, то строка не проходит проверку */
            {
                segmentFlag = false;
            }
        }qDebug() << " segment = " << segment;
    }
    else
    {
        segmentFlag = false;
    }

    return segmentFlag;
}

bool CheckLabelsCS::corrPortSplit(QString stringPortSplit)
{
    bool segmentFlag = true;
    int segment = 0;

    segment = corrIpAddress(stringPortSplit, 1, 100000); //qDebug() << "afterSplit[i] = " << afterSplit[i];
    if (segment == -1) /* Если в сегменте адреса не число, то строка не проходит проверку */
    {
        segmentFlag = false;
    }
    return segmentFlag;
}

QVector <QString> CheckLabelsCS::localIpAddress()
{
       QString localhostname =  QHostInfo::localHostName();
       QString localhostIP;
       QList<QHostAddress> hostList = QHostInfo::fromName(localhostname).addresses();
       foreach (const QHostAddress& address, hostList) {
           if (address.protocol() == QAbstractSocket::IPv4Protocol && address.isLoopback() == false) {
                localhostIP = address.toString();
           }
       }
       QString localMacAddress;
       QString localNetmask;
       foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces()) {
           foreach (const QNetworkAddressEntry& entry, networkInterface.addressEntries()) {
               if (entry.ip().toString() == localhostIP) {
                   localMacAddress = networkInterface.hardwareAddress();
                   localNetmask = entry.netmask().toString();
                   break;
               }
           }
       }

       QVector <QString> ipOptions;

       ipOptions.push_back(localhostname); qDebug() << "Localhost name: " << localhostname;
       ipOptions.push_back(localhostIP); qDebug() << "IP = " << localhostIP;
       ipOptions.push_back(localMacAddress); qDebug() << "MAC = " << localMacAddress;
       ipOptions.push_back(localNetmask); qDebug() << "Netmask = " << localNetmask;

       return ipOptions;
}
