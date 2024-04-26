#include<iostream>
#include<string>
#include<stdlib.h>
#include<iomanip>
#include"Huffman.h"
#include"Compress.h"
#include"Unpack.h"
using namespace std;

//打印权重信息
void PrintWeight(int weight[]) {
	int num = 0;
	cout << "Byte" << '\t' << "Weight" << endl;
	for (int i = 0; i < 256; i++) {
		num += weight[i];
		//printf("0x%02X\t%d\n", i, weight);
		cout << "0x" << setw(2) << setfill('0') << setiosflags(ios::uppercase) << hex << i << '\t';
		cout << dec << weight[i] << endl;
	}
	cout << "字节统计：" << num << endl;
}

//程序主过程
void process() {
	cout << "====== Huffman文件压缩 ======" << endl;
	cout << "请输入文件名：";
	//char filename[256] = { 0 };
	//cin >> filename;
	cout << "C:\\Users\\DELL\\Desktop\\pict.bmp" << endl;
	char filename[256] = "C:\\Users\\DELL\\Desktop\\pict.bmp";

	Head head;
	InitHead(filename, head);

	cout << "原文件字节数：" << head.length << endl;

	//打印权重信息
	//PrintWeight(head.weight);

	HuffmanNode tree[256 * 2 - 1];
	HuffmanTree(head.weight, tree);

	//打印哈夫曼树节点信息
	//TestHuffmanTree(tree);

	//先序遍历哈夫曼树
	//PreHuffmanTree(tree, 510);
	//cout << endl;

	//哈夫曼编码
	HuffmanCode codes[256 * 2 - 1];
	HuffmanCoding(tree, 510, codes, 0, 0);
	ConvertHuffmanCode(codes, 256);//转换为哈夫曼编码
	PrintCode(codes, 256);//打印哈夫曼编码

	//压缩文件操作
	char* pBuffer = NULL;
	int nSize = Compress(codes, head.weight);//返回压缩后的字节数
	pBuffer = (char*)malloc(nSize * sizeof(char));//根据字节数开辟缓冲区
	if (!pBuffer) {
		cerr << "开辟缓冲区失败！" << endl;
		return;
	}
	int flag = Encode(filename, codes, pBuffer, nSize);//压缩编码写入缓冲区
	if (flag == -1) {
		return;
	}
	int len = WriteFile(filename, head, pBuffer, nSize);//将缓冲区的编码信息写入文件
	free(pBuffer);//释放缓冲区内存
	cout << "压缩文件字节数：" << dec << len << endl;
	float rate = (float)(head.length - len) / head.length * 100;
	cout << "压缩比率：" << rate << "%" << endl;

	//文件解压操作
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