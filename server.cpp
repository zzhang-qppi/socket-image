#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

int main(int argc, char *argv[]){
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2),&wsa);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int portno = atoi(argv[1]);
    struct sockaddr_in sv_add;
    sv_add.sin_family = AF_INET;
    sv_add.sin_addr.s_addr = INADDR_ANY;
    sv_add.sin_port = htons(portno);
    bind(sockfd, (struct sockaddr *) &sv_add, sizeof(sv_add));
    listen(sockfd, 5);
    struct sockaddr_in cl_addr;
    int newsockfd = connect(sockfd, (struct sockaddr *) &cl_addr, sizeof(cl_addr));
    char img[900000000];
    recv(newsockfd, img, 900000000, 0);
    printf("%s", img);
}

int rgb_unpack(char *img[]){

}