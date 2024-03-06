/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QRadioButton *radioButton_client;
    QRadioButton *radioButton_server;
    QLabel *label_port;
    QLabel *label_adress;
    QLineEdit *lineEdit_port;
    QLineEdit *lineEdit_adress;
    QTextEdit *textEdit_input;
    QTextEdit *textEdit_output;
    QLineEdit *lineEdit_send_message;
    QPushButton *pushButton_send_message;
    QPushButton *pushButton_create;
    QPushButton *pushButton_connect;
    QLabel *label_IP_adress;
    QLineEdit *lineEdit_forSpamMessage;
    QPushButton *pushButton_stopSpam;
    QSpinBox *spinBox_spamTime;
    QLabel *label_setTime;
    QLabel *label_spamMessage;
    QPushButton *pushButton_spam;
    QLabel *label_nickname;
    QLineEdit *lineEdit_nickname;
    QTextEdit *textEdit_adresses;
    QFrame *line;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(948, 729);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 301, 101));
        radioButton_client = new QRadioButton(groupBox);
        radioButton_client->setObjectName(QString::fromUtf8("radioButton_client"));
        radioButton_client->setGeometry(QRect(10, 20, 151, 31));
        radioButton_server = new QRadioButton(groupBox);
        radioButton_server->setObjectName(QString::fromUtf8("radioButton_server"));
        radioButton_server->setGeometry(QRect(10, 60, 131, 31));
        label_port = new QLabel(centralWidget);
        label_port->setObjectName(QString::fromUtf8("label_port"));
        label_port->setGeometry(QRect(10, 210, 101, 31));
        label_adress = new QLabel(centralWidget);
        label_adress->setObjectName(QString::fromUtf8("label_adress"));
        label_adress->setGeometry(QRect(10, 280, 101, 31));
        lineEdit_port = new QLineEdit(centralWidget);
        lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));
        lineEdit_port->setGeometry(QRect(140, 210, 171, 41));
        lineEdit_adress = new QLineEdit(centralWidget);
        lineEdit_adress->setObjectName(QString::fromUtf8("lineEdit_adress"));
        lineEdit_adress->setGeometry(QRect(140, 280, 171, 41));
        textEdit_input = new QTextEdit(centralWidget);
        textEdit_input->setObjectName(QString::fromUtf8("textEdit_input"));
        textEdit_input->setGeometry(QRect(350, 10, 581, 281));
        textEdit_output = new QTextEdit(centralWidget);
        textEdit_output->setObjectName(QString::fromUtf8("textEdit_output"));
        textEdit_output->setGeometry(QRect(350, 330, 581, 261));
        lineEdit_send_message = new QLineEdit(centralWidget);
        lineEdit_send_message->setObjectName(QString::fromUtf8("lineEdit_send_message"));
        lineEdit_send_message->setGeometry(QRect(350, 620, 431, 31));
        pushButton_send_message = new QPushButton(centralWidget);
        pushButton_send_message->setObjectName(QString::fromUtf8("pushButton_send_message"));
        pushButton_send_message->setGeometry(QRect(800, 620, 131, 31));
        pushButton_create = new QPushButton(centralWidget);
        pushButton_create->setObjectName(QString::fromUtf8("pushButton_create"));
        pushButton_create->setGeometry(QRect(140, 420, 171, 41));
        pushButton_connect = new QPushButton(centralWidget);
        pushButton_connect->setObjectName(QString::fromUtf8("pushButton_connect"));
        pushButton_connect->setGeometry(QRect(140, 480, 171, 41));
        label_IP_adress = new QLabel(centralWidget);
        label_IP_adress->setObjectName(QString::fromUtf8("label_IP_adress"));
        label_IP_adress->setGeometry(QRect(10, 101, 301, 20));
        lineEdit_forSpamMessage = new QLineEdit(centralWidget);
        lineEdit_forSpamMessage->setObjectName(QString::fromUtf8("lineEdit_forSpamMessage"));
        lineEdit_forSpamMessage->setGeometry(QRect(130, 570, 201, 31));
        pushButton_stopSpam = new QPushButton(centralWidget);
        pushButton_stopSpam->setObjectName(QString::fromUtf8("pushButton_stopSpam"));
        pushButton_stopSpam->setGeometry(QRect(180, 620, 151, 31));
        spinBox_spamTime = new QSpinBox(centralWidget);
        spinBox_spamTime->setObjectName(QString::fromUtf8("spinBox_spamTime"));
        spinBox_spamTime->setGeometry(QRect(10, 570, 91, 31));
        spinBox_spamTime->setMinimum(1);
        label_setTime = new QLabel(centralWidget);
        label_setTime->setObjectName(QString::fromUtf8("label_setTime"));
        label_setTime->setGeometry(QRect(10, 540, 91, 21));
        label_spamMessage = new QLabel(centralWidget);
        label_spamMessage->setObjectName(QString::fromUtf8("label_spamMessage"));
        label_spamMessage->setGeometry(QRect(130, 540, 201, 21));
        pushButton_spam = new QPushButton(centralWidget);
        pushButton_spam->setObjectName(QString::fromUtf8("pushButton_spam"));
        pushButton_spam->setGeometry(QRect(10, 620, 151, 31));
        label_nickname = new QLabel(centralWidget);
        label_nickname->setObjectName(QString::fromUtf8("label_nickname"));
        label_nickname->setGeometry(QRect(10, 350, 121, 21));
        lineEdit_nickname = new QLineEdit(centralWidget);
        lineEdit_nickname->setObjectName(QString::fromUtf8("lineEdit_nickname"));
        lineEdit_nickname->setGeometry(QRect(140, 350, 171, 41));
        lineEdit_nickname->setMaxLength(20);
        textEdit_adresses = new QTextEdit(centralWidget);
        textEdit_adresses->setObjectName(QString::fromUtf8("textEdit_adresses"));
        textEdit_adresses->setGeometry(QRect(10, 120, 301, 71));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 190, 301, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 948, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "\320\240\320\265\320\266\320\270\320\274", nullptr));
        radioButton_client->setText(QApplication::translate("MainWindow", "\320\232\320\273\320\270\320\265\320\275\321\202", nullptr));
        radioButton_server->setText(QApplication::translate("MainWindow", "\320\241\320\265\321\200\320\262\320\265\321\200", nullptr));
        label_port->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202", nullptr));
        label_adress->setText(QApplication::translate("MainWindow", "\320\220\320\264\321\200\320\265\321\201", nullptr));
        pushButton_send_message->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton_create->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\201\320\265\321\200\320\262\320\265\321\200", nullptr));
        pushButton_connect->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217 \320\272 \321\201\320\265\321\200\320\262\320\265\321\200\321\203", nullptr));
        label_IP_adress->setText(QApplication::translate("MainWindow", "IP-\320\260\320\264\321\200\320\265\321\201\320\260:", nullptr));
        pushButton_stopSpam->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\265\320\272\321\200\320\260\321\202\320\270\321\202\321\214 \321\201\320\277\320\260\320\274", nullptr));
        label_setTime->setText(QApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \321\201\320\277\320\260\320\274\320\260, \321\201\320\265\320\272", nullptr));
        label_spamMessage->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265 \320\264\320\273\321\217 \321\201\320\277\320\260\320\274\320\260", nullptr));
        pushButton_spam->setText(QApplication::translate("MainWindow", "\320\241\320\277\320\260\320\274", nullptr));
        label_nickname->setText(QApplication::translate("MainWindow", "\320\235\320\270\320\272\320\275\320\265\320\271\320\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
