#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "HuffmanTree.hpp"

#define _SIZE_ 1024
#define _FILE_NAME_SIZE_ 128

struct CodeInfo
{
	CodeInfo()
		: code()
		, cnt(0)
	{}

	friend bool operator>(const CodeInfo &left, const CodeInfo &right)
	{
		return left.cnt > right.cnt;
	}

	friend bool operator!=(const CodeInfo &left, const CodeInfo &right)
	{
		return left.cnt != right.cnt;
	}

	friend CodeInfo operator+(const CodeInfo &left, const CodeInfo &right)
	{
		CodeInfo ret;
		ret.cnt = left.cnt + right.cnt;
		return ret;
	}

	unsigned char ch;	// 字符
	std::string code;	// 编码
	long long cnt;		// 出现次数
};


class FileCompress
{
public:
	// 压缩
	void Compress(const std::string &FilePath);

	// 解压缩
	void UnCompress(const std::string &FilePath);

private:
	// 获取文件名
	void GetFileName(const std::string &FilePath, std::string &output);

	// 获取扩展名
	void GetPostfixName(const std::string &FilePath, std::string &output);

	// 填充info信息
	void FillInfo(FILE *src);

	// 填充编码信息
	void FillCode(const HuffmanTreeNode<CodeInfo> *pRoot);

	// 核心压缩函数
	void CompressCore(FILE *src, FILE *dst, const std::string &FilePath);

	// 保存编码信息至压缩文件首部
	void SaveCode(FILE *dst, const std::string &FilePath);

	// 获取一行元素
	void GetLine(FILE *src, unsigned char *buf, int size);

	// 获取头部信息
	void GetHead(FILE *src, std::string &Postfix);
	
	// 核心解压函数
	void UnCompressCore(FILE *input, FILE *output, HuffmanTreeNode<CodeInfo> * pRoot);
private:
	CodeInfo info[256];
};

