#include <iostream>
#include <stdlib.h>

using namespace std;

typedef int ElemType;
typedef struct _structNode {//链表实现操作
	ElemType *data = NULL;//节点数据//进来的空间
	_structNode* next = NULL;//下一个链表节点
}linklist, structNode;//链表首节点,链表节点;//这样定义区分

//初始化
bool Initlist(linklist*& L) {//只初始化头节点
	L = new structNode;//生成一个节点

	if (!L)return false;//生成节点失败
	L->data = NULL;
	L->next = NULL;//将节点置为NULL
	return true;//初始化成功
}

//后插法()
bool inser_back(linklist*& L, ElemType* e) {
	structNode* node=new structNode;//增加一个空间
	if (!L || !e || !node)return false;//判断是否为空
	structNode* last = L;//尾部
	while (last->next) {
		last = last->next;
	}//跳出就指向尾部节点了

	node->next = NULL;//新尾节点->next置为NULL
	node->data = e;
	last->next = node;//尾节点->next指向新节点,新节点变为新尾节点
	return true;
}

//单链表取值
bool linked_list_value(linklist*& L, ElemType &e) {
	if (!L || !L->next)return false;//判断是否为空
	structNode* last = L->next;
	
	while (last->next) {
		last = last->next;
	}//跳出就指向最后节点
	e = *(last->data);
	return true;
}

//单链表出列
bool linked_list_delete_data(linklist*& L, ElemType &data) {
	if (!L || !L->next) { return false; }//判断是否为空
	structNode* last = L;

	while (last) {
		if (last->next->next == NULL) {//此时是最后一个节点
			data = *(last->next->data);//将数据出给外面
			delete last->next->data;//因为data保存的也是一个空间,所以也需要delete掉
			delete last->next;
			last->next = NULL;
			return true;
		}
		last = last->next;
	}

	return false;
}

//销毁单链表
void linked_list_delete(linklist*& L) {
	structNode* last = L;
	while (last) {
		L = L->next;//指向下一个节点
		//cout << "删除元素:" << last->data << endl;
		delete last->data;
		delete last;//删除头节点
		last = L;
	}
}

//单链表输出
void single_linked_list_output(linklist*& L) {
	if (!L) {
		cout << "此链表为空\n";
		return;
	}
	structNode* p = L->next;

	while (p) {
		cout << *(p->data) << "\t";
		p = p->next;
	}
	cout << endl;
}

int main() {
	linklist* L = NULL;//创建首节点
	Initlist(L);//初始化一个空的链表

	//使用后插法插入数据
	int n; ElemType* s = NULL;
	cout << "创建链表栈\n";
	cout << "请输入元素个数:";
	cin >> n;
	cout << "\n请依次输入" << n << "个元素:\n";
	while (n > 0) {
		s = new ElemType;//生成新节点
		cin >> *s;//输入数据
		inser_back(L, s);//插入链表
		n--;
	}

	//单链表的输出
	single_linked_list_output(L);

	//链表栈取指
	ElemType v;
	linked_list_value(L, v);
	cout << "最后一个元素数据为:" << v << endl;

	//栈顶出列
	linked_list_delete_data(L, v);
	cout << "出列的元素数据为:" << v << endl;

	single_linked_list_output(L);

	//销毁单链表
	linked_list_delete(L);

	system("pause");
	return 0;
}