#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>//包含时间头文件
#include <string.h>//导入字符串处理函数
#include <stdlib.h>//包含动态内存分配头文件

#include "model.h"//包含数据定义头文件
#include "service.h"//包含业务处理头文件
#include "global.h"//包含全局定义头文件
#include "tool.h"//包含工具头文件
#include "card_service.h"
#include"card_file.h"
using namespace std;
int getSize(char* pInfo);
void outputMenu()
{
	cout << "----------菜单----------" << endl;
	cout << "1.添加卡" << endl;
	cout << "2.查询卡" << endl;
	cout << "3.上机" << endl;
	cout << "4.下机" << endl;
	cout << "5.充值" << endl;
	cout << "6.退费" << endl;
	cout << "7.查询统计" << endl;
	cout << "8.注销卡" << endl;
	cout << "0.退出" << endl;
	cout << "请选择菜单选编号（0~8）：";
}

void add()
{
	struct Card card;
	cout << "----------添加卡----------" << endl;
	cout << "请输入卡号（长度为1~18）：";
	cin >> card.aName;
	cout << "请输入密码（长度为1~8）：";
	cin >> card.aPwd;

	int nNameSize = getSize(card.aName);
	int nPwdSize = getSize(card.aPwd);
	if (nNameSize > 18 || nPwdSize > 8)
	{
		cout << "卡号或密码超过规定长度";
		cout << nNameSize << nPwdSize;
		return;
	}
	cout << "请输入开卡金额（RMB):";
	cin >> card.fBalance;
	card.fTotalUse=card.fBalance; card.nStatus = 0; card.nUseCount = 0; card.nDel = 0;
	card.tStart = card.tEnd = card.tLast = time(NULL);
	//printf("\n添加卡信息成功！\n");
	printf("\n-----添加卡的信息如下-----\n");
	printf("卡号\t密码\t卡状态\t余额\n");
	printf("%s\t%s\t%d\t%0.1f\n", card.aName, card.aPwd, card.nStatus, card.fBalance);

	struct tm* startTime, * endTime;
	startTime = localtime(&card.tStart);
	endTime = localtime(&card.tLast);
	endTime->tm_year = startTime->tm_year + 1;
	card.tEnd = mktime(endTime);

	if (FALSE == addCardInfo(card))
		printf("添加卡信息失败！\n");
	else
		printf("添加卡信息成功！\n");
}

int getSize(char* pInfo)
{
	int nSize = 0;
	while (*(pInfo + nSize) != '\0')
		nSize++;
	return nSize;
}

void query()
{
	char aName[18] = { 0 };
	char aTime[20] = { 0 };
	Card*pCard=NULL;

	int i = 0;
	int nlndex = 0;

	printf("请输入查询的卡号：");
	scanf("%s", aName);

	//查询卡
	//pCard=queryCardInfo(aName);
	//if (pCard == NULL)
	//	printf("没有查询到该卡信息\n");

	//else
	//{	//显示
	//	printf("查询到的卡信息如下\n");
	//	printf("卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间\n");
	//	//将时间转换为字符串
	//	timeToString(pCard->tLast, aTime);
	//	printf("%s\t%d\t%0.1f\t%0.1f\t\t%d\t\t%s\n", pCard->aName, pCard->nStatus, pCard->fBalance, pCard->fTotalUse, pCard->nUseCount, aTime);
	//}

	pCard = queryCardsInfo(aName, &nlndex);
	if (pCard == NULL||nlndex==0)
		printf("没有查询到该卡信息\n");
	else
	{	//显示
		printf("查询到的卡信息如下\n");
		for (i = 0; i < nlndex; i++)
		{
			printf("卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间\n");
			//将时间转换为字符串
			timeToString(pCard[i].tLast, aTime);
			printf("%s\t%d\t%0.1f\t%0.1f\t\t%d\t\t%s\n", pCard[i].aName, pCard[i].nStatus, pCard[i].fBalance, pCard[i].fTotalUse, pCard[i].nUseCount, aTime);
		}
	}
}

void logon()
{
	char aName[18] = { 0 };
	char aPwd[8] = { 0 };
	char aTime[20] = { 0 };
	Card* pCard = NULL;
	LogonInfo* pInfo = NULL;
	int nResult = 0;

	printf("请输入上机卡号（长度为1~18）：");
	scanf("%s", aName);
	printf("请输入上机密码（长度为1~8）：");
	scanf("%s", aPwd);

	pInfo = (LogonInfo*)malloc(sizeof(LogonInfo));
	//根据上机结果，提示不同信息
	nResult= doLogon(aName, aPwd,pInfo); 
	switch (nResult)
	{
	case 0:printf("上机失败！\n"); break;
	case 1:
		printf("--------上机信息如下--------\n卡号\t余额\t上机时间\n");
		timeToString(pInfo->tLogon, aTime);
		printf("%s\t%0.1f\t%s\n", pInfo->aCardName, pInfo->fBalance, aTime);
		break;
	case 2:printf("该卡正在使用或者已注销！"); break;
	case 3:printf("卡余额不足！"); break;
	}
	free(pInfo);
}

void settle()
{
	char aName[18] = { 0 };
	char aPwd[8] = { 0 };
	int nResult = -1;
	SettleInfo* pInfo = NULL;
	char aStartTime[20] = { 0 };
	char aEndTime[20] = { 0 };

	printf("--------下机--------\n");
	printf("请输入下机卡号（长度为1~18）：");
	scanf("%s", aName);
	printf("请输入下机密码（长度为1~8）：");
	scanf("%s", aPwd);
	pInfo = (SettleInfo*)malloc(sizeof(SettleInfo));
	nResult = doSettle(aName,aPwd,pInfo);
	printf("--------下机信息如下--------\n");
	switch (nResult)
	{
	case 0:printf("下机失败！\n"); break;
	case 1:printf("卡号\t消费\t余额\t上机时间\t\t下机时间\n");
		timeToString(pInfo->tStart, aStartTime);
		timeToString(pInfo->tEnd, aEndTime);
		printf("%s\t%0.1f\t%0.1f\t%s\t%s\n", pInfo->aCardName, pInfo->fAmount, pInfo->fBalance, aStartTime, aEndTime); break;
	case 2:printf("该卡正在使用或者已注销！"); break;
	case 3:printf("卡余额不足！"); break;
	}
	free(pInfo);
}

void exitApp()
{
	releaseList();
}

void annual()
{

}

void addMoney()
{

}

void refundMoney()
{

}
