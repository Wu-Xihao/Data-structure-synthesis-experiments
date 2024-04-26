#pragma once
#include<iostream>
#include"Huffman.h"
#include"Compress.h"
#include"Unpack.h"
using namespace std;

//将一个字节编码转换为字符串
string ByteStr(char c) {
	string str = "";
	for (int i = 0; i < 8; i++) {
		if (c & 0x01) {
			str = "1" + str;
		}
		else {
			str = "0" + str;
		}
		c = c >> 1;
	}
	return str;
}

//文件信息(读取文件的字节信息，将字节信息转换为0、1字符表示的哈夫曼编码信息并存入到一个临时文件)
void Restore(char filename[],Head &head) {
	char huffile[256] = { 0 };
	strcpy_s(huffile, strlen(filename) + 1, filename);
	strcat_s(huffile, strlen(filename) + 5, ".huf");
	//打开文件
	FILE* in = NULL;
	fopen_s(&in, huffile, "rb");
	int count = fread(&head, sizeof(Head), 1, in);
	if (count != 1) {
		cout << "读取文件头失败！" << endl;
		return;
	}
	char c;
	int ch = 0;
	string str = "";
	FILE* temp = NULL;
	char tempfile[256] = { 0 };
	strcpy_s(tempfile, strlen(filename) + 1, filename);
	strcat_s(tempfile, strlen(tempfile) + 6, ".temp");
	fopen_s(&temp, tempfile, "a+");
	while ((ch = fgetc(in)) != EOF) {
		c = (char)ch;
		str = ByteStr(c);
		for (char c : str) { //将编码字符写入到一个临时文件
			if (c == '0') {
				fputc('0', temp);
			}
			else if (c == '1') {
				fputc('1', temp);
			}
		}
	}
	fclose(in);
	fclose(temp);
	in = NULL;
	temp = NULL;
}

/*
	在逐个读取哈夫曼编码字符时，若读取到‘0’，则向哈夫曼树的左子树查找，
	若读取到‘1’，则向右子树查找。当节点到达叶子节点（没有子树），则该
	节点在数组中的下标即为对应的字节编码，而此时读取到的字符为下一个编码
	的第一个字符，需要将节点指针重新定位到根节点的左子树（0）或右子树（1）。
	而在获取数组下标时，需要查找该节点的父节点，并根据读取的上一个字符，来
	判断是lchild的值还是rchild的值。
*/
void Decompress(char filename[],HuffmanNode tree[],int length) {
	FILE* temp = NULL;
	FILE* out = NULL;
	char tempfile[256] = { 0 };
	char outfile[256] = { 0 };
	strcpy_s(tempfile, strlen(filename) + 1, filename);
	strcpy_s(outfile, strlen(filename) + 1, filename);
	strcat_s(tempfile, strlen(filename) + 6, ".temp");
	strcat_s(outfile, strlen(filename) + 5, ".bmp");
	fopen_s(&temp, tempfile, "rb");
	fopen_s(&out, outfile, "wb");
	int ch = 0;
	int lastch = 0;
	HuffmanNode node = tree[510];
	char c;
	int num = 0;
	
	while ((ch = fgetc(temp)) != EOF && num != length) {
		if (ch == '0') {
			if (node.lchild != -1) {
				node = tree[node.lchild];
			}
			else {
				if (lastch == '0') {
					fputc(tree[node.parent].lchild, out);
				}
				else {
					fputc(tree[node.parent].rchild, out);
				}
				node = tree[tree[510].lchild];
				num++;
			}
			lastch = ch;
		}
		else if (ch == '1') {
			if (node.rchild != -1) {
				node = tree[node.rchild];
			}
			else {
				if (lastch == '0') {
					fputc(tree[node.parent].lchild, out);
				}
				else {
					fputc(tree[node.parent].rchild, out);
				}
				node = tree[tree[510].rchild];
				num++;
			}
			lastch = ch;
		}
		
	}
	fclose(temp);
	fclose(out);
	temp = NULL;
	out = NULL;
	cout << "文件已还原为：" << outfile << endl;
}

//解压文件
void unzip(char filename[], HuffmanNode tree[], int length) {
	Head head;
	Restore(filename, head);
	//输出文件头信息
	cout << "解压文件类型：" << head.type << endl;
	cout << "原文件字节数：" << head.length << endl;
	/*
	cout << "权重：";
	for (int i = 0; i < 256; i++) {
		cout << head.weight[i] << " ";
	}
	cout << endl;
	*/
	Decompress(filename, tree, length);
}