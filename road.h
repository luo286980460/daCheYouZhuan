#ifndef ROAD_H
#define ROAD_H

#include <QObject>

class Road : public QObject
{
    Q_OBJECT
public:
    explicit Road(QObject *parent = nullptr);
    ~Road();

    void setScreenIp(QString screenIp);
    void setScreenPort(QString screenPort);
    void setScreenDevNum(QString screenDevNum);
    void setCameraIp(QString cameraIp);
    void setPicPath(QString picPath);
    void setPicPathBack(QString picPathBack);
    void setRoadNum(QString roadNum);
    QString getScreenIp();
    QString getScreenPort();
    QString getScreenDevNum();
    QString getCameraIp();
    QString getPicPath();
    QString getPicPathBack();
    QString getRoadNum();

signals:
    void showMsg(QString msg);

private:
    QString m_screenIp;     // 屏幕 ip
    QString m_screenPort;   // 屏幕 port
    QString m_screenDevNum; // 屏幕 编号
    QString m_cameraIp;     // 摄像机 ip
    QString m_picPath;      // 图片路径
    QString m_picPathBack;  // 图片备份路径
    QString m_roadNum;      // 车道号

};

#endif // ROAD_H
