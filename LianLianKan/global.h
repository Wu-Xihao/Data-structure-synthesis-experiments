#pragma once

//顶点存储结构
typedef struct tagVertex {
	int row;	//行,y
	int col;	//列,x
	int info;	//信息类型
}Vertex;

#define BLANK -1		//空元素标识
#define ROWS 10			//行数
#define COLS 14			//列数
#define ELEMNUM 14		//元素种类数
#define ID_PLAY_GAME 1	//计时器标识符
#define GAMETIME 180	//游戏时长
#define GAMETOPX 50
#define GAMETOPY 50
#define ELEMSIZE 40
#define RECTWIDTH 40*16
#define RECTHEIGHT 40*12
#define CENTERX 40*7+50
#define CENTERY 40*5+50
#define GAMEDLGWIDTH 800
#define GAMEDLGHEIGHT 600

