#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;

#define MAX_SIZE_1 100 //最大空间

template <typename T = int>
struct ssqlist {
public:
	ssqlist() {
		elems = new T[MAX_SIZE_1];
		lenth = 0;
		head = 0;
		size = MAX_SIZE_1;
	}
	~ssqlist() {
		if (elems) {
			delete[] elems;//释放存储空间
			elems = NULL;
		}
		head = 0;
		lenth = 0;
		size = 0;
	}
	
	void printff() {
		cout << "顺序表的总空间:" << size << "\t元素个数:" << lenth << "\t元素头部:"<<head<<endl;
		/*
		for (int i = head; i <= lenth - 1; i++) {
			cout << elems[i] << " ";
		}
		cout << endl;
		*/
	}

	bool Add_a_tail(T e) {//顺序表尾部添加元素
		if (size == lenth + head) return false;	//存储空间已满
		elems[lenth] = e;	//空间赋值
		lenth++;	//表长加一
		return true;
	}

	bool Insert(int i, T e) {//顺序表的任意位置插入元素
		i--;
		if (i < 0 || i > lenth || lenth >= size)return false;//i值不合法

		//如果头部位置!=0 && 尾部+头部==size 那么头部还有空间,可以插入元素
		if (head != 0 && lenth + head == size) {
			for (int j = head-1; j <= i; j++) {
				elems[j] = elems[j + 1];
			}
			elems[i] = e;
			lenth++;
			head++;
			return true;
		}
		
		for (int j = lenth; j >= i; j--) {
			elems[j] = elems[j - 1];//从最后元素开始后移,直到下标为i的元素后移
		}
		lenth++;
		elems[i] = e;
		return true;
	}

	bool deleteSqlist(int i) {//删除指定位置的元素
		if (i <= 0 || i > lenth)return false;//i值不合法
		i--;
		/*//尾部和指定位置删除元素需分开,不然会产生逻辑混肴.分开后能更好的使用
		if (i == head) {//删除第一元素
			head++;
			lenth--;
			return true;
		}*/
		lenth--;
		if (i == lenth+ head) {//删除最后一个元素
			return true;
		}
		for (int j = i; j < lenth + head; j++) {
			elems[j] = elems[j + 1];//删除位置的后续元素依次往前移
		}
		return true;
	}

	void destruction() {//销毁顺序表
		if (elems) {
			delete[] elems;//释放存储空间
			elems = NULL;
		}
		lenth = 0;
		size = 0;
	}
//private:
	int head;			//头部
	T* elems = NULL;	//顺序表的基地址
	int lenth = 0;		//顺序表的长度(元素个数)
	int size = 0;		//顺序表总空间大小
};


void The_order_sheet() {//顺序表_main()
	ssqlist<int> list;

	list.printff();

	//添加元素
	int count; int e;
	cout << "请输入要添加的元素个数:";
	cin >> count;
	for (int i = 0; i < count; i++) {
		cout << "\n请输入要添加的元素:";
		cin >> e;
		if (list.Add_a_tail(e)) {
			cout << "添加元素成功\n";
		}
		else {
			cout << "添加元素失败\n";
		}
	}
	list.printff();

	//插入元素
	cout << "请输入要插入的位置:";
	cin >> count;
	cout << endl;
	cout << "请输入要插入的数据元素:";
	cin >> e;
	if (list.Insert(count, e)) {
		cout << "任意位置插入成功\n";
		list.printff();
	}
	else {
		cout << "任意位置插入失败\n";
	}

	//删除元素
	cout << "请输入要删除元素的位置:";
	cin >> count;
	if (list.deleteSqlist(count)) {
		cout << "删除成功\n";
		list.printff();
	}
	else {
		cout << "删除失败\n";
	}

	list.destruction();//销毁对象
}
