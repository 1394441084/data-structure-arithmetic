#pragma once
#include <graphics.h>
#include <conio.h>
#include <stdio.h> 
#include <string> 

#define MAX_STAR 100
#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 480 
#define MAX_STEP 5 
#define MAX_RADIUS 3 
#define BOTTOM_MARGIN 100 

//����״̬ 
enum STATUS{ 
	STOP=0, 
	UP, 
	DOWN, 
	LEFT, 
	RIGHT, 
	RANDOM, 
	ALL_STATUS 
};

struct STAR{ 
	int x; //���ǵ� x ���� 
	int y; //���ǵ� y ���� 
	enum STATUS stat; //״̬ 
	unsigned radius; //���ǵİ뾶 
	int step; //ÿ����Ծ�ļ�� 
	int color; //���ǵ���ɫ 
};

struct STAR star[MAX_STAR];//�ṹ������
/************************************ 
* ���ܣ���ʼ������
 * ��������� 
 * i - ������ȫ�������е��±�
 * ����ֵ���� 
 * ***********************************/ 
void initStar(int i) {
	int rgb = 0;
	if (i<0 || i>MAX_STAR) {
		fprintf(stderr, "��˾�����㴫��ֵ i[%d]���ܲ��ˣ�", i); //log �� ־ 
		return; 
	}

	//��ʶ���ṹ�����������
	//rand();//������� //�õ��������Χ 0 - 32767 RAND_MAX; 
	star[i].x = rand()% SCREEN_WIDTH; // x ��Χ 0 -639 
	star[i].y = rand()% (SCREEN_HEIGHT - BOTTOM_MARGIN);// y ��Χ 0 - 379 //- BOTTOM_MARGIN ȥ������������Ļ��������
	//star[i].y = rand() % (SCREEN_HEIGHT);
	//star[i].stat = UP;
	star[i].stat = (enum STATUS)(rand()%ALL_STATUS); //״̬
	star[i].radius = 1+ rand() % MAX_RADIUS; //�뾶���� 1 - 3 
	star[i].step = rand() % MAX_STEP +1; //���� 1 - 5 //ÿ����Ծ�ļ��
	rgb = 255 * star[i].step / MAX_STEP; // 0 - 255 �Ǻڱ�׵���ɫ��ֵ //��ɫ�ı仯
	star[i].color = RGB(rgb, rgb, rgb); //�ṹ����ɫ��ֵ
}

bool isQuit() {//�ж������Ƿ�����Ļ��
	for (int i = 0; i < MAX_STAR; i++) {
		if (star[i].x > 0 && star[i].x < SCREEN_WIDTH && star[i].y>0 && star[i].y < SCREEN_HEIGHT) {
			return false;
		}
	}
	return true;//����
}

void MoveStar(int i) {//�ƶ�����
	if (star[i].stat == STOP) return;//���״̬�Ǿ�ֹ��,�Ͳ���Ҫ�ƶ� 

	//����ԭ�������� 
	setfillcolor(BLACK); //���õ�ǰ�������ɫ
	solidcircle(star[i].x, star[i].y, star[i].radius); //�����Բ(�ޱ߿�)

	//�ж�����״̬,�����ƶ�,���¶�λ
	if(star[i].stat == DOWN){ 
		star[i].y =star[i].y + star[i].step; //
		if(star[i].y>SCREEN_HEIGHT) star[i].y = 0; //�������ܻ��� ��ǽЧ��
	}else if(star[i].stat == UP){
		star[i].y -= star[i].step; //
		if(star[i].y<0) star[i].y = SCREEN_HEIGHT; //�������ܻ��� ������Ч��
	}else if(star[i].stat == LEFT){ 
			star[i].x -= star[i].step; //
			if(star[i].x<0) star[i].x = SCREEN_WIDTH;//�������ܻ���
	}else if(star[i].stat == RIGHT){ 
		star[i].x += star[i].step; //
		if(star[i].x>SCREEN_WIDTH) star[i].x = 0; //�������ܻ���
	}

	//���������ƶ�
	setfillcolor(star[i].color); 
	solidcircle(star[i].x, star[i].y, star[i].radius);
}

void Look_at_the_stars_main(){//������_main()
	initgraph(SCREEN_WIDTH,SCREEN_HEIGHT);
	for (int i = 0; i < MAX_STAR; i++) {
		initStar(i);
	}
	for (int i = 0; i < MAX_STAR; i++) {//���ṹ������չ�� //�ͻ�����
		setfillcolor(star[i].color);//���õ�ǰ�������ɫ
		solidcircle(star[i].x, star[i].y, star[i].radius);//�����Բ(�ޱ߿�)
	}
	/*
	IMAGE tortoise;//����ͼƬ //ͼ�����
	loadimage(&tortoise,_T("tortoise.jpg"), 30, 30, false);//���ļ��ж�ȡͼ������ͼ����
	putimage(SCREEN_WIDTH * 4 / 10 - 30, SCREEN_HEIGHT - 30, &tortoise);//����ͼ��
	putimage(SCREEN_WIDTH * 6 / 10, SCREEN_HEIGHT - 30, &tortoise);
	*/
	bool quit = false;
	while (quit == false) { 
		for (int i = 0; i < MAX_STAR; i++) { 
			MoveStar(i); 
		}
		if (isQuit()) { quit = true; }
		Sleep(50); 
	}
	system("pause");
	closegraph();
} 

