#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6

char *wordList[] = {"APRON", "TABLE", "CHAIR", "LIGHT", "HOUSE", "WATER", "BREAD", "MUSIC", "POWER", "PIANO"};

char* selectRandomWord();
char* getUserGuess(char* guess);
int checkUserGuess(char* guess, char* word);
void suggestUserGuess(char* guess, char* word, char* suggest, int* status);
void draw(char** guess, char* word, char** suggest, int** status);

int main(void)
{
    int tries = 0;
    srand(time(NULL));
    system("color F0");


    char* choosenWord = selectRandomWord();

    char** userGuess = (char**)malloc(6*sizeof(char*));
    for (int i = 0; i < 6; i++)
    {
        userGuess[i] = (char*)calloc(6,sizeof(char));
    }

    char** userSuggest = (char**)malloc(6*sizeof(char*));
    for (int i = 0; i < 6; i++)
    {
        userSuggest[i] = (char*)calloc(6,sizeof(char));
    }

    int** userStatus = (int**)malloc(6*sizeof(int*));
    for (int i = 0; i < 6; i++)
    {
        userStatus[i] = (int*)calloc(6,sizeof(int));
    }

    for(int i = 0; i<6; i++)
    {
        memset(userGuess[i],'-',5);
    }

    for(int i = 0; i<6; i++)
    {
        memset(userSuggest[i],'-',5);
    }

    int guessStatus = 0;

    while (tries != MAX_ATTEMPTS)
    {
        draw(userGuess,choosenWord,userSuggest,userStatus);
        while(1)
        {
            char* temp = getUserGuess(userGuess[tries]);
            if (temp != NULL)
            {
                userGuess[tries] = temp;
                break;
            }
            printf("INVALID ENTRY, TRY AGAIN!! \n\n");
        }

        guessStatus = checkUserGuess(userGuess[tries],choosenWord);
        suggestUserGuess(userGuess[tries],choosenWord,userSuggest[tries],userStatus[tries]);

        if(guessStatus == 1)
        {
            system("color A0");
            draw(userGuess,choosenWord,userSuggest,userStatus);
            printf("YOU HAVE GUESSED THE WORD CORRECTLY!!! \n");
            return 0;
        }
        tries++;
    }
    printf("YOU HAVE RUN OUT OF ATTEMPTS, THE WORD WAS %s!!! \n",choosenWord);
    return 0;
}

char* selectRandomWord()
{
    int index = rand() % (sizeof(wordList) / sizeof(wordList[0]));
    return wordList[index];
}

char* getUserGuess(char* guess)
{
    char userInput[20] = "";
    printf("ENTER A FIVE LETTER WORD \n");
    gets(userInput);
    if(strlen(userInput) == 5)
    {
        for (int i = 0; i<5; i++)
        {
            if(isalpha(userInput[i]) == 0)
            {
                return 0;
            }
        }
        for (int i = 0; i<5; i++)
        {
            guess[i] = toupper(userInput[i]);
        }
        return guess;
    }
    else
    {
        return 0;
    }
}

int checkUserGuess(char* guess, char* word)
{
    if(strcmp(guess,word) == 0)
    {
        return 1;
    }
    return 0;
}

void suggestUserGuess(char* guess, char* word, char* suggest, int* status)
{
    for(int i = 0; i<5; i++)
    {
        for(int j = 0; j<5; j++)
        {
            if(guess[i] != word[j])
            {
                suggest[i] = '-';
                status[i] = 0;
            }
            else
            {
                suggest[i] = guess[i];
                if(i == j)
                {
                    status[i] = 2;
                    break;
                }
                status[i] = 1;
                break;
            }
        }
    }
}

void draw(char** guess, char* word, char** suggest, int** status)
{
    system("cls");
    printf("WORDLE!");
    printf("IN PLACE SCORE - IF 0 LETTER DOES NOT EXIST\n");
    printf("                 IF 1 LETTER EXISTS BUT NOT AT THAT PLACE\n");
    printf("                 IF 2 LETTER EXISTS AT THAT PLACE OF THE WORD TO BE GUESSED\n");
    for(int i = 0; i < 6; i++)
    {
        printf("===================================\n");
        printf("GUESS %d \n",i+1);
        printf("===================================\n");
        printf("GUESSED WORD        ");
        for (int j = 0; j < 5; j++)
        {
            printf("|| %c ",guess[i][j]);
        }
        printf("\n");
        printf("LETTERS THAT MATCH  ");
        for (int j = 0; j < 5; j++)
        {
            printf("|| %c ",suggest[i][j]);
        }
        printf("\n");
        printf("IN PLACE SCORE      ");
        for (int j = 0; j < 5; j++)
        {
            printf("|| %d ",status[i][j]);
        }
        printf("\n");
        printf("===================================\n");
    }
}
