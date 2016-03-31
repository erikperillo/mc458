#include <stdio.h>
#include <stdlib.h>

//boolean types
typedef enum _bool {false, true} bool;

//gets distance of path
#define norm_dist(arr) (arr->end - arr->start)

//gets cycled distance of path
#define cyc_dist(arr, size) (size + norm_dist(arr))

//gets better path between a and b
#define best_seq(a, dist_a, b, dist_b) \
	((a->sum > b->sum)?a:(\
		(b->sum > a->sum)?b:(\
			(a->start < b->start)?a:(\
				(b->start < a->start)?b:(\
					(dist_a < dist_b)?a:(\
						b))))))

//structure for representing sub arrays
typedef struct _sub_array
{
	int start;
	int end;
	int sum;	
} sub_array;

sub_array* get_sub_array(int start, int end, int sum)
{
	sub_array* sub_arr = (sub_array*)malloc(sizeof(sub_array));

	sub_arr->start = start;
	sub_arr->end = end;
	sub_arr->sum = sum;

	return sub_arr;
}

sub_array* copy_sub_array(sub_array* sub_arr)
{
	return get_sub_array(sub_arr->start, sub_arr->end, sub_arr->sum);
}

void invert(int* array, int size)
{
	int i;
	
	for(i=0; i<size; i++)
		array[i] = -array[i];
}

int sum(int* array, int size)
{
	int i, result = 0;

	for(i=0; i<size; i++)
		result += array[i];

	return result;
}

void swap(int* a, int* b)
{
	int aux;

	aux = *a;
	*a = *b;
	*b = aux;	
}

/*
gets circular equivalent of some array.
*/
void cycle(sub_array* sub_arr, int* array, int size)
{
	swap(&sub_arr->start, &sub_arr->end);
	sub_arr->sum = -sum(array, size) + sub_arr->sum;
}

/*
gets the maximum crossing subarray in some array.
accepts circular crossing subarrays, that is, 
a crossing subarray such that start > end.
*/
sub_array* max_cross_array(int* array, int start, int end)
{
	int i;
	int mid = (start + end)/2 - 1;
	int max_left = mid;
	int max_right = mid+1;
	int left_sum = array[max_left];
	int right_sum = array[max_right];
	int sum;

	//getting maximum left subarray
	sum = left_sum;
	for(i=max_left-1; i>=start; i--)
	{
		sum += array[i];
		if(sum >= left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}

	//getting maximum right subarray
	sum = right_sum;
	for(i=max_right+1; i<end; i++)
	{
		sum += array[i];
		if(sum > right_sum)
		{
			right_sum = sum;
			max_right = i;
		}	
	}

	//result is a combination of two subarrays
	return get_sub_array(max_left, max_right+1, left_sum+right_sum);
}

/* 
computes maximum subarray in some array.
returns the start, end and sum of such array.
chooses subarray so as to be the smallest one that starts on the 
smallest index and has smallest path.
*/
sub_array* max_sub_array(int* array, int start, int end)
{
	sub_array *left, *right, *cross, *best;

	//base case
	if(start+1 >= end)
		return get_sub_array(start, end, array[start]);

	//recursively calculating left and right maximum subarrays
	left = max_sub_array(array, start, (start+end)/2);
	right = max_sub_array(array, (start+end)/2, end);
	//computing for case of crossing subarray
	cross = max_cross_array(array, start, end);

	//finding best subarray among three cases
	best = best_seq(left, norm_dist(left), cross, norm_dist(cross));
	best = best_seq(best, norm_dist(best), right, norm_dist(right));
	best = copy_sub_array(best);

	free(left);
	free(cross);
	free(right);
	
	return best;
}

/*
gets the best path for the scavenger problem.
this function also considers the circular case where start >= end.
*/
sub_array* best_path(int* array, int size)
{
	sub_array *norm_path, *cyc_path, *best_path; 

	//normal best path calculation
	norm_path = max_sub_array(array, 0, size);

	//circular best path calculation
	invert(array, size);
	cyc_path = max_sub_array(array, 1, size-1);
	cycle(cyc_path, array, size);

	//getting best path from two options
	best_path = best_seq(norm_path, norm_dist(norm_path),
		cyc_path, cyc_dist(cyc_path, size));

	//checks if it is better not to go through any path
	if(best_path->sum > 0)
		best_path = copy_sub_array(best_path);
	else
		best_path = get_sub_array(-1, 0, 0);

	free(norm_path);
	free(cyc_path);

	return best_path;	
}

int main()
{
	int i, segm_number;
	int* segm_values;
	sub_array* path;

	//reading number of segments
	scanf("%d", &segm_number);

	//reading values of segments
	segm_values = (int*)malloc(segm_number*sizeof(int));
	for(i=0; i<segm_number; i++)
		scanf("%d", &segm_values[i]);

	//getting best path
	path = best_path(segm_values, segm_number);

	printf("%d %d %d\n", path->start+1, path->end, path->sum);

	free(segm_values);
	free(path);
	
	return 0;
}
