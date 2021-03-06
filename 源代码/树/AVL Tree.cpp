// AVL Tree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
/*AVL树需要我们判断各个节点子树的深度，任意节点子树深度差不超过1*/
typedef struct node {
	int data;
	struct node* leftChild;
	struct node* rightChild;
}*NODE;

NODE Insert(NODE,int);
NODE Find(NODE, int);
void Delete(NODE &, NODE);	//想法是用BST的删除法，每次删除后遍历树找到第一个bf错误的地方，旋转

NODE WhichNodeIsBroken(NODE);

int GetDepth(NODE);
NODE LeftSingleRotation(NODE);
NODE RightSingleRotation(NODE);
NODE LeftDoubleRotation(NODE);
NODE RightDoubleRotation(NODE);

int main()
{
	NODE root = NULL;
	root = Insert(root, 4);
	root = Insert(root, 3);
	for (int i = 5; i < 10; i++)
		root = Insert(root, i);
	Delete(root, Find(root, 2));
	_getch();
	return 0;
}

NODE Insert(NODE root,int data) {
	if (root == NULL)
	{
		NODE newNode = (NODE)malloc(sizeof(struct node));
		newNode->data = data;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		root = newNode;
	}
	else {
		if (data <= root->data) {
			root->leftChild = Insert(root->leftChild, data);
			if ((GetDepth((root)->leftChild) - GetDepth((root)->rightChild))==2) {
				if (data < root->leftChild->data)
					root = LeftSingleRotation(root);
				else
					root = LeftDoubleRotation(root);
			}
		}
		else if (data > root->data) {
			root->rightChild = Insert(root->rightChild, data);
			if ((GetDepth((root)->leftChild) - GetDepth((root)->rightChild)) == -2) {
				if (data > root->rightChild->data)
					root = RightSingleRotation(root);
				else
					root = RightDoubleRotation(root);
			}
		}
	}
	return root;
}

int GetDepth(NODE root) {
	int leftDeepth, rightDeepth;
	if (root == NULL)
		return 0;
	
	leftDeepth = GetDepth(root->leftChild);
	rightDeepth = GetDepth(root->rightChild);
	
	return (leftDeepth > rightDeepth) ? (leftDeepth + 1) : (rightDeepth + 1);
}

NODE LeftSingleRotation(NODE root) {
	NODE temp;
	temp = root->leftChild;
	root->leftChild = temp->rightChild;
	temp->rightChild = root;
	return temp;
}
NODE RightSingleRotation(NODE root) {
	NODE temp;
	temp = root->rightChild;
	root->rightChild = temp->leftChild;
	temp->leftChild = root;
	return temp;
}
NODE LeftDoubleRotation(NODE root) {
	root->leftChild = RightSingleRotation(root->leftChild);
	return LeftSingleRotation(root);
}
NODE RightDoubleRotation(NODE root) {
	root->rightChild = LeftSingleRotation(root->rightChild);
	return RightSingleRotation(root);
}

NODE Find(NODE root, int data) {
	if (root == NULL)
		return NULL;
	if (data < root->data) {
		return Find(root->leftChild, data);
	}
	else if (data > root->data)
		return Find(root->rightChild, data);
	else if (data == root->data)
		return root;
}

void Delete(NODE &root, NODE dNode) {

	NODE broke = WhichNodeIsBroken(root);

}

NODE WhichNodeIsBroken(NODE root) {
	if (root == NULL)
		return NULL;
	if (GetDepth(root->leftChild) - GetDepth(root->rightChild) == 2 || GetDepth(root->leftChild) - GetDepth(root->rightChild) == -2)
	{
		return root;
	}
	return WhichNodeIsBroken(root->leftChild);
	return WhichNodeIsBroken(root->rightChild);
}