// Tree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<queue>//这个头文件保存了你需要用的队列操作
#include<stack>//这个头文件保存了你需要用的栈操作
#include<iostream>

using namespace std;

typedef struct node {
	int data;
	struct node *leftChild;
	struct node *rightChild;
}*NODE;
/*插入删除就不想写了，三种遍历的非递归还是有点东西的，算法我写在笔记里了*/
/*有关于树的基本操作，三种遍历,递归实现*/
void PreOrderTraverse(NODE);
void InOrderTraverse(NODE);
void PostOrderTraverse(NODE);
//非递归实现
void _PreOrderTraverse(NODE);
void _InOrderTraverse(NODE);
void _PostOrderTraverse(NODE);
//层序遍历直接调用了头文件queue(不想写队列)，注意queue是存在于std空间中的
void SeqOrderTraverse(NODE);//不知道层序是哪个词

int main()
{
	
    return 0;
}

//下面是递归实现，比较简单
void PreOrderTraverse(NODE root) {
	if (root == NULL )
		return;
	printf("%d", root->data);
	PreOrderTraverse(root->leftChild);
	PreOrderTraverse(root->rightChild);
}
void InOrderTraverse(NODE root) {
	if (root == NULL)
		return;
	InOrderTraverse(root->leftChild);
	printf("%d", root->data);
	InOrderTraverse(root->rightChild);
}
void PostOrderTraverse(NODE root) {
	if (root == NULL)
		return;
	PostOrderTraverse(root->leftChild);
	PostOrderTraverse(root->rightChild);
	printf("%d", root->data);
}
/*----------------------------------------------------------*/
/*如果使用非递归实现，我们就要模拟递归的过程：用栈保存函数调用结果*/
void _PreOrderTraverse(NODE root) {
	stack<NODE> s;
	NODE p = root;
	while (p != NULL || !s.empty()) {
		while (p != NULL) {
			printf("%d", p->data);
			s.push(p);
			p = p->leftChild;
		}
		if (!s.empty()) {
			p = s.top();
			s.pop();
			p = p->rightChild;
		}
	}
}
void _InOrderTraverse(NODE root) {
	stack<NODE> s;
	NODE p = root;
	while (p != NULL || !s.empty) {
		while (p != NULL) {
			s.push(p);
			p = p->leftChild;
		}
		if (!s.empty) {
			p = s.top();
			printf("%d", p->data);
			s.pop();
			p = p->rightChild;
		}
	}
}
void _PostOrderTraverse(NODE root) {
	stack<NODE> s;
	NODE cur = NULL;
	NODE pre = NULL;
	s.push(root);
	while (!s.empty()) {
		cur = s.top();
		if ((cur->leftChild == NULL && cur->rightChild == NULL) || (pre != NULL && (pre == cur->leftChild || pre == cur->rightChild))) {
			//没有子节点或者子节点都已经被访问过
			printf("%d", cur->data);
			s.pop();
			pre = cur;
		}
		else {
			if (cur->rightChild != NULL)
				s.push(cur->rightChild);
			if (cur->leftChild != NULL)
				s.push(cur->leftChild);
		}
	}
}
//层序
void SeqOrderTraverse(NODE root) {
	if (root == NULL)
		return;
	queue<NODE> q;
	q.push(root);
	NODE p = NULL;
	while (!q.empty()) {
		p = q.front();
		printf("%d", p->data);
		q.pop();
		if (p->leftChild != NULL)
			q.push(p->leftChild);
		if (p->rightChild != NULL)
			q.push(p->rightChild);
	}
}