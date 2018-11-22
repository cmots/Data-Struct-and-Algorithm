// Sort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

#include <cstdlib>
#include <iostream>

void QuickSort(int*, int left, int right);	//这里采用比较基本的方法，但是入口要一直传递大数组
void MergeSort(int*, int left, int right);
void Swap(int &, int &);

int main()
{
	int arr[10] = { 3,1,6,4,5,9,5,10,7,2};
	//QuickSort(arr, 0, 9);
	MergeSort(arr, 0, 9);
	for (int i = 0; i < 10; i++) {
		std::cout << arr[i] << std::endl;
	}
}

void QuickSort(int* arr, int left, int right) {
	if (right - left < 1)
		return;
	int max = right;
	int pivot = left;
	if (arr[left] > arr[right])
		arr[(int)(right - left)/2] > arr[left] ? pivot = left: arr[(int)(right - left)/2] > arr[right] ? pivot = (int)(right - left)/2 : pivot = right;
	else
		arr[(int)(right - left)/2] > arr[right] ? pivot = right : arr[(int)(right - left)/2] > arr[left] ? pivot = (int)(right - left)/2 : pivot = left;
	Swap(arr[right], arr[pivot]);
	pivot = right;
	right--;
	while (left < right) {
		while (arr[left] < arr[pivot] && left < right)
			left++;
		while (arr[right] > arr[pivot] && right > left && right >= 0)
			right--;
		Swap(arr[left], arr[right]);
	}
	Swap(arr[left], arr[pivot]);
	QuickSort(arr, 0, left - 1);
	QuickSort(arr, left + 1, max);
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