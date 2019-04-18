struct message{
    char board_pos[4];
    char command[3];
};


int board_len = 8;

char board_game[8][8];

void print_first_board (){

	for (int i=0; i<board_len; i++){
    	for(int j=0; j<board_len; j++){
    		board_game[i][j] = 'A';
    	}
    }

    for (int i=0; i<board_len; i++){
    	for(int j=0; j<board_len; j++){
    		printf("%c", board_game[i][j]);
    	}
    	printf("\n");
    }
}

void update_board(int i, int j, char situation){

    board_game[i][j] = situation;
}

void print_updated_board(){

    for (int i=0; i<board_len; i++){
        for(int j=0; j<board_len; j++){
            printf("%c", board_game[i][j]);
        }
        printf("\n");
    }
}
