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
	struct node *parent;
	struct node *leftChild;
	struct node *rightChild;
}*NODE;
/*在某些资料里，可能没有指向父节点的指针
但是指向父节点的指针能够使操作变得简单，而且使用中都会使用三指针的结构*/

void PrintSortedTree(NODE);	//遍历、打印
NODE FindMin(NODE);	//从树中找最小值
NODE FindMax(NODE);	//从树中找最大值
NODE SearchValue(NODE, int);	//从树中查询一个值
NODE InsertValue(NODE, int);	//往树中插入一个值
int DeleteNode(NODE);	//从树中删除一个值,并且返回这个值
int DeleteLeaf(NODE);	//删除叶节点（被调用）
void InsertNonemptyTree(NODE, NODE);	//向一个非空树中插入节点（被调用）

int main()
{
	NODE root;
	root = NULL;
	NODE node;
	//测试代码:请自己找数据测试……有问题告诉我，这里很乱，但和程序没什么关系
	/*root = InsertValue(root, 18);
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
	node=SearchValue(root, 7);
	printf("%d\n", node->data);
	printf("\n");
	root = InsertValue(root, 0);
	PrintSortedTree(root);
	printf("\n");
	node = SearchValue(root, 4);
	printf("%d\n", DeleteNode(node));
	printf("\n");
	PrintSortedTree(root);*/

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
NODE SearchValue(NODE root, int num) {
	if (root == NULL)	return NULL;

	if (root->data == num)
		return root;
	else if (root->data > num)
		return SearchValue(root->leftChild, num);
	else
		return SearchValue(root->rightChild, num);
}

/*删除节点并返回值。
需要将删除的节点用子节点填补，而子节点可能又需要被填补（多发生在当树只有一边时），所以需要递归到叶节点
填补的节点一般是是左子树中最大的节点（或右子树中最小的点）。
为了利用空间，这里不使用懒惰删除*/
int DeleteNode(NODE node) {
	NODE replace;	//定义一个用来填补的节点
	int data;
	//找到了叶节点
	if (node->leftChild == NULL && node->rightChild == NULL)
		return DeleteLeaf(node);
	//不是叶节点
	else {
		replace = (node->leftChild != NULL) ? FindMax(node->leftChild) : FindMin(node->rightChild);	//如果左子树不空，就找左子树，不然找右子树
		data = node->data;
		node->data = DeleteNode(replace);	//递归到叶节点
		return data;
	}
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

/*我这里用返回值的方法做，如果传入二重指针也是一样的
要求是：插入后的二叉搜索树满足特性*/
NODE InsertValue(NODE root, int data) {
	NODE newNode;
	newNode = (NODE)malloc(sizeof(struct node));
	newNode->data = data;
	newNode->parent = NULL;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	if (root==NULL) {
		root = newNode;
	}
	else {
		InsertNonemptyTree(root, newNode);
	}
	return root;
}

void InsertNonemptyTree(NODE root, NODE newNode) {
	if (newNode->data <= root->data) {
		if (root->leftChild == NULL) {
			newNode->parent = root;
			root->leftChild = newNode;
			return;
		}
		else
			InsertNonemptyTree(root->leftChild, newNode);
	}
	else {
		if (root->rightChild == NULL)
		{
			newNode->parent = root;
			root->rightChild = newNode;
			return;
		}
		else
			InsertNonemptyTree(root->rightChild, newNode);
	}
}