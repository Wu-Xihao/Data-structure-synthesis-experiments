#pragma once
#include<string>
#include"HUffman.H"
using namespace std;

struct Head {
	char type[4];//�ļ�����
	int length;//ԭ�ļ�����
	int weight[256];//Ȩֵ��ֵ
};

char StrByte(string str);
int Compress(HuffmanCode codes[], int weight[]);
int Encode(char filename[], HuffmanCode codes[], char* pBuffer, int nSize);
int InitHead(char filename[], Head& head);
int WriteFile(char filename[], Head head, char* pBuffer, int nSize);