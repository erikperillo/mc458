/*
Copyright (C) Erik Perillo <erik.perillo@gmail.com> 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF (INT_MAX - 1)
#define min(a, b) (((a) < (b))?a:b)

int* get_int_arr(int size)
{
	return (int*)malloc(size*sizeof(int));
}

int** get_mat_arr(int rows, int cols)
{
	int i;
	int** mat;

	mat = (int**)malloc(rows*sizeof(int*));
	for(i=0; i<rows; i++)	
		mat[i] = get_int_arr(cols);

	return mat;
}

void free_mat(int** mat, int rows)
{
	int i;

	for(i=0; i<rows; i++)
		free(mat[i]);
	free(mat);
}

int sum(int* arr, int size)
{
	int i;
	int result = 0;
	
	for(i=0; i<size; i++)
		result += arr[i];

	return result;
}

/*
void print_mat(int** mat, int rows, int cols)
{
	int i, j;

	for(i=0; i<rows; i++)
	{
		for(j=0; j<cols; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}
*/

/*
gets minimum number of values required to add up to make value.
*/
int min_num_elems(int value, int* values, int size)
{
	int i, j, ret;
	int** nums;

	nums = get_mat_arr(size+1, value+1);

	//initializing values
	for(i=0; i<size+1; i++)
	{
		nums[i][0] = 0;
		for(j=1; j<value+1; j++)
			nums[i][j] = INF;	
	}

	//finding mininum number of values to make value
	for(i=1; i<size+1; i++)
		for(j=1; j<value+1; j++)
		{
			if(values[i-1] > j)
				nums[i][j] = nums[i-1][j];	
			else
				nums[i][j] = min(nums[i-1][j], 1 + nums[i-1][j - values[i-1]]);
		}

	ret = nums[size][value];
	free_mat(nums, size+1);

	return ret;
}

/*
gets minimum number of coins to use to pay at least price.
*/
void min_num_coins(int price, int* values, int size, int* to_pay, int* min_num)
{
	int i, num, max_value;

	max_value = sum(values, size);

	for(i=price; i<=max_value; i++)
	{
		num = min_num_elems(i, values, size);
		if(num < INF)
		{
			*to_pay = i;
			*min_num = num;
			return;
		}	
	}

	*to_pay = 0;
	*min_num = 0;
	return;
}

int main(void)
{
	int i, size, price, min_price, min_num;
	int* values;

	//reading price to pay
	scanf("%d", &price);

	//reading number of elements
	scanf("%d", &size);

	//getting values array
	values = get_int_arr(size);
	for(i=0; i<size; i++)
		scanf("%d", &values[i]);

	//getting minimum number of coins to pay price
	min_num_coins(price, values, size, &min_price, &min_num);
	printf("%d %d\n", min_price, min_num);

	free(values);
	
	return 0;
}
