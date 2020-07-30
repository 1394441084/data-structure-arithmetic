#include "栈_迷宫求解_企业级应用案例1.h"
#include <string.h> 
#include <assert.h> 
#define ROW 6 
#define COL 6 

typedef struct _Maze { 
	int map[ROW][COL]; 
}Maze;

void InitMaze(Maze * m, int map[ROW][COL]) //迷宫的初始化 
{ 
	for (int i = 0;i< ROW ;++i) { 
		for (int j = 0; j < COL; ++j) {
			m->map[i][j] = map[i][j];
		}
	}
}

void PrintMaze(Maze* m) //打印迷宫 
{ 
	for (int i = 0; i < ROW; ++i) { 
		for (int j = 0; j < COL; ++j) { 
			printf("%d ",m->map[i][j]);
		}
		printf("\n"); 
	}
	printf("\n");
}

int IsValidEnter(Maze * m, Position cur) //判断是否是有效的入口 
{ 
	assert(m); 
	if ((cur._x == 0 || cur._x == ROW - 1) ||
		(cur._y == 0 || cur._y == COL - 1) &&
		(m->map[cur._x][cur._y] == 1))
		return 1;
	else return 0;
}

int IsNextPass(Maze* m,Position cur, Position next){ //判断当前节点的下一 个节点能否走通
	assert(m); //判断 next 节点是否为 cur 的下一节点 
	if(((next._x == cur._x) && ((next._y == cur._y+1)||(next._y == cur._y-1))) //在同一行上并且相邻 
		||((next._y == cur._y) && ( (next._x == cur._x+1)||(next._x == cur._x-1)))){//或在同一列上并且相邻 
			//判断下一个节点是否在迷宫里面 
		if (((next._x >= 0 && next._x < ROW) || (next._y >= 0 && next._y < COL)) &&(m->map[next._x][next._y] == 1)){ 
			return 1;
		} 
	}
	return 0; 
}

int IsValidExit(Maze* m, Position cur,Position enter) //判断当前节点是 不是有效的迷宫出口 
{ 
	assert(m); //这里首先得保证该节点不是入口点，其次只要它处在迷宫的边界即可 
	if ((cur._x != enter._x || 
		cur._y != enter._y) && 
		((cur._x == 0 || cur._x == ROW - 1) ||
		(cur._y == 0 || cur._y == COL - 1))) { 
		return 1; 
	}
	else {
		return 0;
	}
}

int PassMaze(Maze* m, Position enter, SqStack* s) //找迷宫通路 
{ 
	assert(m && IsValidEnter(m,enter) == 1); //对给的迷宫的入口进行合法 性判断
	Position cur = enter; 
	Position next;
	PushStack(*s, cur); //首先将迷宫的入口压入栈中
	m->map[cur._x][cur._y] = 2; //将入口值改为 2 
	//PrintMaze(m); 
	while (!IsEmpty(*s)) { 
		cur = *GetTop(*s); 
		//printf("cur: %d %d\n",cur._x, cur._y); 
		if (IsValidExit(m,cur,enter) == 1) //判断当前位置是否出口 
			return 1; 

		//尝试向左一步：看当前节点的左一个节点能不能走通
		next = cur;
		next._y = cur._y - 1;
		if (IsNextPass(m, cur, next) == 1) {
			PushStack(*s, next); 
			m->map[next._x][next._y] = m->map[cur._x][cur._y] + 1; 
			//PrintMaze(m); 
			continue; 
		}
		
		//尝试向上一步:看当前节点的上一个节点能不能走通 
		next = cur; 
		next._x = cur._x - 1; 
		if (IsNextPass(m,cur,next) == 1) //next 节点能够走通时，将其压入 栈中
		{ 
			PushStack(*s,next);
			m->map[next._x][next._y] = m->map[cur._x][cur._y]+1; 
			//将 next 节点的值等于 cur 节点的值加 1 
			//PrintMaze(m); 
			continue; 
		}
		
		//右：看当前节点的向右的一个节点能不能走通
		next = cur;
		next._y = cur._y + 1;
		if (IsNextPass(m, cur, next) == 1) {
			PushStack(*s, next); 
			m->map[next._x][next._y] = m->map[cur._x][cur._y] + 1;
			//PrintMaze(m); 
			continue; 
		}
		
		//下：看当前节点的下一个节点能不能走通 
		next = cur; 
		next._x = cur._x + 1; 
		if (IsNextPass(m, cur,next) == 1) {
			PushStack(*s, next); 
			m->map[next._x][next._y] = m->map[cur._x][cur._y] + 1;
			//PrintMaze(m); 
			continue;
		}
		
		//走到这里说明当前节点的四个方向都走不通，进行回溯，看前一个节点 未被遍历的方向是否还能走通 
		Position tmp; 
		PopStack(*s, tmp); 
	}
	return 0; 
}

int main() {
	int map[ROW][COL] = { //用二维数组描绘迷宫：1 代表通路，0 代表墙 
		0,0,1,0,0,0, 
		0,0,1,1,1,0, 
		0,0,1,0,0,0, 
		0,1,1,1,1,0, 
		0,0,1,0,1,0, 
		0,0,0,0,1,0 };

	Maze m;
	Position enter; //迷宫入口 
	enter._x = 0; 
	enter._y = 2; 
	InitMaze(&m, map); 
	PrintMaze(&m); 
	//system("pause");
	//exit(0); 
	SqStack s; //定义栈，保存已走过的坐标轨迹，便于回溯
	InitStack(s); //栈的初始 
	int ret = PassMaze(&m,enter,&s);

	//使用栈和回溯法解开迷宫 
	if(ret){ 
		printf("恭喜你！终于找到了出口~\n"); 
	}else { 
		printf("不是我笨！实在没有出口~\n");
	}
	PrintMaze(&m); 
	system("pause");
	return 0; 
}