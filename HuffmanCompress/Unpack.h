#pragma once
#include<iostream>
#include<string>
#include"Huffman.h"
#include"Compress.h"
using namespace std;

string ByteStr(char c);
void Restore(char huffile[], Head& head);
void Decompress(char filename[], HuffmanNode tree[], int nSize);
void unzip(char filename[], HuffmanNode tree[], int length);
