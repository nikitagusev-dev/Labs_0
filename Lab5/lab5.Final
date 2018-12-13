#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

void swap(int *c, int *b)
{
	int temp;

	temp = *c;
	*c = *b;
	*b = temp;
}

void heapDown(int *arr, int current, int N)
{
	int left;
	int right;
	int min;

	while (current < N)
	{
		min = current;
		left = 2 * current + 1;
		right = 2 * current + 2;

		if ((left < N) && (arr[min] > arr[left]))
		{
			min = left;
		}

		if ((right < N) && (arr[min] > arr[right]))
		{
			min = right;
		}

		if (min != current) 
		{
			swap(&arr[current], &arr[min]);
			current = min;
		}
		else break;
	}
}

void heapUp(int *arr, int N)
{
	int mid = N / 2 - 1;
	while (mid >= 0)
	{
		heapDown(arr, mid, N);
		mid--;
	}
}

void heapSort(int *arr, int N)
{
	heapUp(arr, N);

	while (N > 1)
	{
		swap(&arr[0], &arr[N - 1]);
		N--;
		heapDown(arr, 0, N);
	}
}

int main()
{
	int *arr;
	int N;

	scanf("%d", &N);

	arr = (int*)malloc(N * sizeof(int));

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &arr[i]);
	}

	heapSort(a, N);

	for (int i = N - 1; i >= 0; i--)
	{
		printf("%d ", arr[i]);
	}

	free(arr);

	return 0;
}

