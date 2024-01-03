#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "winbgi2.h"


void drawTable(int offset)
{   

    int x, y;
    x = 1000;

    for (y = 0; y <= 1000; y = y + offset)
    {

        line(x - 1000, y, x, y);
        

    }
    y = 1000;
    for (x = 0; x <= 1000; x = x + offset)
    {
        line(x, y - 1000, x, y);
    }
}

void paint(int x,int y)
{
    floodfill(x,y, WHITE);
}




int main()
{
    graphics(1000, 750);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(490, 200, "SIMS 0.5");
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2.5);
    outtextxy(490, 300, "Start");
    outtextxy(490, 400, "Opcje");
    outtextxy(490, 500, "Exit");
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    int start = 0;
    int offset = 100;
    int howlong = 50;

    
    
    while (start == 0)
    {
        int isclicked = mousedown();

        if (isclicked == 1)
        {
            int x_clicked = mouseclickx();
            int y_clicked = mouseclicky();


            //printf("DEBUG: X: %d, Y: %d \n", x_clicked, y_clicked);
            if (x_clicked >= 450 && x_clicked <= 530 && y_clicked >= 280 && y_clicked <= 300)
            {
                printf("DEBUG: Clicked start\n");
                printf("\n\n");
                start = 1;
                closegraph();
                break;
            }

            if (x_clicked >= 450 && x_clicked <= 530 && y_clicked >= 380 && y_clicked <= 410)
            {
                printf("DEBUG: Clicked options\n");
                printf("\n\n");
            }
            if (x_clicked >= 450 && x_clicked <= 530 && y_clicked >= 480 && y_clicked <= 500)
            {
                printf("DEBUG: Clicked exit\n");
                printf("\n\n");
                closegraph();
                break;
            }


        }
    }

   

    if (start == 1)
    {
        graphics(1000, 1000);
       


        int hwmn = (1000 / offset) * (1000 / offset) + 1; 

        // HWMN - skrót od how many, generalnie odnosi siê do tego ile kwadracików istnieje w naszej planszy 
        //a dodaje +1 bo podwójna tablica wymaga tego odemnie bo inaczej problem zachodzi

        int rowNumber = 1000 / offset;
        int columnNumber = 1000 / offset;
        //printf("DEBUG: row num: %d, column num: %d\n", rowNumber, columnNumber);
        
        int i;
        int** table;
        table = (int**)malloc(hwmn * sizeof(int*));
        for (i = 0; i < hwmn; ++i) 
        {
            table[i] = (int*)malloc(hwmn * sizeof(int));
        }

        int* rows;
        int* columns;

        //rows = (int*)malloc(rowNumber * sizeof(int));
        //columns = (int*)malloc(columnNumber * sizeof(int));


        drawTable(offset);
        for (i = 1; i < hwmn; i++)
        {
             table[i][i] = i;
            *table[i] = 0;
            
            //printf("DEBUG: %d,  %d\n", table[i][i],*table[i]);

        }
        

        printf("DEBUG: For done\n");
        


        while (start == 1)
        {





            int isclicked = mousedown();
            int isKeyclicked = kbhit();
            
            if (isKeyclicked == 0)
            {
                if (isclicked == 1)
                {
                    
                    
                    int x_clicked = mouseclickx();
                    int y_clicked = mouseclicky();
                    int x, y;

                    //printf("DEBUG: X: %d, Y: %d \n", x_clicked, y_clicked);


                    paint(x_clicked, y_clicked);
                    x = 0;
                    y = 0;

                    for (i = 1; i < hwmn; i++)
                    {

                        if (x_clicked <= 1000 && y_clicked <= 1000)
                        {
                            if (x < x_clicked && x_clicked < x + offset && y < y_clicked && y_clicked < y + offset)
                            {
                                if (table[i][i] == i)
                                {
                                    *table[i] = 10;
                                    printf("%d %d\n", table[i][i], *table[i]);

                                }

                            }
                        }
                        x = x + offset;
                        if (x == 1000)
                        {
                            x = 0;
                            y = y + offset;
                        }
                    }

                }
            }
            //esc - 02727 r - 082114 s - 083115
            if (isKeyclicked == 1)
            {
                int keyclicked = getch();

                if (keyclicked == 27)
                {
                    printf("Closed");
                    closegraph();
                    for (int i = 0; i < hwmn; ++i)
                        free(table[i]);

                    free(table);

                    break;
                }
                if (keyclicked == 83)
                {
                    printf("\n\nGAME STARTED\n");

                    
                    for (i = 1; i < hwmn; i++)
                    {
                       // printf("DEBUG: TEST: matrix: %d num: %d\n", table[i][i], *table[i]);
                    }
                    
                    for (i = 0; i < howlong; i++)
                    {
                        int x = 0, y = 0;
                        for (int j = 1; j < hwmn; j++)
                        {
                            //printf("DEBUG: J: %d\n", j);
                            //printf("DEBUG: equates:%d\n", j % rowNumber);
                            //printf("DEBUG: equates 2: %d\n", rowNumber * columnNumber);
                            
                            if (j <= rowNumber || j > (rowNumber*columnNumber)-rowNumber)
                            {
                                if (j == 0)
                                {
                                    if (*table[j + 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber + 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    //printf("DEBUG: 0\n");
                                }
                                if ((j <= rowNumber && j != 0 && j != rowNumber))
                                {
                                    if (*table[j - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber + 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    //printf("DEBUG: 1-9\n");
                                }
                                if (j == rowNumber)
                                {
                                    if (*table[j - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    //printf("DEBUG: 10\n");
                                }
                                if (j == rowNumber * columnNumber)
                                {
                                    if (*table[j - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j - rowNumber] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j - rowNumber - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    //printf("DEBUG: 100\n");
                                }
                                if (j > (rowNumber * columnNumber) - rowNumber && j != rowNumber*columnNumber)
                                {
                                    if (*table[j - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j - rowNumber + 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j - rowNumber] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j - rowNumber - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    //printf("DEBUG: 91-99\n");
                                }
                            }
                            else
                            {
                                if (j % rowNumber == 1)
                                {
                                    
                                    if (*table[j + 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j - rowNumber + 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j - rowNumber] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber + 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    //printf("DEBUG: 11,21,31,...,81\n");
                                }
                                if (j % rowNumber == 0)
                                {
                                    if (*table[j - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j - rowNumber] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j - rowNumber - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    //printf("DEBUG: 20,..,80,90\n");
                                    
                                }
                                else
                                {
                                    if(j % rowNumber != 1 && j % rowNumber != 0)
                                    {
                                    if (*table[j - rowNumber - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j - rowNumber] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j - rowNumber + 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber - 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    if (*table[j + rowNumber + 1] >= 10)
                                    {
                                        *table[j] = *table[j] + 1;
                                    }
                                    }
                                    //printf("DEBUG: unrelated\n");
                                }
                            }
                            

                            



                            //printf("DEBUG: matrix: %d number of neigh: %d \n", table[j][j], *table[j]);
                            //wait();
                            //printf("DEBUG: END\n");
                        }


                        
                        for (int j = 0; j < hwmn; j++)
                        {
                            if (10 == *table[j] || (*table[j] >= 10 && *table[j] < 12) || *table[j] < 3 )
                            {
                                x = (j % (offset / rowNumber)) * offset;
                                y = (j % offset) * (offset / columnNumber);
                                //printf("1 DEBUG: The box dissapears: x: %d y: %d number in matrix: %d\n", x, y, j);
                                floodfill(x-(offset/rowNumber), y-(offset/columnNumber), BLACK);
                                *table[j] = 0;
                            }
                            else if (*table[j] >= 12 && *table[j] <= 13)
                            {
                                x = (j % (offset / rowNumber)) * offset;
                                y = (j % offset) * (offset / columnNumber);
                                //printf("2 DEBUG: The box appears: x: %d y: %d number in matrix: %d\n", x, y, j);
                                floodfill(x - (offset / rowNumber), y - (offset / columnNumber), WHITE);
                                *table[j] = 10;
                            }
                            else if (13 < *table[j])
                            {
                                x = (j % (offset / rowNumber)) * offset;
                                y = (j % offset) * (offset / columnNumber);
                                //printf("3 DEBUG: The box dissapears: x: %d y: %d number in matrix: %d\n", x, y, j);
                                floodfill(x - (offset / rowNumber), y - (offset / columnNumber), BLACK);
                                *table[j] = 0;
                            }
                            else if (0 == *table[j] || (*table[j]>3 && *table[j] < 10))
                            {
                                x = (j % (offset / rowNumber)) * offset;
                                y = (j % offset) * (offset / columnNumber);
                                //printf("4 DEBUG: The box dissapears: x: %d y: %d number in matrix: %d\n", x, y, j);
                                //floodfill(x - (offset / rowNumber), y - (offset / columnNumber), BLACK);
                                *table[j] = 0;
                            }
                            else if (3 == *table[j])
                            {
                                x = (j % (offset / rowNumber)) * offset;
                                y = (j % offset) * (offset / columnNumber);
                                //printf("5 DEBUG: The box appears: x: %d y: %d number in matrix: %d\n", x, y, j);
                                floodfill(x - (offset / rowNumber), y - (offset / columnNumber), WHITE);
                                *table[j] = 10;
                            }
                            
                            
                        }

                        /*
                        * 
                        * DEBUGGING PURPOSES!
                        for (int test = 0; test < hwmn; test++)
                        {
                            printf("DEBUG: NEW MATRIX: point:%d, value: %d\n",table[test][test], *table[test]);
                        }
                        */

                        
                        animate(1);
                        delay(1000);
                        clear();
                        drawTable(offset);

                        
                        
                    }

                }
            }

            
            

            


        }
        //for (int i = 0; i < hwmn; ++i)
            //free(table[i]);

        //free(table);
    }
    
   
    wait();


    return 0;
}
