#pragma once
#include<iostream>
#include"Huffman.h"
#include"Compress.h"
#include"Unpack.h"
using namespace std;

//��һ���ֽڱ���ת��Ϊ�ַ���
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

//�ļ���Ϣ(��ȡ�ļ����ֽ���Ϣ�����ֽ���Ϣת��Ϊ0��1�ַ���ʾ�Ĺ�����������Ϣ�����뵽һ����ʱ�ļ�)
void Restore(char filename[],Head &head) {
	char huffile[256] = { 0 };
	strcpy_s(huffile, strlen(filename) + 1, filename);
	strcat_s(huffile, strlen(filename) + 5, ".huf");
	//���ļ�
	FILE* in = NULL;
	fopen_s(&in, huffile, "rb");
	int count = fread(&head, sizeof(Head), 1, in);
	if (count != 1) {
		cout << "��ȡ�ļ�ͷʧ�ܣ�" << endl;
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
		for (char c : str) { //�������ַ�д�뵽һ����ʱ�ļ�
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
	�������ȡ�����������ַ�ʱ������ȡ����0��������������������������ң�
	����ȡ����1�����������������ҡ����ڵ㵽��Ҷ�ӽڵ㣨û�������������
	�ڵ��������е��±꼴Ϊ��Ӧ���ֽڱ��룬����ʱ��ȡ�����ַ�Ϊ��һ������
	�ĵ�һ���ַ�����Ҫ���ڵ�ָ�����¶�λ�����ڵ����������0������������1����
	���ڻ�ȡ�����±�ʱ����Ҫ���Ҹýڵ�ĸ��ڵ㣬�����ݶ�ȡ����һ���ַ�����
	�ж���lchild��ֵ����rchild��ֵ��
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
	cout << "�ļ��ѻ�ԭΪ��" << outfile << endl;
}

//��ѹ�ļ�
void unzip(char filename[], HuffmanNode tree[], int length) {
	Head head;
	Restore(filename, head);
	//����ļ�ͷ��Ϣ
	cout << "��ѹ�ļ����ͣ�" << head.type << endl;
	cout << "ԭ�ļ��ֽ�����" << head.length << endl;
	/*
	cout << "Ȩ�أ�";
	for (int i = 0; i < 256; i++) {
		cout << head.weight[i] << " ";
	}
	cout << endl;
	*/
	Decompress(filename, tree, length);
}