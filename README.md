# Qt-MultiUser-TCP-Chat
### **TCP multiuser chat application project**
A desktop application for chatting (and to spam too). The application can be used both as a server and as a client.

In this project I mastered:
* "Client-server" interaction
* Qt Classes for implementing server and client nodes over TCP protocol (QNetwork, QTcpServer, QTcpSocket)
* QTimer class for working with the timer

The implementation components are contained in the `MultiUserTCPChatApp` folder. The components for running the application are in the `config` folder.

To run the application locally you need to do the following:
* Clone branch `master` with `git clone https://github.com/RemeshevskiyValeriy/MultiUserTCP-Chat.git` or fork it and then clone it from your forked repository
* In the path `./config/debug` run the `TCP_ChatRV.exe`. To independently evaluate the capabilities of the application, run the executive file again
* In one of the windows select the server role and launch it. **The value of the port number according to the TCP protocol should be in the range from 1 to 65535 inclusive**. In another window select the client role and connect to the previously opened server. To connect you must specify the IP address and port of the server. When used on a local network, you can use the host IP address `127.0.0.1` or the IP address from the section displaying network parameters

