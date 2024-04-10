#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <string>
#include "model.h"
#include "global.h"
#include "card_file.h"
#include "card_service.h"
#include <time.h>
#include "billing_service.h"

int nCount = 0;

lpCardNode head = NULL;
lpCardNode cardList = NULL;
//初始化链表
int initCardList()
{
	head = (lpCardNode)malloc(sizeof(CardNode));//强制类型转换
	if (head != NULL) //如果头结点分配成功
	{
		head->next = NULL;
		cardList = head;
		return TRUE;
	}
	return FALSE;
}

//释放链表
void releaseCardList()
{
	if (head != NULL)
	{
		lpCardNode cur = head->next;
		while (cur != NULL)
		{
			free(head);
			//head = NULL;
			head = cur;
			cur = cur->next;
		}
	}
}

Card* queryCard(const char* pName)
{
	lpCardNode cur = NULL;
	if (FALSE == getCard())
	{
		return FALSE;
	}
	if (head != NULL)
	{
		cur = head->next;
		while (cur != NULL)
		{
			if (strcmp(cur->data.aName, pName) == 0)
			{
				return &cur->data;
			}
			cur = cur->next;
		}
	}
	return NULL;
}

Card* queryCards(const char* pName, int* plndex)
{
	lpCardNode cur = NULL;
	Card* pCard = (Card*)malloc(sizeof(Card));
	if (FALSE == getCard())
	{
		return FALSE;
	}
	if (head != NULL)
	{
		cur = head->next;
		while (cur != NULL)
		{
			if (strstr(cur->data.aName, pName) != NULL)
			{
				pCard[*plndex] = cur->data;
				(*plndex)++;
				pCard = (Card*)realloc(pCard, ((*plndex) + 1) * sizeof(Card));
			}
			cur = cur->next;
		}
	}
	return pCard;
}

int addCard(Card card)
{
	return saveCard(&card, CARDPATH);
}

//将文件中的卡信息保存
int getCard()
{
	int nCount = 0;
	Card* pCard = NULL;
	lpCardNode cur = NULL;
	lpCardNode node = NULL;
	int i = 0;
	if (cardList != NULL)
	{
		releaseCardList();
	}
	initCardList();
	//获取卡信息数量
	nCount = getCardCount(CARDPATH);
	//动态分配内存
	pCard = (Card*)malloc(sizeof(Card) * nCount);
	if (pCard == NULL)
	{
		return FALSE;
	}
	//获取卡信息
	if (readCard(pCard, CARDPATH) == FALSE)
	{
		free(pCard);
		pCard = NULL;
		return FALSE;
	}
	for (i = 0, node = cardList; i < nCount; i++)
	{
		cur = (lpCardNode)malloc(sizeof(CardNode));
		if (cur == NULL)
		{
			free(pCard);
			return FALSE;
		}
		memset(cur, 0, sizeof(CardNode));
		cur->data = pCard[i];
		cur->next = NULL;
		node->next = cur;
		node = cur;
	}
	free(pCard);
	pCard = NULL;
	return TRUE;
}

int doLogon(const char* pName, const char* pPwd,LogonInfo* pLogonInfo)
{
	lpCardNode cardNode = NULL;
	int nlndex = 0;
	Billing billing;
	//获取文件中的卡信息
	if (getCard() == FALSE)
	{
		return FALSE;
	}
	cardNode = cardList->next;
	//遍历链表，判断能否上机
	while (cardNode != NULL)
	{
		if (strcmp(cardNode->data.aName, pName) == 0 && strcmp(cardNode->data.aPwd, pPwd) == 0)
		{
			//只有状态为未在使用，余额大于零的卡 才能进行上机
			if (cardNode->data.nStatus != 0)
			{
				return UNUSE;
			}
			if (cardNode->data.fBalance < 0||cardNode->data.fBalance==0)
			{
				return ENOUGHMONEY;
			}
			//更新链表中的信息
			cardNode->data.nStatus = 1;
			cardNode->data.nUseCount++;
			cardNode->data.tLast = time(NULL);
			//更新文件卡信息
			if (updateCard(&cardNode->data, CARDPATH, nlndex) ==TRUE)
			{
				strcpy(billing.aCardName, pName);
				billing.tStart = cardNode->data.tLast;
				billing.tEnd = 0;
				billing.nStatus = 0;
				billing.fAmount = 0;
				billing.nDel = 0;
				if (addBilling(billing) == TRUE)
				{
					strcpy(pLogonInfo->aCardName, pName);
					pLogonInfo->fBalance = cardNode->data.fBalance;
					pLogonInfo->tLogon = billing.tStart;
					return TRUE;
				}
			}
		}
		cardNode = cardNode->next;
		nlndex++;
	}
	return FALSE;
}

Card* checkCard(const char* pName, const char* pPwd,int*pIndex)
{
	lpCardNode cardNode = NULL;
	//获取文件中的卡信息
	if (getCard() == FALSE)
	{
		return NULL;
	}
	cardNode = cardList->next;
	//遍历链表，判断能否上机
	while (cardNode != NULL)
	{
		if (strcmp(cardNode->data.aName, pName) == 0 && strcmp(cardNode->data.aPwd, pPwd) == 0)
		{
			return &cardNode->data;
		}
		cardNode = cardNode->next;
		(*pIndex)++;
	}
	return NULL;
}