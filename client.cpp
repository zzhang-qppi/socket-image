#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

char * read_ppm_file(char *path[]){
    char * b[900000000];
    return (char *) b;
}

int main(int argc, char *argv[]){
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2),&wsa);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int portno = atoi(argv[2]);

    struct sockaddr_in sv_addr;

    sv_addr.sin_family = AF_INET;
    sv_addr.sin_port = htons(portno);

    inet_pton(AF_INET, "127.0.0.1", &sv_addr.sin_addr);
    sv_addr.sin_port = htons(portno);
    connect(sockfd, (struct sockaddr *)&sv_addr, sizeof(sv_addr)) < 0;

    char path[256];
    scanf("%s", &path);
    char * buffer = read_ppm_file((char **) path);
    send(sockfd,buffer,strlen(buffer),0);
    recv(sockfd,buffer,255,0);
    printf("%s\n",buffer);
    return 0;
}