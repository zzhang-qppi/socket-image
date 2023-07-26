#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <ws2tcpip.h>
#include <stdlib.h>

#pragma comment(lib,"ws2_32.lib")

char * read_ppm_file(char *path[], int x, int y){
    char *b;
    char buff[16];
    FILE *fp;
    int c, rgb_comp_color;
    //open PPM file for reading
    fp = fopen(path, "rb");
    if (!fp) {
        fprintf(stderr, "Unable to open file '%s'\n", *path);
        exit(1);
    }

    //read image format
    fgets(buff, sizeof(buff), fp);

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
        fprintf(stderr, "Invalid image format (must be 'P6')\n");
        exit(1);
    }

    //check for comments
    c = getc(fp);
    while (c == '#') {
        while (getc(fp) != '\n') ;
        c = getc(fp);
    }

    ungetc(c, fp);

    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
        fprintf(stderr, "Invalid rgb component (error loading '%s')\n", path);
        exit(1);
    }

    //check rgb component depth
    if (rgb_comp_color!= 255) {
        fprintf(stderr, "'%s' does not have 8-bits components\n", path);
        exit(1);
    }

    while (fgetc(fp) != '\n') ;
    //memory allocation for pixel data
    b = (char *)malloc(x * y * 3);

    if (!b) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    //read pixel data from file
    if (fread(b, 3 * x, y, fp) != y) {
        fprintf(stderr, "Error loading image '%s'\n", path);
        exit(1);
    }

    fclose(fp);
    return b;
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
    char * buffer = read_ppm_file((char **) path, 900000000);
    send(sockfd,buffer,strlen(buffer),0);
    recv(sockfd,buffer,255,0);
    printf("%s\n",buffer);
    return 0;
}