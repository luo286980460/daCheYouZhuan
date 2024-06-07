#include <QSerialPortInfo>
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>

#include "myserialportworker.h"

#define INIFILE_PORT "/portName.ini"

MySerialPortWorker::MySerialPortWorker(QObject *parent)
    : QObject{parent}
{
    QSettings* settings = new QSettings(QCoreApplication::applicationDirPath() + INIFILE_PORT, QSettings::IniFormat, this);
    m_portName = settings->value("port/portName", "").toString();
    settings->deleteLater();
}

MySerialPortWorker::~MySerialPortWorker()
{
    if(m_serialPort){
        if(m_serialPort->isOpen()){
            m_serialPort->close();
        }
        m_serialPort->deleteLater();
    }
}

void MySerialPortWorker::initSerialPort()
{
    m_serialPort = new QSerialPort();
    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();

    foreach(QSerialPortInfo info, list){
        if(info.portName() == m_portName){
            m_serialPort->setPort(info);
            if(m_serialPort->open(QIODevice::ReadWrite)){
                emit showMsg(QString("串口打开成功，串口名：%1").arg(m_serialPort->portName()));
                return;
            }else{
                emit showMsg(QString("串口打开失败，串口名：%1").arg(m_serialPort->portName()));
            }
            return;
        }
    }

    emit showMsg(QString("********串口 %1 不存在！").arg(m_portName));
}

void MySerialPortWorker::slotInitWorker()
{
    initSerialPort();
}

void MySerialPortWorker::slotSendData(QString data)
{

    int res = m_serialPort->write(data.toUtf8());

    showMsg("发送内容：" + data + QString::number(res)) ;
    m_serialPort->waitForBytesWritten();
}
