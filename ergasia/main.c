#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
char square[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
int checkwin();
void board();
char menu()
{
    char k;
    printf("Tic Tac Toe\n");
    while(1)
    {
        printf("1.Play againt computer\n2.Two players game\n3.See the statistics of a player\n4.Exit\nYour choice:");
        scanf("%c",&k);
        if(k=='1' || k=='2' || k=='3' || k=='4')
        {
            return k;
        }
        else
        {
            fflush(stdin);
            printf("Your choice must be between 1 and 4\n");
            continue;
        }

    }
}
void board()
{
    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);
    printf("     |     |     \n\n");
}
int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
        square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7]
        != '7' && square[8] != '8' && square[9] != '9')
        return 0;
    else
        return  - 1;
}
char gridChar(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}

void draw(int b[9]) {
    printf(" %c | %c | %c\n",gridChar(b[0]),gridChar(b[1]),gridChar(b[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",gridChar(b[3]),gridChar(b[4]),gridChar(b[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",gridChar(b[6]),gridChar(b[7]),gridChar(b[8]));
}

int win(const int board[9]) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}

int minimax(int board[9], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board[i] == 0) {//If legal,
            board[i] = player;//Try the move
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}

void computerMove(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    board[move] = 1;
}

void playerMove(int board[9]) {
    int move = 0;
    do {
        printf("\nInput move ([0..8]): ");
        scanf("%d", &move);
        printf("\n");
    } while (move >= 9 || move < 0 || board[move] != 0);
    board[move] = -1;
}

int main()
{
    char k;
    int player=0;
    k=menu();
    if(k=='2')
    {
        int player1 = 1, i, choice;
        char mark;
        do
        {
            board();
            player1 = (player1 % 2) ? 1 : 2;
            printf("Player %d, enter a number:  ", player1);
            scanf("%d", &choice);
            mark = (player1 == 1) ? 'X' : 'O';
            if (choice == 1 && square[1] == '1')
                square[1] = mark;
            else if (choice == 2 && square[2] == '2')
                square[2] = mark;
            else if (choice == 3 && square[3] == '3')
                square[3] = mark;
            else if (choice == 4 && square[4] == '4')
                square[4] = mark;
            else if (choice == 5 && square[5] == '5')
                square[5] = mark;
            else if (choice == 6 && square[6] == '6')
                square[6] = mark;
            else if (choice == 7 && square[7] == '7')
                square[7] = mark;
            else if (choice == 8 && square[8] == '8')
                square[8] = mark;
            else if (choice == 9 && square[9] == '9')
                square[9] = mark;
            else
            {
                printf("Invalid move\n");
                player1--;
            }
            i = checkwin();
            player1++;
        }while (i ==  - 1);
        board();
        if (i == 1)
            printf("==>\aPlayer %d wins", --player1);
        else
            printf("==>\aGame draw");
        getch();
    }
    if(k=='1')
    {
        int board[9] = {0,0,0,0,0,0,0,0,0};
        //computer squares are 1, player squares are -1.
        printf("Computer: O, You: X\nPlay (1)st or (2)nd? ");
        scanf("%d",&player);
        printf("\n");
        unsigned turn;
        for(turn = 0; turn < 9 && win(board) == 0; ++turn) {
            if((turn+player) % 2 == 0)
                computerMove(board);
            else {
                draw(board);
                playerMove(board);
                }
        }
        switch(win(board)) {
            case 0:
                printf("A draw. How droll.\n");
                break;
            case 1:
                draw(board);
                printf("You lose.\n");
                break;
            case -1:
                printf("You win. Inconceivable!\n");
                break;

            }

    }
    if(k=='4')
        exit(0);
}
