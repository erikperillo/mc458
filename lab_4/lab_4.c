/*
Copyright (C) Erik Perillo <erik.perillo@gmail.com> 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RND_MIN -1000
#define RND_MAX 1000
//gets random number between inclusive interval [min,max]
#define rng_rand(min, max) (rand() % ((max-min)+1) + min)

int* get_int_arr(int size)
{
	return (int*)malloc(size*sizeof(int));
}

float* get_float_arr(int size)
{
	return (float*)malloc(size*sizeof(float));
}

void swap_int(int* a, int* b)
{
	int aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

void swap_float(float* a, float* b)
{
	float aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

float sum(float* arr, int start, int end)
{
	int i;
	float result = 0.0;
	
	for(i=start; i<end; i++)
		result += arr[i];

	return result;
}

/*
partitions array choosing a random pivot.
*/
int partition(int* arr, float* farr, int start, int end)
{
	int k;
	int barrier = start;
	int rand_idx, pivot = end - 1;

	rand_idx = rng_rand(start, end-1);
	swap_int(&arr[rand_idx], &arr[pivot]);
	swap_float(&farr[rand_idx], &farr[pivot]);
		
	for(k=start; k<pivot; k++)
		if(arr[k] <= arr[pivot])
		{
			swap_int(&arr[barrier++], &arr[k]);
			swap_float(&farr[barrier-1], &farr[k]);
		}

	swap_int(&arr[barrier], &arr[pivot]);
	swap_float(&farr[barrier], &farr[pivot]);

	return barrier;
}

/*
main algorithm. 
let ws be the sum of weights.
selects position x such that:
	-the sum off all w respectives to x' less than x is less than ws/2.
	-the sum off all w respectives to x' greater than x is less than or equal 
		to ws/2.
*/
int _w_median(int* xs, float* ws, int start, int end, 
	float left_w_sum_acc, float right_w_sum_acc)
{
	int pivot;
	float left_w_sum, right_w_sum, tot_w_sum;

	if(end - start <= 1)	
		return xs[start];

	pivot = partition(xs, ws, start, end);	
	
	left_w_sum = sum(ws, start, pivot) + left_w_sum_acc;
	right_w_sum = sum(ws, pivot+1, end) + right_w_sum_acc;
	tot_w_sum = left_w_sum + ws[pivot] + right_w_sum;

	if(left_w_sum >= tot_w_sum/2.0)
		return _w_median(xs, ws, start, pivot, 
			left_w_sum_acc, right_w_sum + ws[pivot]);

	if(right_w_sum > tot_w_sum/2.0)
		return _w_median(xs, ws, pivot+1, end, 
			left_w_sum + ws[pivot], right_w_sum_acc);

	return xs[pivot];
}

//macro for providing arguments for first iteration
#define w_median(xs, ws, size) _w_median(xs, ws, 0, size, 0.0, 0.0)

int main(int argc, char** argv)
{
	int i, size, best;
	int* positions;
	float* weights;

	srand(time(NULL));

	//random array 
	if(argc > 1)
	{	
		size = atoi(argv[1]);

		positions = get_int_arr(size);
		weights = get_float_arr(size);

		for(i=0; i<size; i++)
		{
			positions[i] = rng_rand(RND_MIN, RND_MAX);
			weights[i] = 0.001*(float)rng_rand(RND_MIN, RND_MAX);
		}
	}
	else
	//array from input
	{
		//reading number of elements
		scanf("%d", &size);

		//getting positions array
		positions = get_int_arr(size);
		for(i=0; i<size; i++)
			scanf("%d", &positions[i]);

		//getting weights array
		weights = get_float_arr(size);
		for(i=0; i<size; i++)
			scanf("%f", &weights[i]);
	}

	best = w_median(positions, weights, size);	
	printf("%d\n", best);

	free(positions);
	free(weights);
	
	return 0;
}
