#include "header_tic.h"

int main()
{
    char arr[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    printf("Welcome to tic-tac-toe o_x\n");
    tic(arr);

    char name1[30], name2[30];
    printf("Enter player 1 name: ");
    scanf("%[^\n]", name1);
    printf("Enter player 2 name: ");
    scanf("\n%[^\n]", name2);
    gameplay(name1, name2);
}
