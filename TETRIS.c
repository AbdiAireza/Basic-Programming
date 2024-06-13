#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#define sleepInSeconds(seconds) Sleep((DWORD)(seconds * 1000))
#endif

void clrscr()
{
    system("cls");
}
//function to get a random number for shape

int GetRandomNumber()
{
    srand(clock() + time(NULL) + M_PI);
    return rand() % 4;
}
//Function to diplay the game array and score
// This function prints the game board

void displayArray(char arr[20][20], int score)
{
    for (int i = 0; i < 42; i++)
    {
        printf("-");
    }
    printf("      Score: %d\n", score);
    for (int i = 0; i < 20; i++)
    {
        printf("|");
        for (int j = 0; j < 20; j++)
        {
            if (arr[i][j] == '0')
            {
                printf("%s", "  ");
            }
            else if (arr[i][j] == '1')
            {
                printf("%s", "[]");
            }
            else if (arr[i][j] == '2')
            {
                printf("%s", "[]");
            }
        }
        printf("|");
        printf("\n");
    }
    for (int i = 0; i < 42; i++)
    {
        printf("-");
    }
    printf("\n");
}

void set_1_to_0(char arr[20][20])
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (arr[i][j] == '1')
            {
                arr[i][j] = '0';
            }
        }
    }
}
void set_1_to_2(char arr[20][20])
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (arr[i][j] == '1')
            {
                arr[i][j] = '2';
            }
        }
    }
}
void set_all_to_0(char arr[20][20])
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            arr[i][j] = '0';
        }
    }
}

//Function to draw diffrent shapes
void drawshapes(int num, char arr[20][20])
{
    if (num == 0)
    {
        arr[0][9] = '1';
        arr[0][10] = '1';
        arr[1][9] = '1';
        arr[1][10] = '1';
    }
    if (num == 1)
    {
        arr[0][8] = '1';
        arr[0][9] = '1';
        arr[1][9] = '1';
        arr[1][10] = '1';
    }
    if (num == 2)
    {
        arr[0][9] = '1';
        arr[1][8] = '1';
        arr[1][9] = '1';
        arr[1][10] = '1';
    }
    if (num == 3)
    {
        arr[0][8] = '1';
        arr[0][9] = '1';
        arr[0][10] = '1';
        arr[0][11] = '1';
    }
    /*

    0 = [][]
        [][]

    1 = [][]
        [][]

    2 =   []
        [][][]

    3 = [][][][]

    */
}
//Function to diplay the game array and score

void movedown(char arr[20][20])
{
    for (int i = 19; i >= 0; i--)
    {
        for (int j = 19; j >= 0; j--)
        {
            if (arr[i][j] == '1')
            {
                arr[i][j] = '0';
                arr[i + 1][j] = '1';
            }
        }
    }
}
// This function checks the condition of moving the shape to the right depending on the shape type
// This function checks the condition of moving the shape to the left depending on the shape type
void rightleft(char arr[20][20], char x)
{
    int help_var = 1;
    if ((x == 'a') || (x == 'A'))
    {
        for (int i = 19; i >= 0; i--)
        {
            for (int j = 0; j < 20; j++)
            {
                if ((arr[i][j] == '1')&&(arr[i][j-1] == '2'))
                {
                    help_var = 0;
                }
            }
        }
        for (int i = 19; i >= 0; i--)
        {
            for (int j = 0; j < 20; j++)
            {
                if (arr[i][0] == '1')
                {
                    help_var = 0;
                }
            }
        }
        for (int i = 19; i >= 0; i--)
        {
            for (int j = 0; j < 20; j++)
            {
                if ((arr[i][j] == '1') && (help_var))
                {
                    arr[i][j] = '0';
                    arr[i][j - 1] = '1';
                }
            }
        }
    }
    help_var = 1;
    if ((x == 'd') || (x == 'D'))
    {
        for (int i = 0 ; i<20 ; i++){
            for (int j = 0 ; j<20 ; j++){
                if ((arr[i][j] == '1')&&(arr[i][j + 1] == '2')){
                    help_var = 0; 
                }
            }
        }
        for (int i = 19; i >= 0; i--)
        {
            if (arr[i][19] == '1')
            {
                help_var = 0;
            }
        }
        for (int i = 19; i >= 0; i--)
        {
            for (int j = 19; j >= 0; j--)
            {
                if ((arr[i][j] == '1') && (help_var))
                {
                    arr[i][j] = '0';
                    arr[i][j + 1] = '1';
                }
            }
        }
    }
}
// This function deletes a row when it is completely filled and moves the upper rows to the bottom
void ClearRows(char arr[20][20], int *score)
{
    for (int i = 0; i < 20; i++)
    {
        if (
            (arr[i][0] == '2') && (arr[i][1] == '2') && (arr[i][2] == '2') &&
            (arr[i][3] == '2') && (arr[i][4] == '2') && (arr[i][5] == '2') &&
            (arr[i][6] == '2') && (arr[i][7] == '2') && (arr[i][8] == '2') &&
            (arr[i][9] == '2') && (arr[i][10] == '2') && (arr[i][11] == '2') 
            && (arr[i][12] == '2') && (arr[i][13] == '2') && (arr[i][14] == '2') && (arr[i][15] == '2') 
            && (arr[i][16] == '2') && (arr[i][17] == '2') && (arr[i][18] == '2') && (arr[i][19] == '2'))

        {
            for (int j = 0; j < 20; j++)
            {
                arr[i][j] = '0';
            }
            for (int j = 0; j < 20; j++)
            {
                arr[0][j] = '0';
            }
            for (int j = i; j > 0; j--)
            {
                for (int k = 0; k < 20; k++)
                {
                    arr[j][k] = arr[j - 1][k];
                }
            }
            (*score) += 10;
        }
    }
}

int game_over(char arr[20][20])
{
    int isfull = 0;
    for (int i = 0; i < 20; i++)
    {
        if (arr[1][i] == ('2'))
        {
            isfull = 1;
        }
    }
    return isfull;
}
//Function to rotate the shape
void rotateShape(char arr[20][20], int key, int help_rotate, char choose_rotation)
{
    if (choose_rotation == '1')
    {
        /*rotate shape 3*/
        if ((key == ' '))
        {
            if (!(help_rotate % 2))
            { /* if help random is even this condition is true*/
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if ((arr[i][j] == '1') && (arr[i][j + 1] == '1') && (arr[i][j + 2] == '1') && (arr[i][j + 3] == '1'))
                        {
                            set_1_to_0(arr);
                            arr[i - 1][j + 1] = '1';
                            arr[i][j + 1] = '1';
                            arr[i + 1][j + 1] = '1';
                            arr[i + 2][j + 1] = '1';
                        }
                    }
                }
            }
            else if (help_rotate % 2)
            {
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if ((arr[i][j] == '1') && (arr[i + 1][j] == '1') && (arr[i + 2][j] == '1') && (arr[i + 3][j] == '1'))
                        {
                            set_1_to_0(arr);
                            arr[i + 1][j - 1] = '1';
                            arr[i + 1][j] = '1';
                            arr[i + 1][j + 1] = '1';
                            arr[i + 1][j + 2] = '1';
                        }
                    }
                }
            }
        }
        /*rotate shape 1*/
        if ((key == ' '))
        {
            if (!(help_rotate % 2))
            {
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if ((arr[i][j] == '1') && (arr[i][j + 1] == '1') && (arr[i + 1][j + 1] == '1') && (arr[i + 1][j + 2] == '1'))
                        {
                            set_1_to_0(arr);
                            arr[i][j + 1] = '1';
                            arr[i + 1][j + 1] = '1';
                            arr[i + 1][j] = '1';
                            arr[i + 2][j] = '1';
                        }
                    }
                }
            }
            else if (help_rotate % 2)
            {
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if ((arr[i][j] == '1') && (arr[i + 1][j] == '1') && (arr[i + 1][j - 1] == '1') && (arr[i + 2][j - 1] == '1'))
                        {
                            set_1_to_0(arr);
                            arr[i][j - 1] = '1';
                            arr[i][j] = '1';
                            arr[i + 1][j] = '1';
                            arr[i + 1][j + 1] = '1';
                        }
                    }
                }
            }
        }
        /*rotate shape 2*/
        if ((key == ' '))
        {
            if ((help_rotate % 4) == 0)
            {
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if ((arr[i][j] == '1') && (arr[i + 1][j - 1] == '1') && (arr[i + 1][j] == '1') && (arr[i + 1][j + 1] == '1'))
                        {
                            set_1_to_0(arr);
                            arr[i][j] = '1';
                            arr[i + 1][j] = '1';
                            arr[i + 1][j + 1] = '1';
                            arr[i + 2][j] = '1';
                        }
                    }
                }
            }
            else if ((help_rotate % 4) == 1)
            {
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if ((arr[i][j] == '1') && (arr[i + 1][j] == '1') && (arr[i + 1][j + 1] == '1') && (arr[i + 2][j] == '1'))
                        {
                            set_1_to_0(arr);
                            arr[i][j] = '1';
                            arr[i + 1][j] = '1';
                            arr[i][j + 1] = '1';
                            arr[i][j - 1] = '1';
                        }
                    }
                }
            }
            else if ((help_rotate % 4) == 2)
            {
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if ((arr[i][j] == '1') && (arr[i + 1][j] == '1') && (arr[i][j + 1] == '1') && (arr[i][j - 1] == '1'))
                        {
                            set_1_to_0(arr);
                            arr[i][j] = '1';
                            arr[i + 1][j] = '1';
                            arr[i + 1][j - 1] = '1';
                            arr[i + 2][j] = '1';
                        }
                    }
                }
            }
            else if ((help_rotate % 4) == 3)
            {
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if ((arr[i][j] == '1') && (arr[i + 1][j] == '1') && (arr[i + 1][j - 1] == '1') && (arr[i + 2][j] == '1'))
                        {
                            set_1_to_0(arr);
                            arr[i][j] = '1';
                            arr[i + 1][j - 1] = '1';
                            arr[i + 1][j] = '1';
                            arr[i + 1][j + 1] = '1';
                        }
                    }
                }
            }
        }
    }
    if (choose_rotation == '2')
    {
        /*rotate shape 2*/
        if ((key == ' '))
        {
            if (!(help_rotate % 2))
            { /* if help random is even this condition is true*/
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if ((arr[i][j] == '1') && (arr[i + 1][j] == '1') && (arr[i + 1][j + 1] == '1') && (arr[i + 1][j - 1] == '1'))
                        {
                            set_1_to_0(arr);
                            arr[i][j] = '1';
                            arr[i][j + 1] = '1';
                            arr[i][j - 1] = '1';
                            arr[i + 1][j] = '1';
                        }
                    }
                }
            }
            else if (help_rotate % 2)
            {
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if ((arr[i][j] == '1') && (arr[i][j + 1] == '1') && (arr[i][j - 1] == '1') && (arr[i + 1][j] == '1'))
                        {
                            set_1_to_0(arr);
                            arr[i + 1][j] = '1';
                            arr[i + 1][j + 1] = '1';
                            arr[i + 1][j - 1] = '1';
                            arr[i][j] = '1';
                        }
                    }
                }
            }
        }
    }
}
char input(char input)
{
    char input_2;
    while (input = getchar())
    {
        input_2 = input;
        if ((input == '1') || (input == '2'))
        {
            break;
        }
        else
        {
            printf("Please enter a  valid number:\n");
        }
        fflush(stdin);
    }
    return input_2;
}
// The game is executed in this function
int main(void)
{
    int score = 0;
    int *p_score = &score;
    char y_x[20][20];
    set_all_to_0(y_x);
    int help_var_2 = 1;
    char choose_rotation;
    printf("Welcome\n");
    printf("Press any key to start the game\n");
    printf("how much do you want for rotation per space?\n1) 90 \n2) 180\n");
    choose_rotation = input(choose_rotation);
    while (help_var_2)
    {
        set_1_to_2(y_x);
        int help_random = GetRandomNumber();
        int help_rotate = 0;
        drawshapes(help_random, y_x);
        float help_sleep = 0.2;
        for (int help_var = 1; help_var; help_var += 0)
        {
            char key = '\0';
            int help_key = 0;
            if (kbhit())
            {
                char key = _getch();
                rightleft(y_x, key);
                if ((key == 'a') || (key == 'd') || (key == 'A') || (key == 'D'))
                {
                    help_key = 1;
                }

                if (key == ' ')
                {
                    rotateShape(y_x, key, help_rotate, choose_rotation);
                    help_rotate += 1;
                }
                if ((key == 's') || (key == 'S'))
                {
                    if (help_sleep >= 0.01)
                    {
                        help_sleep /= 2;
                    }
                }
            }
            clrscr();
            if (!help_key)
            {
                movedown(y_x);
            }
            displayArray(y_x, score);
            sleepInSeconds(help_sleep);
            for (int j = 0; j < 20; j++)
            {
                if (y_x[19][j] == '1')
                {
                    help_var = 0;
                    set_1_to_2(y_x);
                    break;
                }
            }
            for (int i = 0; i < 20; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    if ((y_x[i][j] == '1') && (y_x[i + 1][j] == '2'))
                    {
                        set_1_to_2(y_x);
                        help_var = 0;
                    }
                }
            }
            ClearRows(y_x, p_score);
            if (game_over(y_x))
            {
                help_var = 0;
                help_var_2 = 0;
            }
        }
    }
printf(" GAME OVER!\n");
    printf("NICE TRY! Your score: %d\n", score);
}


