#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "generic_file_operations.h"
#include "hash_map.h"
#include "file_operation.h"

struct thread_input{
    int client_fd;
    HashMap* hash_map;
};
int socket_d;
HashMap* hash_map;
typedef struct thread_input THREAD_INPUT ;
void handle_sigint(int sig){
    printf("Server is shutting down ...");
    close(socket_d);
    exit(0);
}
void* client_handler(void* client_fd);
int main(){
    signal(SIGINT, handle_sigint);
    int new_client;

    if((socket_d = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sock_addr = {0};  // FIX

    sock_addr.sin_port = htons(9090);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(socket_d,(struct sockaddr*)&sock_addr,sizeof(sock_addr)) == -1){
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if(listen(socket_d, 1) < 0){   // FIX
        perror("listen");
        exit(EXIT_FAILURE);
    }

    hash_map = initialize_hashmap();
    while(1){
        if((new_client = accept(socket_d, NULL, NULL))<0){
            perror("accept");
            break;
        }
        THREAD_INPUT t_i = {new_client,hash_map};
        pthread_t pid;
        pthread_create(&pid, NULL, client_handler,(void*)&t_i);
    }
    
    return 0;
}
void* client_handler(void* t_i){
    THREAD_INPUT *thread_i= (THREAD_INPUT*)t_i;
    while(1){    
        char recv_message[255] = {0};  // FIX

        int bytes = recv(thread_i->client_fd, recv_message, sizeof(recv_message)-1, 0); // FIX

        if(bytes <= 0){
            break;
        }

        recv_message[bytes] = '\0'; // FIX
        hash_map_set(thread_i->hash_map, recv_message, recv_message);
        printf("Received from the client: %s\n", recv_message);
    }
    close(thread_i->client_fd);
    return NULL;
}
