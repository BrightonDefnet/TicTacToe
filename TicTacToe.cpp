//j = columns, i = rows

#include <iostream>
using namespace std;


//reset the board
void setBoard(char array[4][4], bool moveArray[4][4]){
    for(int i = 1; i < 4; i++){
        for(int j = 1; j < 4; j++){
            array[j][i] = '-';
            moveArray[j][i] = false;
        }
    }
    //y labels
    array[0][0] = ' ';
    array[1][0] = '1';
    array[2][0] = '2';
    array[3][0] = '3';
    //x labels
    array[0][1] = '1';
    array[0][2] = '2';
    array[0][3] = '3';
}


//print the contents of the board
void printBoard(char array[4][4]){
    cout << ' ' << endl;
    cout << "Board:" << endl;
    for(int i = 0; i < 4; i++){
        cout << array[0][i] << array[1][i] << array[2][i] << array[3][i] << endl;
    }
}


//change a space on the board
void changeSpace(int x, int y, char array[4][4], char mark){
    array[x][y] = mark;
}


//asks if the player wants to play again
bool playAgain(char array[4][4], bool moveArray[4][4]){
    char yn;
    cout << ' ' << endl;
    cout << "play again? y/n" << endl;
    cin >> yn;
    if(yn == 'n'){
        return false;
    } else {
        setBoard(array, moveArray);
        printBoard(array);
        return true;
    }
}


//play a turn
bool playTurn(char array[4][4], bool turn, bool moveArray[4][4]){
    int xCoordinate;
    int yCoordinate;
    char mark;
    bool legal;

    //tell who's turn it is and ask for a move
    if(turn == true){
        cout << "X's turn!" << endl;
    } else {
        cout << "O's turn!" << endl;
    }
    cout << "input X coordinate:" << endl;
    cin >> xCoordinate;
    cout << "input Y coortinate:" << endl;
    cin >> yCoordinate;

    //check if the move is legal and input a move
    if(moveArray[xCoordinate][yCoordinate] == true){
        cout << "illegal move, try again" << endl;
        return false;
    } else if(turn == true){
        mark = 'X';
        changeSpace(xCoordinate, yCoordinate, array, mark);
        printBoard(array);
        moveArray[xCoordinate][yCoordinate] = true;
        return true;
    } else {
        mark = 'O';
        changeSpace(xCoordinate, yCoordinate, array, mark);
        printBoard(array);
        moveArray[xCoordinate][yCoordinate] = true;
        return true;
    }
}


//check for a win
bool checkWin(char array[4][4], bool turn){

    //determine what mark to check for
    char mark;
    if(turn == true){
        mark = 'X';
    } else {
        mark = 'O';
    }

    //check for three in a row
    if(array[1][1] == mark && array[2][1] == mark && array[3][1] == mark){ //top
        return true;
    } else if(array[1][2] == mark && array[2][2] == mark && array[3][2] == mark){ //mid
        return true;
    } else if(array[1][3] == mark && array[2][3] == mark && array[3][3] == mark){ //bottom
        return true;
    } else if(array[1][1] == mark && array[1][2] == mark && array[1][3] == mark){ //1
        return true;
    } else if(array[2][1] == mark && array[2][2] == mark && array[2][3] == mark){ //2
        return true;
    } else if(array[3][1] == mark && array[3][2] == mark && array[3][3] == mark){ //3
        return true;
    } else if(array[1][1] == mark && array[2][2] == mark && array[3][3] == mark){ //diagonal negative
        return true;
    } else if(array[3][1] == mark && array[2][2] == mark && array[1][3] == mark){ //diagonal positive
        return true;
    } else {
        return false;
    }
}


bool flipTurn(bool turn){
    if(turn == true){
        return false;
    } else {
        return true;
    }
}


//announce a win and ask if they want to play again
void announceWin(bool turn, int xWins, int oWins){
    char mark;
    if(turn == true){
        mark = 'X';
    } else {
        mark = 'O';
    }
    cout << mark << " wins!" << endl;
    cout << "X wins: " << xWins << endl;
    cout << "O Wins: " << oWins << endl;
}


//main program
int main(){

    //initialization
    char board[4][4];
    bool moveArray[4][4];
    bool playing = true;
    bool turn = true;
    bool win = false;
    bool legal;
    int moves = 0;
    int xWins = 0;
    int oWins = 0;

    //set up the board
    setBoard(board, moveArray);
    printBoard(board);

    //play the game
    while(playing == true){
        legal = playTurn(board, turn, moveArray);
        if(legal == true){
            win = checkWin(board, turn);
            if(legal == true) moves++;
            if(win == true){
                if(turn == false){
                    xWins++;
                } else {
                    oWins++;
                }
                announceWin(turn, oWins, xWins);
                playing = playAgain(board, moveArray);
            } else if (moves == 9){
                cout << "tie, nobody wins" << endl;
                playing = playAgain(board, moveArray);
            }
            if(win == true){
                turn = true;
                moves = 0;
            } else {
                turn = flipTurn(turn);
            }
        }
    }
}