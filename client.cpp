#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
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

#define IP "127.0.0.1" //Server IP
#define PORT 6335 //Server Port

struct message{
    char value[3];
};
struct message msg;

int board_len = 8;

char board_game[8][8];

#include "helper.cpp"


int main(){
    int s0; //Sockets
    bool my_turn;

    struct sockaddr_in server; //Struct for Internet addresses

    //Create Sockets - One to send and one to receive
    s0 = socket(AF_INET, SOCK_STREAM, 0);
    if(s0<0){
        cout << "Error while creating socket" << endl;
        exit(1);
    }


    print_first_board();

    //Connect to the Server
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);

    connect(s0, (struct sockaddr *)&server, sizeof(server));
    //connect(s1, (struct sockaddr *)&server, sizeof(server));
    while(1){
    	fflush(stdout);
        //Get message from terminal
        cout << "Enter a integer for the server:" << endl;
        cin >> msg.value;

        //Send message to Server
        send(s0, &msg, sizeof(struct message), 0);

        cout << "The entered value= " << msg.value << endl;

        //msg = void;

        //Receive response from server
        recv(s0, &msg, sizeof(struct message), 0);

        //Show message in terminal
        cout << "The entered value times 2 = " << msg.value << endl;

        recv(s0, &msg, sizeof(struct message), 0);
        //recv(s0, &msg, sizeof(struct message), 0);

        
        /*switch (msg.value[0]){

		   case "T":
		     //Instruções;
		   break;

		   case "U":
		     //Instruções;
		   break;

		   default
		   	printf("oi\n");
		     //Instruções;
		}
        //case msg.value[0]:

        if (my_turn == true)
        {
        	/* code */
        //}
    }

    //Close sockets
    close(s0);
    //close(s1);
}
