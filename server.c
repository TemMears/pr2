#include "server.h"
//#include "Stack.h"
//#include "Queue.h"
//#include "hash.h"
//#include "set.h"
#include "struct.h"

DWORD WINAPI connectthread(LPVOID filedesc) {
    SOCKET fd = *(SOCKET*)filedesc;
    size_t nread;
    while (1) {
        char buf[256] = { '\0' };
        nread = recv(fd, buf, 256, 0);
        if (nread == SOCKET_ERROR) {
            printf("�O���y�q�{�p �����y�v�}�p �t�p�~�~����: %d\n", WSAGetLastError());
            break;
        }
        if (nread == 0) {
            printf("�K�|�y�u�~�� �����{�|�����y�|����\n");
            break;
        }
        printf("�K���}�p�~�t�p ���� �{�|�y�u�~���p %s\n", buf);
        HANDLE mutex;
        mutex = CreateMutex(NULL, FALSE, NULL);
        WaitForSingleObject(mutex, INFINITE); //�q�|���{�y�����u�� �r�������|�~�u�~�y�u ���u�{�����u�s�� ���������{�p �t�� ���u�� ������, �����{�p �}�������u�{�� �~�u �q���t�u�� �t�����������u�~. �^���� �s�p���p�~���y�����u��, ������ �����|���{�� ���t�y�~ ���������{ �q���t�u�� �y�}�u���� �t���������� �{ ���q���u�}�� ���u���������� ���t�~���r���u�}�u�~�~��
        char* answer = pr2(buf);
        ReleaseMutex(mutex); //�������q�� �����r���q���t�y���� �}�������u�{�� �y ���p�x���u���y���� �t�����s�y�} ���������{�p�} �����|�����y���� �t���������� �{ �~�u�}��
        if (send(fd, answer, strlen(answer), 0) == SOCKET_ERROR) {
            printf("�O���y�q�{�p ���������p�r�{�y �t�p�~�~���� %d\n", WSAGetLastError());
            break;
        }
    }
    closesocket(fd);
    return 0;
}

int main() {
    WSADATA wsaData;
    printf("�R�u���r�u�� �����x�t�p�~\n");

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("�O���y�q�{�p �y�~�y���y�p�|�y�x�p���y�y Winsock.\n");
        return 1;
    }
    //�����x�t�p�~�y�u �����{�u���p ���u���r�u���p
    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) {
        printf("�O���y�q�{�p �����x�t�p�~�y�� �����{�u���p %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //�����y�r���x�{�p �����{�u���p �{ �p�t���u����
    struct sockaddr_in adr = { 0 };
    adr.sin_family = AF_INET;
    adr.sin_port = htons(PORT);
    adr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server, (struct sockaddr*)&adr, sizeof adr) == SOCKET_ERROR) {
        printf("�O���y�q�{�p �����y�r���x�{�y �����{�u���p �{ �p�t���u����: %d\n", WSAGetLastError());
        closesocket(server);
        WSACleanup();
        return 1;
    }
    //���������|�����y�r�p�~�y�u ���������p
    if (listen(server, 5) == SOCKET_ERROR) { //�}���w�u�� �����y�~������ ���t�~���r���u�}�u�~�~�� �t�� 5 �����t�{�|�����u�~�y�z
        printf("�O���y�q�{�p �����y �����������{�u ���������|�����y�r�p�~�y�� ���������p %d\n", WSAGetLastError());
        closesocket(server);
        WSACleanup();
        return 1;
    }

    struct sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    SOCKET fd = 0;
    HANDLE mutex; //�y�������|���x���u�} �}�������u�{�� �t�|�� �t�|�� ���y�~�������~�y�x�p���y�y �t�����������p �{ ���q���u�}�� ���u����������
    mutex = CreateMutex(NULL, FALSE, NULL);

    if (mutex == NULL) {
        printf("�O���y�q�{�p �����x�t�p�~�y�� �}�������u�{���p %d\n", GetLastError());
        closesocket(server);
        WSACleanup();
        return 1;
    }

    while ((fd = accept(server, (struct sockaddr*)&clientAddr, &clientAddrSize)) != INVALID_SOCKET) { //���u���r�u�� ���w�y�t�p�u�� �~���r���� �����t�{�|�����u�~�y�z ���� �{�|�y�u�~�����r
        //�P���y �{�p�w�t���} �����t�{�|�����u�~�y�y �����x�t�p�u������ �~���r���z ���������{
        HANDLE thread = CreateThread(NULL, 0, connectthread, (LPVOID)&fd, 0, NULL);
        if (thread == NULL) {
            printf("�O���y�q�{�p �����x�t�p�~�y�� ���������{�p.\n");
            closesocket(fd);
            closesocket(server);
            WSACleanup();
            return 1;
        }
    }
    closesocket(fd); //�x�p�{�����r�p�u������ �t�u���{���y�������� �{�|�y�u�~���p 
    closesocket(server); // �x�p�{�����r�p�u������ �����{�u�� ���u���r�u���p 
    CloseHandle(mutex);
    WSACleanup();
    return 0;
}
