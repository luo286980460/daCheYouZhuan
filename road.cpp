#include "road.h"

Road::Road(QObject *parent)
    : QObject{parent}
{

}

Road::~Road()
{

}

void Road::setScreenIp(QString screenIp)
{
    m_screenIp = screenIp;
}

void Road::setScreenPort(QString screenPort)
{
    m_screenPort = screenPort;
}

void Road::setScreenDevNum(QString screenDevNum)
{
    m_screenDevNum = screenDevNum;
}

void Road::setCameraIp(QString cameraIp)
{
    m_cameraIp = cameraIp;
}

void Road::setPicPath(QString picPath)
{
    m_picPath = picPath;
}

void Road::setPicPathBack(QString picPathBack)
{
    m_picPathBack = picPathBack;
}

void Road::setRoadNum(QString roadNum)
{
    m_roadNum = roadNum;
}

QString Road::getScreenIp()
{
    return m_screenIp;
}

QString Road::getScreenPort()
{
    return m_screenPort;
}

QString Road::getScreenDevNum()
{
    return m_screenDevNum;
}

QString Road::getCameraIp()
{
    return m_cameraIp;
}

QString Road::getPicPath()
{
    return m_picPath;
}

QString Road::getPicPathBack()
{
    return m_picPathBack;
}

QString Road::getRoadNum()
{
    return m_roadNum;
}

