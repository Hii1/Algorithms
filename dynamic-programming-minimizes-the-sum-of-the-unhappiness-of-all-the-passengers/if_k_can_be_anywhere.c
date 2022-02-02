//Using Dyamic algorithm

// this  means the the problem solution depends on the subproblem of k-1 

// opt(m, k) = min[opt(i, k-1) + unhappines(i+1, m, x)]. 
// 1 <= x <= m   
// 1 <= i <= x,

// basis case, when k == 1, just calculate min[unhappines(0, m, x)] , 1 <= x <= m

// Time complexity O(|m|^5), m => magnitude of max destination
                // to be exact Time complexity O(|m|^4 * passengers_size)
// Space complexity O(m*k), k => no. of stops.

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

typedef struct 
{
    int unhappiness;
    int stop;
    int start;
}TABLE;

TABLE **table;//table for memization and traceback
int *destS;// passengers destination
int m = 0, k = 0, pass_size = 0;

void print_table();// for debugging and understanding the problem
void print_stops(int m, int k);
void print_result();
void input();
void creat_2D();
void free_2D();
int calc_unhappiness(int start , int end, int current_k_pos);
void min_unhappiness(); 

int main()
{
    input();    
    creat_2D();
    min_unhappiness();// dynamic algorithm
    print_result();//output
    free_2D();
    free(destS);
}
int calc_unhappiness(int start , int end, int current_k_pos)//O(passengers_size)
{
    // calculate unhappiness for passengers between start and end for current_k_pos stop
    int i = 0, j = 0, temp = 0;
    int total_unhappiness = 0, min_unhappy = INT_MAX;

    for(i = 0; i < pass_size; ++i)//O(pass_size) we can say m
    {        
        if(destS[i] > end || destS[i] < start)
            continue;
        min_unhappy = INT_MAX;
        min_unhappy = pow(destS[i] - current_k_pos, 2);//finding unhappines for the kth stop
        total_unhappiness  += min_unhappy;    //total unhappines for all passengers between start and end       
    }
    return total_unhappiness;    
}
void min_unhappiness()
{
    int i = 0, j = 0, z = 0, x = 0;

    //basis case, when k = 1;
    for(j = 1; j <= m; ++j)//O(m^2)
    {
        table[j][1].unhappiness = INT_MAX; 
        i = 1;// k == 1
        for(x = 1; x <= j; ++x)//O(m) we try ever k possible  
        {         
            int unhappines = calc_unhappiness(0, j, x);//finidng the unhappines  
            if(unhappines < table[j][1].unhappiness)//min // and memoization
            {
                table[j][i].unhappiness = unhappines;
                table[j][i].stop = x;
                table[j][i].start = -1;
            }
        }
    }

    int temp_min = 0;
    for(i = 2; i <= k; ++i)//for loop for stops from 2 to k //O(m^5)
    {
        // we start from 1 max destination
        for(j = 1; j <= m; ++j)//for loop for dest unit from 1 to m//O(m^4)
        {
            table[j][i].unhappiness = INT_MAX;
            //trying every possible solution and taking the optimal solution(min)
            for(x = 1; x <= j; ++x)//for loop to check try every possible k position // O(m^3)
            {                
                for(z = 1; z <= x; ++z)//for loop to find the prev optimal solution for i-1 //O(m^2)
                {
                    int start = z;
                    int prev_opt = table[start-1][i-1].unhappiness;//adding the optimal solution for the subproblem

                    int unhappines = calc_unhappiness(start, j, x);//finidng the unhappines                    
                    temp_min = prev_opt + unhappines;

//printf("z = %d, unhappiness = %d, prevO = %d, start  = %d, k = %d\n", z, unhappines, prev_opt, start, x);
                                    
                    if(temp_min < table[j][i].unhappiness)//min // and memoization
                    {
                        table[j][i].unhappiness = temp_min;
                        table[j][i].stop = x;
                        table[j][i].start = start-1;//this is used for back tracking 
                    }
                }
            }
//printf("i = %d, j = %d\n",i, j);
//print_table();
        }
    }
}
void input()
{
    k = 0, m = INT_MIN;
    scanf("%d", &pass_size);//passengers size

    destS = (int*) malloc(sizeof(int)*pass_size); // memory allocation
    
    int i = 0, j = 0, unwanted;    
    for(i = 0; i < pass_size; ++i)// passenger info input
    {
        //scanf("%d %d", &unwanted,&destS[i]);
        scanf("%d", &destS[i]);
        if(m < destS[i])//max destination
            m = destS[i];
    }
    scanf("%d", &k);//no. of stops
}
void print_stops(int m, int k)//printing using recursive calls
{
    if(k  == 0)
        return;
         print_stops(table[m][k].start, k-1);// find the k-1th stop and call the function again
    printf("%d ", table[m][k].stop);
}
void print_result()
{
    print_stops(m, k);//print the result
    printf("\nminimum unhappines: %d.\n", table[m][k].unhappiness);
}
void creat_2D()
{
    int i = 0,  j = 0;
    table = (TABLE**) malloc(sizeof(TABLE*) * (m+1));// memory allocation for table memoization
    for(i = 0; i <= m; ++i)
        table[i] = (TABLE*) malloc(sizeof(TABLE) * (k+1));

    for(i = 0; i <= m; ++i)
    {
        for(j = 0; j <= k; ++j)
        {
            table[i][j].unhappiness = 0;
            table[i][j].stop = 0;
            table[i][j].start = 0;
        }
    }
}
void free_2D()
{
    int i = 0;
    for(i = 0; i <= m; ++i)
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
            printf("{%d, %d, %d} ", table[i][j].unhappiness, table[i][j].stop, table[i][j].start);
        printf("\n");
    }
    printf("------------------------------\n");
}
