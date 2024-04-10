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

//��ӿ�
int saveCard(const Card* pCard, const char* pPath)
{
	FILE* fp;
	//���ļ�
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
	//�ر��ļ�
	fclose(fp);
	return TRUE;
}

//���ļ��ж�ȡ����Ϣ
int readCard(Card* pCard, const char* pPath)
{
	FILE* fp;
	Card* p = (Card*)malloc(sizeof(Card));
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
		if (fread(p, sizeof(Card), 1, fp) != NULL)
		{
			if (p != 0)
			{
				pCard[i] = (*p) ;
				i++;
			}
		}
	}
	//�ر�
	fclose(fp);
	return TRUE;
}

//�������ļ��ж�ȡ�Ŀ���Ϣ
//Card praseCard(char* pBuf)
//{
//	Card card;
//	const char* delims = "##";//�ַ����еķָ���
//	char* buf = NULL;
//	char* str = NULL;
//	char flag[10][20] = { 0 };//����ָ����ַ���
//	int index = 0;
//
//	buf = pBuf;//��һ�ε���strtokʱ��bufΪ�����ַ���
//	while ((str = strtok(buf, delims)) != NULL)
//	{
//		strcpy(flag[index], str);
//		buf = NULL;//�������strtok����ʱ����һ������ΪNULL
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

//��ȡ�ļ��п���Ϣ������
int getCardCount(const char* pPath)
{
	FILE* fp;
	Card*aBuf=(Card*)malloc(sizeof(Card));
	int nCount = 0;
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
		if (fread(aBuf,sizeof(Card),1,fp) != NULL)
		{
			if(aBuf!=0)
				nCount++;
		}
	}
	free(aBuf);
	//�ر�
	fclose(fp);
	return nCount;
}

int updateCard(const Card* pCard, const char* pPath, int nlndex)
{
	FILE* fp = NULL;
	int nLine = 0;
	Card* aBuf = (Card*)malloc(sizeof(Card));
	long lPosition = 0;

	fp = fopen(pPath, "rb+");//ע�⡰+��������д��
	if (fp == NULL)
		return FALSE;
	//�����ļ����ҵ�������¼�����и���
	while (!feof(fp) && nLine < nlndex)
	{
		if (fread(aBuf,sizeof(Card),1,fp) != NULL)
		{
			lPosition = ftell(fp);
			nLine++;
		}
	}
	fseek(fp, lPosition, 0);
	//������д���ļ�
	fwrite(pCard, sizeof(Card), 1, fp);
	fclose(fp);
	return TRUE;
}
