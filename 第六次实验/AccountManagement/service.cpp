#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string>
#include "model.h"
#include "global.h"
#include "card_service.h"
#include "card_file.h"
#include "billing_file.h"
#include "billing_service.h"
#include "service.h"

int addCardInfo(Card card)
{
	if (TRUE == addCard(card))
		return TRUE;
	else
		return FALSE;
}
Card* queryCardInfo(const char* pName)
{
	Card* pCard = NULL;
	pCard=queryCard(pName);
	return pCard;
}
Card* queryCardsInfo(const char* pName, int* plndex)
{
	Card* pCard = NULL;
	pCard=queryCards(pName, plndex);
	return pCard;
}

void releaseList()
{
	releaseCardList();
}

int doSettle(const char* pName, const char* pPwd,SettleInfo*pInfo)
{
	Card* pCard = NULL;
	Billing* pBilling = NULL;
	double dbAmount = 0;//���ѽ��
	int nIndex = 0;//����Ϣ�������е�������
	int nPosition=0;//�Ʒ���Ϣ�������е�������
	float fBalance = 0;//���
	//�жϸÿ��Ƿ����ϻ���ֻ�������ϻ������ܽ����»�����
	pCard = checkCard(pName, pPwd,&nIndex);
	if (pCard == NULL)
		return FALSE;
	if (pCard->nStatus != 1)
		return UNUSE;
	//���ݿ��ţ���ѯ�Ʒ���Ϣ�������ѯ�Ʒ���ϢΪ�գ���ʾ�»�ʧ��
	pBilling = queryBilling(pName, &nPosition);
	if (pBilling == NULL)
	{
		return FALSE;
	}
	dbAmount = getAmount(pBilling->tStart);
	fBalance = pCard->fBalance - dbAmount;
	if (fBalance < 0)
	{
		return ENOUGHMONEY;
	}
	//��װ�»���Ϣ ���� ���ѽ�� ��� �ϻ�ʱ�� �»�ʱ��
	strcpy(pInfo->aCardName, pName);
	pInfo->fAmount = dbAmount;
	pInfo->fBalance = fBalance;
	pInfo->tStart = pBilling->tStart;
	pInfo->tEnd = time(NULL);
	//���¿���Ϣ ��� ��״̬ �ϴ�ʹ��ʱ��
	pCard->fBalance = fBalance;
	pCard->nStatus = 0;
	pCard->tLast = time(NULL);
	if (updateCard(pCard, CARDPATH, nIndex) == FALSE)
	{
		return FALSE;
	}
	//���¼Ʒ���Ϣ 
	pBilling->fAmount = dbAmount;
	pBilling->nStatus = 1;
	pBilling->tEnd = time(NULL);
	if (updataBilling(pBilling, BILLINGPATH, nPosition) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

double getAmount(time_t t)
{
	int nSec;
	int nMin;
	int nCount;
	double dbAmount;
	time_t tEnd = time(NULL);
	nSec = tEnd - t;//����
	nMin = nSec / 60;
	nCount = nMin / UNIT;
	if (nMin % UNIT != 0)
		nCount++;
	dbAmount = nCount * CHARGE;
	return dbAmount;
}
