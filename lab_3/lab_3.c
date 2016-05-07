#include <stdio.h>
#include <stdlib.h>


int* get_arr(int size)
{
	return (int*)malloc(size*sizeof(int));
}

int* partial_copy(int* arr, int start, int end)
{
	int i;
	int* copy;

	copy = get_arr(end - start);
	for(i=start; i<end; i++)
		copy[i-start] = arr[i];

	return copy;	
}

//merge operation for merge sort. 
//counts number of flips needed to order arrays
int merge_count(int* arr, int start, int mid, int end)
{
	int* left;
	int* right; 
	int p, q, k, count;

	k = 0;
	count = 0;
	p = start;
	q = mid;

	left = partial_copy(arr, start, mid);
	right = partial_copy(arr, mid, end);

	while(p < mid || q < end)
	{
		if(p == mid)
			arr[start + k++] = right[q++ - mid];
		else if(q == end)
			arr[start + k++] = left[p++ - start];
		else if(left[p - start] < right[q - mid])
			arr[start + k++] = left[p++ - start];
		else
		{
			count += mid - p;
			arr[start + k++] = right[q++ - mid];
		}
	}	

	free(left);
	free(right);

	return count;
}

//recursive merge sort.
//counts number of flips needed to merge array.
int merge_sort_count(int* arr, int start, int end)
{
	int left_flips, right_flips, merge_flips;

	if(start >= end - 1)
		return 0;
	
	left_flips = merge_sort_count(arr, start, (start + end)/2);
	right_flips = merge_sort_count(arr, (start + end)/2, end);

	merge_flips = merge_count(arr, start, (start + end)/2, end); 

	return left_flips + right_flips + merge_flips;
}

int main()
{
	int i, size, flips;
	int* arr;

	//reading number of elements
	scanf("%d", &size);

	//getting array
	arr = get_arr(size);
	
	//scanning numbers
	for(i=0; i<size; i++)
		scanf("%d", &arr[i]);

	//getting number of flips
	flips = merge_sort_count(arr, 0, size);
	printf("%d\n", flips);

	free(arr);
	
	return 0;
}
