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
#include "helper.cpp"

struct message msg;

int main(){
    int s0; //Sockets
    char my_turn;
    int client_round;
    bool game_controller;
    struct sockaddr_in server; //Struct for Internet addresses
    int pos_row, pos_col;

    game_controller = true;
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
    while(game_controller){
    	fflush(stdout);
    	clear();
    	recv(s0, &msg, sizeof(struct message), 0);

    	if (decode_message(msg.board_pos[0])){
    		my_turn = msg.board_pos[0];
    		pos_row = msg.board_pos[1];
            pos_row = pos_row - 65;
            pos_col = msg.board_pos[2];
            pos_col = pos_col - 49;
    	}

    	recv(s0, &msg, sizeof(struct message), 0);
    	if (my_turn == 'T'){
    		print_updated_board();
	        //Get message from terminal
	        cout << "Enter the position to launch a missile:" << endl;
	        cout << "(A to H for rows)" << endl;
	        cout << "(1 to 8 for columns)" << endl;
	        cin >> msg.board_pos;

	        //Send message to Server
	        send(s0, &msg, sizeof(struct message), 0);

			pos_row = msg.board_pos[0];
            pos_row = pos_row - 65;
            pos_col = msg.board_pos[1];
            pos_col = pos_col - 49;

	        cout << "The entered value = " << msg.board_pos << endl;
	        //sleep(2);
	        //Receive response from server
	        recv(s0, &msg, sizeof(struct message), 0);

	        //recv(s0, &msg, sizeof(struct message), 0);
	        //recv(s0, &msg, sizeof(struct message), 0);

	        //cout<<"Volta = "<<msg.board_pos[0]<<endl;

	        decode_message(msg.board_pos[0]);

	        if(msg.board_pos[0] == 'R'){    		
	    		update_board(pos_row, pos_col, 'X');
	    	}

			recv(s0, &msg, sizeof(struct message), 0);
			//sleep(5);
    	}else if (my_turn == 'Z'){
    		game_controller = false;
    	}else if (my_turn == 'W'){
    		game_controller = false;
    	}else if(my_turn == 'U'){
    		cout<< "row "<< pos_row<<endl;
    		cout<< "col "<< pos_col<<endl;
    		update_board(pos_row, pos_col, 'X');
    		//sleep(3);
    	}

    }

    //Close sockets
    close(s0);
    //close(s1);
}
