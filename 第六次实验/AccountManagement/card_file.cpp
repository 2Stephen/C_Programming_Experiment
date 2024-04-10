#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#include "global.h"
#include "tool.h"
#include "card_file.h"
#include "card_service.h"
#define CARDCHARNUM 256
using namespace std;
//添加卡
int saveCard(const Card* pCard, const char* pPath)
{
	FILE* fp;
	char startTime[20] = { 0 };
	char endTime[20] = { 0 };
	char lastTime[20] = { 0 };
	//打开文件
	if ((fp = fopen(pPath, "a")) == NULL)
	{
		fp=fopen(pPath, "w");
		if (fp == NULL)
		{
			cout << "File open error!\n";
			exit(0);
		}
	}
	//将时间转换为字符串
	timeToString(pCard->tStart, startTime);
	timeToString(pCard->tEnd, endTime);
	timeToString(pCard->tLast, lastTime);
	//将数据写进文件
	fprintf(fp, "%s##%s##%d##%s##%s##%.1f##%s##%d##%.1f##%d\n", pCard->aName, pCard->aPwd, pCard->nStatus,startTime , endTime, pCard->fTotalUse, lastTime, pCard->nUseCount, pCard->fBalance, pCard->nDel);
	//关闭文件
	fclose(fp);
	return TRUE;
}

//从文件中读取卡信息
int readCard(Card* pCard, const char* pPath)
{
	FILE* fp;
	char aBuf[CARDCHARNUM] = { 0 };
	int i = 0;
	//打开
	fp = fopen(pPath, "r");
	if (fp == NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	//读取
	while (!feof(fp))
	{
		memset(aBuf, 0, CARDCHARNUM); //清空数组
		if (fgets(aBuf, CARDCHARNUM, fp) != NULL)
		{
			if (strlen(aBuf) > 0)
			{
				//调用praseCard(),解析读取的卡信息
				pCard[i] = praseCard(aBuf);
				i++;
			}
		}
	}
	//关闭
	fclose(fp);
	return TRUE;
}

//解析从文件中读取的卡信息
Card praseCard(char* pBuf)
{
	Card card;
	const char* delims = "##";//字符串中的分隔符
	char* buf = NULL;
	char* str = NULL;
	char flag[10][20] = { 0 };//保存分割后的字符串
	int index = 0;

	buf = pBuf;//第一次调用strtok时，buf为解析字符串
	while ((str = strtok(buf, delims)) != NULL)
	{
		strcpy(flag[index], str);
		buf = NULL;//后面调用strtok函数时，第一个参数为NULL
		index++;
	}
	strcpy(card.aName, flag[0]);
	strcpy(card.aPwd, flag[1]);
	card.nStatus = atoi(flag[2]);
	card.tStart = stringToTime(flag[3]);
	card.tEnd = stringToTime(flag[4]);
	card.fTotalUse = (float)atof(flag[5]);
	card.tLast = stringToTime(flag[6]);
	card.nUseCount = atoi(flag[7]);
	card.fBalance = (float)atof(flag[8]);
	card.nDel = atoi(flag[9]);
	return card;
}

//获取文件中卡信息的数量
int getCardCount(const char* pPath)
{
	FILE* fp;
	char aBuf[CARDCHARNUM] = { 0 };
	int nCount = 0;
	//打开
	fp = fopen(pPath, "r");
	if (fp == NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	//读取
	while (!feof(fp))
	{
		memset(aBuf, 0, CARDCHARNUM); //清空数组
		if (fgets(aBuf, CARDCHARNUM, fp) != NULL)
		{
			if (strlen(aBuf) > 0)
			{
				nCount++;
			}
		}
	}
	//关闭
	fclose(fp);
	return nCount;
}

int updateCard(const Card* pCard, const char* pPath, int nlndex)
{
	FILE* fp = NULL;
	int nLine = 0;
	char aBuf[CARDCHARNUM] = { 0 };
	long lPosition = 0;

	fp = fopen(pPath, "r+");//注意“+”，可以写入
	if (fp == NULL)
		return FALSE;
	//遍历文件，找到该条记录，进行更新
	while (!feof(fp) && nLine < nlndex)
	{
		if (fgets(aBuf, CARDCHARNUM, fp) != NULL)
		{
			lPosition = ftell(fp);
			nLine++;
		}
	}
	fseek(fp, lPosition, 0);
	//将数据写进文件
	char startTime[20] = { 0 };
	char endTime[20] = { 0 };
	char lastTime[20] = { 0 };
	timeToString(pCard->tStart, startTime);
	timeToString(pCard->tEnd, endTime);
	timeToString(pCard->tLast, lastTime);

	fprintf(fp, "%s##%s##%d##%s##%s##%.1f##%s##%d##%.1f##%d\n", pCard->aName, pCard->aPwd, pCard->nStatus, startTime, endTime, pCard->fTotalUse, lastTime, pCard->nUseCount, pCard->fBalance, pCard->nDel);

	fclose(fp);
	return TRUE;
}
