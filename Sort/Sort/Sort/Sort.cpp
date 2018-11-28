// Sort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

#include <stdlib.h>
#include <iostream>

void BubbleSort(int *, int size);
void InsertSort(int*, int size);
void SelectionSort(int*, int size);
void QuickSort(int*, int left, int right);	//这里采用比较基本的方法，但是入口要一直传递大数组
void MergeSort(int*, int left, int right);
void Swap(int &, int &);

int main()
{
	int arr[10] = { 3,1,6,4,5,9,5,10,7,2 };
	//BubbleSort(arr, 9);
	//InsertSort(arr, 9);
	//SelectionSort(arr, 9);
	//QuickSort(arr, 0, 9);
	//MergeSort(arr, 0, 9);
	for (int i = 0; i < 10; i++) {
		std::cout << arr[i] << std::endl;
	}
}

void BubbleSort(int *arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i; j++)
			if (arr[j] > arr[j + 1])
				Swap(arr[j], arr[j + 1]);
	}
}

void InsertSort(int *arr, int size) {
	for (int i = 1; i <= size; i++) {
		int j;
		int temp = arr[i];
		for (j = i ; j > 0 && arr[j-1] >= temp; j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = temp;
	}
}

void SelectionSort(int *arr, int size) {
	for (int i = 1; i < size; i++) {
		if (arr[i] < arr[0])
			Swap(arr[i], arr[0]);
	}
	for (int i = 1; i < size; i++) {
		for (int j = i + 1; j <= size; j++) {
			if (arr[j] < arr[i])
				Swap(arr[i], arr[j]);
		}
	}
}

void QuickSort(int* arr, int left, int right) {
	if (right - left < 1)
		return;
	int min = left;
	int max = right;
	int pivot = left;
	int center = (right + left) / 2;
	if (arr[left] > arr[center])
		Swap(arr[left], arr[center]);
	if (arr[left] > arr[right])
		Swap(arr[left], arr[right]);
	if (arr[center] > arr[right])
		Swap(arr[center], arr[right]);
	Swap(arr[center], arr[max - 1]);
	pivot = max - 1;
	right -= 2;
	while (left < right) {
		while (arr[left] < arr[pivot] && left < right)
			left++;
		while (arr[right] > arr[pivot] && right > left && right >= 0)
			right--;
		Swap(arr[left], arr[right]);
	}
	if (arr[left] > arr[pivot])
	{
		Swap(arr[left], arr[pivot]);
		pivot = left;
	}
	QuickSort(arr, min, pivot - 1);
	QuickSort(arr, pivot + 1, max);
}

void MergeSort(int* arr, int left, int right) {
	if (right == left)
		return;
	int mid = (right + left - 1) / 2;
	MergeSort(arr, left, mid);
	MergeSort(arr, mid + 1, right);

	int* temp = new int[right - left + 1];

	int i = left, j = mid + 1;
	int n = 0;
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j])
			temp[n++] = arr[i++];
		else
			temp[n++] = arr[j++];
	}
	while (i<=mid)
		temp[n++] = arr[i++];
	while (j <= right)
		temp[n++] = arr[j++];
	for (int i = 0; i < n; i++)
		arr[i + left] = temp[i];
	delete[] temp;
}


void Swap(int &a, int &b) {
	if (a == b)
		return;
	int temp = a;
	a = b;
	b = temp;
}