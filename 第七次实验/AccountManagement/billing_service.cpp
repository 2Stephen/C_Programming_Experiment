#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "model.h"
#include "global.h"
#include "billing_file.h"
#include"tool.h"
using namespace std;
lpBillingNode billingList = NULL;
lpBillingNode head1 = NULL;

void initBillingList()
{
	head1 = (lpBillingNode)malloc(sizeof(BillingNode));//强制类型转换
	if (billingList==NULL) //如果头结点分配成功
	{
		head1->next = NULL;
		billingList = head1;
	}
}

void releaseBillingList()
{
	lpBillingNode cur = billingList;
	lpBillingNode next = NULL;
	if (cur != NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	billingList = NULL;
}

int addBilling(Billing billing)
{
	lpBillingNode billingNode = NULL;
	lpBillingNode cur = NULL;
	if (billingList == NULL)
	{
		initBillingList();
	}
	cur = (lpBillingNode)malloc(sizeof(BillingNode));
	if (cur == NULL)
	{
		return FALSE;
	}
	cur->data = billing;
	cur->next = NULL;
	billingNode = billingList;
	while (billingNode->next != NULL)
	{
		billingNode=billingNode->next;
	}
	billingNode->next = cur;
	return saveBilling(&billing,BILLINGPATH);
}

//将计费信息保存到链表中
int getBilling()
{
	int nCount = 0;
	Billing*pBilling = NULL;
	lpBillingNode cur = NULL;
	lpBillingNode node = NULL;
	int i = 0;
	if (billingList != NULL)
	{
		releaseBillingList();
	}
	initBillingList();
	//获取卡信息数量
	nCount = getBillingCount(BILLINGPATH);
	//动态分配内存
	pBilling = (Billing*)malloc(sizeof(Billing) * nCount);
	if (pBilling == NULL)
	{
		return FALSE;
	}
	//获取卡信息
	if (readBilling(pBilling, BILLINGPATH) == FALSE)
	{
		free(pBilling);
		pBilling = NULL;
		return FALSE;
	}
	for (i = 0, node = billingList; i < nCount; i++)
	{
		cur = (lpBillingNode)malloc(sizeof(BillingNode));
		if (cur == NULL)
		{
			free(pBilling);
			return FALSE;
		}
		memset(cur, 0, sizeof(BillingNode));
		cur->data = pBilling[i];
		cur->next = NULL;
		node->next = cur;
		node = cur;
	}
	free(pBilling);
	pBilling = NULL;
	return TRUE;
}

Billing* queryBilling(const char* pName, int* pIndex)
{
	//根据卡号查找计费信息
	lpBillingNode cur = NULL;
	if (FALSE == getBilling())
	{
		return FALSE;
	}
	if (head1 != NULL)
	{
		cur = head1->next;
		while (cur != NULL)
		{
			if (strcmp(cur->data.aCardName, pName) == 0&&cur->data.nStatus==0)
			{
				return &cur->data;
			}
			cur = cur->next;
			(*pIndex)++;
		}
	}
	return NULL;
}

void ShowBilling(const char* pName)
{
	lpBillingNode node = NULL;
	int nIndex = 0;
	if (FALSE == getBilling())
	{
		return;
	}
	// 遍历链表
	node = billingList->next;
	while (node)
	{
		// 查询到卡号相同，并且没有结算的计费信息
		if (strcmp(node->data.aCardName, pName) == 0)
		{
			char tlogin[50] = { '\0' };
			char tlogout[20] = { '\0' };
			timeToString(node->data.tStart, tlogin);
			timeToString(node->data.tEnd, tlogout);
			cout << "卡号" << "\t上机时间" << "\t\t下机时间" << "\t\t消费金额" << endl;
			cout << node->data.aCardName << '\t' << tlogin << '\t' << tlogout << '\t' << node->data.fAmount << endl;
		}
		node = node->next;
	}
}