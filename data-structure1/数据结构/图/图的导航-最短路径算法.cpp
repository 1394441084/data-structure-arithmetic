#include <iostream> 

using namespace std; 

#define MaxSize 1024 

typedef struct _EdgeNode {//与节点连接的边的定义 
	int adjvex; //邻接的顶点 
	int weight; //权重 
	struct _EdgeNode *next; //下一条边 
}EdgeNode; 

typedef struct _VertexNode{//顶点节点 
	char data; //节点数据 
	struct _EdgeNode *first;//指向邻接第一条边
}VertexNode, AdjList; 

typedef struct _AdjListGraph { //邻接表 //图
	AdjList *adjlist; //节点
	int vex; //顶点数 
	int edge; //边数 
}AdjListGraph;

 bool visited[MaxSize] = { 0 }; //全局数组，用来记录节点是否已被访问 
 int Location(AdjListGraph &G, char c); 

 /*图的初始化*/ 
 void Init(AdjListGraph &G){
	 G.adjlist = new AdjList[MaxSize];//生成MaxSize个顶点节点
	 G.edge = 0; 
	 G.vex = 0; 
	 for (int i = 0; i < MaxSize; i++) {
		 visited[i] = false;
	 } 
 }
 
 /*图的创建*/ 
 void Create(AdjListGraph& G) {
	 cout << "请输入该图的顶点数以及边数：" << endl;
	 cin >> G.vex >> G.edge;//不能>MaxSize和<0和不是数字

	 cout << "请输入相关顶点：" << endl;
	 for (int i = 0; i < G.vex; i++) {
		 cin >> G.adjlist[i].data;
		 G.adjlist[i].first = NULL;//没有指向
	 }

	 char v1 = 0, v2 = 0;//保存输入的顶点的字符 
	 int i1, i2; //保存顶点在数组中的下标
	 int weight = 0;
	 cout << "请输入想关联边的顶点及权重：" << endl;
	 for (int i = 0; i < G.edge; i++) {
		 cin >> v1 >> v2 >> weight;
		 i1 = Location(G, v1);
		 i2 = Location(G, v2);

		 if (i1 != -1 && i2 != -1) {//寻找到位置 
			 EdgeNode* temp = new EdgeNode;
			 temp->adjvex = i2;
			 temp->next = G.adjlist[i1].first;//链表头插法
			 temp->weight = weight;
			 G.adjlist[i1].first = temp;
		 }
	 }
 }
 
 /*通过顶点对应的字符寻找顶点在图中的邻接点*/
 int Location(AdjListGraph& G, char c) {
	 for (int i = 0; i < G.vex; i++) { //遍历顶点
		 if (G.adjlist[i].data == c) {//对上了返回下标
			 return i; 
		 } 
	 }
	 return -1; 
 }

 int min_weights = 0x7FFFFFFF; //最大的整数 2 的 32 次方-1
 int steps = 0; 
 int path[MaxSize] = {0};//保存走过的路径
 int shortest_path[MaxSize] = {0}; //保存最短的路径

 /*对图上的顶点进行深度遍历*/
 void DFS(AdjListGraph& G, int start, int end, int weights) {
	 int cur = -1;
	 //if(visited[start]) return; //访问过了
	 cur = start;
	 if (cur == end) {//已找到终点，不用继续遍历
					//打印所经过的所有路径
		 for (int i = 0; i < steps; i++) /// 输出所有可能的路径
		 {
			 cout << G.adjlist[path[i]].data << " "; //输出路径 
		 }
		 printf("\t\t 该路径对应的长度是：%d\n", weights);//输出对应路 径长度 
		 if (min_weights > weights) //更新最小路径 
		 {
			 min_weights = weights;
			 memcpy(shortest_path, path, steps * sizeof(int));
		 }
	 }
	 visited[start] = true; //设置为已访问

	 EdgeNode* temp = G.adjlist[start].first;
	 while (temp) {
		 int weight = temp->weight;
		 cur = temp->adjvex;
		 if (visited[cur] == false) {
			 visited[cur] = true; //标记城市 i 已经在路径中
			 path[steps++] = cur;//保存路径到 path 数组中 
			 DFS(G, cur, end, weights + weight);
			 visited[cur] = false;// 之前一步探索完毕后,取消对城市 i 的 标记以便另一条路径选择顶点 
			 path[--steps] = 0;
		 }
		 temp = temp->next;
	 }
 }
 
 int main() {
	 AdjListGraph G;
	 //初始化
	 Init(G);
	 //创建图
	 Create(G);
	 char start, end;
	 cout << "请输入要查询的最短路径的起点和终点：" << endl;
	 cin >> start >> end;
	 //求两点间的最短路径 
	 DFS(G, Location(G, start), Location(G, end), 0);
	 cout << "最小路径长度为：" << min_weights << endl;
	 cout << "路径：";
	 int i = 0;
	 while (i < MaxSize && shortest_path[i]>0) {
		 cout << G.adjlist[shortest_path[i]].data << " ";
		 i++;
	 }
	 cout << endl;
	 system("pause");
	 return 0;
 }