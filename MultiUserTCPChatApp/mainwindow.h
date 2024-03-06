#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer> //для сервера
#include <QtNetwork/QTcpSocket> //для соединения
#include <QIntValidator>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegExp>
#include <QDebug>
#include <QHostInfo>
#include <QTimer>
#include <QVector>
#include <QCloseEvent>
#include <QNetworkInterface>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void read_data(void); //поступили данные

    void new_connection(void); //подключился клиент

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_radioButton_client_clicked();

    void on_radioButton_server_clicked();

    void on_pushButton_create_clicked();

    void on_pushButton_connect_clicked();

    void on_pushButton_send_message_clicked();

    void disconnection(void); //слот для обработки сигнала disconnected

    void IP_adress_show(void); //функция демонстрации IP-адреса

    void timer_tick(void); //слот для обработки сигнала таймера

    void on_pushButton_spam_clicked();

    void on_pushButton_stopSpam_clicked();

    void on_lineEdit_nickname_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QTcpServer *TCPServer=nullptr;
    QTcpSocket *TCPSocket=nullptr;
    QTcpSocket *TCPSocket_tmp=nullptr;

    QHostAddress *adress=nullptr;

    QVector<QTcpSocket*> Sockets;

    bool gl_flConnection;
    bool glFlag_client;
    bool glFlag_server;
    bool glFlag_serverDisconnected;

    QTimer *timer; //указатель на класс Таймер
    int counter; //счетчик

    QString UserNickname="";

};

#endif // MAINWINDOW_H
