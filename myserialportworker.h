#ifndef MYSERIALPORTWORKER_H
#define MYSERIALPORTWORKER_H

#include <QObject>
#include <QSerialPort>

class MySerialPortWorker : public QObject
{
    Q_OBJECT
public:
    explicit MySerialPortWorker(QObject *parent = nullptr);
    ~MySerialPortWorker();

private:
    void initSerialPort();                  // 初始化串口信息

signals:
    void showMsg(QString msg);

public slots:
    void slotInitWorker();                  // 初始化工作类
    void slotSendData(QString data);        // 发送数据

private:
    QSerialPort* m_serialPort = nullptr;    // 控屏串口
    QString m_portName;

};

#endif // MYSERIALPORTWORKER_H
