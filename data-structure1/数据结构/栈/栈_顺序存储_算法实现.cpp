#include <iostream>
#include <stdlib.h>

using namespace std;

/*
Jack �ҵĺ�ͬ��խ��ֻ��ͨ��һ����������������ͬ��ֻ�ܴӺ�ͬ�ڽ�����
��ͬ���С�������ų�һ��ֱ�ߣ����������У�����ֻ�ܴ�һ�˽�����
����������ȳ�ȥ����� �ȳ���Last In First Out��LIFO����
�����"ջ"��ջҲ��һ�����Ա�ֻ�������ǲ������޵����� ��
ֻ����һ�˲����� 
������һ�˳�Ϊջ����top������һ�˳�Ϊջ�ף�base����
ջ������˳��洢��Ҳ��������ʽ�洢�� �����ȿ�˳��洢��ʽ��

���У�base ָ��ջ�ף�top ָ��ջ���� 
ע�⣺ջֻ����һ�˲���������ȳ�������ջ�Ĺؼ�������
Ҳ����˵���������м���ҡ�ȡֵ�����롢ɾ���� ������
�������պ�˳��ջ�ĳ�ʼ������ջ����ջ��ȡջ��Ԫ�صȲ�������
*/

//ջ���ݽṹ�Ķ��� 
#define MaxSize 128 //Ԥ�ȷ���ռ䣬�����ֵ����ʵ����ҪԤ��ȷ�� 

typedef int ElemType; 
typedef struct _SqStack{ 
	ElemType *base; //ջ��ָ�� 
	ElemType *top; //ջ��ָ�� 
}SqStack;

/*//ʹ��ָ��ƫ��
typedef struct _SqStack{ 
int top; //ջ����λ�� 
ElemType *base; //ջ��ָ�� 
}SqStack;
*/

//ջ��ʼ��
bool InitStack(SqStack& S){//����һ����ջ S 
	S.base = new int[MaxSize];//Ϊ˳��ջ����һ���������Ϊ Maxsize �Ŀռ�
	if (!S.base)return false;  //�ռ����ʧ��
	S.top=S.base; //top ��ʼΪ base����ջ 
	return true; 
}

//��ջ�������ж��Ƿ�ջ�������ջ����������ջʧ�ܣ�����Ԫ�ط���ջ����ջ��ָ�������ƶ�һ���ռ䣨top++����
bool PushStack(SqStack& S, int e) {//����Ԫ�� e Ϊ�µ�ջ��Ԫ�� 
	if (S.top-S.base == MaxSize)return false;//ջ�� 
	*(S.top++) = e;//Ԫ��eѹ��ջ��,Ȼ��ջ��ָ��� 1,�ȼ���*S.top=e; S.top++; 
	return true; 
}

//��ջ����: ����ջ�෴,��ջǰҪ�ж��Ƿ�ջ��,���ջ�ǿյ�,���ջʧ��,����ջ��Ԫ���ݴ��һ������,ջ��ָ�������ƶ�һ���ռ�(top--)
bool PopStack(SqStack& S, ElemType& e){//ɾ�� S ��ջ��Ԫ�أ��ݴ��ڱ��� e ��
	if (S.base == S.top){ //ջ�� 
		return false; 
	}
	e = *(--S.top); //ջ��ָ��� 1����ջ��Ԫ�ظ��� e 
	return true; 
}

//ȡջ��Ԫ�غͳ�ջ��ͬ��ȡջ��Ԫ��ֻ�ǰ�ջ��Ԫ�ظ���һ�ݣ�ջ��Ԫ�ظ������䣬����ջ��ָջ��Ԫ��ȡ��,ջ�ڲ��ٰ������Ԫ�ء�
ElemType GetTop(SqStack& S){//���� S ��ջ��Ԫ�أ�ջ��ָ�벻��
	if (S.top != S.base){ //ջ�ǿ� 
		return *(S.top - 1); //����ջ��Ԫ�ص�ֵ��ջ��ָ�벻�� 
	}else{ 
		return -1; 
	} 
}
bool GetTop(SqStack& S, ElemType& e) {//���� S ��ջ��Ԫ�أ�ջ��ָ�벻��
	if (S.top != S.base) { //ջ�ǿ� 
		e= *(S.top - 1); //����ջ��Ԫ�ص�ֵ��ջ��ָ�벻�� 
		return true;
	}
	else {
		return false;
	}
}

//�жϿ�ջ
bool IsEmpty(SqStack& S) {//�ж�ջ�Ƿ�Ϊ�� 
	if (S.top == S.base){
		return true; 
	}else{
		return false; 
	} 
}

//��ȡԪ�ظ���
int GetSize(SqStack& S) {
	return S.top - S.base;
}

void DestoryStack(SqStack& S) { //����
	if (S.base) { 
		free(S.base); 
		S.base = NULL;
		S.top = NULL; 
	} 
}

int main() {
	
	int n, x; 
	SqStack S; 
	InitStack(S);//��ʼ��һ��˳��ջ S 
	cout <<"������Ԫ�ظ��� n��" <<endl; 
	cin>>n; 
	cout <<"���������� n ��Ԫ�أ�������ջ��" <<endl;
	while (n--) {
		cin >> x; //����Ԫ�� 
		PushStack(S, x); 
	}
	cout <<"Ԫ�����γ�ջ��" <<endl;
	while(!IsEmpty(S))//���ջ���գ������γ�ջ 
	{ 
		cout<<GetTop(S)<<"\t";//���ջ��Ԫ�� 
		PopStack(S, x); //ջ��Ԫ�س�ջ 
	}
	cout <<endl; 
	DestoryStack(S); 

	system("pause");
	return 0; 
}