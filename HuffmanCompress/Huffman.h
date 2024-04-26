#pragma once
#include<string>
struct HuffmanNode {
	int weight;//权值
	int parent;//父节点
	int lchild;//左孩子
	int rchild;//右孩子
};
struct HuffmanCode {
	int len;//位数
	int code;//十进制编码
	std::string str;//转换为0/1表示的字符串
};
void HuffmanTree(int weight[], HuffmanNode tree[]);
int Select(HuffmanNode tree[], int num);
void TestHuffmanTree(HuffmanNode tree[]);
void PreHuffmanTree(HuffmanNode tree[], int root);
void HuffmanCoding(HuffmanNode tree[], int root, HuffmanCode codes[], int num, int level);
void PrintCode(HuffmanCode codes[], int size);
void ConvertHuffmanCode(HuffmanCode codes[], int size);