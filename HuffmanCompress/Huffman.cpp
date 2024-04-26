#pragma once 
#include"Huffman.h"
#include<iostream>
#include<string>
#include<stdlib.h>
#include<iomanip>
#include<bitset>
using namespace std;

//������������
void HuffmanTree(int weight[], HuffmanNode tree[]) {
	int length = 256;//Ҷ�ӽڵ����
	int num = 2 * length - 1;
	//����Ҷ�ӽڵ�
	for (int i = 0; i < num; i++) {
		if (i < length) {
			tree[i].weight = weight[i];
		}
		else {
			tree[i].weight = -1;
		}
		tree[i].parent = -1;
		tree[i].lchild = -1;
		tree[i].rchild = -1;
	}
	//�����Ҷ�ӽڵ�
	int min1, min2;
	for (int i = 0; i < length - 1; i++) {
		//�ҵ�������С�ڵ�,�������丸�ڵ�
		min1 = Select(tree, length + i);
		tree[min1].parent = length + i;
		min2 = Select(tree, length + i);
		tree[min2].parent = length + i;
		//���ø��ڵ����Ϣ
		tree[length + i].weight = tree[min1].weight + tree[min2].weight;
		tree[length + i].lchild = min1;
		tree[length + i].rchild = min2;
	}
}

//ѡ��Ȩ����С�Ľڵ�
int Select(HuffmanNode tree[],int num) {
	int min = 0;
	int minValue = INT32_MAX;
	for (int i = 0; i < num; i++) {
		if (tree[i].parent == -1 && tree[i].weight < minValue) {
			minValue = tree[i].weight;
			min = i;
		}
	}
	return min;
}

//������������ڵ���Ϣ
void TestHuffmanTree(HuffmanNode tree[]) {
	cout << "���������ڵ���Ϣ��" << endl;
	cout << "TheNode" << '\t' << "Weight" << '\t' << "Parent" << '\t' << "LChild" << '\t' << "RChild" << endl;
	for (int i = 1; i < 512; i++) {
		cout << "Node[" << i << "]" << '\t' << tree[i - 1].weight << '\t' << tree[i - 1].parent << '\t' << tree[i - 1].lchild << '\t' << tree[i - 1].rchild << endl;
	}
}

//���������������
void PreHuffmanTree(HuffmanNode tree[],int root) {
	cout << tree[root].weight << " ";
	if (tree[root].lchild != -1) {
		PreHuffmanTree(tree, tree[root].lchild);
	}
	if (tree[root].rchild != -1) {
		PreHuffmanTree(tree, tree[root].rchild);
	}
}

//����������
void HuffmanCoding(HuffmanNode tree[], int root, HuffmanCode codes[], int num, int level) {
	codes[root].code = num;
	codes[root].len = level;
	if (tree[root].lchild != -1) {
		
		HuffmanCoding(tree, tree[root].lchild, codes, num << 1, level + 1);
	}
	if (tree[root].rchild != -1) {
		HuffmanCoding(tree, tree[root].rchild, codes, (num << 1) + 1, level + 1);
	}
}
//��ӡ������Ϣ
void PrintCode(HuffmanCode codes[], int size) {
	cout << "Byte" << '\t' << "HuffmanCode" << endl;
	for (int i = 0; i < size; i++) {
		cout << "0x" << setw(2) << setfill('0') << setiosflags(ios::uppercase) << hex << i << '\t';
		cout << codes[i].str << endl;
	}
}
//������Ϣת��
void ConvertHuffmanCode(HuffmanCode codes[], int size) {
	for (int i = 0; i < size; i++) {
		int num = 0;
		int code = codes[i].code;
		int level = codes[i].len;
		string str = "";
		int temp = 0;
		while (code != 0) {
			temp = code % 2;
			code /= 2;
			if (temp) {
				str = "1" + str;//str.insert(0,"1");
			}
			else {
				str = "0" + str;
			}
			num++;
		}
		for (int k = 0; k < level - num; k++) {
			str = "0" + str;
		}
		codes[i].str = str;
	}
}