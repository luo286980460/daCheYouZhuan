#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QObject>
#include <QThread>
#include <QSerialPort>

class MySerialPortWorker;

class MySerialPort : public QObject
{
    Q_OBJECT
public:
    explicit MySerialPort(QObject *parent = nullptr);
    ~MySerialPort();

    void start();
    void stop();

signals:
    void signalInitWorker();
    void showMsg(QString msg);
    void signalSendData(QString data);

private:
    QThread m_workerThread;         // UDP工作线程
    MySerialPortWorker *m_work = nullptr; // UDP工作类
};

#endif // MYSERIALPORT_H
