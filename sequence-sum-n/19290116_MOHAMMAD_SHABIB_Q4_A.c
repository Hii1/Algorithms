#include <stdio.h>
#include<stdlib.h>

// In order to get time efficiency O(nlogn), we need to sort the array using merge sort or quick sort
// in this code merge sort is being used O(nlogn)
// After sorting we check if there is an equl sum using O(n) time efficiency using 2 pivot (1 in index 0, 1 in index n)

// Time efficiency O(nlogn)
// Space complexity is O(n) (due to mergesort) 

//MergeSort
void merge_sort(int *array,int n)
{	
	if(n<2) return;
	
	int mid=n/2;
	int *left = (int*) malloc(mid*sizeof(int));
	int *right = (int*) malloc((n-mid)*sizeof(int));

	//copy 
	for(int i=0;i<mid;++i)
		left[i]=array[i];
	for(int i=mid;i<n;++i)
		right[i-mid]=array[i];
		
	merge_sort(left,mid);
	merge_sort(right,n-mid);
	
	int li=0,ri=0,i=0;
	for(i=0;li<mid && ri<n-mid;++i){
		if(left[li]<=right[ri]){
			array[i]=left[li];
			++li;
		}
		else {
			array[i]=right[ri];
			++ri;
		}
	}
	if(ri<n-mid){
		for(;ri<n-mid;++ri,++i)
			array[i]=right[ri];
	}
	else if(li<mid){
		for(;li<mid;++li,++i)
			array[i]=left[li];
	}
	free(left);
    free(right);
}

//since its sorted we use 2 pivot and we approach the sum from left and right.
int check_sum(int *arr,int n,int sum)
{	
        int left = 0, right = n - 1;
        while (left < right) {
                if (arr[left] + arr[right] == sum) // if left+right = sum then we are done
                        return 1;
                else if (arr[left] + arr[right] < sum)  // if the sum of the 2 pivot is < sum then we need to move the smaller pivot to the right (left pivot)
                        left++;
                else  // otherwise we move the right pivot  to the left
                        right--;
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

	//Merge sort
	merge_sort(arr,n);


	if(check_sum(arr,n,sum))
		printf("YES");
	else
		printf("NO");
    
    free(arr);
	
	
}

