#pragma once
#include<string>
struct HuffmanNode {
	int weight;//Ȩֵ
	int parent;//���ڵ�
	int lchild;//����
	int rchild;//�Һ���
};
struct HuffmanCode {
	int len;//λ��
	int code;//ʮ���Ʊ���
	std::string str;//ת��Ϊ0/1��ʾ���ַ���
};
void HuffmanTree(int weight[], HuffmanNode tree[]);
int Select(HuffmanNode tree[], int num);
void TestHuffmanTree(HuffmanNode tree[]);
void PreHuffmanTree(HuffmanNode tree[], int root);
void HuffmanCoding(HuffmanNode tree[], int root, HuffmanCode codes[], int num, int level);
void PrintCode(HuffmanCode codes[], int size);
void ConvertHuffmanCode(HuffmanCode codes[], int size);