#include "myserialport.h"
#include "myserialportworker.h"
#include <QSerialPortInfo>
#include <QDebug>

MySerialPort::MySerialPort(QObject *parent)
    : QObject{parent}
{

    m_work = new MySerialPortWorker();
    m_work->moveToThread(&m_workerThread);

    connect(&m_workerThread, &QThread::finished, m_work, &QObject::deleteLater);    // 退出线程必加
    connect(m_work,SIGNAL(showMsg(QString)), this, SIGNAL(showMsg(QString)));
    connect(this,SIGNAL(signalInitWorker()), m_work, SLOT(slotInitWorker()));       // 初始化工作类
    connect(this, &MySerialPort::signalSendData, m_work, &MySerialPortWorker::slotSendData);
}

MySerialPort::~MySerialPort()
{
    m_workerThread.quit();
    m_workerThread.wait();
}

void MySerialPort::start()
{
    emit signalInitWorker();
    m_workerThread.start();
}

void MySerialPort::stop()
{
    m_workerThread.quit();
    m_workerThread.wait();
}
