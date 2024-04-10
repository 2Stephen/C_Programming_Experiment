#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>//����ʱ��ͷ�ļ�
#include <string>//�����ַ���������
#include <cstdlib>//������̬�ڴ����ͷ�ļ�
#include "model.h"//�������ݶ���ͷ�ļ�
#include "service.h"//����ҵ����ͷ�ļ�
#include "global.h"//����ȫ�ֶ���ͷ�ļ�
#include "tool.h"//��������ͷ�ļ�
#include "card_service.h"
#include"card_file.h"
#include"billing_service.h"
using namespace std;

extern lpBillingNode billingList;
extern lpBillingNode head1;
int getSize(char* pInfo);
void outputMenu()
{
	cout << "----------�˵�----------" << endl;
	cout << "1.��ӿ�" << endl;
	cout << "2.��ѯ��" << endl;
	cout << "3.�ϻ�" << endl;
	cout << "4.�»�" << endl;
	cout << "5.��ֵ" << endl;
	cout << "6.�˷�" << endl;
	cout << "7.��ѯͳ��" << endl;
	cout << "8.ע����" << endl;
	cout << "0.�˳�" << endl;
	cout << "��ѡ��˵�ѡ��ţ�0~8����";
}

void add()
{
	Card card;
	cout << "----------��ӿ�----------\n";
	cout << "�����뿨��<����Ϊ1~18>��";
	cin >> card.aName;
	cout << "����������<����Ϊ1~8>��";
	cin >> card.aPwd;

	int nNameSize = getSize(card.aName);
	int nPwdSize = getSize(card.aPwd);
	if (nNameSize > 18 || nPwdSize > 8)
	{
		cout << "���Ż����볬���涨����";
		cout << nNameSize << nPwdSize;
		return;
	}
	cout << "�����뿪�����<RMB>��";
	cin >> card.fBalance;
	card.fTotalUse=card.fBalance; card.nStatus = 0; card.nUseCount = 0; card.nDel = 0;
	card.tStart = card.tEnd = card.tLast = time(NULL);
	cout << "\n-----��ӿ�����Ϣ����-----\n";
	cout << "����\t����\t��״̬\t���\n";
	cout << card.aName << '\t' << card.aPwd << '\t' << card.nStatus << '\t' << card.fBalance << endl;

	struct tm* startTime, * endTime;
	startTime = localtime(&card.tStart);
	endTime = localtime(&card.tLast);
	endTime->tm_year = startTime->tm_year + 1;
	card.tEnd = mktime(endTime);

	if (FALSE == addCardInfo(card))
		cout << "��ӿ���Ϣʧ�ܣ�\n";
	else
		cout << "��ӿ���Ϣ�ɹ���\n";
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

	cout << "�������ѯ�Ŀ��ţ�";
	cin >> aName;
	pCard = queryCardsInfo(aName, &nlndex);
	if (pCard == NULL || nlndex == 0)
		cout << "û�в�ѯ���ÿ���Ϣ\n";
	else
	{	//��ʾ
		cout << "��ѯ���Ŀ���Ϣ����\n";
		for (i = 0; i < nlndex; i++)
		{
			cout << "����\t״̬\t���\t�ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n";
			//��ʱ��ת��Ϊ�ַ���
			timeToString(pCard[i].tLast, aTime);
			//�˴���printf��cout����
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

	cout << "�������ϻ����ţ�����Ϊ1~18����";
	cin >> aName;
	cout << "�������ϻ����루����Ϊ1~8����";
	cin >> aPwd;

	pInfo = (LogonInfo*)malloc(sizeof(LogonInfo));
	//�����ϻ��������ʾ��ͬ��Ϣ
	nResult= doLogon(aName, aPwd,pInfo); 
	switch (nResult)
	{
	case 0:cout << "�ϻ�ʧ�ܣ�\n"; break;
	case 1:
		cout << "--------�ϻ���Ϣ����--------\n����\t���\t�ϻ�ʱ��\n";
		timeToString(pInfo->tLogon, aTime);
		printf("%s\t%0.1f\t%s\n", pInfo->aCardName, pInfo->fBalance, aTime);
		break;
	case 2:cout << "�ÿ�����ʹ�û�����ע����"; break;
	case 3:cout << "�����㣡"; break;
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

	cout << "--------�»�--------\n";
	cout << "�������»����ţ�����Ϊ1~18����";
	cin >> aName;
	cout << "�������»����루����Ϊ1~8����";
	cin >> aPwd;
	pInfo = (SettleInfo*)malloc(sizeof(SettleInfo));
	nResult = doSettle(aName,aPwd,pInfo);
	cout << "--------�»���Ϣ����--------\n";
	switch (nResult)
	{
	case 0:cout << "�»�ʧ�ܣ�\n"; break;
	case 1:cout << "����\t����\t���\t�ϻ�ʱ��\t\t�»�ʱ��\n";
		timeToString(pInfo->tStart, aStartTime);
		timeToString(pInfo->tEnd, aEndTime);
		printf("%s\t%0.1f\t%0.1f\t%s\t%s\n", pInfo->aCardName, pInfo->fAmount, pInfo->fBalance, aStartTime, aEndTime);
		break;
	case 2:cout << "�ÿ������ڻ�����ע����"; break;
	case 3:cout << "�����㣡"; break;
	}
	free(pInfo);
}

void addMoney()
{
	char aName[18] = { 0 };
	char aPwd[8] = { 0 };
	float money = 0;
	int nResult = -1;
	MoneyInfo* pInfo = NULL;

	cout << "--------��ֵ--------\n";
	cout << "�������ֵ���ţ�����Ϊ1~18����";
	cin >> aName;
	cout << "�������ֵ���루����Ϊ1~8����";
	cin >> aPwd;
	cout << "�������ֵ��RMB����";
	cin >> money;
	pInfo = (MoneyInfo*)malloc(sizeof(MoneyInfo));
	strcpy(pInfo->aCardName, aName);
	pInfo->fMoney = money;
	nResult = doAddMoney(aName, aPwd, pInfo);
	cout << "--------��ֵ��Ϣ����--------\n";
	if (nResult == 0)
		cout << "��ֵʧ�ܣ�\n";
	else if (nResult == 1)
	{
		cout << "����\t��ֵ���\t���\n";
		printf("%s\t%0.1f\t\t%0.1f\n", pInfo->aCardName, pInfo->fMoney,pInfo->fBalance); 
	}
	free(pInfo);
}

void refundMoney()
{
	char aName[18] = { 0 };
	char aPwd[8] = { 0 };
	int nResult = -1;
	MoneyInfo* pInfo = NULL;

	cout << "--------�˷�--------\n";
	cout << "�������˷ѿ��ţ�����Ϊ1~18����";
	cin >> aName;
	cout << "�������˷����루����Ϊ1~8����";
	cin >> aPwd;
	pInfo = (MoneyInfo*)malloc(sizeof(MoneyInfo));
	nResult = doRefundMoney(aName, aPwd, pInfo);
	cout << "--------�˷���Ϣ����--------\n";
	switch (nResult)
	{
	case 0:	cout << "�˷�ʧ�ܣ�\n"; break;
	case 1:	cout << "����\t�˷ѽ��\t���\n";
			cout << pInfo->aCardName << '\t' << pInfo->fMoney << "\t\t" << pInfo->fBalance;
			break;
	case 2:	cout << "�ÿ������ϻ�����ע����"; break;
	case 3:	cout << "�����㣡"; break;
	}
	free(pInfo);
}

void annual()
{
	char aName[18] = { 0 };
	char aPwd[8] = { 0 };
	int nResult = -1;
	Card* pCard = NULL;

	cout << "--------ע����--------\n";
	cout << "������ע�����ţ�����Ϊ1~18����";
	cin >> aName;
	cout << "���������루����Ϊ1~8����";
	cin >> aPwd;
	pCard = (Card*)malloc(sizeof(Card));
	strcpy(pCard->aName, aName);
	strcpy(pCard->aPwd, aPwd);
	nResult = annulCard(pCard);
	cout << "--------ע����Ϣ����--------\n";
	if (nResult == 0)
		cout << "ע����ʧ�ܣ�\n";
	else if (nResult == 1)
	{
		cout << "����\t�˿���\n";
		cout << pCard->aName << '\t' << pCard->fBalance;
	}
	free(pCard);
}

void exitApp()
{
	releaseList();
}

void querycount()
{
	cout << "-----------��ѯͳ��----------\n";
	char aName[18] = { 0 };    // ����
	char aPwd[8] = { 0 };      // ������
	cout << "�������ѯ���ţ�";
	cin >> aName;
	getBilling();
	int cardIndex = -1;
	Billing* pBilling = queryBilling(aName, &cardIndex);
	if (pBilling != NULL)
	{
		ShowBilling(aName);
	}
}
