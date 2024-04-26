#pragma once
#include<iostream>
#include"Huffman.h"
#include"Compress.h"
using namespace std;

//��8���ַ�ת��Ϊһ���ַ�
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

//����ѹ������ֽ���
int Compress(HuffmanCode codes[], int weight[]) {
	int nSize = 0;
	for (int i = 0; i < 256; i++) {
		nSize += weight[i] * codes[i].len;
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	return nSize;
}

//ѹ������д�뻺����
int Encode(char filename[], HuffmanCode codes[], char* pBuffer, int nSize) {
	//���ļ�
	FILE* in = NULL;
	fopen_s(&in, filename, "rb");
	int ch;
	string StrFile = "";
	string s = "";
	int pos = 0;
	/*
	//test����������������Ϣд��һ���ļ���
	FILE* temphuf = NULL;
	char tempfile[256] = { 0 };
	strcpy_s(tempfile, strlen(filename) + 1, filename);
	strcat_s(tempfile, strlen(filename) + 7, "0.temp");
	fopen_s(&temphuf, tempfile, "wb");
	*/
	//ɨ���ļ�(������������洢Ϊһ���ܳ����ַ���)
	while ((ch = fgetc(in)) != EOF) {
		StrFile = StrFile + codes[ch].str;
		if (StrFile.length() > 8) {
			s = StrFile.substr(0, 8);//��ȡǰ8���ַ�
			pBuffer[pos++] = StrByte(s);//�򻺳���������ֽ�
			StrFile = StrFile.substr(8);//����8λ������ַ�
			/*
			//cout << s;//��ӡѹ���ֽ���Ϣ
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
	//���ʣ����ַ��������8������0�󽫶�Ӧ�ֽ�д�뻺����
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

//��ʼ���ļ�ͷ��Ϣ
int InitHead(char filename[], Head &head) {
	//��ʼ��
	strcpy_s(head.type,4, "HUF");
	head.length = 0;
	for (int i = 0; i < 256; i++) {
		head.weight[i] = 0;
	}
	//���ļ�
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

//д���ļ�
int WriteFile(char filename[], Head head, char* pBuffer, int nSize) {
	//�����ļ���
	char newname[256] = { 0 };
	strcpy_s(newname,strlen(filename)+1,filename);
	strcat_s(newname,strlen(filename)+5, ".huf");
	//���ļ���д��
	FILE* out = NULL;
	fopen_s(&out, newname, "wb");
	if (out == NULL) {
		cout << "�ļ���ʧ�ܣ�" << endl;
		return 0;
	}
	//дͷ�ļ�
	fwrite(&head, sizeof(Head), 1, out);
	//дѹ����ı���
	fwrite(pBuffer, sizeof(char), nSize, out);
	//�ر��ļ�
	fclose(out);
	out = NULL;
	string s = newname;
	cout << "����ѹ���ļ���" << s << endl;
	int len = sizeof(Head) + strlen(filename) + 1 + nSize;
	return len;
}
