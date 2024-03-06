#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : //конструктор
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("MultiUserTCP_ChatRV");

    ui->pushButton_connect->hide();
    ui->pushButton_create->hide();
    ui->pushButton_send_message->hide();

    ui->label_adress->hide();
    ui->label_port->hide();

    ui->lineEdit_adress->hide();
    ui->lineEdit_port->hide();
    ui->lineEdit_send_message->hide();

    ui->label_nickname->hide();
    ui->lineEdit_nickname->hide();

    ui->textEdit_input->hide();
    ui->textEdit_output->hide();

    //делаем красоту с расположением кнопок
    QPoint point;
    point=ui->pushButton_connect->pos();
    point.setY(420);
    ui->pushButton_connect->move(point);

    point=ui->pushButton_create->pos();
    point.setY(300);
    ui->pushButton_create->move(point);

    //целочисленный валидатор на порт
    QIntValidator *my_Validator=new QIntValidator(1,65536,this);
    ui->lineEdit_port->setValidator(my_Validator);

    //устанавливаем валидатор на ввод IP-адрес
    //создаем строку для регулярного выражения
    QString IP_Range="(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

    //создаем регулярное выражение с применением строки, как повторяющегося элемента
    QRegExp ipRegex ("^" + IP_Range + "\\." + IP_Range + "\\." + IP_Range + "\\." + IP_Range + "$");

    //создаем валидатор регулярного выражения с применением созданного регулярного выражения и устанавливаем его на lineEdit_adress
    QRegExpValidator *my_IP_Validator=new QRegExpValidator(ipRegex,this);
    ui->lineEdit_adress->setValidator(my_IP_Validator);

    //настройка интерфейса дополнительного функционала
    ui->label_IP_adress->hide();
    ui->textEdit_adresses->hide();
    ui->line->hide();

    ui->label_setTime->hide();
    ui->label_spamMessage->hide();
    ui->spinBox_spamTime->hide();
    ui->lineEdit_forSpamMessage->hide();
    ui->pushButton_spam->hide();
    ui->pushButton_stopSpam->hide();
    ui->pushButton_stopSpam->setEnabled(false);

    //инициализация таймера
    timer=new QTimer(this); //создаем экземпляр класса
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_tick()));
    counter=0; //инициализация счетчика
    timer->setInterval(1000);
    timer->setTimerType(Qt::PreciseTimer);

    //необходимые флаги
    gl_flConnection=false;
    glFlag_client=false;
    glFlag_server=false;
    glFlag_serverDisconnected=false;
}

MainWindow::~MainWindow() //деструктор
{
    if (adress!=nullptr)
    {
        delete adress;
    }

    if (TCPSocket!=nullptr)
    {
        delete TCPSocket;
    }

    if (TCPServer!=nullptr)
    {
        delete TCPServer;
    }

    delete ui;
}

void MainWindow::read_data() //поступили данные
{
    if (gl_flConnection)
    {
        if (glFlag_client) //считывание данных клиентом
        {
            QByteArray ba;
            ba=TCPSocket->readAll();
            QString stroka=QString::fromLocal8Bit(ba);
            ui->textEdit_input->append(stroka);
        }

        if (glFlag_server) //считывание данных сервером для их перенаправки всем клиентам
        {
            QByteArray ba;
            if (TCPSocket_tmp==nullptr)
            {
                for (int i=Sockets.size()-1;i>=0;i--)
                {
                    if (Sockets[i]!=nullptr)
                    {
                        ba=Sockets[i]->readAll();
                        //Так как сообщение клиента записывается только в один из сокетов, хранящихся в контейнере,
                        //идентифицируем этот сокет и выходим из цикла, иначе мы можем считать данные из пустого сокета
                        //и разослать эту пустоту всем клиентам
                        if (ba.size()!=0)
                        {
                            QString stroka=QString::fromLocal8Bit(ba);
                            ui->textEdit_input->append(stroka);
                            break;
                        }
                    }
                }

                //рассылаем сообщение одного пользователя всем остальным (и ему в том числе)
                for (int i=Sockets.size()-1;i>=0;i--)
                {
                    if (Sockets[i]!=nullptr)
                    {
                        Sockets[i]->write(ba);
                    }
                }
            }
        }
    }
}

void MainWindow::timer_tick() //отправка спама по таймеру
{
    if (counter<ui->spinBox_spamTime->value())
    {
        counter++;
        QByteArray ba_spam;
        if (glFlag_client) //аналогично с отправкой обычного сообщения, спам отсылаем серверу, который перенаправляет его всем клиентам
        {
            ba_spam=UserNickname.toLocal8Bit() + ": " + ui->lineEdit_forSpamMessage->text().toLocal8Bit();
            TCPSocket->write(ba_spam);
            ui->textEdit_output->append("Вы: " + ui->lineEdit_forSpamMessage->text());
        }

        if (glFlag_server) //сервер сразу спамит всем подключенным пользователям
        {
            for (int i=Sockets.size()-1;i>=0;i--)
            {
                if (Sockets[i]!=nullptr)
                {
                    QString server_name="Сервер: ";
                    ba_spam=server_name.toLocal8Bit() + ui->lineEdit_forSpamMessage->text().toLocal8Bit();
                    Sockets[i]->write(ba_spam);
                }
            }
            ui->textEdit_output->append("Вы: " + ui->lineEdit_forSpamMessage->text());
            ui->textEdit_input->append("Сервер: " + ui->lineEdit_forSpamMessage->text());
        }
    }
    else
    {
        timer->stop();
        ui->pushButton_stopSpam->setEnabled(false);
        ui->spinBox_spamTime->setEnabled(true);
        counter=0;
    }
}

void MainWindow::new_connection() //подключился клиент
{  
    if (Sockets.size()<5)
    {
        TCPSocket=new QTcpSocket;
        TCPSocket=TCPServer->nextPendingConnection();
        connect(TCPSocket,SIGNAL(readyRead()),this,SLOT(read_data()));
        connect(TCPSocket,SIGNAL(disconnected()),this,SLOT(disconnection()));
        Sockets.push_back(TCPSocket); //при каждом новом подключении создаем отдельный сокет для связи с клиентом и добавляем сокет в контейнер

        ui->textEdit_input->show();
        ui->textEdit_output->show();
        ui->lineEdit_send_message->show();
        ui->pushButton_send_message->show();

        ui->label_setTime->show();
        ui->label_spamMessage->show();
        ui->spinBox_spamTime->show();
        ui->lineEdit_forSpamMessage->show();
        ui->pushButton_spam->show();
        ui->pushButton_stopSpam->show();
    }
    else
    {
        TCPSocket_tmp=TCPServer->nextPendingConnection();
        connect(TCPSocket_tmp,SIGNAL(readyRead()),this,SLOT(read_data()));
        connect(TCPSocket_tmp,SIGNAL(disconnected()),this,SLOT(disconnection()));
        QString ser_mes="<font color=red> Не удалось подключиться - на сервере ведется СЛИШКОМ оживленная дискуссия </font";
        QByteArray ba_service9=ser_mes.toLocal8Bit();
        TCPSocket_tmp->write(ba_service9);
        TCPSocket_tmp->close();
        TCPSocket_tmp=nullptr;
    }
}

void MainWindow::closeEvent(QCloseEvent *event) //при закрытии окна отправляем нужную служебную рассылку
{
    if (glFlag_server) //закрываем окно в режиме "сервера"
    {
        if (!Sockets.isEmpty()) //проверяем, есть ли кому сообщить информацию о закрытии сервера
        {
            for (int i=Sockets.size()-1;i>=0;i--)
            {
                if (Sockets[i]!=nullptr)
                {
                    QString ser_mes="<font color=red> Соединение с сервером разорвано </font";
                    QByteArray ba_service3=ser_mes.toLocal8Bit();
                    Sockets[i]->write(ba_service3);
                    Sockets[i]->close();
                    Sockets[i]=nullptr;
                    Sockets.removeLast();
                }
            }
        }
    }

    if (glFlag_client && TCPSocket!=nullptr) //закрываем окно в режиме "клиента"
    {
        QString ser_mes=UserNickname + "<font color=red> отключился от сервера </font";
        QByteArray ba_service4=ser_mes.toLocal8Bit();
        TCPSocket->write(ba_service4);
        TCPSocket->close();
        TCPSocket=nullptr;
    }

    event->accept();
}

void MainWindow::disconnection() //сигнал отключения клиента или сервера
{
    //При срабатывании у сокета сигнала disconnected() вызывается этот слот
    //Если отключается один сокет, то отключается и тот сокет, с которым он был связан,
    //соответственно, данный слот будет вызываться на обеих сторонах

    if (glFlag_client) //когда закрывается сервер, сторона клиента должна узнать о своем отключении
    {
        ui->pushButton_connect->setText("Подключиться к серверу");
        TCPSocket=nullptr;
        gl_flConnection=false;
    }

    if (!glFlag_serverDisconnected && glFlag_server) //когда отключается клиент, удаляем не нужный более сокет
    {
        for (int i=Sockets.size()-1;i>=0;i--)
        {
            if (Sockets[i]->state()==QAbstractSocket::UnconnectedState) //идентифицируем сокет отключившегося клиента
                                                                        //через соответствующее состояние его сокета
            {
                Sockets[i]=nullptr;
                Sockets.remove(i); //удаляем из контейнера найденный сокет
            }
        }
    }

    glFlag_serverDisconnected=false;

    if (timer->isActive()) //если во время спама срабатывает сигнал disconnected(), то спам необходимо прервать для предотвращения авариек
    {
        timer->stop();
        counter=0;
        ui->pushButton_stopSpam->setEnabled(false);
        ui->spinBox_spamTime->setEnabled(true);
    }
}


void MainWindow::IP_adress_show() //демонстрация IP-адреса
{
    ui->textEdit_adresses->clear();

    QString localhostname=QHostInfo::localHostName(); //возвращаем имя хоста данного устройства
    QString localhostIP;
    QList<QHostAddress> hostList=QHostInfo::fromName(localhostname).addresses(); //находим IP-адреса, связанные с именем хоста
    foreach (const QHostAddress& address, hostList)
    {
        if (address.protocol()==QAbstractSocket::IPv4Protocol && address.isLoopback()==false) //находим нужный IPv4-адрес
        {
            localhostIP=address.toString();
            ui->label_IP_adress->show();
            ui->textEdit_adresses->show();
            ui->line->show();
            ui->textEdit_adresses->append(localhostIP);
        }
    }

    QString localMacAddress;
    QString localNetmask;
    foreach (const QNetworkInterface& networkInterface, QNetworkInterface::allInterfaces())
    {
        foreach (const QNetworkAddressEntry& entry, networkInterface.addressEntries())
        {
            if (entry.ip().toString()==localhostIP) {
                localMacAddress=networkInterface.hardwareAddress();
                localNetmask=entry.netmask().toString();
                ui->textEdit_adresses->append("MAC-адрес: " + localMacAddress);
                ui->textEdit_adresses->append("Маска: " + localNetmask);
                break;
            }
        }
    }

    //Суть константных ссылок заключается в том, что мы получаем доступ к значению переменной,
    //на которую сделана ссылка, но изменить ее не имеем права
}


void MainWindow::on_radioButton_client_clicked() //выбран режим клиента
{
    IP_adress_show();

    ui->radioButton_client->setEnabled(false);
    ui->radioButton_server->setEnabled(true);

    if (Sockets.isEmpty() && TCPServer==nullptr)
    {
        ui->pushButton_connect->show();
        ui->pushButton_create->hide();

        ui->label_adress->show();
        ui->label_port->show();

        ui->lineEdit_adress->show();
        ui->lineEdit_port->show();

        ui->label_nickname->show();
        ui->lineEdit_nickname->show();

        ui->pushButton_send_message->hide();
        ui->lineEdit_send_message->hide();

        ui->lineEdit_nickname->clear();
        ui->lineEdit_send_message->clear();
        ui->lineEdit_forSpamMessage->clear();
        ui->spinBox_spamTime->setValue(1);
        ui->lineEdit_port->clear();
        ui->lineEdit_adress->clear();
        ui->textEdit_input->clear();
        ui->textEdit_output->clear();

        ui->textEdit_input->hide();
        ui->textEdit_output->hide();

        ui->label_setTime->hide();
        ui->label_spamMessage->hide();
        ui->spinBox_spamTime->hide();
        ui->lineEdit_forSpamMessage->hide();
        ui->pushButton_spam->hide();
        ui->pushButton_stopSpam->hide();
    }

    //переход в режим "клиента" из режима "сервера" с открытым сервером
    if(TCPServer!=nullptr)
    {
        glFlag_serverDisconnected=true;;
        if (!Sockets.isEmpty())
        {
            for (int i=Sockets.size()-1;i>=0;i--)
            {
                if (Sockets[i]!=nullptr)
                {
                    QString ser_mes="<font color=red> Соединение с сервером разорвано </font";
                    QByteArray ba_service5=ser_mes.toLocal8Bit();
                    Sockets[i]->write(ba_service5);
                    Sockets[i]->close();
                    Sockets[i]=nullptr;
                    Sockets.removeLast();
                }
            }
        }
        else
        {
            glFlag_serverDisconnected=false;
        }
        TCPSocket=nullptr;
        TCPServer->close();
        TCPServer=nullptr;
        ui->pushButton_create->setText("Создать сервер");
        ui->textEdit_output->append("<font color=magenta> Сервер закрыт </font");
        gl_flConnection=false;

        ui->lineEdit_nickname->clear();
        ui->lineEdit_send_message->clear();
        ui->lineEdit_forSpamMessage->clear();
        ui->spinBox_spamTime->setValue(1);
        ui->lineEdit_port->clear();
        ui->lineEdit_adress->clear();
        ui->textEdit_input->clear();
        ui->textEdit_output->clear();

        ui->textEdit_input->hide();
        ui->textEdit_output->hide();

        ui->label_setTime->hide();
        ui->label_spamMessage->hide();
        ui->spinBox_spamTime->hide();
        ui->lineEdit_forSpamMessage->hide();
        ui->pushButton_spam->hide();
        ui->pushButton_stopSpam->hide();

        ui->pushButton_connect->show();
        ui->pushButton_connect->setText("Подключиться к серверу");
        ui->pushButton_create->hide();
        ui->label_port->show();
        ui->lineEdit_port->show();
        ui->label_adress->show();
        ui->lineEdit_adress->show();
        ui->label_nickname->show();
        ui->lineEdit_nickname->show();
        ui->pushButton_send_message->hide();
        ui->lineEdit_send_message->hide();

        glFlag_client=false;
        glFlag_server=false;
        glFlag_serverDisconnected=false;
    }
}

void MainWindow::on_radioButton_server_clicked() //выбран режим сервера
{
    IP_adress_show();

    ui->radioButton_server->setEnabled(false);
    ui->radioButton_client->setEnabled(true);

    if (TCPServer==nullptr)
    {
        ui->pushButton_create->show();
        ui->pushButton_connect->hide();

        ui->label_adress->hide();
        ui->lineEdit_adress->hide();

        ui->label_nickname->hide();
        ui->lineEdit_nickname->hide();

        ui->label_port->show();
        ui->lineEdit_port->show();

        ui->pushButton_send_message->hide();
        ui->lineEdit_send_message->hide();

        ui->lineEdit_nickname->clear();
        ui->lineEdit_send_message->clear();
        ui->lineEdit_forSpamMessage->clear();
        ui->spinBox_spamTime->setValue(1);
        ui->lineEdit_port->clear();
        ui->lineEdit_adress->clear();
        ui->textEdit_input->clear();
        ui->textEdit_output->clear();

        ui->textEdit_input->hide();
        ui->textEdit_output->hide();

        ui->label_setTime->hide();
        ui->label_spamMessage->hide();
        ui->spinBox_spamTime->hide();
        ui->lineEdit_forSpamMessage->hide();
        ui->pushButton_spam->hide();
        ui->pushButton_stopSpam->hide();
    }

    //переход в режим "сервера" из режима "клиента" с подключенным статусом
    if (TCPSocket!=nullptr && TCPServer==nullptr && glFlag_client)
    {
        QString ser_mes=UserNickname + "<font color=red> отключился от сервера </font";
        QByteArray ba_service8=ser_mes.toLocal8Bit();
        TCPSocket->write(ba_service8);
        TCPSocket->close();
        TCPSocket=nullptr;
        ui->pushButton_connect->setText("Подключиться к серверу");
        ui->textEdit_output->append("<font color=magenta> Вы отключились от сервера </font>");
        gl_flConnection=false;

        ui->label_setTime->hide();
        ui->label_spamMessage->hide();
        ui->spinBox_spamTime->hide();
        ui->lineEdit_forSpamMessage->hide();
        ui->pushButton_spam->hide();
        ui->pushButton_stopSpam->hide();

        ui->pushButton_connect->hide();
        ui->pushButton_create->show();
        ui->pushButton_create->setText("Создать сервер");
        ui->pushButton_send_message->hide();
        ui->lineEdit_send_message->hide();

        ui->lineEdit_adress->hide();
        ui->label_adress->hide();
        ui->label_nickname->hide();
        ui->lineEdit_nickname->hide();

        ui->textEdit_input->hide();
        ui->textEdit_output->hide();

        ui->lineEdit_nickname->clear();
        ui->lineEdit_send_message->clear();
        ui->lineEdit_forSpamMessage->clear();
        ui->spinBox_spamTime->setValue(1);
        ui->lineEdit_port->clear();
        ui->lineEdit_adress->clear();
        ui->textEdit_input->clear();
        ui->textEdit_output->clear();

        glFlag_client=false;
        glFlag_server=false;
        glFlag_serverDisconnected=false;
    }
}

void MainWindow::on_pushButton_create_clicked() //создание соединения (сервера)
{
    if (TCPServer==nullptr)
    {//если серевер не создан
        int port;
        port=ui->lineEdit_port->text().toInt();
        if (port>0 && port<65536) //в протоколе TCP под номер порта отведены числа в диапазоне от 1 до 65535
        {
            TCPServer=new QTcpServer(this);
            if (TCPServer->listen(QHostAddress::Any,quint16(port))) //узнаем статус прослушивания со стороны сервера
            {//если сервер готов прослушивать адреса
                connect(TCPServer,SIGNAL(newConnection()),this,SLOT(new_connection()));
                ui->textEdit_output->append("<font color=green> Сервер создан </font>");
                ui->pushButton_create->setText("Закрыть сервер");
                gl_flConnection=true;
                glFlag_server=true;
            }
            else
            {//если сервер не готов прослушивать адреса
                QMessageBox::information(this,"","Не удалось создать сервер");
                TCPServer->deleteLater();
                TCPServer=nullptr;
            }
        }
        else
        {
            QMessageBox::information(this,"","Значение порта должно быть в диапазоне от 1 дл 65535");
            gl_flConnection=false;
        }
    }
    else
    {//если сервер создан, закрываем сервер и сокет клиента
        glFlag_serverDisconnected=true;
        if (!Sockets.isEmpty()) //проверяем, есть ли кому сообщить информацию о закрытии сервера
        {
            for (int i=Sockets.size()-1;i>=0;i--)
            {
                if (Sockets[i]!=nullptr)
                {
                    QString ser_mes="<font color=red> Соединение с сервером разорвано </font";
                    QByteArray ba_service5=ser_mes.toLocal8Bit();
                    Sockets[i]->write(ba_service5);
                    Sockets[i]->close();
                    Sockets[i]=nullptr;
                    Sockets.removeLast();
                }
            }
        }
        else
        {
            glFlag_serverDisconnected=false;
        }
        TCPServer->close();
        TCPServer=nullptr;
        ui->pushButton_create->setText("Создать сервер");
        ui->textEdit_output->append("<font color=magenta> Сервер закрыт </font");
        gl_flConnection=false;
    }
}

void MainWindow::on_pushButton_connect_clicked() //подключаемся к серверу со стороны клиента
{
    if (TCPSocket==nullptr)
    {//если сокет клиента не подключен к серверу
        int port;
        port=ui->lineEdit_port->text().toInt();
        if (port>0 && port<65536) //в протоколе TCP под номер порта отведены числа в диапазоне от 1 до 65535
        {
            QString adress_name=ui->lineEdit_adress->text();
            int dot_counter=0;
            for (int i=0;i<adress_name.length()-1;i++) //считаем количество точек в введнном IP-адресе -_-
            {
                if (adress_name[i]==".")
                {
                    dot_counter+=1;
                }
            }

            if (dot_counter==3) //если насчитали три точки, то IP-адрес введен верно, можно переходить к следующему испытанию
            {
                //UserNickname=ui->lineEdit_nickname->text();
                if (UserNickname!="") //проверяем, был ли введен никнейм
                {
                    TCPSocket=new QTcpSocket(this);
                    connect(TCPSocket,SIGNAL(readyRead()),this,SLOT(read_data()));
                    connect(TCPSocket,SIGNAL(disconnected()),this,SLOT(disconnection()));

                    adress=new QHostAddress;
                    adress->setAddress(adress_name);
                    TCPSocket->connectToHost(*adress,quint16(port));
                    TCPSocket->waitForConnected(100); //ожидаем подключения к хосту (серверу)

                    if (TCPSocket->state()==QTcpSocket::ConnectedState) //если подключились, то можно начинать общение
                    {
                        gl_flConnection=true;
                        glFlag_client=true;
                        ui->pushButton_connect->setText("Отключиться от сервера");

                        ui->textEdit_input->show();
                        ui->textEdit_output->show();
                        ui->lineEdit_send_message->show();
                        ui->pushButton_send_message->show();

                        ui->label_setTime->show();
                        ui->label_spamMessage->show();
                        ui->spinBox_spamTime->show();
                        ui->lineEdit_forSpamMessage->show();
                        ui->pushButton_spam->show();
                        ui->pushButton_stopSpam->show();

                        QString ser_mes=UserNickname + "<font color=green> подключился к серверу </font";
                        QByteArray ba_service6=ser_mes.toLocal8Bit();
                        TCPSocket->write(ba_service6);
                    }
                    else
                    {
                        QMessageBox::information(this,"","Не удалось подключиться к серверу");
                        TCPSocket=nullptr;
                        gl_flConnection=false;
                    }
                }
                else
                {
                    QMessageBox::information(this,"","Введите свой никнейм");
                    gl_flConnection=false;
                }
            }
            else
            {
                QMessageBox::information(this,"","IP-адрес введен неверно");
                gl_flConnection=false;
            }
        }
        else
        {
            QMessageBox::information(this,"","Значение порта должно быть в диапазоне от 1 дл 65535");
            gl_flConnection=false;
        }
    }
    else
    {//если клиент отключается от сервера
        QString ser_mes=UserNickname + "<font color=red> отключился от сервера </font";
        QByteArray ba_service7=ser_mes.toLocal8Bit();
        TCPSocket->write(ba_service7);
        TCPSocket->close();
        TCPSocket=nullptr;
        ui->pushButton_connect->setText("Подключиться к серверу");
        ui->textEdit_output->append("<font color=magenta> Вы отключились от сервера </font>");
        gl_flConnection=false;
    }
}

void MainWindow::on_pushButton_send_message_clicked() //отправка сообщений
{
    if (gl_flConnection)
    {
        if (glFlag_client) //если отправляем данные за клиента
        {
            if (TCPSocket!=nullptr)
            {
                QByteArray ba=UserNickname.toLocal8Bit() + ": " + ui->lineEdit_send_message->text().toLocal8Bit();
                TCPSocket->write(ba);
                ui->textEdit_output->append("Вы: " + ui->lineEdit_send_message->text());
                ui->lineEdit_send_message->clear();
            }
            else
            {
                QMessageBox::information(this,"","Соединение не установлено");
            }
        }

        if (glFlag_server) //если отправляем данные за сервер
        {
            if (!Sockets.isEmpty())
            {
                ui->textEdit_input->append("Сервер: " + ui->lineEdit_send_message->text());
                ui->textEdit_output->append("Вы: " + ui->lineEdit_send_message->text());
                for (int i=Sockets.size()-1;i>=0;i--)
                {
                    if (Sockets[i]!=nullptr)
                    {
                        QString server_name="Сервер: ";
                        QByteArray ba=server_name.toLocal8Bit() + ui->lineEdit_send_message->text().toLocal8Bit();
                        Sockets[i]->write(ba);
                    }
                }
                ui->lineEdit_send_message->clear();
            }
            else
            {
                QMessageBox::information(this,"","На сервере нет клиентов :(");
            }
        }
    }
    else
    {
        QMessageBox::information(this,"","Соединение не установлено");
    }
}


void MainWindow::on_pushButton_spam_clicked() //запускаем спам
{
    if (gl_flConnection==true)
    {
        if (glFlag_client)
        {
            if (TCPSocket!=nullptr)
            {
                timer->start();
                ui->pushButton_stopSpam->setEnabled(true);
                ui->spinBox_spamTime->setEnabled(false);
            }
            else
            {
                QMessageBox::information(this,"","Соединение не установлено");
            }
        }

        if (glFlag_server)
        {
            if (!Sockets.isEmpty())
            {
                timer->start();
                ui->pushButton_stopSpam->setEnabled(true);
                ui->spinBox_spamTime->setEnabled(false);
            }
            else
            {
                QMessageBox::information(this,"","На сервере нет клиентов :(");
            }
        }
    }
    else
    {
        QMessageBox::information(this,"","Соединение не установлено");
    }
}


void MainWindow::on_pushButton_stopSpam_clicked() //остановка спама
{
    timer->stop();
    counter=0;
    ui->pushButton_stopSpam->setEnabled(false);
    ui->spinBox_spamTime->setEnabled(true);
}


void MainWindow::on_lineEdit_nickname_textChanged(const QString &arg1) //изменение никнейма при редактировании его поля ввода
{
    UserNickname=arg1;
}
