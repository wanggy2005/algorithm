#include<stdio.h>
void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}
//—°‘Ò≈≈–Ú
void selectionsort(int* a, int length) {
	if (a == nullptr || length < 2)	return;
	for (int i = 0; i < length; i++) {
		int min_index = i;
		for (int j = i + 1; j < length; j++) {
			if (a[j] < a[min_index]) {
				min_index = j;
			}
		}
		if (min_index != i) {
			swap(a[i], a[min_index]);
		}
		if (min_index != i)	swap(a[i], a[min_index]);
	}
}
//√∞≈›≈≈–Ú
void bubblesort(int* a, int length) {
	if (a == nullptr || length < 2) return;
	for (int i = 0; i < length - 1; i++) {
		bool swapped = false;
		for (int j = 0; j < length - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
}
//≤Â»Î≈≈–Ú
void insertionsort(int* a, int length) {
	if (a == nullptr || length < 2) return;
	for (int i = 1; i < length; i++) {
		int key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}
