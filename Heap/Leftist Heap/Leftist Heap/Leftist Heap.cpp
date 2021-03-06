// Leftist Heap.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef node Node;

typedef struct node {
	Node *left;
	Node *right;
	int npl;
	int data;
}*NODE;

//这个是把一个空左倾堆与非空左倾堆合并
NODE Insert(int, NODE);
NODE Merge(NODE, NODE);
NODE _Merge(NODE, NODE);
void swap(NODE);
int main()
{
    return 0;
}

//这个是把一个空左倾堆与非空左倾堆合并
NODE Insert(int value, NODE heap) {
	NODE newNode = (NODE)malloc(sizeof(Node));
	newNode->data = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return Merge(newNode, heap);
}

NODE Merge(NODE h1, NODE h2) {
	if (h1 == NULL)
		return h2;
	if (h2 == NULL)
		return h1;

	if (h1->data < h2->data)
		return _Merge(h1, h2);
	else
		return _Merge(h2, h1);
}

NODE _Merge(NODE h1, NODE h2) {
	if (h1->left == NULL)
		h1->right = h2;
	else
	{
		h1->right = Merge(h1->right, h2);
		if (h1->left->npl < h1->right->npl)
			swap(h1);
		h1->npl = h1->right->npl + 1;
	}
	return h1;
}

void swap(NODE h) {
	NODE temp = h->left;
	h->left = h->right;
	h->right = temp;
}