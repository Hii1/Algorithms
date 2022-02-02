#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//Using dynamic programming
// A(n, m) = 1 + min[ max(A(n-1, m-1), A(k-n, m))]
// if we are in n'th floor there will be alaways + 1 for dropping the ball on that floor
//when we drop the balls, there is 2 possible events

// 1- the ball breaks, then we need to check n-1, and we have now balls m - 1
// 2- the ball doesn't break, then we need to check the above floor total_floors - n, and the ball count will stay the same m

// Time complexity : O((m*n^2),  m : for the outer loop, n: for the 1s't nest loop, n: for the 2'nd nested loop
// Space complexity: O(n*m), for memoization table

int** table;
void print_table(int floors, int balls)
{
	int i = 0, j = 0;
	for( i  = 1; i <= balls; ++i)
	{
		for( j  = 1; j <= floors; ++j)
			printf("%d ", table[i][j]);
		printf("\n");
	}
}
int min_drops_bottomUP(int floors, int balls)
{
	int i = 0, j = 0, k = 0;
	if(balls == 0 || floors == 0)//base case, when the balls = 0 or floors = 0, 0 drops needed
		return 0;
	if(balls == 1)//balls == 1, then we need to try floors time
		return floors;

	

	for(i = 0; i <= balls; ++i)//O(m)
	{
		table[i][1] = 1;// 1 floor, 1 drop
		table[i][0] = 0;// 0 floors, 0 drops
	}

	for(j = 0; j <= floors; ++j)//O(n)		
	{
			table[0][j] = 0;// 1 ball so no of drops = j
			table[1][j] = j;
	}	

	for(i = 2; i <= balls; ++i)//O(m*n*n)
	{
		for(j = 2; j <= floors; ++j) //O(n*n)
		{
			//if we are in k+1'th floor in bulding with j+1'th floors
			table[i][j] = INT_MAX;
			for(k = 1; k <= j; ++k)//o(n), 2 + 3 + ... + n = O(n)
			{
				int p1 = table[i-1][k-1]; //A(n-1, m-1)
				int p2 = table[i][j-k]; // A(k-n, m)
				int try = ( p1 > p2 ) ? p1 : p2;// we choose the bigger one,  since we are finding the minum drops for the ***WORST CASE*** not best case
				++try;// +1 A(n, m) = 1 + min(...), we can do it after the for loop for k is terminated
				if(try  < table[i][j]) //min[ max(A(n-1, m-1), A(k-n, m))] for all k
					table[i][j]= try;
			}
		}
	}
	//print_table(floors, balls);
	return table[balls][floors];// the min value
}


int main()
{
    
	int floors = 0;
	int balls = 0;
	
	scanf(" %d  %d", &floors, &balls);
	
	table = (int**) malloc(sizeof(int*) * (balls+1));//memory allocation for 2d array
	for(int i  = 0; i <= balls; ++i)
		table[i] = (int*) malloc(sizeof(int) * (floors+1));

	for(int i  = 0; i <= balls; ++i)
		for(int j  = 0; j <= floors; ++j)
				table[i][j] = INT_MAX;
	
	printf("%d",min_drops_bottomUP(floors,balls));
	
	for(int i  = 0; i <= balls; ++i)
		free(table[i]);
	free(table);
    return 0;
}