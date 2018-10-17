// Binary Search Tree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*
二叉搜索树是一种二叉树，它的特性是：
左子节点比根节点小，右子节点比根节点大
*/

typedef struct node {
	int data;	
	struct node *parent;
	struct node *leftChild;
	struct node *rightChild;
}*NODE;
/*在某些资料里，可能没有指向父节点的指针
但是指向父节点的指针能够使操作变得简单，而且使用中都会使用三指针的结构*/

void PrintSortedTree(NODE);	//遍历、打印
NODE FindMin(NODE);	//从树中找最小值
NODE FinMax(NODE);	//从树中找最大值
NODE SearchValue(NODE, int);	//从树中查询一个值
NODE InsertValue(NODE, int);	//往树中插入一个值
int DeleteNode(NODE);	//从树中删除一个值,并且返回这个值
int DeleteLeaf(NODE);	//删除叶节点

int main()
{
	NODE head;
	head = (NODE)malloc(sizeof(NODE));
	_getch();
    return 0;
}

/*递归，不断将树拆分成两个子树*/
void PrintSortedTree(NODE head) {
	if (head == NULL)
		return;
	PrintSortedTree(head->leftChild);
	printf("%d \n", head->data);
	PrintSortedTree(head->rightChild);
}

/*因为二叉搜索树的性质，最小值只会在左子树里*/
NODE FindMin(NODE head) {
	NODE min;
	min = head;
	if (min == NULL)	return NULL;
	while (min->leftChild != NULL)
		min = min->leftChild;
	return min;
}

/*同理，最大值在右子树里*/
NODE FindMax(NODE head) {
	NODE max;
	max = head;
	if (max == NULL)	return NULL;
	while (max->rightChild != NULL)
		max = max->rightChild;
	return max;
}

/*一般我们会通过搜索某个特征值(比如ID)找到节点然后得到这个节点内的其他值。
利用二叉搜索树的性质去寻找值，对于深度为n的树，时间复杂度为：
平衡：O(Log2n)
完全不平衡：O(n)*/
NODE SearchValue(NODE head, int num) {
	if (head == NULL)	return NULL;

	if (head->data == num)
		return head;
	else if (head->data > num)
		return SearchValue(head->leftChild, num);
	else
		return SearchValue(head->rightChild, num);
}

/*删除节点并返回值。
需要将删除的节点用子节点填补，而子节点又需要被填补，所以需要递归到叶节点
为了利用空间，这里不使用懒惰删除*/
int DeleteNode(NODE head) {

	if (head->leftChild == NULL && head->rightChild == NULL)
		return DeleteLeaf(head);
}

/*叶节点可以直接删除，对二叉树结构没有任何影响*/
int DeleteLeaf(NODE node) {
	int data = node->data;
	if (node->parent != NULL) {			//不是根节点
		if (node->parent->leftChild == node)
			node->parent->leftChild = NULL;
		else
			node->parent->rightChild = NULL;
	}
	free(node);
	return data;
}