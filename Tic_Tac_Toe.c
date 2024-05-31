#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include<conio.h>
#include<time.h>
#include<math.h>

void draw(int* grid,int mode,int player);
char changeToXO(int num);
int chooseMode(void);
int chooseFirst(void);
int* getUserInput(int* grid, int mode, int player, int currPlayer);
int checkValidPosition(int* grid, int pos);
int checkWin(int* grid, int player);
int checkMovesLeft(int* grid);
int findBestMove(int* grid, int player);
int minimax(int* grid, int depth, int isMax, int player);
int min(int a, int b);
int max(int a, int b);

int main()
{
    srand(time(NULL));
    system("color F0");
    printf("TIC TAC TOE!\n");

    int playerXO = 0;
    int gameMode = 0;
    int currentPlayer = 0; //0 is player 1 and 1 is player 2 or computer based on mode

    gameMode = chooseMode();
    playerXO = chooseXO();

    if(gameMode == 1)
    {
        currentPlayer = chooseFirst();
    }

    int* mainGrid = malloc(10*sizeof(int));

    for(int i = 0; i<10; i++)
    {
        mainGrid[i] = 2;
    }

    while(1)
    {
        draw(mainGrid,gameMode,playerXO);
        int* temp = NULL;

        if(currentPlayer == 0 || gameMode == 0)
        {
            while (1)
            {
                temp = getUserInput(mainGrid,gameMode,playerXO,currentPlayer);
                if(temp != NULL)
                {
                    mainGrid = temp;
                    break;
                }
            }
        }
        else
        {
            int best  = findBestMove(mainGrid,playerXO);
            mainGrid[best] = !playerXO;
        }

        int win = checkWin(mainGrid,playerXO);

        if(win < 0)
        {
            system("color A0");
            draw(mainGrid,gameMode,playerXO);
            printf("\nPLAYER 1 WINS!! \n");
            break;
        }

        if(win > 0)
        {
            system("color C0");
            draw(mainGrid,gameMode,playerXO);
            if(gameMode == 1)
            {
                printf("\nCOMPUTER WINS!! \n");
                break;
            }
            printf("\nPLAYER 2 WIN!! \n");
            break;
        }


        if (checkMovesLeft(mainGrid) == 0)
        {
            system("color B0");
            draw(mainGrid,gameMode,playerXO);
            printf("\nTIE!!");
            break;
        }

        currentPlayer++;

        if(currentPlayer == 2)
        {
            currentPlayer = 0;
        }
    }
    return 0;
}

char changeToXO (int num)
{
    if (num == 1)
    {
        return 'X';
    }
    else if (num == 0)
    {
        return 'O';
    }
    else
    {
        return '-';
    }
}

void draw(int* grid,int mode,int player)
{
    system("cls");
    if (mode == 1)
    {
        printf("      PLAYER 1 '%c' VS COMPUTER '%c' \n\n",changeToXO(player),changeToXO(!player));
    }
    else
    {
        printf("      PLAYER 1 '%c' VS PLAYER 2 '%c' \n\n",changeToXO(player),changeToXO(!player));
    }
    printf("\t      ||       ||      \n");
    printf("\t      ||       ||      \n");
    printf("\t%c     ||   %c   ||     %c\n",changeToXO(grid[0]),changeToXO(grid[1]),changeToXO(grid[2]));
    printf("\t      ||       ||      \n");
    printf("\t1     ||   2   ||     3\n");
    printf("    =============================== \n");
    printf("\t      ||       ||      \n");
    printf("\t      ||       ||      \n");
    printf("\t%c     ||   %c   ||     %c\n",changeToXO(grid[3]),changeToXO(grid[4]),changeToXO(grid[5]));
    printf("\t      ||       ||      \n");
    printf("\t4     ||   5   ||     6\n");
    printf("    =============================== \n");
    printf("\t      ||       ||      \n");
    printf("\t      ||       ||      \n");
    printf("\t%c     ||   %c   ||     %c\n",changeToXO(grid[6]),changeToXO(grid[7]),changeToXO(grid[8]));
    printf("\t      ||       ||      \n");
    printf("\t7     ||   8   ||     9\n");
}

int chooseMode(void)
{
    int playerChoice = 0;
    printf("\n\nPRESS 1 FOR PLAYER VS COMPUTER OR PRESS 0 FOR PLAYER 1 VS PLAYER 2 ");
    scanf("%d",&playerChoice);
    if (playerChoice != 0 && playerChoice != 1)
    {
        printf("\n\nINVALID ENTRY, CHOOSING PLAYER 1 VS PLAYER 2 BY DEFAULT!");
        return 0;
    }
    else
    {
        return playerChoice;
    }
}

int chooseXO(void)
{
    int playerChoice = 0;
    printf("\n\nPLAYER 1, PRESS 1 TO CHOOSE X OR PRESS 0 TO CHOOSE O ");
    scanf("%d",&playerChoice);
    if (playerChoice != 0 && playerChoice != 1)
    {
        printf("\n\nINVALID ENTRY, CHOOSING O BY DEFAULT!!");
        return 0;
    }
    else
    {
        return playerChoice;
    }
}

int chooseFirst(void)
{
    int playerChoice = 0;
    printf("\n\nPLAYER 1, PRESS 0 TO PLAY FIRST OR PRESS 1 TO LET COMPUTER PLAY FIRST ");
    scanf("%d",&playerChoice);
    if (playerChoice != 0 && playerChoice != 1)
    {
        printf("\n\nINVALID ENTRY, CHOOSING PLAYER 1 TO PLAY FIRST BY DEFAULT!!");
        return 0;
    }
    else
    {
        return playerChoice;
    }
}

int* getUserInput(int* grid, int mode, int player, int currPlayer)
{
    int position = 0;
    if (currPlayer == 0)
    {
        printf("\n\nPLAYER 1 '%c' ",changeToXO(player));
    }
    else
    {
        printf("\n\nPLAYER 2 '%c' ",changeToXO(!player));
    }
    printf("ENTER POSITION BETWEEN 1 TO 9 ");
    scanf("%d",&position);
    position = position - 1;
    if (((checkValidPosition(grid,position))==1) && (position >= 0 && position < 9))
    {
        int XO = 0;
        if(currPlayer == 0)
        {
            XO = player;
        }
        else
        {
            XO = !player;
        }
        grid[position] = XO;
        return grid;

    }
    else
    {
        char clrbuf[100];
        gets(clrbuf);
        printf("\n\nINVALID POSITION, ENTER AGAIN! ");
        return 0;
    }
}

int checkValidPosition(int* grid, int pos)
{
    if(pos >= 0 && pos < 9)
    {
        if(grid[pos] == 2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int checkWin(int* grid, int player)
{
    if(
        (grid[0] == 0 && grid[1] == 0 && grid[2] == 0) ||
        (grid[3] == 0 && grid[4] == 0 && grid[5] == 0) ||
        (grid[6] == 0 && grid[7] == 0 && grid[8] == 0) ||
        (grid[0] == 0 && grid[3] == 0 && grid[6] == 0) ||
        (grid[1] == 0 && grid[4] == 0 && grid[7] == 0) ||
        (grid[2] == 0 && grid[5] == 0 && grid[8] == 0) ||
        (grid[0] == 0 && grid[4] == 0 && grid[8] == 0) ||
        (grid[2] == 0 && grid[4] == 0 && grid[6] == 0))
    {
        if(player == 0)
        {
            return -10;
        }
        else
        {
            return 10;
        }
    }
    else if(
        (grid[0] == 1 && grid[1] == 1 && grid[2] == 1) ||
        (grid[3] == 1 && grid[4] == 1 && grid[5] == 1) ||
        (grid[6] == 1 && grid[7] == 1 && grid[8] == 1) ||
        (grid[0] == 1 && grid[3] == 1 && grid[6] == 1) ||
        (grid[1] == 1 && grid[4] == 1 && grid[7] == 1) ||
        (grid[2] == 1 && grid[5] == 1 && grid[8] == 1) ||
        (grid[0] == 1 && grid[4] == 1 && grid[8] == 1) ||
        (grid[2] == 1 && grid[4] == 1 && grid[6] == 1))
    {
        if(player == 1)
        {
            return -10;
        }
        else
        {
            return 10;
        }
    }

    else
    {
        return 0;
    }
}

int checkMovesLeft(int* grid)
{
    for(int i = 0; i < 9; i++)
    {
        if (grid[i] == 2)
        {
            return 1;
        }
    }
    return 0;
}

int minimax(int* grid, int depth, int isMax, int player)
{
    int score = checkWin(grid,player);
    if (score == 10)
        return score;
    if (score == -10)
        return score;
    if (checkMovesLeft(grid)==0)
        return 0;

    if (isMax)
    {
        int best = -1000;
        for (int i = 0; i<9; i++)
        {
            if (grid[i]==2)
            {
                grid[i] = !player;
                best = max(best,minimax(grid, depth+1, !isMax, player));
                grid[i] = 2;
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = 0; i<9; i++)
        {
            if (grid[i]==2)
            {
                grid[i] = player;
                best = min(best,minimax(grid, depth+1, !isMax, player));
                grid[i] = 2;
            }
        }
        return best;
    }
}

int findBestMove(int* grid, int player)
{
    int bestVal = -1000;
    int bestMove = 0;

    for (int i = 0; i<9; i++)
    {
        if (grid[i] == 2)
        {

            grid[i] = !player;
            int moveVal = minimax(grid, 0, 0, player);
            grid[i] = 2;
            if (moveVal > bestVal)
            {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

int min(int a, int b)
{
    if (a<b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int max(int a, int b)
{
    if (a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

