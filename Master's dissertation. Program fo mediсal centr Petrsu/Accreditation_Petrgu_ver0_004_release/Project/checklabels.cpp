#include "checklabels.h"

CheckLabels::CheckLabels()
{

}

CheckLabels::CheckLabels(QVector<QString> ForCheckData)
{
    this->InputData = ForCheckData;
}

CheckLabels::~CheckLabels()
{

}

string CheckLabels::getIpAddress()
{
    string ipAddress;
    QString tetr1, tetr2, tetr3, tetr4;
    string tetr1s, tetr2s, tetr3s, tetr4s;
    int corrIp1, corrIp2, corrIp3, corrIp4;

    /* Получить части ip-адреса из входных полей */
    tetr1 = this->InputData[0];    //ui -> TetraAddressOne -> text();
    tetr2 = this->InputData[1];    //ui -> TetraAddressTwo -> text();
    tetr3 = this->InputData[2];    //ui -> TetraAddressThree -> text();
    tetr4 = this->InputData[3];    //ui -> TetraAddressFour -> text();

    /* Конвертировать QString в String */
    tetr1s = tetr1.toUtf8().constData();
    tetr2s = tetr2.toUtf8().constData();
    tetr3s = tetr3.toUtf8().constData();
    tetr4s = tetr4.toUtf8().constData();

    /* Преобразовать в int */
    corrIp1 = corrIpAddress(tetr1);
    corrIp2 = corrIpAddress(tetr2);
    corrIp3 = corrIpAddress(tetr3);
    corrIp4 = corrIpAddress(tetr4);

    if ((corrIp1 == -1) || (corrIp2 == -1) || (corrIp3 == -1) || (corrIp4 == -1))
        ipAddress = "";
    else
        ipAddress = tetr1s + "." + tetr2s + "." + tetr3s + "." + tetr4s;

    return ipAddress;
}

int CheckLabels::corrIpAddress(QString ipForCorr)
{
    int ipCorr;
    bool ok;

    ipCorr = ipForCorr.toInt(&ok, 10);

    if ((ok == false) || (ipCorr < 0) || (ipCorr > 255))
        ipCorr = -1;

    return ipCorr;
}
