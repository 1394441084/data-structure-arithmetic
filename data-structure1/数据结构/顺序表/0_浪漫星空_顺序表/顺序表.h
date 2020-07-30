#pragma once

#include <iostream>
#include <Windows.h>
using namespace std;

#define MAX_SIZE_2 6 //最大空间

/*
typedef struct _sqlist sqlist;
struct _sqlist {
	int* elems;  //顺序表的基地址
	int lenth;   //顺序表的长度(元素个数)
	int size;    //顺序表总空间大小
};*/

typedef struct {
	int* elems=NULL;		//顺序表的基地址
	int lenth=0;		//顺序表的长度(元素个数)
	int size=0;		//顺序表总空间大小
}sqlist;//定义一个别名
//}sqlist,sqlist1;//定义多个别名

bool initsqlist(sqlist &other) {//构造一个空的顺序表
	other.elems = new int[MAX_SIZE_2];//为顺序表分配 MAX_SIZE 个空间
	if (!other.elems)return false;//防御检查 //存储失败
	other.lenth = 0;
	other.size = MAX_SIZE_2;
	return true;
}

void sqlistprintf(const sqlist &list) {//输出整个顺序表
	cout << "顺序表的总空间:" << list.size << "\t顺序表的元素个数:" << list.lenth << endl;
	for (int i = 0; i <= list.lenth-1; i++) {
		cout << list.elems[i] << " ";
	}
	cout << endl;
}

bool listAdd_a_tail(sqlist& list,int e) {//顺序表尾部添加元素
	if (list.size == list.lenth) return false;	//存储空间已满

	list.elems[list.lenth] = e;	//空间赋值
	list.lenth++;	//表长加一
	return true;
}

bool listInsert(sqlist& list,int i,int e) {//顺序表的任意位置插入元素
	i--;
	if (i < 0 || i > list.lenth || list.lenth >=list.size)return false;//i值不合法 
	for (int j = list.lenth; j >= i ; j--) {
		list.elems[j] = list.elems[j-1];//从最后元素开始后移,直到下标为i的元素后移
	}
	list.lenth++;
	list.elems[i] = e;
	return true;
}

bool listdelete(sqlist& list, int i) {//删除指定位置的元素
	if (i <= 0 || i > list.lenth )return false;//i值不合法
	i--;
	list.lenth--;
	if (i == list.lenth) {//删除最后一个元素
		return true;
	}
	for (int j = i; j < list.lenth; j++) {
		list.elems[j] = list.elems[j+1];//删除位置的后续元素依次往前移
	}
	return true;
}

void listdestruction(sqlist& list) {//销毁顺序表
	if (list.elems) {
		delete[] list.elems;//释放存储空间
		list.elems = NULL;
	}
	list.lenth = 0;
	list.size = 0;
}

void The_order_sheet_main() {//顺序表_main()
	sqlist list;
	cout << "顺序表初始化中-------\n";
	if (initsqlist(list)) {
		cout << "顺序表初始化成功\n";
		sqlistprintf(list);
	}
	else {
		cout << "顺序表初始化失败\n";
	}

	//添加元素
	int count; int e;
	cout << "请输入要添加的元素个数:";
	cin >> count;
	for (int i = 0; i < count; i++) {
		cout << "\n请输入要添加的元素:";
		cin >> e;
		if (listAdd_a_tail(list, e)) {
			cout << "添加元素成功\n";
		}
		else {
			cout << "添加元素失败\n";
		}
	}
	sqlistprintf(list);

	//插入元素
	cout << "请输入要插入的位置:";
	cin >> count;
	cout << endl;
	cout << "请输入要插入的数据元素:";
	cin >> e;
	if (listInsert(list, count, e)) {
		cout << "任意位置插入成功\n";
		sqlistprintf(list);
	}
	else {
		cout << "任意位置插入失败\n";
	}

	//删除元素
	cout << "请输入要删除元素的位置:";
	cin >> count;
	if (listdelete(list, count)) {
		cout << "删除成功\n";
		sqlistprintf(list);
	}
	else {
		cout << "删除失败\n";
	}

	listdestruction(list);
}

