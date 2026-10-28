#include <iostream>
#include <algorithm>
using namespace std;

char board[3][3]={
    {' ',' ',' '},
    {' ',' ',' '},
    {' ',' ',' '}
};

void printBoard()
{
    cout<<"\n";
    cout<<" "<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<endl;
    cout<<"---+---+---\n";
    cout<<" "<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<endl;
    cout<<"---+---+---\n";
    cout<<" "<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<endl;
    cout<<"\n";
}

bool checkWin(char player)
{
    for(int i=0;i<3;i++)
    {
        if((board[i][0]==player && board[i][1]==player && board[i][2]==player) ||
           (board[0][i]==player && board[1][i]==player && board[2][i]==player))
            return true;
    }

    if((board[0][0]==player && board[1][1]==player && board[2][2]==player) ||
       (board[0][2]==player && board[1][1]==player && board[2][0]==player))
        return true;

    return false;
}

bool isfull()
{
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]==' ')
                return false;

    return true;
}

int minimax(bool isMaximizing)
{
    if(checkWin('O'))
        return 10;

    if(checkWin('X'))
        return -10;

    if(isfull())
        return 0;

    if(isMaximizing)
    {
        int bestScore=-1000;

        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(board[i][j]==' ')
                {
                    board[i][j]='O';
                    int score=minimax(false);
                    board[i][j]=' ';
                    bestScore=max(score,bestScore);
                }
            }
        }

        return bestScore;
    }
    else
    {
        int bestScore=1000;

        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(board[i][j]==' ')
                {
                    board[i][j]='X';
                    int score=minimax(true);
                    board[i][j]=' ';
                    bestScore=min(score,bestScore);
                }
            }
        }

        return bestScore;
    }
}

void bestmove()
{
    int bestScore=-1000;
    int moveRow=-1,moveCol=-1;

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==' ')
            {
                board[i][j]='O';
                int score=minimax(false);
                board[i][j]=' ';

                if(score>bestScore)
                {
                    bestScore=score;
                    moveRow=i;
                    moveCol=j;
                }
            }
        }
    }

    if(moveRow!=-1 && moveCol!=-1)
        board[moveRow][moveCol]='O';
}

int main()
{
    cout<<"Tic Tac Toe Game\n";
    cout<<"You are X, AI is O\n";
    printBoard();

    while(true)
    {
        int row,col;
        cout<<"Enter your move (row and column: 0-2): ";
        cin>>row>>col;

        if(row<0 || row>2 || col<0 || col>2 || board[row][col]!=' ')
        {
            cout<<"Invalid move. Try again.\n";
            continue;
        }

        board[row][col]='X';
        printBoard();

        if(checkWin('X'))
        {
            cout<<"You win!\n";
            break;
        }

        if(isfull())
        {
            cout<<"It's a draw!\n";
            break;
        }

        bestmove();
        printBoard();

        if(checkWin('O'))
        {
            cout<<"AI wins!\n";
            break;
        }

        if(isfull())
        {
            cout<<"It's a draw!\n";
            break;
        }
    }

    return 0;
}

// g++ file.cpp -o file
// .\file