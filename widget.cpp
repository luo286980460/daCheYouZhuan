#include <QFileInfo>
#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QSerialPortInfo>
#include <QTextCodec>
#include <QDebug>
#include <QThread>

#include "widget.h"
#include "ui_widget.h"

#define INIFILE_ROAD "/road.ini"
//#define PIC_PATH "/home/ftp3/%1/%2"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_roadCount(0)
    , m_startTime(QTime::fromString("08:00:00", "hh:mm:ss"))
    , m_stopTime(QTime::fromString("20:00:00", "hh:mm:ss"))
{
    ui->setupUi(this);

    setWindowTitle("大车右转辅助屏控制端_2024年06月07日");
    setFixedSize(size());

    ui->delPicWaitTime1->setValue(m_delPicWaitTime);
    connect(ui->ipList, SIGNAL(currentIndexChanged(int)), this, SLOT(slotIpListCurrentIndexChanged(int)));

    initTimer();        // 初始化定时器
    initSerialPort();   // 初始化串口
    initRoad();         // 初始化路口信息
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initTimer()
{
    ui->timerLabel->setText(QDateTime::currentDateTime().toString("yyyy年MM月dd hh:mm:ss"));

    m_secTimer = new QTimer(this);
    connect(m_secTimer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
    m_secTimer->setInterval(1000);
    m_secTimer->start();
}

void Widget::initSerialPort()
{
    mySerialPort = new MySerialPort(this);
    connect(mySerialPort, SIGNAL(showMsg(QString)), this, SLOT(showMsg(QString)));
    connect(this, SIGNAL(signalSendData(QString)), mySerialPort, SIGNAL(signalSendData(QString)));

    mySerialPort->start();
}

void Widget::initRoad()
{
    // 获取路口配置信息
    QString iniPath = QCoreApplication::applicationDirPath() + INIFILE_ROAD;
    if(!QFileInfo::exists(iniPath)){
        showMsg("****** road.ini 配置文件丢失 ******");
        return;
    }
    QSettings settings(QCoreApplication::applicationDirPath() + INIFILE_ROAD, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

    QString encoding = settings.value("others/encoding", 0).toString();
    if(encoding == "UTF_8"){
        m_encoding = UTF_8;
    }else if(encoding == "GB2312"){
        m_encoding = GB2312;
    }else{
        m_encoding = unknow;
    }

    m_roadCount = settings.value("others/roadCount", 0).toInt();
    m_startTime = QTime::fromString(settings.value("others/startTime", 0).toString(), "hh:mm:ss");
    m_stopTime = QTime::fromString(settings.value("others/stopTime", 0).toString(), "hh:mm:ss");
    m_picsSaveDays = settings.value("others/picsSaveDays", 3).toInt();  // 初始化文件保存的天数
    ui->startTimeEdit->setTime(m_startTime);
    ui->stopTimeEdit->setTime(m_stopTime);

    int tmp = 0;
    for(int i=0; i<m_roadCount; i++){
        QString screenDevNum;
        QString cameraIp;
        QString picPath;
        QString picPathBack;
        QString roadNum;

        cameraIp = settings.value(QString("road/cameraIp%1").arg(i+tmp+1,2,10,QLatin1Char('0')), "error").toString();

        while(cameraIp == "error"){
            ++tmp;
            cameraIp = settings.value(QString("road/cameraIp%1").arg(i+tmp+1,2,10,QLatin1Char('0')), "error").toString();
        }

        Road* road = new Road(this);    // 创建路口
        connect(road, SIGNAL(showMsg(QString)), this, SLOT(showMsg(QString)));

        screenDevNum = settings.value(QString("road/screenDevNum%1").arg(i+tmp+1,2,10,QLatin1Char('0'))).toString();
        picPath = settings.value("others/filePath", "error").toString();
        if(picPath == "error") {
            showMsg("ini error, get others/filePath=picPath failed!!!");
            return;
        }
        picPath.replace("%1", QDate::currentDate().toString("yyyyMMdd")).replace("%2", cameraIp);
        picPathBack = picPath;
        picPathBack.replace(cameraIp, cameraIp + "_backUp");
        roadNum = settings.value(QString("road/roadNum%1").arg(i+tmp+1,2,10,QLatin1Char('0'))).toString();

        QDir dir(picPathBack);
        if(!dir.exists()){
            dir.mkpath(picPathBack);
        }

        road->setScreenDevNum(screenDevNum);
        road->setCameraIp(cameraIp);
        road->setPicPath(picPath);
        road->setPicPathBack(picPathBack);
        road->setRoadNum(roadNum);

        ui->ipList->addItem(cameraIp);
        m_roadList.append(road);
    }
    loadCurIpInfo();
    openFileWatcher();  // 打开文件监控
}

void Widget::unInitRoad()
{
    if(m_roadList.size() > 0){
        qDeleteAll(m_roadList);
        m_roadList.clear();
        m_roadCount = 0;
        ui->ipList->clear();
        m_fileWather->deleteLater();
    }
}

void Widget::openFileWatcher()
{
    // 获取屏幕配置文件
    m_fileWather = new QFileSystemWatcher(this);
    connect(m_fileWather, SIGNAL(directoryChanged(QString)), this, SLOT(dealPicFiles(QString)));

    for(int i=0; i<m_roadCount; i++){

        QString path = m_roadList.at(i)->getPicPath();
        QDir dir(path);
        if(!dir.exists()){
            dir.mkpath(path);
        }
        m_fileWather->addPath(path);
        showMsg("监控文件夹已更改: " + path);
    }
}

void Widget::sendData(Road* road, QString plate, QString color)
{
    //QString data = plate.toLocal8Bit() + "_" + color + "_|" + road->getScreenDevNum();
    QString data = plate + "_" + color + "_|" + road->getScreenDevNum();
    emit signalSendData(data);

}

void Widget::loadCurIpInfo()
{
    QString currentCamerIp;
    currentCamerIp = ui->ipList->currentText();

    foreach(Road* road, m_roadList){
        if(road->getCameraIp() == currentCamerIp){
            ui->currentIpEdit->setText(currentCamerIp);
            ui->currentScreenDevNumEdit->setText(road->getScreenDevNum());
            ui->currentRoadEdit->setText(road->getRoadNum());
            break;
        }
    }
}

void Widget::deleteOverTimePics()
{
    // 获取路径
    QString iniPath = QCoreApplication::applicationDirPath() + INIFILE_ROAD;
    if(!QFileInfo::exists(iniPath)){
        showMsg("****** road.ini 配置文件丢失 ******");
        return;
    }
    QSettings settings(QCoreApplication::applicationDirPath() + INIFILE_ROAD, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    QString path = settings.value("others/filePath", "error").toString().replace("%1/%2", "");

    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(QDir::NoDot | QDir::NoDotDot | QDir::Dirs);
    foreach(QFileInfo info, list){
        if(QDate::fromString(info.fileName(), "yyyyMMdd").daysTo(QDate::currentDate()) > m_picsSaveDays){
            QDir(info.filePath()).removeRecursively();
        }
    }
}

QString Widget::utf8ToGb2312(char *strUtf8)
{
    //printf("~~~~utf8  strUtf8:%s\n", strUtf8);
    QTextCodec* utf8Codec= QTextCodec::codecForName("utf-8");
    QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

    QString strUnicode= utf8Codec->toUnicode(strUtf8);
    QByteArray ByteGb2312= gb2312Codec ->fromUnicode(strUnicode);

    strUtf8= ByteGb2312.data();
    //printf("~~~~~gb2312	strUtf8toGb2312:%s\n", strUtf8);
    return QString::fromLocal8Bit(strUtf8);//注意这里要fromLocal8Bit()
}

QString Widget::gb2312ToUtf8(QString strGb2312)
{
    //printf("@@@ gb2312 str is:%s\n",strGb2312.toLocal8Bit().data());
    QTextCodec* utf8Codec= QTextCodec::codecForName("utf-8");
    QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

    QString strUnicode= gb2312Codec->toUnicode(strGb2312.toLocal8Bit().data());
    QByteArray ByteUtf8= utf8Codec->fromUnicode(strUnicode);

    //char *utf8code = ByteUtf8.data();
    return QString::fromUtf8(ByteUtf8.data());
    //printf("@@@ Utf8  strGb2312toUtf8:%s\n",utf8code);
}

void Widget::showMsg(QString msg)
{
    ui->history->appendPlainText(QDateTime::currentDateTime().toString("yyyy年MM月dd日hh:mm:ss") + "----->" + msg);
}

void Widget::slotTimeout()
{deleteOverTimePics();
    QString currTime = QDateTime::currentDateTime().toString("yyyy年MM月dd hh:mm:ss");
    ui->timerLabel->setText(currTime);

    // 00：00：00 刷新监控文件夹
    if(QTime::currentTime().toString("hh:mm:ss") == "00:00:00"){
        unInitRoad();
        initRoad();
        openFileWatcher();

        // 删除超过保存时限文件
        deleteOverTimePics();
    }
}

void Widget::dealPicFiles(QString filePath)
{
    switch(m_encoding){
    case UTF_8:
        dealPicFilesUTF_8(filePath);
        break;
    case GB2312:
        dealPicFilesGB2312(filePath);
        break;
    case unknow:
        dealPicFilesUnkown(filePath);
        break;
    }
}

void Widget::dealPicFilesUTF_8(QString filePath)
{
//    QEventLoop eventloop;
//    QTimer::singleShot(m_delPicWaitTime, &eventloop, SLOT(quit()));
//    eventloop.exec();

    Road* road = nullptr;
    QString cameraIp = filePath.split("/", Qt::SkipEmptyParts).at(3);
    foreach(Road* tmp, m_roadList){
        if(tmp->getCameraIp() == cameraIp){
            road = tmp;
            break;
        }
    }

    if(road == nullptr) return;

    QDir dir(filePath);   //打开目录

    //筛选不要 . 和 .. 文件 , 只要文件(如果需要文件夹,加上 QDir::Dirs
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);

    //提取文件信息链表
    QFileInfoList inforList = dir.entryInfoList();

    //遍历文件信息链表,并进行相关操作
    foreach (QFileInfo info, inforList) {
        QString fileName = info.fileName();
        //qDebug() << "fileName: " << fileName;

        QString fileNamePath = info.filePath();
        QStringList strList = QString(fileName.toLocal8Bit()).split("_", Qt::SkipEmptyParts);

        if(strList.size() != 5) {
            showMsg("文件名格式不对：" + QString::number(strList.size()));
            showMsg(fileName);
            remove(fileNamePath.toLocal8Bit());
            continue;
        }else if(fileNamePath .contains("ini")){
            //showMsg("ini文件：" + fileNamePath);
            remove(fileNamePath.toLocal8Bit());
            continue;
        }


        //if(fileName.toLocal8Bit().contains("黄")){     // 如果是黄牌，发送至屏幕
        if(fileName.contains("黄")){     // 如果是黄牌，发送至屏幕
            QThread::msleep(m_delPicWaitTime);
            // 车道号是否正确
            if(road->getRoadNum().toInt() == QString(strList.at(3)).toInt()){
                //是否在工作时间
                if(QTime::currentTime() > m_startTime && QTime::currentTime() < m_stopTime){
                    // 备份图片
                    rename((road->getPicPath() + "/" + fileName).toLocal8Bit(), (road->getPicPathBack()+ "/" + fileName).toLocal8Bit());
                    showMsg(road->getPicPath() + "/" + fileName);
                    showMsg(road->getPicPathBack()+ "/" + fileName);

                    sendData(road, fileName.split("_", Qt::SkipEmptyParts).at(1), "黄");
                }else{
                    showMsg("不在工作时间内");
                    remove(fileNamePath.toLocal8Bit());
                }
            }else{
                showMsg("车道号错误");
                remove(fileNamePath.toLocal8Bit());
            }
        }else{                          // 不是黄牌，直接删除
            showMsg("非黄牌");
            remove(fileNamePath.toLocal8Bit());
        }
    }

}

void Widget::dealPicFilesGB2312(QString filePath)
{
//    QEventLoop eventloop;
//    QTimer::singleShot(m_delPicWaitTime, &eventloop, SLOT(quit()));
//    eventloop.exec();

    Road* road = nullptr;
    QString cameraIp = filePath.split("/", Qt::SkipEmptyParts).at(3);

    foreach(Road* tmp, m_roadList){
        if(tmp->getCameraIp() == cameraIp){
            road = tmp;
            break;
        }
    }

    if(road == nullptr) return;

    QDir dir(filePath);   //打开目录

    //筛选不要 . 和 .. 文件 , 只要文件(如果需要文件夹,加上 QDir::Dirs
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);

    //提取文件信息链表
    QFileInfoList inforList = dir.entryInfoList();

    //遍历文件信息链表,并进行相关操作
    foreach (QFileInfo info, inforList) {
        QString fileName = info.fileName();
        QString fileNamePath = info.filePath();
        QStringList strList = QString(fileName.toLocal8Bit()).split("_", Qt::SkipEmptyParts);

        if(strList.size() != 5) {
            showMsg("文件名格式不对：" + QString::number(strList.size()));
            showMsg(fileName);
            //showMsg(fileName.toLocal8Bit());
            remove(fileNamePath.toLocal8Bit());
            continue;
        }else if(fileNamePath .contains("ini")){
            showMsg("ini文件：" + fileNamePath);
            remove(fileNamePath.toLocal8Bit());
            continue;
        }


        //if(fileName.toLocal8Bit().contains("黄")){     // 如果是黄牌，发送至屏幕
        if(fileName.contains("黄")){     // 如果是黄牌，发送至屏幕
            QThread::msleep(m_delPicWaitTime);
            // 车道号是否正确
            if(road->getRoadNum().toInt() == QString(strList.at(3)).toInt()){
                //是否在工作时间
                if(QTime::currentTime() > m_startTime && QTime::currentTime() < m_stopTime){
                    // 备份图片
                    rename((road->getPicPath() + "/" + fileName).toLocal8Bit(), (road->getPicPathBack()+ "/" + fileName).toLocal8Bit());
                    sendData(road, fileName.split("_", Qt::SkipEmptyParts).at(1), "黄");
                }else{
                    showMsg("不在工作时间内");
                    remove(fileNamePath.toLocal8Bit());
                }
            }else{
                showMsg("车道号错误");
                remove(fileNamePath.toLocal8Bit());
            }
        }else{                          // 不是黄牌，直接删除
            showMsg("非黄牌");
            remove(fileNamePath.toLocal8Bit());
        }
    }
}

void Widget::dealPicFilesUnkown(QString filePath)
{
//    QEventLoop eventloop;
//    QTimer::singleShot(m_delPicWaitTime, &eventloop, SLOT(quit()));
//    eventloop.exec();

    Road* road = nullptr;
    QString cameraIp = filePath.split("/", Qt::SkipEmptyParts).at(3);

    foreach(Road* tmp, m_roadList){
        if(tmp->getCameraIp() == cameraIp){
            road = tmp;
            break;
        }
    }

    if(road == nullptr) return;

    QDir dir(filePath);   //打开目录

    //筛选不要 . 和 .. 文件 , 只要文件(如果需要文件夹,加上 QDir::Dirs
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);

    //提取文件信息链表
    QFileInfoList inforList = dir.entryInfoList();

    //遍历文件信息链表,并进行相关操作
    foreach (QFileInfo info, inforList) {
        QString fileName = info.fileName();
        QString fileNamePath = info.filePath();
        QStringList strList = QString(fileName.toLocal8Bit()).split("_", Qt::SkipEmptyParts);

        if(strList.size() != 5) {
            showMsg("文件名格式不对：" + QString::number(strList.size()));
            showMsg(fileName);
            //showMsg(fileName.toLocal8Bit());
            remove(fileNamePath.toLocal8Bit());
            continue;
        }else if(fileNamePath .contains("ini")){
            showMsg("ini文件：" + fileNamePath);
            remove(fileNamePath.toLocal8Bit());
            continue;
        }


        //if(fileName.toLocal8Bit().contains("黄")){     // 如果是黄牌，发送至屏幕
        if(fileName.contains("黄")){     // 如果是黄牌，发送至屏幕
            QThread::msleep(m_delPicWaitTime);
            // 车道号是否正确
            if(road->getRoadNum().toInt() == QString(strList.at(3)).toInt()){
                //是否在工作时间
                if(QTime::currentTime() > m_startTime && QTime::currentTime() < m_stopTime){
                    // 备份图片
                    rename((road->getPicPath() + "/" + fileName).toLocal8Bit(), (road->getPicPathBack()+ "/" + fileName).toLocal8Bit());
                    sendData(road, fileName.split("_", Qt::SkipEmptyParts).at(1), "黄");
                }else{
                    showMsg("不在工作时间内");
                    remove(fileNamePath.toLocal8Bit());
                }
            }else{
                showMsg("车道号错误");
                remove(fileNamePath.toLocal8Bit());
            }
        }else{                          // 不是黄牌，直接删除
            showMsg("非黄牌");
            remove(fileNamePath.toLocal8Bit());
        }
    }
}

void Widget::on_clearBtn_clicked()
{
    ui->history->clear();
}

void Widget::slotIpListCurrentIndexChanged(int index)
{
    Q_UNUSED(index);
    loadCurIpInfo();
}

void Widget::on_changeBtn_clicked()
{
    // 获取路口配置信息
    QString iniPath = QCoreApplication::applicationDirPath() + INIFILE_ROAD;
    if(!QFileInfo::exists(iniPath)){
        showMsg("****** road.ini 配置文件丢失 ******");
        return;
    }
    QSettings settings(QCoreApplication::applicationDirPath() + INIFILE_ROAD, QSettings::IniFormat);

    int tmp = 0;
    for(int i=0; i<m_roadCount; i++){
        while(settings.value(QString("road/cameraIp%1").arg(i+tmp+1,2,10,QLatin1Char('0')), "-1").toString() == "-1"){
            ++tmp;
        }
        if(m_roadList.at(i)->getCameraIp() == ui->ipList->currentText()){
            settings.setValue(QString("road/cameraIp%1").arg(i+1,2,10,QLatin1Char('0')), ui->currentIpEdit->text());
            settings.setValue(QString("road/screenDevNum%1").arg(i+1,2,10,QLatin1Char('0')), ui->currentScreenDevNumEdit->text());
            settings.setValue(QString("road/roadNum%1").arg(i+1,2,10,QLatin1Char('0')), ui->currentRoadEdit->text());
            break;
        }
    }
    unInitRoad();
    initRoad();

    showMsg("修改路口管理信息成功");
    system("sudo sync");
}

void Widget::on_deleteBtn_clicked()
{
    QString iniPath = QCoreApplication::applicationDirPath() + INIFILE_ROAD;
    if(!QFileInfo::exists(iniPath)){
        showMsg("****** road.ini 配置文件丢失 ******");
        return;
    }
    QSettings settings(QCoreApplication::applicationDirPath() + INIFILE_ROAD, QSettings::IniFormat);

    int tmp = 0;
    for(int i=0; i<m_roadCount; i++){
        while(settings.value(QString("road/cameraIp%1").arg(i+tmp+1,2,10,QLatin1Char('0')), "-1").toString() == "-1"){
            ++tmp;
        }

        if(m_roadList.at(i)->getCameraIp() == ui->ipList->currentText()){
            settings.remove(QString("road/cameraIp%1").arg(i+tmp+1,2,10,QLatin1Char('0')));
            settings.remove(QString("road/roadNum%1").arg(i+tmp+1,2,10,QLatin1Char('0')));
            settings.remove(QString("road/screenDevNum%1").arg(i+tmp+1,2,10,QLatin1Char('0')));
            settings.setValue(QString("others/roadCount").arg(i+tmp+1,2,10,QLatin1Char('0')), --m_roadCount);
            break;
        }
    }
    unInitRoad();
    initRoad();

    showMsg("删除路口管理信息成功");
    system("sudo sync");
}


void Widget::on_addBtn_clicked()
{
    if(ui->addIpEdit->text().isEmpty()
        || ui->addScreenDevNumEdit->text().isEmpty()
        || ui->addRoadEdit->text().isEmpty()){
        showMsg("添加新路口管理信息失败，值有误");
        return;
    }

    QString ip = ui->addIpEdit->text();
    foreach(Road* road, m_roadList){
        if(ip == road->getCameraIp()){
            showMsg("******添加失败！相机IP已存在，请检查配置文件");
            return;
        }
    }

    QString iniPath = QCoreApplication::applicationDirPath() + INIFILE_ROAD;
    if(!QFileInfo::exists(iniPath)){
        showMsg("****** road.ini 配置文件丢失 ******");
        return;
    }
    QSettings settings(QCoreApplication::applicationDirPath() + INIFILE_ROAD, QSettings::IniFormat);

    int i = 0;
    while(settings.value(QString("road/cameraIp%1").arg(i+1,2,10,QLatin1Char('0')), -1) != -1){
        i++;
        if(i == 10) break;
    }

    settings.setValue(QString("road/cameraIp%1").arg(i+1,2,10,QLatin1Char('0')), ui->addIpEdit->text());
    settings.setValue(QString("road/screenDevNum%1").arg(i+1,2,10,QLatin1Char('0')), ui->addScreenDevNumEdit->text());
    settings.setValue(QString("road/roadNum%1").arg(i+1,2,10,QLatin1Char('0')), ui->addRoadEdit->text());
    settings.setValue(QString("others/roadCount").arg(i+1,2,10,QLatin1Char('0')), ++m_roadCount);

    unInitRoad();
    initRoad();
    showMsg("添加新路口管理信息成功");
    system("sudo sync");
}

void Widget::on_changeWorkTimeBtn_clicked()
{
    QTime startTime = ui->startTimeEdit->time();
    QTime stopTime = ui->stopTimeEdit->time();

    if(startTime > stopTime){
        showMsg("时间设置失败！结束时间需要设置大于开始时间！");
        return;
    }

    QString iniPath = QCoreApplication::applicationDirPath() + INIFILE_ROAD;
    if(!QFileInfo::exists(iniPath)){
        showMsg("****** road.ini 配置文件丢失 ******");
        return;
    }
    QSettings settings(QCoreApplication::applicationDirPath() + INIFILE_ROAD, QSettings::IniFormat);

    m_startTime = startTime;
    m_stopTime = stopTime;

    settings.setValue(QString("others/startTime"), m_startTime.toString("hh:mm:ss"));
    settings.setValue(QString("others/stopTime"), m_stopTime.toString("hh:mm:ss"));
    showMsg("程序工作时间修改成功");
    system("sudo sync");
}


void Widget::on_delPicWaitTimeBtn_clicked()
{
    m_delPicWaitTime = ui->delPicWaitTime1->value();
    showMsg("延时修改成功：" + QString::number(m_delPicWaitTime));
}

