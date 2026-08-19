/* Pseudocode for the mergesort by Cormen,2° edition
 * THIS PROCEDURE ASSUMES THAT THE TWO SUBARRAYS ARE ALREADY SORTED
 *
 * MERGE(A,p,q,r)
 * n1 <- q-p-1
 * n2 <- r-q
 * creates arrays L[1..n1+1] and R[1..n2+1]
 * for i<- 1 to n1
 * 	do L[i] <- A[p+i-1]
 * for <- j 1 to n2
 * 	do R[j] <-A[q+j]
 * L[n1+1] <- inf
 * R[n2+1] <- inf
 * i <- 1
 * j <- 1 
 * for k <- p to r
 * 	do if L[i]<= R[j]
 * 		then A[k] <- L[i]
 * 			i <- i +1
 * 		else A[k] <- R[j]
 * 			j<-j+1 
 *
 * 					*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void mergesort(int* arr, int begin, int end);
void merge(int *A, size_t p,size_t q,size_t r);

int main(int argc, char**argv){
int A[] =  {2,4,5,7,1,2,3,6};
 size_t p = 0;
 //size_t q = (sizeof(A) / sizeof(A[0])) / 2 - 1;
 size_t q = 3; 
 size_t r = 7;

 printf("p >>> %ld\nq >>> %ld\nr >>> %ld\n",p,q,r);
	return 0;

}

void merge(int* A, size_t p, size_t q, size_t r){

 size_t n1 = q-p+1; 
 size_t n2 = r-q; 

 int L[4]; 
 int R[4]; 
 for(size_t i = 0; i<=n1; i++){
 	L[i] = A[p+i-1];
 }
 for(size_t j = 1; j<=n2; j++){
 	R[j] = A[q+j];
 }
/* CODE COMMENT: It's very important to place a sentinel value at the end
 * of each array. When the sentinel element appears, all non-sentinel
 * elements will have already been placed in the final array... */
L[n1+1] = 100000;
R[n2+1] = 100000;

size_t i = 1;
size_t j = 1; 

for(size_t k = p; k<r; k++){
	if(L[i] <= R[j]){
		A[k] = L[i];
		i++;
	} else {
		A[k] = R[j];
		j++;
		}
	}
}
