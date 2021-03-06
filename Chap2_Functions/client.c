#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char *argv[]){
    /*Check if right input*/
    if(argc != 2){
        printf("Wrong input!\n");
        return -1;
    }

    int clientSocket;
    int server_port;
    struct sockaddr_in server_address;
    int returnStatus;
    char buffer[256] = "";

    /*Set up client socket*/
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == -1){
        printf("Unsuccessfull creating client socket!\n");
        return -1;
    }

    /*Clear temp data then set up server_address
    **Why we use bzero() instead using memset() ?*/
    bzero(&server_address, sizeof(server_address));
    server_port = atoi(argv[1]);
  
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(server_port);

    returnStatus = connect(clientSocket, (struct sockaddr *)&server_address, sizeof(server_address));

    if (returnStatus == 0){
        printf("Connect successfully!\n");
        
    }
    else{
        printf("Can not connect to server socket!\n");
        close(clientSocket);
        return-1;
    }
    
    /*Get message from the server*/
    returnStatus = read(clientSocket, &buffer, sizeof(buffer));
    if (returnStatus > 0){
        printf("Received: %s\n", returnStatus, buffer);
    }
    else{
        printf("Read unsuccessfully! Return %d\n", returnStatus);
    }

    return 0;
}