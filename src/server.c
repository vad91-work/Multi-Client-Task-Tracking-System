

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
        size_t addr_len = sizeof(cl_addr);
        int client_sock = accept(serv_sock, (struct sockaddr *)&cl_addr, &addr_len);
        if(client_sock<=0)
        {
            printf("accept - error.\n");
            continue;
        }

        

    }

    return EXIT_SUCCESS;
}
