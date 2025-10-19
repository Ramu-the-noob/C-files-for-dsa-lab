#include <stdio.h>

int main() {
	int arr[] = { 1, 2, 3, 4, 5 ,6,7,8,9};
	int size = sizeof(arr) / sizeof(arr[0]);
	int ans = binsearch(arr,size,4);
	printf("Element found at index: %d\n", ans);
	return 0;
}

int binsearch(int arr[],int size, int x) {
	int low = arr[0];
	int high = arr[size-1];
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < arr[mid]) {
			high = mid - 1;
		} else if (x > arr[mid]) {
			low = mid + 1;
		} else {
			return mid;
		}
	}
	printf("Element not found\n");
	return -1;
}
