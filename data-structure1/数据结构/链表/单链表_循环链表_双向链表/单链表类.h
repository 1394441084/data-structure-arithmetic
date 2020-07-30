#pragma once
//链表的节点均指向下一个节点,形成一条单向访问的数据链
//(首节点一般不存储数据,只存下一个节点)(尾节点存储数据,指向下一个节点的指针置为NULL,以示尽头)
#include <iostream>
using namespace std;

//链表概念:请百度链表就能知道是啥了,真是个抖机灵
template <typename T>
class LinkedList{
	LinkedList() {


	}

	typedef struct {//链表实现操作
		T data;//数据
		LinkedList* next;//下一个
	}linklist, structNode;//链表首节点,链表节点;//这样定义能有效区分


};