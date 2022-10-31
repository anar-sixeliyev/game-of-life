#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int **arr;
void show(int **u, int w, int h)
{
    printf("\033[H");
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            printf(u[i][j] ? "\033[07m  \033[m" : "  ");
        }

        printf("\033[E");
    }
    fflush(stdout);
    // for (int i = 0; i < w; i++)
    // {
    //     for (int j = 0; j < h; j++)
    //     {
    //         printf("%d ", u[i][j]);
    //     }
    //     printf("\n");
    // }
}

int **createRandomTable(int w, int h)
{
    srand(time(NULL));
    int **randomArray = (int **)malloc(w * sizeof(int *));
    for (int i = 0; i < w; i++)
        randomArray[i] = (int *)malloc(h * sizeof(int));

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            randomArray[i][j] = 0; /*rand() % 2;*/
        }
    }
    return randomArray;
}

int **nextBoard(int **array, int w, int h)
{
    int **initial = array;
    // int **nextArray = array;
    int liveCounter = 0;
    int **nextArray = (int **)malloc(w * sizeof(int *));
    for (int i = 0; i < w; i++)
        nextArray[i] = (int *)malloc(h * sizeof(int));
    // show(initial, w, h);
    // printf("\n");
    // show(nextArray, w, h);
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            for (int i1 = i - 1; i1 < i + 2; i1++)
            {
                if (i1 < 0 || i1 >= w)
                    continue;

                for (int j1 = j - 1; j1 < j + 2; j1++)
                {
                    if (j1 < 0 || j1 >= h)
                        continue;

                    if (i1 == i && j1 == j)
                    {
                        continue;
                    }

                    if (initial[i1][j1])
                    {
                        liveCounter++;
                    }
                }
            }
            // printf("[%d : %d] liveCounter=%d\n", i, j, liveCounter);
            if (initial[i][j] == 1)
            {
                if (liveCounter == 0 || liveCounter == 1) //under population
                {
                    nextArray[i][j] = 0;
                }
                if (liveCounter == 2 || liveCounter == 3)
                {
                    nextArray[i][j] = 1;
                    // printf("nextarray[%d][%d]=%d", i, j, nextArray[i][j]);
                }
                if (liveCounter > 3) //over population
                {
                    nextArray[i][j] = 0;
                    // printf("nextarray[%d][%d]=%d\n", i, j, nextArray[i][j]);
                }
            }
            if (initial[i][j] == 0)
            {
                if (liveCounter == 3)
                {
                    nextArray[i][j] = 1;
                }
            }
            liveCounter = 0;
        }
    }
    return nextArray;
}

int main(int argc, char const *argv[])

{
    int width = 0, height = 0;
    if (argc > 1)
        width = atoi(argv[1]);
    if (argc > 2)
        height = atoi(argv[2]);

    arr = createRandomTable(width, height);
    // Beacon
    arr[1][1] = 1;
    arr[1][2] = 1;
    arr[2][1] = 1;
    arr[2][2] = 1;
    arr[3][3] = 1;
    arr[3][4] = 1;
    arr[4][3] = 1;
    arr[4][4] = 1;

    // Glider
    // arr[1][2] = 1;
    // arr[2][3] = 1;
    // arr[3][3] = 1;
    // arr[3][2] = 1;
    // arr[3][1] = 1;

    show(arr, width, height);
    int **nextArray = nextBoard(arr, width, height);
    printf("~~~~~~~~~~~~~~~~~~~~\n");
    show(nextArray, width, height);
    // while (1)
    // {
    //     sleep(1);
    //     show(nextBoard(arr, width, height), width, height);
    // }

    return 0;
}
