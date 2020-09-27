// CLEINT
#include <stdio.h>
#include <iostream>
using namespace std;
#pragma comment(lib, "ws2_32.lib") // доступ к некоторым функциям
#include <winsock2.h>
#include <thread>
#pragma warning(disable: 4996)
#include <vector>
#include <conio.h>


SOCKET Connection;

void RecivieMessageFromServer()
{
    char msg1[256];

    while (true)
    {
        recv(Connection, msg1 , sizeof(msg1), NULL);
        cout << "answer from server: " << msg1 << endl;
    }
}

void esc() // выход по клавише esc
{

    char symb;
    int code_symb;

    symb = getch();
    code_symb = symb;

    if (code_symb == 27)
    {
        cout << "You have successfully disconnected" << endl;
        exit(1);
    }

}
   
int main()
{
    cout << "If you need to disconnect press ESC..." << endl;
    // загржуаем нужную версию  .. 
    // создадим структуру
    WSADATA wsaData;
    WORD Version = MAKEWORD(2, 1); // версия 2.1
    // проверяем как загрузилась библиотека
    if (WSAStartup(Version, &wsaData) != 0)
    {
        cout << "Error load of library\n" << endl;
        exit(1);
    }
    // соберем всю информацию для сокета
    char buffer[1000];


    SOCKADDR_IN addr;
    int size = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // local
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET; // семейство протоколов (TCP/UPD)

    Connection = socket(AF_INET, SOCK_STREAM, NULL);

    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
    {
        cout << "Connection to server return error\n" << endl;
    }
    else
    {
        cout << "Connection to server succed\n" << endl;
        //CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)RecivieMessageFromServer, NULL, NULL, NULL); // поток который принимает сообщения от сервера
        thread th(RecivieMessageFromServer);

        thread th1(esc);
        

        char msg[256];
        while (true)
        {
            std::cin.getline(msg, sizeof(msg));
            send(Connection, msg, sizeof(msg), NULL);
            Sleep(100);
        }
    }
    return 0;

       
      
   
}       