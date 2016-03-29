#include <stdio.h>
#include <stdlib.h>

typedef struct _sub_array
{
	int start;
	int end;
	float sum;	
} sub_array;

sub_array* get_sub_array(int start, int end, float sum)
{
	sub_array* sub_arr = (sub_array*)malloc(sizeof(sub_array));

	sub_arr->start = start;
	sub_arr->end = end;
	sub_arr->sum = sum;

	return sub_arr;
}

#define circ_incr(i, end) ((i==end-1)?0:(i+1))
#define circ_decr(i, end) ((i>0)?(i-1):(end-1))

//gets the maximum crossing subarray in some array.
//accepts circular crossing subarrays, that is, 
//a crossing subarray such that start > end.
sub_array* max_cross_array(float* array, int start, int mid, int end)
{
	int i, j;
	int mid_next = (mid+1 >= end)?start:(mid+1);
	int max_left=mid, max_right=mid_next;
	float left_sum=array[mid], right_sum=array[mid_next];
	float sum = 0.0;

	//debug
	printf("start=%d, mid=%d, end=%d, next_mid=%d\n", 
		start, mid, end, mid_next);

	//getting maximum left subarray
	for(i=mid; i>=start; i--)
	{
		sum += array[i];
		if(sum >= left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}

	//getting maximum right subarray
	sum = 0.0;
	for(i=mid_next; i<end; i++)
	{
		sum += array[i];
		if(sum > right_sum)
		{
			right_sum = sum;
			max_right = i;
		}	
	}

	//returns a combination of both subarrays
	return get_sub_array(max_left, max_right, left_sum + right_sum);
}

#define max_circ_cross_array(array, start, end) \
	max_cross_array(array, start, end-1, end)

int main()
{
	int i, segm_number;
	float* segm_values;
	char* line;
	sub_array* sub_arr;

	//reading number of segments
	scanf("%d", &segm_number);

	//reading values of segments
	segm_values = (float*)malloc(segm_number*sizeof(float));
	for(i=0; i<segm_number; i++)
		scanf("%f", &segm_values[i]);

	sub_arr = max_cross_array(segm_values, 0, segm_number/2, segm_number);
	printf("max_left=%d, max_right=%d, sum=%f\n",
		sub_arr->start, sub_arr->end, sub_arr->sum);

	free(sub_arr);
	printf("circular:\n");

	sub_arr = max_circ_cross_array(segm_values, 0, segm_number);
	printf("max_left=%d, max_right=%d, sum=%f\n",
		sub_arr->start, sub_arr->end, sub_arr->sum);

	//desallocating memory
	free(segm_values);
	free(sub_arr);

	return 0;
}
