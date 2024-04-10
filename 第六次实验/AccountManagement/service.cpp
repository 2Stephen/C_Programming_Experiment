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
	double dbAmount = 0;//消费金额
	int nIndex = 0;//卡信息在链表中的索引号
	int nPosition=0;//计费信息在链表中的索引号
	float fBalance = 0;//余额
	//判断该卡是否在上机，只有正在上机卡才能进行下机操作
	pCard = checkCard(pName, pPwd,&nIndex);
	if (pCard == NULL)
		return FALSE;
	if (pCard->nStatus != 1)
		return UNUSE;
	//根据卡号，查询计费信息，如果查询计费信息为空，表示下机失败
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
	//组装下机信息 卡号 消费金额 余额 上机时间 下机时间
	strcpy(pInfo->aCardName, pName);
	pInfo->fAmount = dbAmount;
	pInfo->fBalance = fBalance;
	pInfo->tStart = pBilling->tStart;
	pInfo->tEnd = time(NULL);
	//更新卡信息 余额 卡状态 上次使用时间
	pCard->fBalance = fBalance;
	pCard->nStatus = 0;
	pCard->tLast = time(NULL);
	if (updateCard(pCard, CARDPATH, nIndex) == FALSE)
	{
		return FALSE;
	}
	//更新计费信息 
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
	nSec = tEnd - t;//秒数
	nMin = nSec / 60;
	nCount = nMin / UNIT;
	if (nMin % UNIT != 0)
		nCount++;
	dbAmount = nCount * CHARGE;
	return dbAmount;
}
