#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX_SIZE 100

//This type of matrices is called 'Hadamard matrices' 
// if we  see when the size of the matrix is 2, then result = [(v1+v2), v1-v2)]
// we can divide the matrix into 2 matrices n/2 of size, and apply the same ideal when the size is 2 (same as strassen matrix multiplication)
// the base point is when  n = 1, k = 0;
//there is no need to find the Hadamard matrix since H0 = [1], IF H0 was different from 1 then we have had to make some changes

//(Hkv)1 = Hk−1v1 +Hk−1v2 = Hk−1(v1 +v2), v1 = the first half of the vector, v2, is the second half of the vector
//and
//(Hkv)2 = Hk−1v1 −Hk−1v2 = Hk−1(v1 −v2)


//Tn() = 2T(n/2) + n
//case 2: thus O(nlogn)
//Time efficiency  = O(nlogn)


void  hadamard_matrix(int **A_array,int k);

void  find_A_v(int **A_array, int *vec, int k, int* result)
{
    if(k == 0)//base, when the algorithm will stop.
        return;

    int i = 0, j = 0, l = 0, m = 0;
    int n = pow(2,k),  middle = pow(2, k-1);

    //the 2 for loops are o(n)
    for(i = j; i < middle; ++i)//finding the sum, (Hkv)1 = Hk−1v1 +Hk−1v2 = Hk−1(v1 +v2)
        result[i] = vec[i] + vec[i+middle];
    for(i = middle+j; i < n; ++i)//finding the subtraction, (Hkv)2 = Hk−1v1 −Hk−1v2 = Hk−1(v1 −v2)
        result[i] = vec[i-middle] - vec[i];

    //O(n)
    for(i = 0; i < n; ++i)// copying the result to vec, to use it in the next fucntion call.
        vec[i] = result[i];
    
    find_A_v(A_array, vec, k-1, result);
    find_A_v(A_array, vec+middle, k-1, result+middle);

    //Tn() = 2T(n/2) + n
    //case 2: thus O(nlogn)

}
int main()
{
    int vec[MAX_SIZE] = {0};
    int i = 0, j = 0;
    while(scanf("%d", vec + i++) != EOF);// input
    int n = --i; // size of the matrix
    int k = log2(n); // finding k

    int **A_Array = (int**) malloc(n*sizeof(int*)); //  memory allocation
    for(i = 0; i  < n; ++i)
        A_Array[i] = (int*) malloc(n*sizeof(int));


    int *result = (int*) malloc(n*sizeof(int));


   /* hadamard_matrix(A_Array, k);// O(n^2) we  dont use it

    for(i = 0; i < n ; ++i)// printing the Hadamard matrix
    {
        for(j = 0; j < n; ++j)
           printf("%d ", A_Array[i][j]);
        printf("\n");

    }*/

    // finding the Muliplication result
    find_A_v(A_Array, vec, k, result);  // O(nlogn)

    for(i = 0; i < n ; ++i) //O(n)
        printf("%d\n", result[i]);
  
    for(i = 0; i  < n; ++i) // deallocate the memory
       free( A_Array[i]);
    free(A_Array);
    free(result);


}


//O(n^2) but we dont use it in our code, so the efficiency will stay the same O(nlogn)
void  hadamard_matrix(int **A_array,int k)
{
    if(k == 0)//stop when K = 0 and H0 = 1
    {
        A_array[0][0] = 1;
        return;
    }
        
    hadamard_matrix(A_array, k-1);// recursive call

    int i = 0, j = 0, l = 0, m = 0;
    int n = pow(2,k),  middle = pow(2, k-1);


    for(i = 0, l = 0; i < middle ; ++i, ++l)//filling the first part H0
        for(j = 0, m = 0; j < middle; ++j, ++m)
            A_array[i][j] = A_array[l][m];

          

    for(i = middle, l = 0; i < n ; ++i, ++l)//filling the SECOND part H1
        for(j = 0, m = 0; j < middle; ++j, ++m)          
            A_array[i][j] = A_array[l][m];

            
 
   for(i = 0, l = 0; i < middle ; ++i, ++l)//filling the THIRD part H2
        for(j = middle, m = 0; j < n; ++j, ++m)
            A_array[i][j] = A_array[l][m];
            
    for(i = middle, l = 0; i < n ; ++i, ++l)// //filling the LAST  part H3
        for(j = middle, m = 0; j < n; ++j, ++m)
            A_array[i][j] = -1*A_array[l][m];    

}