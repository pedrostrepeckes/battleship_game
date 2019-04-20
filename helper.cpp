
#define board_len 8
#define clear() printf("\033[H\033[J")


struct message{
    char board_pos[4];
};

int number_of_right_missiles = 0;
int number_of_ships_parts = 0;

//int board_len = 8;

char board_game_client[board_len][board_len];
char board_game_server[board_len][board_len];

void print_first_board (){

	for (int i=0; i<board_len; i++){
    	for(int j=0; j<board_len; j++){
    		board_game_client[i][j] = 'A';
    	}
    }

    for (int i=0; i<board_len; i++){
    	for(int j=0; j<board_len; j++){
    		printf("%c", board_game_client[i][j]);
    	}
    	printf("\n");
    }
}

void update_board(int i, int j, char situation){

    board_game_client[i][j] = situation;
}

void print_updated_board(){

    for (int i=0; i<board_len; i++){
        for(int j=0; j<board_len; j++){
            printf("%c", board_game_client[i][j]);
        }
        printf("\n");
    }
}

void print_server_board(){
    for (int i=0; i<board_len; i++){
        for(int j=0; j<board_len; j++){
            printf("%c", board_game_server[i][j]);
        }
        printf("\n");
    }
}

void set_vert_battleship(int i, int j){
    //length 4
    board_game_server[i][j] = 'S';
    board_game_server[i+1][j] = 'S';
    board_game_server[i+2][j] = 'S';
    board_game_server[i+3][j] = 'S';
    number_of_ships_parts = number_of_ships_parts + 4;
}

void set_horiz_battleship(int i, int j){
    //length 4
    board_game_server[i][j] = 'S';
    board_game_server[i][j+1] = 'S';
    board_game_server[i][j+2] = 'S';
    board_game_server[i][j+3] = 'S';
    number_of_ships_parts = number_of_ships_parts + 4;
}

void set_the_ships(){

    for (int i=0; i<board_len; i++){
        for(int j=0; j<board_len; j++){
            board_game_server[i][j] = 'A';
        }
    }

    //set_aircraft_carrier();
    set_vert_battleship(1,1);
    set_horiz_battleship(3,3);
    //set_sub();
    //set_frigate();

    for (int i=0; i<board_len; i++){
        for(int j=0; j<board_len; j++){
            printf("%c", board_game_server[i][j]);
        }
        printf("\n");
    }
}

bool is_a_hit(int row, int column){
    //Reminder...the columns and rows starts in 0
    //row = A -> row 0
    //col = 1 --> vector position 0
    if (board_game_server[row][column] == 'S')
    {
        board_game_server[row][column] = 'X';
        number_of_right_missiles++;
        return true;
    }
    return false;
}

bool decode_message(char command){

    switch (command){

           case 'R':
             cout << "Acertouuuu" <<endl;
             return true;
           break;

           case 'M':
             cout << "Errouuu" <<endl;
             return true;
           break;

           case 'T':
             cout << "Your turn" <<endl;
             return true;
           break;

           case 'N':
             cout << "Not your turn" <<endl;
             return true;
           break;

           case 'Z':
             cout << "Game is over" <<endl;
             cout << "You lost" <<endl;
             return true;
           break;

           case 'W':
             cout << "Game is over" <<endl;
             cout << "You Win" <<endl;
             return true;
           break;

           case 'U':
            cout << "update" <<endl;
            return true;
           break;

           default:
            printf("Unknown command\n");
            return false;
             //Instruções;
        }
}

bool is_end_of_game(){
    if (number_of_ships_parts == number_of_right_missiles){
        return true;
    }
    return false;
}