#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int socket_d;

    if((socket_d = socket(AF_INET,SOCK_STREAM,0)) < 0){  // FIX
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sock_addr = {0}; // FIX

    sock_addr.sin_port = htons(9090);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // FIX

    int connection = connect(socket_d, (struct sockaddr*)&sock_addr, sizeof(sock_addr));
    if(connection==-1){
        perror("connect"); // FIX
    }
    else{
        while(1){
            char user_input[255];

            printf("Write the message: "); // FIX
            scanf("%s", user_input);

            if(strcmp(user_input, "exit") == 0){ // FIX
                break;
            }

            send(socket_d, user_input, strlen(user_input)+1, 0); // FIX
        }
    }

    close(socket_d); // FIX
    return 0;
}
