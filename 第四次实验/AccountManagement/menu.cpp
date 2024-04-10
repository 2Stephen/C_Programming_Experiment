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
	struct Card card;
	cout << "----------��ӿ�----------" << endl;
	cout << "�����뿨�ţ�����Ϊ1~18����";
	cin >> card.aName;
	cout << "���������루����Ϊ1~8����";
	cin >> card.aPwd;
	if (strlen(card.aName) > 18 || strlen(card.aPwd) > 8)
	{
		cout << "���Ż����볬���涨����";
		return;
	}
	cout << "�����뿪����RMB):";
	cin >> card.fBalance;
	cout << "��ӿ���Ϣ�ɹ���" << endl;
	card.fTotalUse = card.fBalance;
	card.nUseCount = 0;
	card.nStatus = 0;
	card.nDel = 0;
	card.tStart = card.tEnd = card.tLast = time(NULL);
	cout << endl;
	cout << "��ӵĿ���Ϣ���£�" << endl;
	cout << "����\t����\t��״̬\t���" << endl;
	cout << card.aName << '\t' << fixed << setprecision(1) << card.aPwd << '\t' << card.nStatus << '\t' << card.fBalance;
	addCard(card);
}
void query()
{
	cout << "----------��ѯ��----------" << endl;
	char aName[18] = { 0 };
	char aTime[20] = { 0 };
	Card* pCard = NULL;
	int pIndex = 0;
	cout << "�������ѯ�Ŀ��ţ�";
	cin >> aName;
	//pCard = queryCard(aName);			//��ȷ����
	pCard = queryCards(aName, &pIndex);	//ģ������
	//��ʾ
	if (pCard == NULL || pIndex == 0)
		printf("û�в�ѯ���ÿ���Ϣ\n");
	else
	{
		cout << "��ѯ���Ŀ���Ϣ����" << endl;
		cout << "����\t״̬\t���\t�ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��" << endl;
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
	cout << "----------�˳�----------" << endl;
}
void logon() 
{
	cout << "----------�ϻ�----------" << endl;
}
void settle()
{
	cout << "----------�»�----------" << endl;
}
void annul()
{
	cout << "----------ע����----------" << endl;
}
void addMoney()
{
	cout << "----------��ֵ----------" << endl;
}
void refundMoney()
{
	cout << "----------�˷�----------" << endl;
}

