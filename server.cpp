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
#include "helper.cpp"
#include "server_config.cpp"


struct client Client[3];
struct message msg;



int main(){
    int sock, s0, s1, s2, length;
    struct sockaddr_in server;
    int client_rounds[3];
    char command;
    bool game_control;
    game_control = true;
    client_rounds[0] = client_rounds[1] = client_rounds[2] = 0;

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
    Client[1].sockID = accept(sock, (struct sockaddr *)0,0);

    if (Client[1].sockID == -1)
    {
        handle_error("accept");
    }
    printf("con1\n");
    Client[2].sockID = accept(sock, (struct sockaddr *)0,0);

    if (Client[2].sockID == -1)
    {
        handle_error("accept");
    }
    printf("con2\n");

    set_the_ships();
    cout<<"Starting Round "<<client_rounds[0]+1<<endl;
    while(game_control == true){

        for(int i=0; i<3; i++){
            round_controller(i, Client);
            int msg_len = recv(Client[i].sockID, &msg, sizeof(message), 0);
            int pos_row, pos_col;
            
            cout << "Position = " << msg.board_pos << endl;
            command = 'S';
            cout << "Command = "<< command << endl;
            pos_row = msg.board_pos[0];
            //since vector has position 0, it necessary to also start
            pos_row = pos_row - 65;
            cout << "Row received "<< pos_row << endl;
            pos_col = msg.board_pos[1];
            //since vector has position 0, it necessary to also start
            pos_col = pos_col - 49;
            cout << "Row received "<< pos_col << endl;
            cout << "-----------------"<< pos_col << endl;

            if (is_a_hit(pos_row, pos_col) == true)
            {
                //printf("Acertou miseravi\n");
                warn_others_about_hit(i, Client, msg.board_pos[0], msg.board_pos[1]);
                msg.board_pos[0] = 'R';   
            }else{
                //printf("Errou otario\n");
                msg.board_pos[0] = 'M';
            }
            send(Client[i].sockID, &msg, sizeof(struct sockaddr *),0);
            if(is_end_of_game()){
                game_is_over_win(Client);
                game_control = false;
            }
            client_rounds[i]++;
        }
        print_server_board();
        if (client_rounds[2] == 10)
        {
            cout<<"game is over...the machine won"<<endl;
            game_is_over(Client);
            game_control = false;
        }else{
            cout<<"Starting Round "<<client_rounds[0]+1<<endl;
        }

    }
    //Close sockets
    for(int i; i<3; i++){
            close(Client[i].sockID);
        }
}