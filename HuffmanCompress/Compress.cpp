#pragma once
#include<iostream>
#include"Huffman.h"
#include"Compress.h"
using namespace std;

//将8个字符转换为一个字符
char StrByte(string str) {
	char b = 0x00;
	for (int i = 0; i < 8; i++) {
		b = b << 1;
		if (str[i] == '1') {
			b = b | 0x01;
		}
	}
	return b;
}

//返回压缩后的字节数
int Compress(HuffmanCode codes[], int weight[]) {
	int nSize = 0;
	for (int i = 0; i < 256; i++) {
		nSize += weight[i] * codes[i].len;
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	return nSize;
}

//压缩编码写入缓冲区
int Encode(char filename[], HuffmanCode codes[], char* pBuffer, int nSize) {
	//打开文件
	FILE* in = NULL;
	fopen_s(&in, filename, "rb");
	int ch;
	string StrFile = "";
	string s = "";
	int pos = 0;
	/*
	//test（将哈夫曼编码信息写入一个文件）
	FILE* temphuf = NULL;
	char tempfile[256] = { 0 };
	strcpy_s(tempfile, strlen(filename) + 1, filename);
	strcat_s(tempfile, strlen(filename) + 7, "0.temp");
	fopen_s(&temphuf, tempfile, "wb");
	*/
	//扫描文件(将哈夫曼编码存储为一个很长的字符串)
	while ((ch = fgetc(in)) != EOF) {
		StrFile = StrFile + codes[ch].str;
		if (StrFile.length() > 8) {
			s = StrFile.substr(0, 8);//截取前8个字符
			pBuffer[pos++] = StrByte(s);//向缓冲区中添加字节
			StrFile = StrFile.substr(8);//保留8位后面的字符
			/*
			//cout << s;//打印压缩字节信息
			for (int i = 0; i < 8; i++) {//test
				if (s[i] == '0') {
					fputc('0', temphuf);
				}
				else {
					fputc('1', temphuf);
				}
			}
			*/
		}
	}
	//最后剩余的字符如果不足8个，补0后将对应字节写入缓冲区
	if (StrFile != "") {
		StrFile = StrFile + "00000000";
		s = StrFile.substr(0, 8);
		pBuffer[pos] = StrByte(s);
	}
	fclose(in);
	in = NULL;
	/*
	fclose(temphuf);//test
	temphuf = NULL;//test
	*/
	return 0;
}

//初始化文件头信息
int InitHead(char filename[], Head &head) {
	//初始化
	strcpy_s(head.type,4, "HUF");
	head.length = 0;
	for (int i = 0; i < 256; i++) {
		head.weight[i] = 0;
	}
	//打开文件
	FILE* in = NULL;
	fopen_s(&in, filename, "rb");
	int ch;
	while ((ch = fgetc(in)) != EOF) {
		head.weight[ch]++;
		head.length++;
	}
	fclose(in);
	in = NULL;
	return 0;
}

//写入文件
int WriteFile(char filename[], Head head, char* pBuffer, int nSize) {
	//生成文件名
	char newname[256] = { 0 };
	strcpy_s(newname,strlen(filename)+1,filename);
	strcat_s(newname,strlen(filename)+5, ".huf");
	//打开文件（写）
	FILE* out = NULL;
	fopen_s(&out, newname, "wb");
	if (out == NULL) {
		cout << "文件打开失败！" << endl;
		return 0;
	}
	//写头文件
	fwrite(&head, sizeof(Head), 1, out);
	//写压缩后的编码
	fwrite(pBuffer, sizeof(char), nSize, out);
	//关闭文件
	fclose(out);
	out = NULL;
	string s = newname;
	cout << "生成压缩文件：" << s << endl;
	int len = sizeof(Head) + strlen(filename) + 1 + nSize;
	return len;
}
