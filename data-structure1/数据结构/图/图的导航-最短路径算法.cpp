#include <iostream> 

using namespace std; 

#define MaxSize 1024 

typedef struct _EdgeNode {//��ڵ����ӵıߵĶ��� 
	int adjvex; //�ڽӵĶ��� 
	int weight; //Ȩ�� 
	struct _EdgeNode *next; //��һ���� 
}EdgeNode; 

typedef struct _VertexNode{//����ڵ� 
	char data; //�ڵ����� 
	struct _EdgeNode *first;//ָ���ڽӵ�һ����
}VertexNode, AdjList; 

typedef struct _AdjListGraph { //�ڽӱ� //ͼ
	AdjList *adjlist; //�ڵ�
	int vex; //������ 
	int edge; //���� 
}AdjListGraph;

 bool visited[MaxSize] = { 0 }; //ȫ�����飬������¼�ڵ��Ƿ��ѱ����� 
 int Location(AdjListGraph &G, char c); 

 /*ͼ�ĳ�ʼ��*/ 
 void Init(AdjListGraph &G){
	 G.adjlist = new AdjList[MaxSize];//����MaxSize������ڵ�
	 G.edge = 0; 
	 G.vex = 0; 
	 for (int i = 0; i < MaxSize; i++) {
		 visited[i] = false;
	 } 
 }
 
 /*ͼ�Ĵ���*/ 
 void Create(AdjListGraph& G) {
	 cout << "�������ͼ�Ķ������Լ�������" << endl;
	 cin >> G.vex >> G.edge;//����>MaxSize��<0�Ͳ�������

	 cout << "��������ض��㣺" << endl;
	 for (int i = 0; i < G.vex; i++) {
		 cin >> G.adjlist[i].data;
		 G.adjlist[i].first = NULL;//û��ָ��
	 }

	 char v1 = 0, v2 = 0;//��������Ķ�����ַ� 
	 int i1, i2; //���涥���������е��±�
	 int weight = 0;
	 cout << "������������ߵĶ��㼰Ȩ�أ�" << endl;
	 for (int i = 0; i < G.edge; i++) {
		 cin >> v1 >> v2 >> weight;
		 i1 = Location(G, v1);
		 i2 = Location(G, v2);

		 if (i1 != -1 && i2 != -1) {//Ѱ�ҵ�λ�� 
			 EdgeNode* temp = new EdgeNode;
			 temp->adjvex = i2;
			 temp->next = G.adjlist[i1].first;//����ͷ�巨
			 temp->weight = weight;
			 G.adjlist[i1].first = temp;
		 }
	 }
 }
 
 /*ͨ�������Ӧ���ַ�Ѱ�Ҷ�����ͼ�е��ڽӵ�*/
 int Location(AdjListGraph& G, char c) {
	 for (int i = 0; i < G.vex; i++) { //��������
		 if (G.adjlist[i].data == c) {//�����˷����±�
			 return i; 
		 } 
	 }
	 return -1; 
 }

 int min_weights = 0x7FFFFFFF; //�������� 2 �� 32 �η�-1
 int steps = 0; 
 int path[MaxSize] = {0};//�����߹���·��
 int shortest_path[MaxSize] = {0}; //������̵�·��

 /*��ͼ�ϵĶ��������ȱ���*/
 void DFS(AdjListGraph& G, int start, int end, int weights) {
	 int cur = -1;
	 //if(visited[start]) return; //���ʹ���
	 cur = start;
	 if (cur == end) {//���ҵ��յ㣬���ü�������
					//��ӡ������������·��
		 for (int i = 0; i < steps; i++) /// ������п��ܵ�·��
		 {
			 cout << G.adjlist[path[i]].data << " "; //���·�� 
		 }
		 printf("\t\t ��·����Ӧ�ĳ����ǣ�%d\n", weights);//�����Ӧ· ������ 
		 if (min_weights > weights) //������С·�� 
		 {
			 min_weights = weights;
			 memcpy(shortest_path, path, steps * sizeof(int));
		 }
	 }
	 visited[start] = true; //����Ϊ�ѷ���

	 EdgeNode* temp = G.adjlist[start].first;
	 while (temp) {
		 int weight = temp->weight;
		 cur = temp->adjvex;
		 if (visited[cur] == false) {
			 visited[cur] = true; //��ǳ��� i �Ѿ���·����
			 path[steps++] = cur;//����·���� path ������ 
			 DFS(G, cur, end, weights + weight);
			 visited[cur] = false;// ֮ǰһ��̽����Ϻ�,ȡ���Գ��� i �� ����Ա���һ��·��ѡ�񶥵� 
			 path[--steps] = 0;
		 }
		 temp = temp->next;
	 }
 }
 
 int main() {
	 AdjListGraph G;
	 //��ʼ��
	 Init(G);
	 //����ͼ
	 Create(G);
	 char start, end;
	 cout << "������Ҫ��ѯ�����·���������յ㣺" << endl;
	 cin >> start >> end;
	 //�����������·�� 
	 DFS(G, Location(G, start), Location(G, end), 0);
	 cout << "��С·������Ϊ��" << min_weights << endl;
	 cout << "·����";
	 int i = 0;
	 while (i < MaxSize && shortest_path[i]>0) {
		 cout << G.adjlist[shortest_path[i]].data << " ";
		 i++;
	 }
	 cout << endl;
	 system("pause");
	 return 0;
 }