#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define STRING_SIZE 100

// the algortihm is based on that A(i,j) = A(i-1, j) or A(i, j-1).

// Time complexity O(n*m) n size of first string,m size of second string
// Space complexity (n*m)

typedef struct 
{
    char set[STRING_SIZE];
    int size;
}Set;

int table[STRING_SIZE][STRING_SIZE] = {0}; // Memoization table - extra column and row to help with initializing base cases

void print_table(int n, int m);

void interval(Set *z, Set *x, Set* y)
{
    
    int i = 0, j = 0;    
    table[0][0] = 1;//base case , the string is empty    

    for(i = 0; i < x->size; ++i)//filling the table considring the 2'nd array is empty
		if(x->set[i] == z->set[i])
			table[i+1][0] = table[i][0];

    for(j = 0; j < y->size; ++j)//filling the table considring the 1'st array is empty
		if(y->set[j] == z->set[j])
			table[0][j+1] = table[0][j];
			
    //print_table(x->size, y->size);

    for(i = 1; i <= x->size  ; ++i) //O(n*m) // travesing the table from left to right, downward
    {
        for(j = 1; j <= y->size; ++j)
        {
            if(i-1 < x->size && x->set[i-1] == z->set[i+j-1] && table[i-1][j])// if the the i-1 -means the i'th index - item in the X set is equal to i+j-1 item in z, then we check if the subproblem is correct which is A(i-1, j) - 1which is table[i-1][j], 
                table[i][j] = 1;
            if(j-1 < y->size && y->set[j-1] == z->set[i+j-1] && table[i][j-1])//same as above  but from A(i, j-1)
                table[i][j] = 1;
            //printf("i = %d, j = %d, i+j-1 = %d\n", i-1, j-1, i+j-1);
            //print_table(x->size, y->size);
        }
    }
    if(table[x->size][y->size])//if  the end of the table and its true then we can interval the set 
        printf("YES");
    else
        printf("NO");
}

int main()
{
    Set x, y, z;

    scanf(" %s %s %s", x.set, y.set, z.set);//input

    x.size = strlen(x.set), y.size = strlen(y.set), z.size = x.size + y.size;// sets size

    interval(&z, &x, &y);
    return 0;
}

void print_table(int n, int m)
{
    for(int i = 0; i <= n; ++i)
	{
		for(int j = 0; j <= m; ++j)
			printf("%d ", table[i][j]);
		printf("\n");		
	}
	printf("**************\n");
}