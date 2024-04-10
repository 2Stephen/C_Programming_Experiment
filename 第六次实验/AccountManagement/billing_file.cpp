#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "model.h"
#include "global.h"
#include "tool.h"
#include "stdlib.h"
#include "string.h"
#include "billing_service.h"
#include "billing_file.h"
#define CARDCHARNUM 256
//将计费信息保存到billing.ams文件中
int saveBilling(const Billing*pBilling,const char*pPath)
{
	FILE* fp = NULL;
	char startTime[20] = { 0 };
	char endTime[20] = { 0 };
	//打开文件
	if ((fp = fopen(pPath, "a")) == NULL)
	{
		fp = fopen(pPath, "w");
		if (fp == NULL)
		{
			printf("File open error!\n");
			exit(0);
		}
	}
	timeToString(pBilling->tStart, startTime);
	timeToString(pBilling->tEnd, endTime);
	fprintf(fp, "%s##%s##%s##%.1f##%d##%d\n", pBilling->aCardName, startTime, endTime, pBilling->fAmount, pBilling->nStatus, pBilling->nDel);
	/*fp = fopen(pPath, "ab");
	if (fp == NULL)
	{
		return FALSE;
	}*/
	//将数据写进二进制文件
	//fwrite(pBilling, sizeof(Billing), 1, fp);
	fclose(fp);
	return TRUE;
}

int readBilling(Billing* pBilling, const char* pPath)
{
	//读取计费信息文件中的所有计费信息
	FILE* fp;
	char aBuf[CARDCHARNUM] = { 0 };
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
		memset(aBuf, 0, CARDCHARNUM); //清空数组
		if (fgets(aBuf, CARDCHARNUM, fp) != NULL)
		{
			if (strlen(aBuf) > 0)
			{
				//调用praseBilling(),解析读取的卡信息
				pBilling[i] =praseBilling(aBuf);
				i++;
			}
		}
	}
	//关闭
	fclose(fp);
	return TRUE;
}

//解析从文件中读取的卡信息
Billing praseBilling(char* pBuf)
{
	Billing billing;
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
	strcpy(billing.aCardName, flag[0]);
	billing.tStart = stringToTime(flag[1]);
	billing.tEnd = stringToTime(flag[2]);
	billing.fAmount = (float)atof(flag[3]);
	billing.nStatus = atoi(flag[4]);
	billing.nDel = atoi(flag[5]);
	return billing;
}

int getBillingCount(const char* pPath)
{
	//读取文件中计费信息数量
	FILE* fp;
	char aBuf[CARDCHARNUM] = { 0 };
	int nCount = 0;
	//打开
	fp = fopen(BILLINGPATH, "rb");
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
	return 0;
}

int updataBilling(Billing*pBilling,const char*pPath,int nIndex)
{
	FILE* fp = NULL;
	int nLine = 0;
	char aBuf[CARDCHARNUM] = { 0 };
	long lPosition = 0;

	fp = fopen(pPath, "r+");//注意“+”，可以写入
	if (fp == NULL)
		return FALSE;
	//遍历文件，找到该条记录，进行更新
	while (!feof(fp) && nLine < nIndex)
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
	timeToString(pBilling->tStart, startTime);
	timeToString(pBilling->tEnd, endTime);

	fprintf(fp, "%s##%s##%s##%.1f##%d##%d\n", pBilling->aCardName, startTime, endTime, pBilling->fAmount, pBilling->nStatus, pBilling->nDel);
	fclose(fp);
	return TRUE;
}