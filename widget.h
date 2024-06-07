#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileSystemWatcher>
#include <QTimer>
#include <QSerialPort>
#include <QSettings>

#include "qdatetime.h"
#include "road.h"
#include "myserialport.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    typedef enum{
        UTF_8,
        GB2312,
        unknow
    }e_encoding;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void initTimer();           // 初始化定时器
    void initSerialPort();      // 初始化串口
    void initRoad();            // 初始化路口信息
    void unInitRoad();          // 释放路口信息
    void openFileWatcher();     // 打开文件监控
    void sendData(Road* road, QString plate, QString color);        // 发送车牌上屏
    void loadCurIpInfo();       // 加载当前ip对应的信息
    void deleteOverTimePics();  // 删除超时的备份图片
    QString utf8ToGb2312(char *strUtf8);        // utf8 转 gb2312
    QString gb2312ToUtf8(QString strGb2312);    // gb2312 转 utf8

signals:
    void signalSendData(QString data);

public slots:
    void showMsg(QString msg);
    void slotTimeout();
    void dealPicFiles(QString filePath);
    void dealPicFilesUTF_8(QString filePath);
    void dealPicFilesGB2312(QString filePath);
    void dealPicFilesUnkown(QString filePath);

private slots:
    void on_clearBtn_clicked();
    void slotIpListCurrentIndexChanged(int index);
    void on_changeBtn_clicked();
    void on_deleteBtn_clicked();
    void on_addBtn_clicked();
    void on_changeWorkTimeBtn_clicked();

    void on_delPicWaitTimeBtn_clicked();

private:
    Ui::Widget *ui;
    QList<Road*> m_roadList;            // 路口列表
    int m_roadCount;                    // 路口数量
    QFileSystemWatcher* m_fileWather;   // 文件监控
    QString m_filePath;                 // 文件监控路径
    QTimer* m_secTimer;                 // 秒级定时器
    MySerialPort* mySerialPort;         // 串口类
    QTime m_startTime;                  // 辅助屏开启时间
    QTime m_stopTime;                   // 辅助屏关闭时间
    int m_picsSaveDays;                 // 备份文件最大保存时间
    e_encoding m_encoding = unknow;     // 摄像头上传文件的编码
    int m_delPicWaitTime = 500;         // 处理图片延时

};
#endif // WIDGET_H
