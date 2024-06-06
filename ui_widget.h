/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPlainTextEdit *history;
    QLabel *timerLabel;
    QPushButton *clearBtn;
    QComboBox *ipList;
    QLabel *label;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QPushButton *changeBtn;
    QLineEdit *currentIpEdit;
    QLineEdit *currentRoadEdit;
    QLineEdit *currentScreenDevNumEdit;
    QPushButton *deleteBtn;
    QGroupBox *groupBox_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *addBtn;
    QLineEdit *addIpEdit;
    QLineEdit *addRoadEdit;
    QLineEdit *addScreenDevNumEdit;
    QGroupBox *groupBox_3;
    QPushButton *changeWorkTimeBtn;
    QLabel *label_8;
    QLabel *label_10;
    QTimeEdit *startTimeEdit;
    QTimeEdit *stopTimeEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(638, 349);
        history = new QPlainTextEdit(Widget);
        history->setObjectName(QString::fromUtf8("history"));
        history->setGeometry(QRect(10, 240, 621, 81));
        history->setReadOnly(true);
        timerLabel = new QLabel(Widget);
        timerLabel->setObjectName(QString::fromUtf8("timerLabel"));
        timerLabel->setGeometry(QRect(480, 320, 150, 20));
        clearBtn = new QPushButton(Widget);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));
        clearBtn->setGeometry(QRect(10, 320, 91, 21));
        ipList = new QComboBox(Widget);
        ipList->setObjectName(QString::fromUtf8("ipList"));
        ipList->setGeometry(QRect(100, 10, 111, 20));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 81, 20));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 40, 200, 191));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 30, 50, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 70, 50, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 110, 50, 20));
        changeBtn = new QPushButton(groupBox);
        changeBtn->setObjectName(QString::fromUtf8("changeBtn"));
        changeBtn->setGeometry(QRect(110, 150, 81, 28));
        currentIpEdit = new QLineEdit(groupBox);
        currentIpEdit->setObjectName(QString::fromUtf8("currentIpEdit"));
        currentIpEdit->setGeometry(QRect(72, 30, 120, 24));
        currentRoadEdit = new QLineEdit(groupBox);
        currentRoadEdit->setObjectName(QString::fromUtf8("currentRoadEdit"));
        currentRoadEdit->setGeometry(QRect(72, 70, 120, 24));
        currentScreenDevNumEdit = new QLineEdit(groupBox);
        currentScreenDevNumEdit->setObjectName(QString::fromUtf8("currentScreenDevNumEdit"));
        currentScreenDevNumEdit->setGeometry(QRect(70, 110, 120, 24));
        deleteBtn = new QPushButton(groupBox);
        deleteBtn->setObjectName(QString::fromUtf8("deleteBtn"));
        deleteBtn->setGeometry(QRect(10, 150, 81, 28));
        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(220, 40, 200, 191));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 30, 50, 20));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 70, 50, 20));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 110, 50, 20));
        addBtn = new QPushButton(groupBox_2);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));
        addBtn->setGeometry(QRect(50, 150, 81, 28));
        addIpEdit = new QLineEdit(groupBox_2);
        addIpEdit->setObjectName(QString::fromUtf8("addIpEdit"));
        addIpEdit->setGeometry(QRect(72, 30, 120, 24));
        addRoadEdit = new QLineEdit(groupBox_2);
        addRoadEdit->setObjectName(QString::fromUtf8("addRoadEdit"));
        addRoadEdit->setGeometry(QRect(72, 70, 120, 24));
        addScreenDevNumEdit = new QLineEdit(groupBox_2);
        addScreenDevNumEdit->setObjectName(QString::fromUtf8("addScreenDevNumEdit"));
        addScreenDevNumEdit->setGeometry(QRect(70, 110, 120, 24));
        groupBox_3 = new QGroupBox(Widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(430, 40, 200, 191));
        changeWorkTimeBtn = new QPushButton(groupBox_3);
        changeWorkTimeBtn->setObjectName(QString::fromUtf8("changeWorkTimeBtn"));
        changeWorkTimeBtn->setGeometry(QRect(50, 150, 81, 28));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 30, 50, 20));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 70, 50, 20));
        startTimeEdit = new QTimeEdit(groupBox_3);
        startTimeEdit->setObjectName(QString::fromUtf8("startTimeEdit"));
        startTimeEdit->setGeometry(QRect(70, 30, 81, 20));
        startTimeEdit->setMinimumDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 0, 0)));
        startTimeEdit->setMinimumTime(QTime(0, 0, 0));
        stopTimeEdit = new QTimeEdit(groupBox_3);
        stopTimeEdit->setObjectName(QString::fromUtf8("stopTimeEdit"));
        stopTimeEdit->setGeometry(QRect(70, 70, 81, 20));
        stopTimeEdit->setMinimumDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 0, 0)));
        stopTimeEdit->setMinimumTime(QTime(0, 0, 0));
        history->raise();
        clearBtn->raise();
        timerLabel->raise();
        ipList->raise();
        label->raise();
        groupBox->raise();
        groupBox_2->raise();
        groupBox_3->raise();

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        timerLabel->setText(QString());
        clearBtn->setText(QCoreApplication::translate("Widget", "clear", nullptr));
        label->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\346\221\204\345\203\217\346\234\272\345\210\227\350\241\250</p></body></html>", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\345\275\223\345\211\215", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">ip</p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\350\275\246\351\201\223</p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\350\256\276\345\244\207\345\217\267</p></body></html>", nullptr));
        changeBtn->setText(QCoreApplication::translate("Widget", "\344\277\256\346\224\271\345\217\202\346\225\260", nullptr));
        currentIpEdit->setPlaceholderText(QCoreApplication::translate("Widget", "\346\221\204\345\203\217\346\234\272ip", nullptr));
        currentRoadEdit->setPlaceholderText(QCoreApplication::translate("Widget", "\347\256\241\347\220\206\347\232\204\350\275\246\351\201\223\345\217\267", nullptr));
        currentScreenDevNumEdit->setText(QString());
        currentScreenDevNumEdit->setPlaceholderText(QCoreApplication::translate("Widget", "\350\276\205\345\212\251\345\261\217\350\256\276\345\244\207\345\217\267", nullptr));
        deleteBtn->setText(QCoreApplication::translate("Widget", "\345\210\240\351\231\244\345\275\223\345\211\215", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\346\267\273\345\212\240", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">ip</p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\350\275\246\351\201\223</p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\350\256\276\345\244\207\345\217\267</p></body></html>", nullptr));
        addBtn->setText(QCoreApplication::translate("Widget", "\346\267\273\345\212\240\347\256\241\347\220\206", nullptr));
        addIpEdit->setPlaceholderText(QCoreApplication::translate("Widget", "\346\221\204\345\203\217\346\234\272ip", nullptr));
        addRoadEdit->setPlaceholderText(QCoreApplication::translate("Widget", "\347\256\241\347\220\206\347\232\204\350\275\246\351\201\223\345\217\267", nullptr));
        addScreenDevNumEdit->setText(QString());
        addScreenDevNumEdit->setPlaceholderText(QCoreApplication::translate("Widget", "\350\276\205\345\212\251\345\261\217\350\256\276\345\244\207\345\217\267", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Widget", "\346\234\211\346\225\210\345\267\245\344\275\234\346\227\266\351\227\264", nullptr));
        changeWorkTimeBtn->setText(QCoreApplication::translate("Widget", "\344\277\256\346\224\271\346\227\266\351\227\264", nullptr));
        label_8->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\345\274\200\345\247\213</p></body></html>", nullptr));
        label_10->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\347\273\223\346\235\237</p></body></html>", nullptr));
        startTimeEdit->setDisplayFormat(QCoreApplication::translate("Widget", "hh:mm:ss", nullptr));
        stopTimeEdit->setDisplayFormat(QCoreApplication::translate("Widget", "hh:mm:ss", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
