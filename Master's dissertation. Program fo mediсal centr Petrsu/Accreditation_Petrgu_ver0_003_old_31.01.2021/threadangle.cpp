#include "threadangle.h"

threadAngle::threadAngle()
{
    //this->cickleFlag = true;
}

threadAngle::~threadAngle()
{
    //this->cickleFlag = false;
}

void threadAngle::XYToProcess(int X, int Y)
{
    this->X = X;
    this->Y = Y;

    qDebug() << "Class [threadAngle]: XY coordinates is:" << this->X << ", " << this->Y;

    emit AngleToLabel(X, Y);
}
