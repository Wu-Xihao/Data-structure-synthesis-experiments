#pragma once

//����洢�ṹ
typedef struct tagVertex {
	int row;	//��,y
	int col;	//��,x
	int info;	//��Ϣ����
}Vertex;

#define BLANK -1		//��Ԫ�ر�ʶ
#define ROWS 10			//����
#define COLS 14			//����
#define ELEMNUM 14		//Ԫ��������
#define ID_PLAY_GAME 1	//��ʱ����ʶ��
#define GAMETIME 180	//��Ϸʱ��
#define GAMETOPX 50
#define GAMETOPY 50
#define ELEMSIZE 40
#define RECTWIDTH 40*16
#define RECTHEIGHT 40*12
#define CENTERX 40*7+50
#define CENTERY 40*5+50
#define GAMEDLGWIDTH 800
#define GAMEDLGHEIGHT 600

