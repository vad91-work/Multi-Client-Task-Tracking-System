

#include "server.h"



int main(void)
{

    //create a new socket
    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    //check if socket was created
    if(serv_sock<=0){
        perror("sock()\n");
        return EXIT_FAILURE;
    }

    //fill address structure
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, LOCAL_HOST, &addr.sin_addr);

    //give socket address from address structure
    int rs = bind(serv_sock, (struct sockaddr *)&addr, sizeof(addr));
    //check bind error
    if(rs<0){
        perror("bind()");
        return EXIT_FAILURE;
    }

    //start listening
    rs = listen(serv_sock, MAX_CONN);
    if(rs<0){
        perror("listen()");
        return EXIT_FAILURE;
    }

    printf("\nServer is running on %s:%d\n", LOCAL_HOST, PORT);

    while(1)
    {
        struct sockaddr_in cl_addr;
        socklen_t addr_len = sizeof(cl_addr);
        int client_sock = accept(serv_sock, (struct sockaddr *)&cl_addr, &addr_len);
        if(client_sock<=0)
        {
            printf("accept - error.\n");
            continue;
        }

        

        int *client_sock_ptr = malloc(sizeof(int));
        *client_sock_ptr = client_sock;

        //create a thread id
        pthread_t tid;
        //start thread
        pthread_create(&tid, NULL, client_func, (void *)client_sock_ptr);

        //free thread without join
        pthread_detach(tid);
    }

    //close server socket
    close(serv_sock);
    return EXIT_SUCCESS;
}



void *client_func(void *arg)
{
    //save value to local var
    int client_sock = *(int *)arg;
    
    //free var client_sock_ptr
    free(arg);

    
    printf("Client connected.\n");

    //close client socket
    close(client_sock);
    // close thread
    pthread_exit(NULL);
    return NULL;
}
