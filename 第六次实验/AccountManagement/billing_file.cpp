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
//���Ʒ���Ϣ���浽billing.ams�ļ���
int saveBilling(const Billing*pBilling,const char*pPath)
{
	FILE* fp = NULL;
	char startTime[20] = { 0 };
	char endTime[20] = { 0 };
	//���ļ�
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
	//������д���������ļ�
	//fwrite(pBilling, sizeof(Billing), 1, fp);
	fclose(fp);
	return TRUE;
}

int readBilling(Billing* pBilling, const char* pPath)
{
	//��ȡ�Ʒ���Ϣ�ļ��е����мƷ���Ϣ
	FILE* fp;
	char aBuf[CARDCHARNUM] = { 0 };
	int i = 0;
	//��
	fp = fopen(pPath, "rb");
	if (fp == NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	//��ȡ
	while (!feof(fp))
	{
		memset(aBuf, 0, CARDCHARNUM); //�������
		if (fgets(aBuf, CARDCHARNUM, fp) != NULL)
		{
			if (strlen(aBuf) > 0)
			{
				//����praseBilling(),������ȡ�Ŀ���Ϣ
				pBilling[i] =praseBilling(aBuf);
				i++;
			}
		}
	}
	//�ر�
	fclose(fp);
	return TRUE;
}

//�������ļ��ж�ȡ�Ŀ���Ϣ
Billing praseBilling(char* pBuf)
{
	Billing billing;
	const char* delims = "##";//�ַ����еķָ���
	char* buf = NULL;
	char* str = NULL;
	char flag[10][20] = { 0 };//����ָ����ַ���
	int index = 0;

	buf = pBuf;//��һ�ε���strtokʱ��bufΪ�����ַ���
	while ((str = strtok(buf, delims)) != NULL)
	{
		strcpy(flag[index], str);
		buf = NULL;//�������strtok����ʱ����һ������ΪNULL
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
	//��ȡ�ļ��мƷ���Ϣ����
	FILE* fp;
	char aBuf[CARDCHARNUM] = { 0 };
	int nCount = 0;
	//��
	fp = fopen(BILLINGPATH, "rb");
	if (fp == NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	//��ȡ
	while (!feof(fp))
	{
		memset(aBuf, 0, CARDCHARNUM); //�������
		if (fgets(aBuf, CARDCHARNUM, fp) != NULL)
		{
			if (strlen(aBuf) > 0)
			{
				nCount++;
			}
		}
	}
	//�ر�
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

	fp = fopen(pPath, "r+");//ע�⡰+��������д��
	if (fp == NULL)
		return FALSE;
	//�����ļ����ҵ�������¼�����и���
	while (!feof(fp) && nLine < nIndex)
	{
		if (fgets(aBuf, CARDCHARNUM, fp) != NULL)
		{
			lPosition = ftell(fp);
			nLine++;
		}
	}
	fseek(fp, lPosition, 0);
	//������д���ļ�
	char startTime[20] = { 0 };
	char endTime[20] = { 0 };
	timeToString(pBilling->tStart, startTime);
	timeToString(pBilling->tEnd, endTime);

	fprintf(fp, "%s##%s##%s##%.1f##%d##%d\n", pBilling->aCardName, startTime, endTime, pBilling->fAmount, pBilling->nStatus, pBilling->nDel);
	fclose(fp);
	return TRUE;
}