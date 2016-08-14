#include "FileCompress.h"

void FileCompress::Compress(const std::string &FilePath)
{
	FILE *input = fopen(FilePath.c_str(), "rb");
	if (NULL == input)
	{
		std::cout << FilePath << " Not Found !" << std::endl;
		exit(1);
	}

	FillInfo(input);

	std::string CompressFileName;
	GetFileName(FilePath, CompressFileName);
	CompressFileName += ".gl";

	FILE *output = fopen(CompressFileName.c_str(), "wb");
	if (NULL == output)
	{
		std::cout << CompressFileName << " Can Not Be Create !" << std::endl;
		exit(2);
	}

	CompressCore(input, output, FilePath);

	fclose(input);
	fclose(output);
}

void FileCompress::UnCompress(const std::string &FilePath)
{
	FILE *input = fopen(FilePath.c_str(), "rb");
	if (NULL == input)
	{
		std::cout << FilePath << " Not Found !" << std::endl;
		exit(3);
	}

	// 处理头部信息
	std::string Postfix;
	GetHead(input, Postfix);
	
	 // 创建输出文件
	size_t begin = FilePath.find_first_of("\\");
	if (begin == std::string::npos)
		begin = -1;
	size_t end = FilePath.find_last_of(".");
	if (end == std::string::npos)
		end = FilePath.length();
	std::string FileName = FilePath.substr(begin + 1, end - begin - 1);
	FileName += Postfix;
	FILE *output = fopen(FileName.c_str(), "wb");
	if (NULL == output)
	{
		std::cout << FileName << " Can Not Open !" << std::endl;
		exit(4);
	}

	int i = 0;
	// 填充字符
	for (; i < 256; ++i)
	{
		info[i].ch = i;
	}
	
	CodeInfo invalid;
	invalid.cnt = 0;
	HuffmanTree<CodeInfo> hfm(info, 256, invalid);
	
	UnCompressCore(input, output, hfm.GetRoot());

	fclose(input);
	fclose(output);
}

void FileCompress::UnCompressCore(FILE *input, FILE *output, HuffmanTreeNode<CodeInfo> * pRoot)
{
	assert(NULL != input);
	assert(NULL != output);

	unsigned char ReadBuf[_SIZE_];
	unsigned char WriteBuf[_SIZE_];
	memset(WriteBuf, '\0', _SIZE_);

	size_t n;
	size_t w_idx = 0;
	size_t pos = 0;
	HuffmanTreeNode<CodeInfo> * pCur = pRoot;
	long long file_len = pRoot->_weight.cnt;
	do
	{
		memset(ReadBuf, '\0', _SIZE_);
		n = fread(ReadBuf, 1, _SIZE_, input);

		// 转换ReadBuf至WriteBuf
		size_t r_idx = 0;
		for (; r_idx < n; r_idx++)
		{
			// 转换单个字节
			unsigned char ch = ReadBuf[r_idx];
			for (; pos < 8; pos++, ch <<= 1)
			{
				if ((ch & 0x80) == 0x80)
				{
					pCur = pCur->pRight;
				}
				else
				{
					pCur = pCur->pLeft;
				}

				if (NULL == pCur->pLeft && NULL == pCur->pRight)
				{
					WriteBuf[w_idx++] = pCur->_weight.ch;
					pCur = pRoot;
					if (w_idx == _SIZE_)
					{
						fwrite(WriteBuf, 1, w_idx, output);
						memset(WriteBuf, '\0', _SIZE_);
						w_idx = 0;
					}
					file_len--;
				} // if
				if (file_len == 0)
					break;
			} // for
			if (pos == 8)
				pos = 0;

		} // for

	} while (n > 0);

	if (w_idx < _SIZE_ && w_idx > 0)
		fwrite(WriteBuf, 1, w_idx, output);
}

void FileCompress::GetHead(FILE *src, std::string &Postfix)
{
	assert(src);

	// 获取后缀名
	unsigned char buf[_FILE_NAME_SIZE_];
	int size = _FILE_NAME_SIZE_;
	GetLine(src, buf, size);
	Postfix += (char *)buf;

	// 获取行数
	GetLine(src, buf, size);
	int line = atoi((char *)buf);

	// 获取并设置字符出现次数
	while (line--)
	{
		GetLine(src, buf, size);
		info[*buf].cnt = atoi((char *)(buf + 2));
	}
}

void FileCompress::GetLine(FILE *src, unsigned char *buf, int size)
{
	assert(src);
	
	size_t n = 0;
	int index = 0;
	while (fread(buf + index, 1, 1, src) > 0)
	{
		if (index != 0 && buf[index] == '\n')
			break;

		index++;
	}
	buf[index] = '\0';
}


void FileCompress::GetFileName(const std::string &FilePath, std::string &output)
{
	// test.txt
	// f:\\ab\\c\\test.txt
	
	size_t begin = FilePath.find_last_of("\\");
	if (begin == std::string::npos)
	{
		begin = -1;
	}
	size_t end = FilePath.find_last_of(".");
	if (end == std::string::npos)
	{
		end = FilePath.length();
	}
	output = FilePath.substr(begin + 1, end - begin - 1);
}

void FileCompress::GetPostfixName(const std::string &FilePath, std::string &output)
{
	size_t begin = FilePath.find_last_of(".");
	if (begin != std::string::npos)
		output = FilePath.substr(begin, FilePath.length() - begin);
}

void FileCompress::FillInfo(FILE *src)
{
	assert(src);

	int i = 0;
	// 填充字符
	for (; i < 256; ++i)
	{
		info[i].ch = i;
	}

	// 填充出现次数
	unsigned char buf[_SIZE_];
	size_t n;
	do
	{
		n = fread(buf, 1, _SIZE_, src);
		size_t idx = 0;
		while (idx < n)
		{
			info[buf[idx++]].cnt++;
		}
	} while (n > 0);

	// 填充编码
	CodeInfo invalid;
	invalid.cnt = 0;
	HuffmanTree<CodeInfo> hfm(info, 256, invalid);

	FillCode(hfm.GetRoot());
}

void FileCompress::FillCode(const HuffmanTreeNode<CodeInfo> *pRoot)
{
	if (NULL != pRoot)
	{
		FillCode(pRoot->pLeft);
		FillCode(pRoot->pRight);

		if (NULL == pRoot->pLeft && NULL == pRoot->pRight)
		{
			const HuffmanTreeNode<CodeInfo> *tmp = pRoot;
			std::string code;
			const HuffmanTreeNode<CodeInfo> *pParent = tmp->pParent;
			while (NULL != pParent)
			{
				if (pParent->pLeft == tmp)
				{
					code += "0";
				}
				else
				{
					code += "1";
				}
				tmp = pParent;
				pParent = tmp->pParent;
			}
			std::reverse(code.begin(), code.end());
			info[pRoot->_weight.ch].code = code;
		}
	}
}

void FileCompress::CompressCore(FILE *src, FILE *dst, const std::string &FilePath)
{
	assert(NULL != src);
	assert(NULL != dst);

	fseek(src, 0, SEEK_SET);

	unsigned char buf[_SIZE_];
	unsigned char out[_SIZE_];
	int out_idx = 0;
	size_t n;
	int pos = 0;
	unsigned char ch = 0;

	SaveCode(dst, FilePath);
	
	// 读数据
	do
	{
		// 依次取每个字节转换
		memset(buf, '\0', _SIZE_);
		n = fread(buf, 1, _SIZE_, src);
		size_t idx = 0;
		while (idx < n)
		{
			// 转换单个字节
			const std::string &CurCode = info[buf[idx++]].code;
			size_t len = CurCode.length();
			size_t i_len = 0;
			while (i_len < len)
			{
				for (; pos < 8 && i_len < len; pos++)
				{
					ch <<= 1;
					if (CurCode[i_len++] == '1')
					{
						ch |= 1;
					}
				}
				
				// 先缓存到out
				if (8 == pos)
				{
					out[out_idx++] = ch;
					pos = 0;
					ch = 0;

					// 输出到文件
					if (_SIZE_ == out_idx)
					{
						fwrite(out, 1, out_idx, dst);
						out_idx = 0;
					}
				}
			} //while
		} // while
	} while (n > 0);

	// 处理剩余的位
	if (8 > pos && 0 < pos)
	{
		int j = 0;
		while (j++ < 8 - pos)
			ch <<= 1;
		out[out_idx++] = ch;
	}

	// 处理剩余的字节
	if (out_idx > 0)
		fwrite(out, 1, out_idx, dst);
}

void FileCompress::SaveCode(FILE *dst, const std::string &FilePath)
{
	// 压缩文件头格式:
	// 扩展名
	// 编码行数
	// 编码行 ...

	assert(NULL != dst);

	std::string output;
	GetPostfixName(FilePath, output);
	output += "\n";

	std::string code;
	int cnt = 0;
	unsigned char buf[33];
	for (int i = 0; i < 256; ++i)
	{
		if (info[i].cnt != 0)
		{
			cnt++;
			code += info[i].ch;
			code += ",";
			sprintf((char *)buf, "%lld", info[i].cnt);
			//_itoa((int)(info[i].cnt), (char *)buf, 10);
			code += (char *)buf;	//////////////////////////////////////////
			code += "\n";
		}
	}
	
	sprintf((char *)buf, "%d", cnt);
	//_itoa(cnt, (char *)buf, 10);
	output += (char *)buf;		////////////////////////
	output += "\n";
	output += code;

	fwrite(output.c_str(), 1, output.size(), dst);
}

