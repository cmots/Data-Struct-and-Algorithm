// Dijkstra.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
#define MAXNUM 7
#define MAXVALUE 65535

using namespace std;

typedef struct node {
	int value;	//指向节点
	int weight;	//权值
	struct node *next;	//邻接表下一位
}NODE;

void InsertEdge(NODE graph[MAXNUM], int from, int to, int weight);

int* Dijkstra(NODE graph[MAXNUM], int start);

int FindMin(bool known[MAXNUM], int distance[MAXNUM]);

int main()
{
	NODE graph[MAXNUM];
	for (int i = 0; i < MAXNUM; i++) {
		graph[i].weight = 0;
		graph[i].next = NULL;
		graph[i].value = i;	//初始化，填入1-11总共10个顶点
	} 
	InsertEdge(graph, 0, 1, 2);
	InsertEdge(graph, 1, 4, 10);
	InsertEdge(graph, 4, 6, 6);
	InsertEdge(graph, 6, 5, 1);
	InsertEdge(graph, 2, 5, 5);
	InsertEdge(graph, 2, 0, 4);
	InsertEdge(graph, 0, 3, 1);
	InsertEdge(graph, 1, 3, 3);
	InsertEdge(graph, 3, 4, 2);
	InsertEdge(graph, 3, 6, 4);
	InsertEdge(graph, 3, 5, 8);
	InsertEdge(graph, 3, 2, 2);	//以上都是构造图的过程
	int* distance;
	distance = Dijkstra(graph, 0);	//调用Dijkstra函数
	for (int i = 0; i < MAXNUM; i++) {
		printf("position:%d -- %d\n", i, distance[i]);
	}
}

void InsertEdge(NODE graph[MAXNUM], int from, int to, int weight) {
	NODE *newNode = (NODE*)malloc(sizeof(NODE));
	newNode->value = to;
	newNode->weight = weight;
	newNode->next = NULL;
	if (graph[from].next == NULL) 	
		graph[from].next = newNode;
	else{
		NODE* position = graph[from].next;
		while (position->next != NULL)
			position = position->next;
		position->next = newNode;
	}
}

int* Dijkstra(NODE graph[MAXNUM], int start) {
	int* distance = (int*)malloc(sizeof(int)*MAXNUM);
	int prev[MAXNUM];
	bool known[MAXNUM];
	for (int i = 0; i < MAXNUM; i++) {
		distance[i] = MAXVALUE;
		known[i] = false;
	}
	NODE* next = graph[start].next;
	while (next != NULL) {
		distance[next->value] = next->weight;
		next = next->next;
	}
	distance[start] = 0;
	known[start] = true;
	while (1) {
		int pos = FindMin(known, distance);
		if (pos == -1)
			break;
		known[pos] = true;
		next = graph[pos].next;
		while (next!=NULL) {
			if (distance[pos] + next->weight < distance[next->value]) {
				distance[next->value] = distance[pos] + next->weight;
				prev[next->value] = pos;
			}
			next = next->next;
		}
	}
	return distance;
}

/*找到未知点里目前距离最小的
*没有用全局变量，所以这里是返回未知点里距离最小的下标(就是点的名字)
*/
int FindMin(bool known[MAXNUM], int distance[MAXNUM]) {
	int min = MAXVALUE;
	int pos = -1;
	for (int i = 0; i < MAXNUM; i++) {
		if (distance[i] < min && !known[i]) {
			min = distance[i];
			pos = i;
		}
	}
	return pos;
}