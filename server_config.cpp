
struct client{

    int index;
    int sockID;
    struct sockaddr_in clientAddr;
    int len;

};

#define PORT 6335 //Server Port

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

void warn_client_round(int player, struct client Client[]){
    struct message msg;
    msg.board_pos[0]='T';
    send(Client[player].sockID, &msg, sizeof(struct sockaddr *),0);
}

void warn_client_not_yr_round(int player, struct client Client[]){
    struct message msg;
    msg.board_pos[0]='N';
    send(Client[player].sockID, &msg, sizeof(struct sockaddr *),0);
}

void round_controller(int player, struct client Client[]){
    for(int i=0; i<3; i++){
        //cout << "Position = " << Client[i].sockID << endl;
        if (i != player){
            warn_client_not_yr_round(i, Client);
        }
    }
    warn_client_round(player, Client);
}

void game_is_over(struct client Client[]){
    for(int i=0; i<3; i++){
    	struct message msg;
	    msg.board_pos[0]='Z';
	    send(Client[i].sockID, &msg, sizeof(struct sockaddr *),0);
    }
}

void game_is_over_win(struct client Client[]){
    for(int i=0; i<3; i++){
    	struct message msg;
	    msg.board_pos[0]='W';
	    send(Client[i].sockID, &msg, sizeof(struct sockaddr *),0);
    }
}

void warn_others_about_hit(int player, struct client Client[], char row, char col){
    
    struct message msg;
    msg.board_pos[0]='U';
    msg.board_pos[1] = row;
    msg.board_pos[2] = col;
    for(int i=0; i<3; i++){
        if (i != player){
        	//cout<<"Row"<<msg.board_pos[1]<<endl;
        	//cout<<"Col"<<msg.board_pos[2]<<endl;
            send(Client[i].sockID, &msg, sizeof(struct sockaddr *),0);
        }
    }    
}