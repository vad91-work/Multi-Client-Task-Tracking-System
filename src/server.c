

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

    //get length of operation
    uint32_t protocol_len;
    recv(client_sock, &protocol_len, sizeof(protocol_len), 0);

    //get name of operation
    char protocol[protocol_len+1];
    recv(client_sock, protocol, protocol_len, 0);
    protocol[protocol_len] = '\0';

    
    if(strcmp(protocol, "REGISTER") == 0){ //1 REGISTER <username> <password>
        register_user(client_sock);
    } else if (strcmp(protocol, "LOGIN") == 0){ //2 LOGIN <usename> <password>

    } else if (strcmp(protocol, "GET_TASK") == 0){ //3 GET_TASKS <user_token>

    } else if (strcmp(protocol, "CREATE") == 0){ //4 CREATE <user_token> <task_name> <description>
        
    } else if (strcmp(protocol, "UPDATE") == 0){ //5 UPDATE <user_token> <task_id> <status>
        
    } else if (strcmp(protocol, "DELETE") == 0){ //6 DELETE <user_token> <task_id>
        
    } else { //send error
        
    }

    //close client socket
    close(client_sock);
    // close thread
    pthread_exit(NULL);
    return NULL;
}

//function register new user
int register_user(int client_sock)
{
    int len;
    ssize_t bytes_recv = recv(client_sock, &len, sizeof(len), 0);
    if(bytes_recv<=0)
    {
        return -1;
    }

    //get username
    char username[len+1];
    bytes_recv = recv(client_sock, username, len, 0);
    if(bytes_recv<=0)
    {
        return -1;
    }

    username[len] = '\0';

    
    //get password len
    bytes_recv = recv(client_sock, &len, sizeof(len), 0);
    if(bytes_recv<=0)
    {
        return -1;
    }

    //get password
    char password[len + 1];
    bytes_recv = recv(client_sock, password, len, 0);

    if(bytes_recv<=0)
    {
        return -1;
    }

    password[len] = '\0';


    return 0;
}


