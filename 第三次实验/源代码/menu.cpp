#include<iostream>
#include<ctime>
#include<string>
#include<cstdlib>
#include<iomanip>

#include"model.h"
#include"service.h"
#include"global.h"
#include"tool.h"
#include"card_service.h"
#include"card_file.h"
using namespace std;
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
	if (strlen(card.aName) > 18 || strlen(card.aPwd) > 8)
	{
		cout << "卡号或密码超过规定长度";
		return;
	}
	cout << "请输入开卡金额（RMB):";
	cin >> card.fBalance;
	cout << "添加卡信息成功！" << endl;
	card.fTotalUse = card.fBalance;
	card.nUseCount = 0;
	card.nStatus = 0;
	card.nDel = 0;
	card.tStart = card.tEnd = card.tLast = time(NULL);
	cout << endl;
	cout << "添加的卡信息如下：" << endl;
	cout << "卡号\t密码\t卡状态\t余额" << endl;
	cout << card.aName << '\t' << fixed << setprecision(1) << card.aPwd << '\t' << card.nStatus << '\t' << card.fBalance;
	addCard(card);
}
void query()
{
	cout << "----------查询卡----------" << endl;
	char aName[18] = { 0 };
	char aTime[20] = { 0 };
	Card* pCard = NULL;
	int pIndex = 0;
	cout << "请输入查询的卡号：";
	cin >> aName;
	//pCard = queryCard(aName);			//精确查找
	pCard = queryCards(aName, &pIndex);	//模糊查找
	//显示
	if (pCard == NULL || pIndex == 0)
		printf("没有查询到该卡信息\n");
	else
	{
		cout << "查询到的卡信息如下" << endl;
		cout << "卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间" << endl;
		int i = 0;
		while (i < pIndex)
		{
			timeToString((*(pCard + i)).tLast, aTime);
			cout << (pCard + i)->aName << '\t';
			cout << (pCard + i)->nStatus << '\t';
			cout << (pCard + i)->fBalance << "\t";
			cout << (pCard + i)->fTotalUse << "\t\t";
			cout << (pCard + i)->nUseCount << "\t\t";
			cout << aTime << endl;
			i++;
		}
	}
}
void exitApp()
{
	delete_list();
	cout << "----------退出----------" << endl;
}
void logon() 
{
	cout << "----------上机----------" << endl;
}
void settle()
{
	cout << "----------下机----------" << endl;
}
void annul()
{
	cout << "----------注销卡----------" << endl;
}
void addMoney()
{
	cout << "----------充值----------" << endl;
}
void refundMoney()
{
	cout << "----------退费----------" << endl;
}

