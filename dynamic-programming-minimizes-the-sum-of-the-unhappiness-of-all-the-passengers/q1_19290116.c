//Using Dyamic algorithm

// this  means the the problem solution depends on the subproblem of k-1 

// opt(m, k) = min[opt(i, k-1) + unhappines(i+1, m, x)]. 
// 1 <= x <= m   
// 1 <= i <= x,
// basis case, when k == 1, just calculate min[unhappines(0, m, x)] , 1 <= x <= m

// Time complexity O(m^5), m => # of passengers               
// Space complexity O(m^2).

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

typedef struct 
{
    int unhappiness;
    int stop;
    int prev_stop;
}TABLE;

TABLE **table;//table for memization and traceback
int *destS;// passengers destination
int k = 0, m = 0;

void print_table();// for debugging and understanding the problem
void print_stops(int m, int k);
void print_result();
void input();
void creat_2D(int rows, int cols);
void free_2D(int rows);
void min_unhappiness(); 

int main()
{
    input();    
    creat_2D(m+1, k+1);

    min_unhappiness();// dynamic algorithm
    print_result();//output

    free_2D(m+1);
    free(destS);
}

void min_unhappiness()
{
    int **values = NULL;    
    int i = 0, j = 0, x = 0, z = 0, z2 = 0;;

    values = (int**) malloc(sizeof(int*) * (m+1));
    for(i = 0; i <= m; ++i)
        values[i] = (int*) malloc(sizeof(TABLE) * (m+1));


    for (i = 1; i <= m; i++)//values table, used for memoization (doesnt save subproblem optimal solution, it just make calcs easier).
        for (j = 1; j <= m; j++)
             values[i][j]= pow(destS[i] - destS[j],2);

   //basis case, when k = 1, we just find the optimal stop and fill the table used to save subproblem sols.
    for(i = 1; i <= m; ++i)//O(m^3)
    {
        table[i][1].unhappiness = INT_MAX; 
        for(j = 1; j <= i; ++j)//O(m^2)
        {         
            int unhappines = 0;
            for(z2 = 1; z2 <= i; ++z2)//O(m)
            {       
                unhappines += values[z2][j];
            } 
//printf("i= %d, j= %d, unhappines= %d\n", i, j, unhappines);
            if(unhappines < table[i][1].unhappiness)
            {
                table[i][1].unhappiness = unhappines;
                table[i][1].stop = destS[j];
                table[i][1].prev_stop = -1;
            }
        }
    }

    //bottom-up approach
    int unhappines = 0;
    for(i = 2; i <= k; ++i)//start from 2 stops until we have k stops//O(m^5)
    {
        for(j = 1; j <=m; ++j)//find the optimal solutions when end = j-last passenger-//O(m^4)
        {
            table[j][i].unhappiness = INT_MAX;
            for(x = 1; x <= j; ++x)//try every possible stop position from 1 to j//O(m^3)
            {
                for(z = 1; z <= x; ++z)//start postions for the kth stop we find the unhappines sum between z and j//O(m^2)
                {
                    unhappines = 0;
                    for(z2 = z; z2 <= j; ++z2)//sum the unhappines between z and j //O(m)                      
                        unhappines += values[z2][x];
             
                    int temp_min = unhappines + table[z-1][i-1].unhappiness;
                    if(temp_min < table[j][i].unhappiness)//min // and memoization
                    {
                        table[j][i].unhappiness = temp_min;
                        table[j][i].stop = destS[x];//optimal solution
                        table[j][i].prev_stop = z-1;//this is used for back tracking 
                    }
                }
            }
        }
    }
//print_table();
    for(i = 0; i <= m; ++i)
        free(values[i]); 
    free(values);
}
void input()
{
    scanf("%d", &m);//passengers size

    destS = (int*) malloc(sizeof(int)*(m+1)); // memory allocation
    
    int i = 0, j = 0, unwanted;    
    for(i = 1; i <= m; ++i)// passenger info input
    {
        scanf("%d %d", &unwanted,&destS[i]);
    }
    scanf("%d", &k);//no. of stops
}
void print_stops(int m, int k)//printing using recursive calls
{
    if(k  == 0)
        return;
         print_stops(table[m][k].prev_stop, k-1);// find the k-1th stop and call the function again
    printf("%d ", table[m][k].stop);
}
void print_result()
{
    print_stops(m, k);//print the result
    printf("\n");
//printf("minimum unhappines: %d.\n", table[m][k].unhappiness);
}
void creat_2D(int rows, int cols)
{
    int i = 0,  j = 0;
    table = (TABLE**) malloc(sizeof(TABLE*) * (rows));// memory allocation for table memoization
    for(i = 0; i < rows; ++i)
        table[i] = (TABLE*) malloc(sizeof(TABLE) * (cols));

}
void free_2D(int rows)
{
    int i = 0;
    for(i = 0; i < rows; ++i)
        free(table[i]); 
    free(table);
}


void print_table()
{
    printf("------------------------------\n");
    int i = 0, j = 0;
    for(i = 1; i <= m; ++i)
    {
        printf("%d\t", i);
        for(j = 1; j <= k; ++j)
            printf("{%d, %d, %d} ", table[i][j].unhappiness, table[i][j].stop, table[i][j].prev_stop);
        printf("\n");
    }
    printf("------------------------------\n");
}


