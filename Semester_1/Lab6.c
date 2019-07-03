#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

void q_sort(int *a, int left, int right)
{
	int mid;
	int i = left;
	int j = right;
		
	mid = (i + j) / 2;

	do{
		while (a[i] < a[mid]) {
			i++;
		}
		while (a[j] > a[mid]) {
			j--;
		}
		if (i <= j) {
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;

			i++;
			j--;
		}
	} while (i < j);

	if (left <= j) q_sort(a, left, j);
	if (i <= right) q_sort(a, i, right);
}

int main() 
{
	int n;
	int *a;

	scanf("%d", &n);
	
	if (n <= 0) {
		exit(0);
	}

	a = (int*)malloc(n * sizeof(int));
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	q_sort(a, 0, n-1);

	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	
	free(a);

	return 0;
}
	
