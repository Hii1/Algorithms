#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//using dynamic programming, we know that A(j)= max(A(j-1), A(p(j)) + 1), if j itself is included or not, where p(j) finds the longest subset in j-1 and have arr[j] > arr[p(j)]
// we use memoization for overlapping subproblems

// Time complexity O(n^2)
// Space Complexity O(n) 


typedef struct //table memory
{
    int longest; // for table[i].longest, shows the optimal solution for this subset
    int traceBack; // show traceback 
}Table;

Table *table;



int longest_sub(int *arr, int size)//O(n^2)
{
    table[0].longest = 0; // base case length of 0 subset is 0       
    int max = 0, max_index = 0;
    for(int i = 1; i <= size; ++i)//O(n^2)
    {
        table[i].longest = 0;
        table[i].traceBack =  0;
         
        for(int j = i - 1; j >= 0 ; --j)//we consider  A(p(j)) + 1
        {
            if(arr[i] > arr[j] && table[i].longest < table[j].longest)//applying memoization
            {    
                    table[i].longest = table[j].longest;//applying memoization
                    table[i].traceBack = j;//applying traceback to we can print the sequence later
            }            
        } 
        table[i].longest++;// +1 for the value itself

        if(max < table[i].longest)//applying traceback by memorizing the index of the last value of the longest subset so we use it when we traceback. A(j)= max(A(j-1), A(p(j)) + 1)
        {
            max = table[i].longest;
            max_index = i;
        } 
    }  

    /*************** Traceback **********************/
    
    int i = max_index, k = 0;
    int *longest_seq  = (int*) malloc(max * sizeof(int));// since traceback will be in reverse we need to reverse the order

    while(i > 0)//adding the longest subset to the array o(n)
    {        
        longest_seq[k++] = arr[i];
        i  = table[i].traceBack;
    } 
    for(i = k-1; i >= 0; --i) //printing longest subset o(n)
        printf("%d ", longest_seq[i]);
    //printf("\n");
    
   /*for(int i = 1; i <= size; ++i)
        printf("i = %d, arr[i] = %d traceBack = %d, longest = %d\n", i, arr[i], table[i].traceBack, table[i].longest);
    printf("\n");*/

    free(longest_seq);

}


int main()
{
    int size = 0;
    scanf(" %d",  &size);
    int *arr = (int*) malloc(sizeof(int) * (size+1));//the set

    table = (Table *) malloc(sizeof(Table) * (size+1));//table for memoization

    arr[0] = INT_MIN;
    
    for(int i = 1; i <= size; ++i)//input
        scanf("%d", arr+i );

    longest_sub(arr, size);// finding the optimal soltuion and creating the memoization table

    free(arr);
    free(table);

    return 0;
}