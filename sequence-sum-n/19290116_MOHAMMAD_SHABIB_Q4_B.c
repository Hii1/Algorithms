#include <stdio.h>
#include <stdlib.h>


// we need to used a space-time trade-off method to get time effeciency O(n).
// we creat an array with size = k, k -> the magnagtuide between smallest and biggest number
// we check if the sum exist while filling the array, we do this because if we filled and then checked there will be a bug.
// e.x: 2 2 2 4, we fill the array and the result will be there is no sum equal to 4;

// sequence in it.so that I can access array and compare with a value with O(1) time.
// Then I iterate through sequence and  compare with a O(n) time-complexity
// 

// Time effeciency : O(n),  n -> size of array
// Space compelxity: O(k),  k -> the magnagtuide between smallest and biggest number




int check_sum(int *arr,int n, int sum,  int *spaceTradeOffArr, int min)
{
    int remaining = 0;
    if(min < 0)// to use the array from index 0
        min *= 1;// if the min is negative --> ex: min = -5, to fill the arr we use space[min+5]  =  space[0]
    else    
        min *= -1; // same for posstive, ex: min = 2, min --> space[min+-2]  =  space[0]

    int i = 0;

    for(i = 0; i < n; ++i)// O(n)
    {
        remaining = sum - arr[i]; // check if the remaining sum exist in the space array
        if(spaceTradeOffArr[remaining + min] == 1)
            return 1;
        spaceTradeOffArr[arr[i] + min] = 1; // add the found num to the array.
    }
    return 0;
}
int main()
{
	
    int n=0;
	scanf("%d",&n); // how many numbers

    int *arr = (int*) malloc(n*sizeof(int)); // allocating memory

	for(int i=0;i<n;++i)
		scanf("%d",&arr[i]); // array
			
	int sum=0;
	scanf("%d",&sum); // wanted sum
	
	
	//find min and max range in the array.
	int min = arr[0], max=arr[0];
	for(int i=0;i<n;++i) // O(n)
    {
        if(max<arr[i])
			max=arr[i];
        if(min>arr[i])
			min=arr[i];
    }
		
    int *spaceTradeOffArr = (int*) malloc((max-min+1)*sizeof(int));		
    for(int i = 0; i < (max - min + 1); ++i)// O(k)
        spaceTradeOffArr[i] = 0;

	if(check_sum(arr, n, sum, spaceTradeOffArr, min))//O(n)
		printf("YES");
	else
		printf("NO");

    free(spaceTradeOffArr);
}

