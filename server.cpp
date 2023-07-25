#include <stdio.h>
#include <winsock2.h>
#include <string.h>

#pragma comment(lib,"ws2_32.lib")

int create_ppm_file(char *img[]){
    const int dimx = 100, dimy = 100;
    FILE *fp = fopen("image1.ppm", "wb");
    fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
    for (int j = 0; j < dimy; ++j){
        for (int i = 0; i < dimx; ++i){
            static unsigned char color[3];
            strncpy((char *)(color), (char *) img + j * 900 + i * 9, 3);  /* red */
            strncpy((char *)(color) + 1, (char *) img + j * 900 + i * 9 + 3, 3);;  /* green */
            strncpy((char *)(color) + 2, (char *) img + j * 900 + i * 9 + 6, 3);;  /* blue */
            fwrite(color, 1, 3, fp);
        }
    }
    fclose(fp);
    return 0;
}

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
    if(create_ppm_file((char *)(img)) == 0){printf("PPM file successfully created.");}
}