#ifndef IPCAMERA_H
#define IPCAMERA_H

#include <QMainWindow>
#include <QString>
#include <QDebug>

#include "HCNetSDK.h"

using namespace std;

class ipCamera
{
public:
    ipCamera();
    ~ipCamera();

    ipCamera(QVector <QString> ForCameraData);

    void ipCameraConnect();

    DWORD ipCameraMoveLeft(); /* Добавить потоки, чтобы получить доступ к кнопкам. */

    DWORD ipCameraMoveRight();

    DWORD ipCameraMoveUp(); /* Добавить потоки, чтобы получить доступ к кнопкам. */

    DWORD ipCameraMoveDown();

    DWORD ipCameraMoveLeftUp(); /* Добавить потоки, чтобы получить доступ к кнопкам. */

    DWORD ipCameraMoveRightUp();

    DWORD ipCameraMoveLeftDown(); /* Добавить потоки, чтобы получить доступ к кнопкам. */

    DWORD ipCameraMoveRightDown();

    void ipCameraMoveStop(DWORD dwPTZCommad);

    void ipCameraDisconnect(); 

private:

    QVector <QString> InputData;
    /* ID пользователя */
    LONG lUserID;
    /* lRealHandle модификатор */
    LONG lRealPlayHandle;

    //void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);

};

#endif // IPCAMERA_H
