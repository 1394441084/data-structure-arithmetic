#pragma once
#pragma once
#include "˳�����.h"
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

//����״̬ 
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
	int x; //���ǵ� x ���� 
	int y; //���ǵ� y ���� 
	enum STATUS stat; //״̬ 
	unsigned radius; //���ǵİ뾶 
	int step; //ÿ����Ծ�ļ�� 
	int color; //���ǵ���ɫ 
}STAR;


/************************************
* ���ܣ���ʼ������
 * ���������
 * i - ������ȫ�������е��±�
 * ����ֵ����
 * ***********************************/
void initStar(STAR & star) {
	int rgb = 0;
	//��ʶ���ṹ�����������
	//rand();//������� //�õ��������Χ 0 - 32767 RAND_MAX; 
	star.x = rand() % SCREEN_WIDTH; // x ��Χ 0 -639 
	star.y = rand() % (SCREEN_HEIGHT - BOTTOM_MARGIN);// y ��Χ 0 - 379 //- BOTTOM_MARGIN ȥ������������Ļ��������
	//star.elems[i].y = rand() % (SCREEN_HEIGHT);
	star.stat = UP;
	//star.elems[i].stat = (enum STATUS)(rand() % ALL_STATUS); //״̬
	star.radius = 1 + rand() % MAX_RADIUS; //�뾶���� 1 - 3 
	star.step = rand() % MAX_STEP + 1; //���� 1 - 5 //ÿ����Ծ�ļ��
	rgb = 255 * star.step / MAX_STEP; // 0 - 255 �Ǻڱ�׵���ɫ��ֵ //��ɫ�ı仯
	star.color = RGB(rgb, rgb, rgb); //�ṹ����ɫ��ֵ
}

bool isQuit(ssqlist<STAR>& star,int i) {//�ж������Ƿ�����Ļ��
	for (int i = 0; i < star.lenth; i++) {
		if (star.elems[i].x > 0 && star.elems[i].x < SCREEN_WIDTH && star.elems[i].y>0 && star.elems[i].y < SCREEN_HEIGHT) {
			return false;
		}
	}
	return true;//����
}

void MoveStar(ssqlist<STAR> &star,int i) {//�ƶ�����
	if (star.elems[i].stat == STOP) return;//���״̬�Ǿ�ֹ��,�Ͳ���Ҫ�ƶ� 

	//����ԭ�������� 
	setfillcolor(BLACK); //���õ�ǰ�������ɫ
	solidcircle(star.elems[i].x, star.elems[i].y, star.elems[i].radius); //�����Բ(�ޱ߿�)

	//�ж�����״̬,�����ƶ�,���¶�λ
	if (star.elems[i].stat == DOWN) {
		star.elems[i].y = star.elems[i].y + star.elems[i].step; //
		if (star.elems[i].y > SCREEN_HEIGHT) star.elems[i].y = 0; //�������ܻ��� ��ǽЧ��
	}
	else if (star.elems[i].stat == UP) {
		star.elems[i].y -= star.elems[i].step; //
		if (star.elems[i].y < 0) {
			star.deleteSqlist(i+1);
			return;
		}
		//if (star.elems[i].y < 0) star.elems[i].y = SCREEN_HEIGHT; //�������ܻ��� ������Ч��
	}
	else if (star.elems[i].stat == LEFT) {
		star.elems[i].x -= star.elems[i].step; //
		if (star.elems[i].x < 0) star.elems[i].x = SCREEN_WIDTH;//�������ܻ���
	}
	else if (star.elems[i].stat == RIGHT) {
		star.elems[i].x += star.elems[i].step; //
		if (star.elems[i].x > SCREEN_WIDTH) star.elems[i].x = 0; //�������ܻ���
	}

	//���������ƶ�
	setfillcolor(star.elems[i].color);
	solidcircle(star.elems[i].x, star.elems[i].y, star.elems[i].radius);
}

void Look_at_the_stars() {//������_main()
	ssqlist<STAR> star;
	STAR star1;
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	for (int i = 0; i < MAX_STAR; i++) {
		initStar(star1);
		star.Add_a_tail(star1);
	}
	for (int i = 0; i < star.lenth; i++) {//���ṹ������չ�� //�ͻ�����
		setfillcolor(star.elems[i].color);//���õ�ǰ�������ɫ
		solidcircle(star.elems[i].x, star.elems[i].y, star.elems[i].radius);//�����Բ(�ޱ߿�)
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
