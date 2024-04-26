#include<iostream>
#include<string>
#include<stdlib.h>
#include<iomanip>
#include"Huffman.h"
#include"Compress.h"
#include"Unpack.h"
using namespace std;

//��ӡȨ����Ϣ
void PrintWeight(int weight[]) {
	int num = 0;
	cout << "Byte" << '\t' << "Weight" << endl;
	for (int i = 0; i < 256; i++) {
		num += weight[i];
		//printf("0x%02X\t%d\n", i, weight);
		cout << "0x" << setw(2) << setfill('0') << setiosflags(ios::uppercase) << hex << i << '\t';
		cout << dec << weight[i] << endl;
	}
	cout << "�ֽ�ͳ�ƣ�" << num << endl;
}

//����������
void process() {
	cout << "====== Huffman�ļ�ѹ�� ======" << endl;
	cout << "�������ļ�����";
	//char filename[256] = { 0 };
	//cin >> filename;
	cout << "C:\\Users\\DELL\\Desktop\\pict.bmp" << endl;
	char filename[256] = "C:\\Users\\DELL\\Desktop\\pict.bmp";

	Head head;
	InitHead(filename, head);

	cout << "ԭ�ļ��ֽ�����" << head.length << endl;

	//��ӡȨ����Ϣ
	//PrintWeight(head.weight);

	HuffmanNode tree[256 * 2 - 1];
	HuffmanTree(head.weight, tree);

	//��ӡ���������ڵ���Ϣ
	//TestHuffmanTree(tree);

	//���������������
	//PreHuffmanTree(tree, 510);
	//cout << endl;

	//����������
	HuffmanCode codes[256 * 2 - 1];
	HuffmanCoding(tree, 510, codes, 0, 0);
	ConvertHuffmanCode(codes, 256);//ת��Ϊ����������
	PrintCode(codes, 256);//��ӡ����������

	//ѹ���ļ�����
	char* pBuffer = NULL;
	int nSize = Compress(codes, head.weight);//����ѹ������ֽ���
	pBuffer = (char*)malloc(nSize * sizeof(char));//�����ֽ������ٻ�����
	if (!pBuffer) {
		cerr << "���ٻ�����ʧ�ܣ�" << endl;
		return;
	}
	int flag = Encode(filename, codes, pBuffer, nSize);//ѹ������д�뻺����
	if (flag == -1) {
		return;
	}
	int len = WriteFile(filename, head, pBuffer, nSize);//���������ı�����Ϣд���ļ�
	free(pBuffer);//�ͷŻ������ڴ�
	cout << "ѹ���ļ��ֽ�����" << dec << len << endl;
	float rate = (float)(head.length - len) / head.length * 100;
	cout << "ѹ�����ʣ�" << rate << "%" << endl;

	//�ļ���ѹ����
	unzip(filename, tree,head.length);
}

void test() {
	char filename[256] = "C:\\Users\\DELL\\Desktop\\picture.bmp";
	char newfile[256] = "C:\\Users\\DELL\\Desktop\\picture1.bmp";
	FILE* in = NULL;
	FILE* out = NULL;
	fopen_s(&in, filename, "rb");
	fopen_s(&out, newfile, "wb");
	int ch = 0;
	while ((ch = fgetc(in)) != EOF) {
		fputc(ch, out);
	}
	fclose(in);
	fclose(out);
}

int main() {
	process();
	//test();
	return 0;
}