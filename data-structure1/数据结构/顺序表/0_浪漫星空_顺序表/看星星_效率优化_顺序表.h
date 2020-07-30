#pragma once
#pragma once
#include "顺序表类.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h> 
#include <string> 

#define MAX_STAR MAX_SIZE_1
#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 480 
#define MAX_STEP 5 
#define MAX_RADIUS 3 
#define BOTTOM_MARGIN 100 

//星星状态 
enum STATUS {
	STOP = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	RANDOM,
	ALL_STATUS
};

typedef struct {
	int x; //星星的 x 坐标 
	int y; //星星的 y 坐标 
	enum STATUS stat; //状态 
	unsigned radius; //星星的半径 
	int step; //每次跳跃的间隔 
	int color; //星星的颜色 
}STAR;


/************************************
* 功能：初始化星星
 * 输入参数：
 * i - 星星在全局数组中的下标
 * 返回值：无
 * ***********************************/
void initStar(STAR & star) {
	int rgb = 0;
	//初识化结构体数组的数据
	//rand();//随机种子 //得到随机数范围 0 - 32767 RAND_MAX; 
	star.x = rand() % SCREEN_WIDTH; // x 范围 0 -639 
	star.y = rand() % (SCREEN_HEIGHT - BOTTOM_MARGIN);// y 范围 0 - 379 //- BOTTOM_MARGIN 去掉就能整个屏幕是星星了
	//star.elems[i].y = rand() % (SCREEN_HEIGHT);
	star.stat = UP;
	//star.elems[i].stat = (enum STATUS)(rand() % ALL_STATUS); //状态
	star.radius = 1 + rand() % MAX_RADIUS; //半径控制 1 - 3 
	star.step = rand() % MAX_STEP + 1; //步长 1 - 5 //每次跳跃的间隔
	rgb = 255 * star.step / MAX_STEP; // 0 - 255 是黑变白的颜色数值 //颜色的变化
	star.color = RGB(rgb, rgb, rgb); //结构体颜色赋值
}

bool isQuit(ssqlist<STAR>& star,int i) {//判断星星是否在屏幕里
	for (int i = 0; i < star.lenth; i++) {
		if (star.elems[i].x > 0 && star.elems[i].x < SCREEN_WIDTH && star.elems[i].y>0 && star.elems[i].y < SCREEN_HEIGHT) {
			return false;
		}
	}
	return true;//外面
}

void MoveStar(ssqlist<STAR> &star,int i) {//移动星星
	if (star.elems[i].stat == STOP) return;//如果状态是静止的,就不需要移动 

	//擦除原来的星星 
	setfillcolor(BLACK); //设置当前的填充颜色
	solidcircle(star.elems[i].x, star.elems[i].y, star.elems[i].radius); //画填充圆(无边框)

	//判断星星状态,往哪移动,重新定位
	if (star.elems[i].stat == DOWN) {
		star.elems[i].y = star.elems[i].y + star.elems[i].step; //
		if (star.elems[i].y > SCREEN_HEIGHT) star.elems[i].y = 0; //让星星跑回来 穿墙效果
	}
	else if (star.elems[i].stat == UP) {
		star.elems[i].y -= star.elems[i].step; //
		if (star.elems[i].y < 0) {
			star.deleteSqlist(i+1);
			return;
		}
		//if (star.elems[i].y < 0) star.elems[i].y = SCREEN_HEIGHT; //让星星跑回来 往回跑效果
	}
	else if (star.elems[i].stat == LEFT) {
		star.elems[i].x -= star.elems[i].step; //
		if (star.elems[i].x < 0) star.elems[i].x = SCREEN_WIDTH;//让星星跑回来
	}
	else if (star.elems[i].stat == RIGHT) {
		star.elems[i].x += star.elems[i].step; //
		if (star.elems[i].x > SCREEN_WIDTH) star.elems[i].x = 0; //让星星跑回来
	}

	//往新坐标移动
	setfillcolor(star.elems[i].color);
	solidcircle(star.elems[i].x, star.elems[i].y, star.elems[i].radius);
}

void Look_at_the_stars() {//看星星_main()
	ssqlist<STAR> star;
	STAR star1;
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	for (int i = 0; i < MAX_STAR; i++) {
		initStar(star1);
		star.Add_a_tail(star1);
	}
	for (int i = 0; i < star.lenth; i++) {//将结构体数组展现 //就画星星
		setfillcolor(star.elems[i].color);//设置当前的填充颜色
		solidcircle(star.elems[i].x, star.elems[i].y, star.elems[i].radius);//画填充圆(无边框)
	}

	bool quit = false;
	while (quit == false) {
		for (int i = star.lenth - 1; i >= 0; i--) {
			MoveStar(star,i);
		}
		if (star.lenth==0) { 
			quit = true; 
		}
		Sleep(50);
	}
	closegraph();
}
