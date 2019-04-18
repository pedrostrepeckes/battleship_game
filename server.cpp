#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace std;

#define PORT 6335 //Server Port

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

#include "helper.cpp"

struct message msg;

struct client{

    int index;
    int sockID;
    struct sockaddr_in clientAddr;
    int len;

};

struct client Client[3];

int main(){
    int sock, s0, s1, s2, length;
    struct sockaddr_in server;
    int clientCount;
    //Client[0].sockID = s0 = s1 = s2 = 789;

    //Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        cout << "Error while creating socket" << endl;
        exit(1);
    }

    //Open connection and listen to client
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htons(INADDR_ANY);

    length = sizeof(server);

    // Binds the socket name to the address and port specified in addr
    bind(sock, (struct sockaddr *)&server, length);

    // The integer value in the listen corresponds to the maximum number of
    // pending connections in the queue.
    listen(sock,3);
    cout << "Server is listening..." << endl;
    
    // Accept the first pending connection on the queue
    Client[0].sockID = accept(sock, (struct sockaddr *)0,0);

    if (Client[0].sockID == -1)
    {
        handle_error("accept");
    }
    printf("con0\n");
    /*Client[1].sockID = accept(sock, (struct sockaddr *)0,0);

    if (Client[1].sockID == -1)
    {
        handle_error("accept");
    }
    printf("con1\n");
    Client[2].sockID = accept(sock, (struct sockaddr *)0,0);

    if (Client[2].sockID == -1)
    {
        handle_error("accept");
    }*/

    printf("con2\n");
    while(1){

        for(int i=0; i<1; i++){
            int msg_len = recv(Client[i].sockID, &msg, sizeof(message), 0); 
            //msg.board_pos[3] = '\0';
            cout << "Position = " << msg.board_pos << endl;
            cout << "Command = " << msg.board_pos[0] << endl;
            send(Client[i].sockID, &msg, sizeof(struct sockaddr *),0);
        }

    }
    //Close sockets
    for(int i; i<3; i++){
            close(Client[i].sockID);
        }
}