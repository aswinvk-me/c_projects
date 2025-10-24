#include "header_tic.h"
void gameplay(char name1[], char name2[])
{
    char arr[3][3] = {{' '}};
    char choice1, choice2;
    
    tic(arr);

    do
    {
        printf("Player 1 >>>>\t", "name1");
        scanf("%c", &choice1);
        if(choice1 <= '9' && choice1 > '0')
        {
            arr[(choice1 - '0' - 1)/3][(choice1- '0' - 1)%3] = 'X';
            
            tic(arr);
            do
            {
                printf("Player2 >>>>\t");
                scanf("%c", &choice2);
                if(choice2 <= '9' && choice2 > '0')
                {
                    arr[(choice2 - '0' - 1)/3][(choice2 - '0' - 1)%3] = 'O';
                    
                    tic(arr);
                    break;
                }
            }while(2);
        }
        
    } while (1);
    
    

}
void tic(char arr[3][3])
{
    system("clear");
    printf("-------------------------------------------------\n");
    printf("|\t\t|\t\t|\t\t|\n");
    printf("|\t%c\t|\t%c\t|\t%c\t|\n", arr[0][0], arr[0][1], arr[0][2]);
    printf("|\t\t|\t\t|\t\t|\n");
    printf("-------------------------------------------------\n");
    printf("|\t\t|\t\t|\t\t|\n");
    printf("|\t%c\t|\t%c\t|\t%c\t|\n", arr[1][0], arr[1][1], arr[1][2]);
    printf("|\t\t|\t\t|\t\t|\n");
    printf("-------------------------------------------------\n");
    printf("|\t\t|\t\t|\t\t|\n");
    printf("|\t%c\t|\t%c\t|\t%c\t|\n", arr[2][0], arr[2][1], arr[2][2]);
    printf("|\t\t|\t\t|\t\t|\n");
    printf("-------------------------------------------------\n");
}