#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <string>
#include "model.h"
#include "global.h"
#include "tool.h"
#include "card_file.h"
#include "card_service.h"
using namespace std;
#define CARDCHARNUM 256

//添加卡
int saveCard(const Card* pCard, const char* pPath)
{
	FILE* fp;
	//打开文件
	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		fp=fopen(pPath, "wb");
		if (fp == NULL)
		{
			cout << "File open error!\n";
			exit(0);
		}
	}
	fwrite(pCard, sizeof(Card), 1, fp);
	//关闭文件
	fclose(fp);
	return TRUE;
}

//从文件中读取卡信息
int readCard(Card* pCard, const char* pPath)
{
	FILE* fp;
	Card* p = (Card*)malloc(sizeof(Card));
	int i = 0;
	//打开
	fp = fopen(pPath, "rb");
	if (fp == NULL)
	{
		cout << "File open error!\n";
		exit(0);
	}
	//读取
	while (!feof(fp))
	{
		if (fread(p, sizeof(Card), 1, fp) != NULL)
		{
			if (p != 0)
			{
				pCard[i] = (*p) ;
				i++;
			}
		}
	}
	//关闭
	fclose(fp);
	return TRUE;
}


//获取文件中卡信息的数量
int getCardCount(const char* pPath)
{
	FILE* fp;
	Card*aBuf=(Card*)malloc(sizeof(Card));
	int nCount = 0;
	//打开
	fp = fopen(pPath, "rb");
	if (fp == NULL)
	{
		cout << "File open error!\n";
		exit(0);
	}
	//读取
	while (!feof(fp))
	{
		if (fread(aBuf,sizeof(Card),1,fp) != NULL)
		{
			if(aBuf!=0)
				nCount++;
		}
	}
	free(aBuf);
	//关闭
	fclose(fp);
	return nCount;
}

int updateCard(const Card* pCard, const char* pPath, int nlndex)
{
	FILE* fp = NULL;
	int nLine = 0;
	Card* aBuf = (Card*)malloc(sizeof(Card));
	long lPosition = 0;

	fp = fopen(pPath, "rb+");//注意“+”，可以写入
	if (fp == NULL)
		return FALSE;
	//遍历文件
	while (!feof(fp) && nLine < nlndex)
	{
		if (fread(aBuf,sizeof(Card),1,fp) != NULL)
		{
			lPosition = ftell(fp);
			nLine++;
		}
	}
	fseek(fp, lPosition, 0);
	//将数据写进文件
	fwrite(pCard, sizeof(Card), 1, fp);
	fclose(fp);
	return TRUE;
}
