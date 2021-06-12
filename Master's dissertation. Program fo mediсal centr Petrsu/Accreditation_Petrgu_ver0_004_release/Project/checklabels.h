#ifndef CHECKLABELS_H
#define CHECKLABELS_H

#include <QMainWindow>
#include <QString>

using namespace std;

class CheckLabels
{
public:
    CheckLabels();

    CheckLabels(QVector <QString> ForCheckData);

    string getIpAddress();

    ~CheckLabels();

private:

    QVector <QString> InputData;

    int corrIpAddress(QString ipForCorr);

};

#endif // CHECKLABELS_H
