/*
Copyright (C) Erik Perillo <erik.perillo@gmail.com> 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define min(a, b) ((a < b)?(a):(b))
//gets random number between inclusive interval [min,max]
#define rng_rand(min, max) (rand() % ((max-min)+1) + min)

int* get_int_arr(int size)
{
	return (int*)malloc(size*sizeof(int));
}

void swap(int* a, int* b)
{
	int aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

//partition function for quicksort
int part(int* arr, int start, int end)
{
	int k;
	int barrier = start;
	int pivot = end - 1;
		
	for(k=start; k<pivot; k++)
		if(arr[k] <= arr[pivot])
			swap(&arr[barrier++], &arr[k]);

	swap(&arr[barrier], &arr[pivot]);

	return barrier;
}

//randomized partition for rand_quicksort
int rand_part(int* arr, int start, int end)
{
	int to_swap;
	int pivot;

	to_swap = rng_rand(start, end-1);
	swap(&arr[to_swap], &arr[end-1]);

	pivot = part(arr, start, end);	

	return pivot;
}

//sorts arr in ascending order
void rand_quicksort(int* arr, int start, int end)
{
	int mid;

	if(end - start < 2)
		return;

	mid = rand_part(arr, start, end);
	rand_quicksort(arr, start, mid);	
	rand_quicksort(arr, mid+1, end);
}

/*
main routine. 
gets the value of best crossing via a greedy choice.
assumes arr is sorted in ascending order.
*/
int _best_crossing(int* arr, int size)
{
	int greedy_best;

	if(size == 0)
		return 0;

	if(size < 3)
		return arr[size-1];

	if(size == 3)
		return arr[0] + arr[1] + arr[2];

	greedy_best = min(2*arr[0] + arr[size-1] + arr[size-2], 
		arr[0] + 2*arr[1] + arr[size-1]);

	return greedy_best + _best_crossing(arr, size-2);
}

//sorts arr and calls _best_crossing. 
int best_crossing(int* arr, int size)
{
	rand_quicksort(arr, 0, size);
	return _best_crossing(arr, size);
}

int main(int argc, char** argv)
{
	int i, size, min_time;
	int* times;

	srand(time(NULL));

	//getting array size
	scanf("%d", &size);

	//getting array values
	times = get_int_arr(size);
	for(i=0; i<size; i++)
		scanf("%d", &times[i]);

	//getting solution
	min_time = best_crossing(times, size);
	printf("%d\n", min_time);

	free(times);
	
	return 0;
}
