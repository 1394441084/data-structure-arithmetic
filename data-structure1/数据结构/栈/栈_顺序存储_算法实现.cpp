#include <iostream>
#include <stdlib.h>

using namespace std;

/*
Jack 家的胡同很窄，只能通过一辆车，而且是死胡同，只能从胡同口进出，
胡同里的小汽车是排成一条直线，是线性排列，而且只能从一端进出，
后进的汽车先出去，后进 先出（Last In First Out，LIFO），
这就是"栈"。栈也是一种线性表，只不过它是操作受限的线性 表，
只能在一端操作。 
进出的一端称为栈顶（top），另一端称为栈底（base）。
栈可以用顺序存储，也可以用链式存储。 我们先看顺序存储方式：

其中，base 指向栈底，top 指向栈顶。 
注意：栈只能在一端操作，后进先出，这是栈的关键特征，
也就是说不允许在中间查找、取值、插入、删除等 操作，
我们掌握好顺序栈的初始化、入栈，出栈，取栈顶元素等操作即可
*/

//栈数据结构的定义 
#define MaxSize 128 //预先分配空间，这个数值根据实际需要预估确定 

typedef int ElemType; 
typedef struct _SqStack{ 
	ElemType *base; //栈底指针 
	ElemType *top; //栈顶指针 
}SqStack;

/*//使用指针偏移
typedef struct _SqStack{ 
int top; //栈顶的位置 
ElemType *base; //栈底指针 
}SqStack;
*/

//栈初始化
bool InitStack(SqStack& S){//构造一个空栈 S 
	S.base = new int[MaxSize];//为顺序栈分配一个最大容量为 Maxsize 的空间
	if (!S.base)return false;  //空间分配失败
	S.top=S.base; //top 初始为 base，空栈 
	return true; 
}

//入栈操作：判断是否栈满，如果栈已满，则入栈失败，否则将元素放入栈顶，栈顶指针向上移动一个空间（top++）。
bool PushStack(SqStack& S, int e) {//插入元素 e 为新的栈顶元素 
	if (S.top-S.base == MaxSize)return false;//栈满 
	*(S.top++) = e;//元素e压入栈顶,然后栈顶指针加 1,等价于*S.top=e; S.top++; 
	return true; 
}

//出栈操作: 和入栈相反,出栈前要判断是否栈空,如果栈是空的,则出栈失败,否则将栈顶元素暂存给一个变量,栈顶指针向下移动一个空间(top--)
bool PopStack(SqStack& S, ElemType& e){//删除 S 的栈顶元素，暂存在变量 e 中
	if (S.base == S.top){ //栈空 
		return false; 
	}
	e = *(--S.top); //栈顶指针减 1，将栈顶元素赋给 e 
	return true; 
}

//取栈顶元素和出栈不同，取栈顶元素只是把栈顶元素复制一份，栈的元素个数不变，而出栈是指栈顶元素取出,栈内不再包含这个元素。
ElemType GetTop(SqStack& S){//返回 S 的栈顶元素，栈顶指针不变
	if (S.top != S.base){ //栈非空 
		return *(S.top - 1); //返回栈顶元素的值，栈顶指针不变 
	}else{ 
		return -1; 
	} 
}
bool GetTop(SqStack& S, ElemType& e) {//返回 S 的栈顶元素，栈顶指针不变
	if (S.top != S.base) { //栈非空 
		e= *(S.top - 1); //返回栈顶元素的值，栈顶指针不变 
		return true;
	}
	else {
		return false;
	}
}

//判断空栈
bool IsEmpty(SqStack& S) {//判断栈是否为空 
	if (S.top == S.base){
		return true; 
	}else{
		return false; 
	} 
}

//获取元素个数
int GetSize(SqStack& S) {
	return S.top - S.base;
}

void DestoryStack(SqStack& S) { //销毁
	if (S.base) { 
		free(S.base); 
		S.base = NULL;
		S.top = NULL; 
	} 
}

int main() {
	
	int n, x; 
	SqStack S; 
	InitStack(S);//初始化一个顺序栈 S 
	cout <<"请输入元素个数 n：" <<endl; 
	cin>>n; 
	cout <<"请依次输入 n 个元素，依次入栈：" <<endl;
	while (n--) {
		cin >> x; //输入元素 
		PushStack(S, x); 
	}
	cout <<"元素依次出栈：" <<endl;
	while(!IsEmpty(S))//如果栈不空，则依次出栈 
	{ 
		cout<<GetTop(S)<<"\t";//输出栈顶元素 
		PopStack(S, x); //栈顶元素出栈 
	}
	cout <<endl; 
	DestoryStack(S); 

	system("pause");
	return 0; 
}