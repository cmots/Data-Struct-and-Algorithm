// Binary Heap.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
/*二叉搜索树使用了链表实现，所以二叉堆我就用数组去做了
二叉堆的特性：
除了最底层都要填满，并且最底层也要从左到右添入
任意节点不能比子节点键值小（或大）

本程序使用最小堆，就是说堆顶元素键值最小
*/

//结构是用来保存信息的，其中除了要有你的信息，还需要一个键值
typedef struct Infomation {
	int key;//键值用int方便排,键值一般可以是你想要的优先度
	int data;//数据类型就随意了
}info;

void Insert(info,info*,int&);
void PercolateUp(info*, int);

info Delete(info*, int&);
void PercolateDown(info*, int);
int MinIsLeft(info*, int);

int main()
{
	/*定义了一个很大的数组，所以要求空间复杂度的时候还是用链表吧
	我们可以知道 对于下标为i的节点，子节点下标是是2i+1和2i+2，父节点下标是floor(i-1)/2    
		#floor意思是向下取整
	同时内存访问的时候，子节点因为下标过大，可能储存在另一分页，跑的时间就会很长*/
	info heap[10000] = {};
	int currentSize = 0;//定义堆的最后一位元素位置,也就是堆内元素数量
	//数据验证
	/*info a = { 1,3 };
	info b = { 3,2 };
	info c = { 4,1 };
	info d = { 2,7 };
	Insert(a, heap, currentSize);
	Insert(b, heap, currentSize);
	Insert(c, heap, currentSize);
	Insert(d, heap, currentSize);
	Insert(a, heap, currentSize);
	Delete(heap, currentSize);*/
	_getch();
    return 0;
}

//插入新元素到堆的最后
void Insert(info newNode, info* heap,int& currentSize) {
	heap[currentSize] = newNode;
	PercolateUp(heap, currentSize);
	currentSize++;
}

//堆内元素上滤
void PercolateUp(info* heap, int currentSize) {
	while (heap[currentSize].key < heap[(int)floor((currentSize - 1) / 2 )].key) {
		info temp = heap[currentSize];
		heap[currentSize] = heap[(int)floor((currentSize - 1) / 2)];
		heap[(int)floor((currentSize - 1) / 2)] = temp;
		currentSize = (int)floor((currentSize - 1) / 2);
	}
}

//弹出根节点，只能弹出根节点，删除也是同理（因为二叉堆就是对优先级进行排序的）
info Delete(info* heap, int& currentSize) {
	info temp;
	temp = heap[0];
	currentSize--;
	heap[0] = heap[currentSize];
	currentSize--;
	PercolateDown(heap, currentSize);
	return temp;
}

//堆内元素下滤
void PercolateDown(info *heap, int currentSize) {
	int i=0;
	while (2 * i < currentSize){
		int minTag;
		if (2 * i + 1 == currentSize)
			minTag = 1;
		else
			minTag = MinIsLeft(heap, i);
		if (heap[i].key > heap[i * 2 + minTag].key) {
			info temp;
			temp = heap[i * 2 + minTag];
			heap[i * 2 + minTag] = heap[i];
			heap[i] = temp;
			i = i * 2 + minTag;
		}
		else {
			return;
		}
	}
	return;
}

//左子节点比右子节点小则返回1，大则返回2
int MinIsLeft(info* heap, int pos) {
	if (heap[pos * 2 + 1].key <= heap[pos * 2 + 2].key)
		return 1;
	else
		return 2;
}
