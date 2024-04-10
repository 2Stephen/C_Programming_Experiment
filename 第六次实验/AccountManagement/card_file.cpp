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
//��ӿ�
int saveCard(const Card* pCard, const char* pPath)
{
	FILE* fp;
	char startTime[20] = { 0 };
	char endTime[20] = { 0 };
	char lastTime[20] = { 0 };
	//���ļ�
	if ((fp = fopen(pPath, "a")) == NULL)
	{
		fp=fopen(pPath, "w");
		if (fp == NULL)
		{
			cout << "File open error!\n";
			exit(0);
		}
	}
	//��ʱ��ת��Ϊ�ַ���
	timeToString(pCard->tStart, startTime);
	timeToString(pCard->tEnd, endTime);
	timeToString(pCard->tLast, lastTime);
	//������д���ļ�
	fprintf(fp, "%s##%s##%d##%s##%s##%.1f##%s##%d##%.1f##%d\n", pCard->aName, pCard->aPwd, pCard->nStatus,startTime , endTime, pCard->fTotalUse, lastTime, pCard->nUseCount, pCard->fBalance, pCard->nDel);
	//�ر��ļ�
	fclose(fp);
	return TRUE;
}

//���ļ��ж�ȡ����Ϣ
int readCard(Card* pCard, const char* pPath)
{
	FILE* fp;
	char aBuf[CARDCHARNUM] = { 0 };
	int i = 0;
	//��
	fp = fopen(pPath, "r");
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
				//����praseCard(),������ȡ�Ŀ���Ϣ
				pCard[i] = praseCard(aBuf);
				i++;
			}
		}
	}
	//�ر�
	fclose(fp);
	return TRUE;
}

//�������ļ��ж�ȡ�Ŀ���Ϣ
Card praseCard(char* pBuf)
{
	Card card;
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

//��ȡ�ļ��п���Ϣ������
int getCardCount(const char* pPath)
{
	FILE* fp;
	char aBuf[CARDCHARNUM] = { 0 };
	int nCount = 0;
	//��
	fp = fopen(pPath, "r");
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
}

int updateCard(const Card* pCard, const char* pPath, int nlndex)
{
	FILE* fp = NULL;
	int nLine = 0;
	char aBuf[CARDCHARNUM] = { 0 };
	long lPosition = 0;

	fp = fopen(pPath, "r+");//ע�⡰+��������д��
	if (fp == NULL)
		return FALSE;
	//�����ļ����ҵ�������¼�����и���
	while (!feof(fp) && nLine < nlndex)
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
	char lastTime[20] = { 0 };
	timeToString(pCard->tStart, startTime);
	timeToString(pCard->tEnd, endTime);
	timeToString(pCard->tLast, lastTime);

	fprintf(fp, "%s##%s##%d##%s##%s##%.1f##%s##%d##%.1f##%d\n", pCard->aName, pCard->aPwd, pCard->nStatus, startTime, endTime, pCard->fTotalUse, lastTime, pCard->nUseCount, pCard->fBalance, pCard->nDel);

	fclose(fp);
	return TRUE;
}
