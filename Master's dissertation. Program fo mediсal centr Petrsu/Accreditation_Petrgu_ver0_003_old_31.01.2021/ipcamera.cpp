#include "ipcamera.h"

void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
    char tempbuf[256] = {0};
    switch(dwType)
    {
    case EXCEPTION_RECONNECT:      // reconnect when preview
        printf("----------reconnect--------%d\n", time(NULL));
    break;
  default:
    break;
    }
}

ipCamera::ipCamera()
{

}

ipCamera::ipCamera(QVector<QString> ForCameraData)
{
    this->InputData = ForCameraData;
}

void ipCamera::ipCameraConnect()
{
    qDebug() << "Class [ipCamera]: ipCameraConnect";

    NET_DVR_Init();

    //Set connect time and reconnect time
     NET_DVR_SetConnectTime(2000, 1);
     NET_DVR_SetReconnect(10000, true);

     //---------------------------------------

     QString strIn;
     strIn.append(this->InputData[0]);
     strIn.append(".");
     strIn.append(this->InputData[1]);
     strIn.append(".");
     strIn.append(this->InputData[2]);
     strIn.append(".");
     strIn.append(this->InputData[3]);
     //char *strOut;
     //strOut = strIn.toUtf8().data();

     //QString dataSrc("FooBar");
     //QString databa = strIn.toUtf8();
     //std::vector<char> data(databa.begin(), databa.end());
     //char* strOut = data.data();

     NET_DVR_DEVICEINFO_V30 struDeviceInfo;
     this->lUserID = NET_DVR_Login_V30("172.20.141.15", 8000, "operator", "Cvjnhbntkm12", &struDeviceInfo);
     if (this->lUserID < 0)
     {
          //printf("Login error, %d\n", NET_DVR_GetLastError());
          qDebug() << "Class [ipCamera]: Login error! - " << NET_DVR_GetLastError();
          NET_DVR_Cleanup();
          //return 1;
     } else {

     qDebug() << "Class [ipCamera]: UserID = " << this->lUserID;
     }

     //---------------------------------------
     //Set exception callback function
     NET_DVR_SetExceptionCallBack_V30(0, NULL,g_ExceptionCallBack, NULL);
     //---------------------------------------
     //Start preview and set to callback stream data
     //LONG lRealPlayHandle;
     //HWND hWnd = GetConsoleWindow();          //Get window handle
     NET_DVR_CLIENTINFO ClientInfo = {0};
     //ClientInfo.hPlayWnd = hWnd;
     //If need to decode, please set it valid. If want to get stream data only, it can be set to NULL
     ClientInfo.lChannel          = 1;              // Preview channel NO.
     ClientInfo.lLinkMode        = 0;            /* The high bit (31) 0 means the main stream, while 1 means the sub
   stream. Bit 0~bit 30 are used for link mode: 0- TCP mode, 1- UDP mode, 2- Multi-play mode, 3- RTP mode, 4- RTP
   over RTSP, 5- RTSP over HTTP */
     ClientInfo.sMultiCastIP = NULL;      // Multicast IP. Please set when require to preview in multicast mode.

     BOOL bPreviewBlock = false;
       //Whether blocked when requiring a stream connection, 0 means unblocked, 1 means blocked
     this->lRealPlayHandle = NET_DVR_RealPlay_V30(lUserID, &ClientInfo, NULL, NULL, 0);
     if (this->lRealPlayHandle < 0)
     {
         printf("NET_DVR_RealPlay_V30 error\n");
       NET_DVR_Logout(lUserID);
         NET_DVR_Cleanup();
         return;
     }
}

DWORD ipCamera::ipCameraMoveLeft()
{
    qDebug() << "Class [ipCamera]: ipCameraMoveLeft";

    DWORD dwPTZCommand = PAN_LEFT; /* Макрос команды обозначает направление */

    DWORD dwStart = 0; /* Команда начала движения */

    LONG lRealHandle = this->lRealPlayHandle;

    bool flagStartMove = NET_DVR_PTZControl(lRealHandle, dwPTZCommand, dwStart);

    return dwPTZCommand;
}

DWORD ipCamera::ipCameraMoveRight()
{
    qDebug() << "Class [ipCamera]: ipCameraMoveRight";

    DWORD dwPTZCommand = PAN_RIGHT; /* Макрос команды обозначает направление */

    DWORD dwStart = 0; /* Команда начала движения */

    LONG lRealHandle = this->lRealPlayHandle;

    bool flagStartMove = NET_DVR_PTZControl(lRealHandle, dwPTZCommand, dwStart);

    return dwPTZCommand;
}

DWORD ipCamera::ipCameraMoveUp()
{
    qDebug() << "Class [ipCamera]: ipCameraMoveLeft";

    DWORD dwPTZCommand = TILT_UP; /* Макрос команды обозначает направление */

    DWORD dwStart = 0; /* Команда начала движения */

    LONG lRealHandle = this->lRealPlayHandle;

    bool flagStartMove = NET_DVR_PTZControl(lRealHandle, dwPTZCommand, dwStart);

    return dwPTZCommand;
}

DWORD ipCamera::ipCameraMoveDown()
{
    qDebug() << "Class [ipCamera]: ipCameraMoveDown";

    DWORD dwPTZCommand = TILT_DOWN; /* Макрос команды обозначает направление */

    DWORD dwStart = 0; /* Команда начала движения */

    LONG lRealHandle = this->lRealPlayHandle;

    bool flagStartMove = NET_DVR_PTZControl(lRealHandle, dwPTZCommand, dwStart);

    return dwPTZCommand;
}

DWORD ipCamera::ipCameraMoveLeftUp()
{
    qDebug() << "Class [ipCamera]: ipCameraMoveLeftUp";

    DWORD dwPTZCommand = UP_LEFT; /* Макрос команды обозначает направление */

    DWORD dwStart = 0; /* Команда начала движения */

    LONG lRealHandle = this->lRealPlayHandle;

    bool flagStartMove = NET_DVR_PTZControl(lRealHandle, dwPTZCommand, dwStart);

    return dwPTZCommand;
}

DWORD ipCamera::ipCameraMoveRightUp()
{
    qDebug() << "Class [ipCamera]: ipCameraMoveRightUp";

    DWORD dwPTZCommand = UP_RIGHT; /* Макрос команды обозначает направление */

    DWORD dwStart = 0; /* Команда начала движения */

    LONG lRealHandle = this->lRealPlayHandle;

    bool flagStartMove = NET_DVR_PTZControl(lRealHandle, dwPTZCommand, dwStart);

    return dwPTZCommand;
}

DWORD ipCamera::ipCameraMoveLeftDown()
{
    qDebug() << "Class [ipCamera]: ipCameraMoveLeftDown";

    DWORD dwPTZCommand = DOWN_LEFT; /* Макрос команды обозначает направление */

    DWORD dwStart = 0; /* Команда начала движения */

    LONG lRealHandle = this->lRealPlayHandle;

    bool flagStartMove = NET_DVR_PTZControl(lRealHandle, dwPTZCommand, dwStart);

    return dwPTZCommand;
}

DWORD ipCamera::ipCameraMoveRightDown()
{
    qDebug() << "Class [ipCamera]: ipCameraMoveRightDown";

    DWORD dwPTZCommand = DOWN_RIGHT; /* Макрос команды обозначает направление */

    DWORD dwStart = 0; /* Команда начала движения */

    LONG lRealHandle = this->lRealPlayHandle;

    bool flagStartMove = NET_DVR_PTZControl(lRealHandle, dwPTZCommand, dwStart);

    return dwPTZCommand;
}

void ipCamera::ipCameraMoveStop(DWORD dwPTZCommand) /* PAN_LEFT, PAN_RIGHT */
{
    qDebug() << "Class [ipCamera]: ipCameraMoveStop";

    DWORD dwStop = 1; /* Команды начала и окончания движения */

    LONG lRealHandle = this->lRealPlayHandle;

    bool flagStopMove = NET_DVR_PTZControl(lRealHandle, dwPTZCommand, dwStop);
}

void ipCamera::ipCameraDisconnect()
{
    qDebug() << "Class [ipCamera]: ipCameraDisconnect";

    // Logout
    NET_DVR_Logout(this->lUserID);
    // Release SDK resource
    NET_DVR_Cleanup();
}

ipCamera::~ipCamera()
{

}
