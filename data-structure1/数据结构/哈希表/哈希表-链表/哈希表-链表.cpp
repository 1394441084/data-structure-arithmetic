#include "��ϣ��-����.h"

void main(void) {
	//char* elems[] = { (char*)"�仨",(char*)"С��",(char*)"����ʦ" };//�Ա�������ǿת
	char* elems[] = { "�仨","С��","����ʦ" };//���� -> C/C++ ->���� -> ����ģʽ��->��
	
	int i = 0;
	HashTable* HashTable;
	HashTable = InitHash(31);//��ʼ��
	Insert(HashTable, 1, elems[0]);//��������
	Insert(HashTable, 2, elems[1]);
	Insert(HashTable, 3, elems[2]);
	Delete(HashTable, 1);
	for (i = 0; i < 4; i++) {
		Element e = Find(HashTable, i);
		if (e) {
			printf("%s\n", (const char*)Retrieve(e));
		}
		else {
			printf("Not found [key:%d]\n", i);
		}
	}
	system("pause");
}