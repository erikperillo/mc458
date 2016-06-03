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

void swap_int(int* a, int* b)
{
	int aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

int sum(int* arr, int start, int end)
{
	int i;
	int result = 0.0;
	
	for(i=start; i<end; i++)
		result += arr[i];

	return result;
}

int best(int* arr, int size)
{
	return 1;
}

int main(int argc, char** argv)
{
	int i, size, min_time;
	int* times;

	//getting array size
	scanf("%d", &size);

	//getting array values
	times = get_int_arr(size);
	for(i=0; i<size; i++)
		scanf("%d", &times[i]);

	//getting solution
	min_time = best(times, size);
	printf("%d\n", min_time);

	free(times);
	
	return 0;
}
