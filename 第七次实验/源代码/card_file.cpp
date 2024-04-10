#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#include "global.h"
#include "tool.h"
#include "card_file.h"
#include "card_service.h"
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
			printf("File open error!\n");
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
		printf("File open error!\n");
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

//解析从文件中读取的卡信息
//Card praseCard(char* pBuf)
//{
//	Card card;
//	const char* delims = "##";//字符串中的分隔符
//	char* buf = NULL;
//	char* str = NULL;
//	char flag[10][20] = { 0 };//保存分割后的字符串
//	int index = 0;
//
//	buf = pBuf;//第一次调用strtok时，buf为解析字符串
//	while ((str = strtok(buf, delims)) != NULL)
//	{
//		strcpy(flag[index], str);
//		buf = NULL;//后面调用strtok函数时，第一个参数为NULL
//		index++;
//	}
//	strcpy(card.aName, flag[0]);
//	strcpy(card.aPwd, flag[1]);
//	card.nStatus = atoi(flag[2]);
//	card.tStart = stringToTime(flag[3]);
//	card.tEnd = stringToTime(flag[4]);
//	card.fTotalUse = (float)atof(flag[5]);
//	card.tLast = stringToTime(flag[6]);
//	card.nUseCount = atoi(flag[7]);
//	card.fBalance = (float)atof(flag[8]);
//	card.nDel = atoi(flag[9]);
//	return card;
//}

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
		printf("File open error!\n");
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
	//遍历文件，找到该条记录，进行更新
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
