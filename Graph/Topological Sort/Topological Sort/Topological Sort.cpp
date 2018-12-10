// Topological Sort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include<queue>
#define MAXNUM 4

using namespace std;

typedef struct Node {
	int value;
	struct Node *next;
}NODE;

void InsertEdge(NODE graph[MAXNUM], int from, int to);
void TopologicalSort(NODE* graph);
void Update(NODE* graph,queue<int>&queue,int indegree[MAXNUM]);

int main()
{
	struct Node graph[MAXNUM];

	for (int i = 0; i < MAXNUM; i++) {
		graph[i].value = i;
		graph[i].next = NULL;
	}

	InsertEdge(graph, 0, 1);
	InsertEdge(graph, 0, 3);
	InsertEdge(graph, 2, 1);
	InsertEdge(graph, 3, 1);
	InsertEdge(graph, 3, 2);

	TopologicalSort(graph);
}


void InsertEdge(NODE graph[MAXNUM], int from, int to) {
	NODE *newNode = (NODE*)malloc(sizeof(NODE));
	newNode->value = to;
	newNode->next = NULL;
	if (graph[from].next == NULL)
		graph[from].next = newNode;
	else {
		NODE* position = graph[from].next;
		while (position->next != NULL)
			position = position->next;
		position->next = newNode;
	}
}

void TopologicalSort(NODE* graph) {
	int indegree[MAXNUM];
	for (int i = 0; i < MAXNUM; i++)
		indegree[i] = 0;
	queue<int> queue;
	for (int i = 0; i < MAXNUM; i++) {
		NODE* next = graph[i].next;
		while (next != NULL) {
			indegree[next->value]++;
			next = next->next;
		}
	}
	for (int i = 0; i < MAXNUM; i++) {
		if (indegree[i] == 0)
		{
			queue.push(i);
			indegree[i] = -1;
		}
	}
	for (int i = 0; i < MAXNUM; i++) {
		printf("%d->", queue.front());
		Update(graph, queue, indegree);
	}
}

void Update(NODE* graph, queue<int>&queue, int indegree[MAXNUM]) {

	NODE* next = graph[queue.front()].next;
	while (next != NULL) {
		indegree[next->value]--;
		next = next->next;
	}
	queue.pop();
	for (int i = 0; i < MAXNUM; i++) {
		if (indegree[i] == 0)
		{
			queue.push(i);
			indegree[i] = -1;
		}
	}
}