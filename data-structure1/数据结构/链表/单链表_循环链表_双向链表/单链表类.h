#pragma once
//����Ľڵ��ָ����һ���ڵ�,�γ�һ��������ʵ�������
//(�׽ڵ�һ�㲻�洢����,ֻ����һ���ڵ�)(β�ڵ�洢����,ָ����һ���ڵ��ָ����ΪNULL,��ʾ��ͷ)
#include <iostream>
using namespace std;

//�������:��ٶ��������֪����ɶ��,���Ǹ�������
template <typename T>
class LinkedList{
	LinkedList() {


	}

	typedef struct {//����ʵ�ֲ���
		T data;//����
		LinkedList* next;//��һ��
	}linklist, structNode;//�����׽ڵ�,����ڵ�;//������������Ч����


};