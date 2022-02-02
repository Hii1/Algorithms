#include<stdio.h>
#include<stdlib.h>

//using Greedy Algorithm
//when we are in step k, we choose the longest consecutive sequence starting from k between the workers
//then we assign this worker from step k to k + sequence to the schedule
// and the new subproblem will be min(k+sequence, steps), which means find the minum steps from k+sequence to the end

//Proof:
//suppose we have the optimal solution and 
//suppose in step k we chose a sequence which is not the longest,
//if we swapped the worker with the longest sequence  with the sequnce at step k
// the same worker will cover more tasks since longest_seq > the choosen sequence
//less switches will occure
// opt = *  * 1 1 1 * * *
// opt' = *  * 2 2 2 2 * *
//this leads us to a contridiction. which opt(1) > opt(2)

// Time complexity O(k*n*m), k => no. of steps, n = no. of workers, m => the max no. of steps the worker can take
// Space complexity O(k)

typedef struct WORKER//structure for each worker
{
    int size;// the size of taks the worker is allowed
    int *steps;// which tasks the worker is allowed
}WORKER;

int *schedule;
int  switchs_count = -1;
void min_scheduling(WORKER *workers, int workers_size, int steps)
{
    int i = 0, j = 0, k = 1;
    int longest_seq = 0, temp_longest_seq = 0;
    int longest_seq_index = 0;
    while(k <= steps)//we start from 1 // O(k*n*m), k no of steps, n = no of workers, m = the max no, of steps  the worker can take
    {
        longest_seq = 0;
        for(i = 0; i < workers_size; ++i)//check each worker// O(n*m)
        {  
            temp_longest_seq = 0;          
            for(j = 0; j < workers[i].size; ++j)//check the worker for the longest sequence starting from k
            //this for loop with the nested for loop will be O(m) since the nested for loop from from j to m
            {
                if(workers[i].steps[j] == k)//this help use to find only and only the longest sequence ***starting from k***
                {
                    ++temp_longest_seq;// +1 since we found the first task
                    for(j = j; j < workers[i].size - 1; ++j)
                    {
                        if(workers[i].steps[j] == workers[i].steps[j+1] - 1)//if the next step can be dont by the same worker +1 for the sequence
                            ++temp_longest_seq;
                        else   //if its not just break and check the next worker
                            break;
                    }
                }
            }

            if(longest_seq < temp_longest_seq)//max(longest_seq(i, k)) 0 <= i < workers_size 
            {
                longest_seq = temp_longest_seq;
                longest_seq_index = i;//memorizing the index of the longest sequence
            }
        }

        for(i = k; i < k+longest_seq; ++i)//filling the schedule with the index of the longest  sequence starting from k
            schedule[i-1] = longest_seq_index+1;
        ++switchs_count;
        k +=  (longest_seq) ? (longest_seq) : (1);//this if statment exist only if a step can't be done by any worker, otherwise k+ longest_seq
    }    
}

int main()
{
    int steps = 0, workers_size = 0;
    scanf(" %d %d", &steps, &workers_size);//input
    int i = 0, j = 0;

    WORKER *workers = (WORKER*) malloc(sizeof(WORKER)*workers_size);// memory allocation for workers

    for(i = 0; i < workers_size; ++i)
    {
        scanf("%d", &workers[i].size);// the size of tasks the worker is allowed
        workers[i].steps = (int*) malloc(sizeof(int) * workers[i].size);//memory allocation for the size of taks for each worker
        for(j = 0; j < workers[i].size; ++j)
            scanf("%d", &workers[i].steps[j]);
    }
    schedule = (int*) malloc(sizeof(int) * steps);//the output array

    min_scheduling(workers, workers_size, steps);//O(k*n*m), k no of steps, n = no of workers, m = the max no, of steps  the worker can take

    for(i = 0; i < steps; ++i)//output
        printf("%d ", schedule[i]);
    printf("with %d switches", switchs_count);

    for(i = 0; i < workers_size; ++i)
        free(workers[i].steps);    
    free(schedule);
}