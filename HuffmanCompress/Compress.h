#pragma once
#include<string>
#include"HUffman.H"
using namespace std;

struct Head {
	char type[4];//文件类型
	int length;//原文件长度
	int weight[256];//权值数值
};

char StrByte(string str);
int Compress(HuffmanCode codes[], int weight[]);
int Encode(char filename[], HuffmanCode codes[], char* pBuffer, int nSize);
int InitHead(char filename[], Head& head);
int WriteFile(char filename[], Head head, char* pBuffer, int nSize);