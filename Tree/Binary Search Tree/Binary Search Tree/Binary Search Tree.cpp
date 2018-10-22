// Binary Search Tree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*
二叉搜索树是一种二叉树，它的特性是：
左子树每个元素都比根节点小，右子树每个元素都比根节点大
*/

typedef struct node {
	int data;	
	struct node *leftChild;
	struct node *rightChild;
}*NODE;
/*在某些资料里，可能有指向父节点的指针
使用指向父节点的指针能够使操作变得简单*/

void PrintSortedTree(NODE);	//遍历、打印
NODE FindMin(NODE);	//从树中找最小值
NODE FindMax(NODE);	//从树中找最大值
NODE Find(NODE, int);	//从树中查询一个值
NODE InsertValue(NODE, int);	//往树中插入一个值
int DeleteNode(NODE,int);	//从树中删除一个值,并且返回这个值
NODE _DeleteNode(NODE, int);	//常规二叉树的删除操作

int main()
{
	NODE root;
	root = NULL;
	NODE node;
	//测试代码:请自己找数据测试……有问题告诉我，这里很乱，但和程序没什么关系
	root = InsertValue(root, 18);
	root = InsertValue(root, 46);
	root = InsertValue(root, 14);
	root = InsertValue(root, 7);
	root = InsertValue(root, 22);
	root = InsertValue(root, 13);
	root = InsertValue(root, 45);
	root = InsertValue(root, 4);
	PrintSortedTree(root);
	printf("\n");
	node=FindMin(root);
	printf("%d\n", node->data);
	printf("\n");
	node=FindMax(root);
	printf("%d\n", node->data);
	printf("\n");
	node=Find(root, 7);
	printf("%d\n", node->data);
	printf("\n");
	root = InsertValue(root, 0);
	PrintSortedTree(root);
	printf("\n");
	printf("%d\n", DeleteNode(root,4));
	printf("\n");
	PrintSortedTree(root);

	_getch();	//这个在这里的作用就是windows("pause")
    return 0;
}

/*递归，不断将树拆分成两个子树*/
void PrintSortedTree(NODE root) {
	if (root == NULL)
		return;
	PrintSortedTree(root->leftChild);
	printf("%d \n", root->data);
	PrintSortedTree(root->rightChild);
}

/*因为二叉搜索树的性质，最小值只会在左子树里*/
NODE FindMin(NODE root) {
	NODE min;
	min = root;
	if (min == NULL)	return NULL;
	while (min->leftChild != NULL)
		min = min->leftChild;
	return min;
}

/*同理，最大值在右子树里*/
NODE FindMax(NODE root) {
	NODE max;
	max = root;
	if (max == NULL)	return NULL;
	while (max->rightChild != NULL)
		max = max->rightChild;
	return max;
}

/*一般我们会通过搜索某个特征值(比如ID)找到节点然后得到这个节点内的其他值。
利用二叉搜索树的性质去寻找值，对于深度为n的树，时间复杂度为：
平衡：O(Log2n)
完全不平衡：O(n)*/
NODE Find(NODE root, int data) {
	if (root == NULL)
		return NULL;
	if (root->data == data)
		return root;
	else if (root->data > data)
		return Find(root->leftChild, data);
	else if (root->data < data)
		return Find(root->rightChild, data);
}

/*删除节点并返回值。
因为结构体中没有使用父节点，所以删除使用迭代更简单
需要将删除的节点用子节点填补，而子节点可能又需要被填补（多发生在当树只有一边时），所以需要递归到叶节点
填补的节点一般是是左子树中最大的节点（或右子树中最小的点）。
为了利用空间，这里不使用懒惰删除*/
int DeleteNode(NODE root,int data) {
	NODE position = Find(root, data);
	NODE replace = FindMax(root->leftChild);

}

//常规二叉树的删除
NODE _DeleteNode(NODE root, int data) {
	if (root->data == data)
		return NULL;
	else {
		if (root->rightChild == NULL) {
			return root->leftChild;
		}
		else {
			NODE cur;
			while (cur->leftChild != NULL)
				cur = cur->leftChild;
			int temp = cur->data;
			cur->data = root->data;
			root->data = temp;
		}
	}
	root->leftChild = _DeleteNode(root->leftChild, data);
	root->rightChild = _DeleteNode(root->rightChild, data);
}

/*我这里用返回值的方法做，如果传入二重指针也是一样的
要求是：插入后的二叉搜索树满足特性*/
NODE InsertValue(NODE root, int data) {
	if (root == NULL) {
		NODE newNode;
		newNode = (NODE)malloc(sizeof(struct node));
		newNode->data = data;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		root = newNode;
	}
	else if (root->data > data)
		root->leftChild = InsertValue(root->leftChild, data);
	else if (root->data < data)
		root->rightChild = InsertValue(root->rightChild, data);
	return root;
}
