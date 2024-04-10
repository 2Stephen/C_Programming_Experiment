#include"model.h"
#include"global.h"
#include"tool.h"
#include"card_file.h"
#include"card_service.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
using namespace std;
lpCardNode head = NULL;
lpCardNode CardList = NULL;
Card praseCard(string pBuf);
int saveCard(const Card* pCard,const char*ip,int stat)
{
	ip = CARDPATH;
	ofstream ofs;
	//���ļ�
	if (stat)
		ofs.open(ip, ios::app);
	else
		ofs.open(ip, ios::out);
	if (!ofs.is_open())
	{
		return false;
	}
	//ʱ��ת�����ַ���
	char startTime[20] = { 0 };
	char endTime[20] = { 0 };
	char lastTime[20] = { 0 };
	timeToString(pCard->tStart, startTime);
	timeToString(pCard->tEnd, endTime);
	timeToString(pCard->tLast, lastTime);
	//������д���ļ�
	ofs << pCard->aName << "##" << pCard->aPwd << "##" << pCard->nStatus
		<< "##" << startTime << "##" << endTime << "##" << fixed << setprecision(1) <<
		pCard->fTotalUse << "##" << lastTime << "##" << pCard->nUseCount
		<< "##" << fixed << setprecision(1) << pCard->fBalance << "##" << pCard->nDel << endl;

	//�ر��ļ�
	ofs.close();
	return 1;
}

bool readCard()
{
	ifstream ifs;
	//���ļ�
	ifs.open(CARDPATH, ios::in);
	if (!ifs.is_open())
	{
		return false;
	}
	//��ȡ�ļ�
	string aBuf;
	while (ifs.peek() != EOF)
	{
		getline(ifs, aBuf);
		Card temp_card = praseCard(aBuf);
		addCard_index_setup(temp_card);
	}
	//�ر��ļ�
	ifs.close();
	return true;
}

Card praseCard(string pBuf)			//���ļ�������ת����Card����
{
	Card card;		//���ڴ���޸ĺ��card���ͽṹ��
	int i = 0;		//ָ������
	int case_num = 0;	//ָʾ����Ϣ����
	while (i < pBuf.size())
	{
		string temp_cur;
		while (i < pBuf.size()&&pBuf.at(i) != '#')
		{
			temp_cur.push_back(pBuf.at(i));
			i++;
		}
		i += 2;
		case_num++;
		if (case_num == 1)
		{
			int k = 0;
			for (; k < temp_cur.size(); k++)
				card.aName[k] = temp_cur.at(k);
			card.aName[k] = '\0';
		}
		else if (case_num == 2)
		{
			int k = 0;
			for (; k < temp_cur.size(); k++)
				card.aPwd[k] = temp_cur.at(k);
			card.aPwd[k] = '\0';
		}
		else if (case_num == 3)
		{
			card.nStatus = std::stoi(temp_cur);
		}
		else if (case_num == 4)
		{
			char timestr[20];
			for (int m = 0; m < temp_cur.size(); m++)
			{
				timestr[m] = temp_cur.at(m);
			}
			card.tStart = stringToTime(timestr);
		}
		else if (case_num == 5)
		{
			char timestr[20];
			for (int m = 0; m < temp_cur.size(); m++)
			{
				timestr[m] = temp_cur.at(m);
			}
			card.tEnd = stringToTime(timestr);
		}
		else if (case_num == 6)
		{
			istringstream isa_str(temp_cur);
			isa_str >> card.fTotalUse;
		}
		else if (case_num == 7)
		{
			char timestr[20];
			for (int m = 0; m < temp_cur.size(); m++)
			{
				timestr[m] = temp_cur.at(m);
			}
			card.tLast = stringToTime(timestr);
		}
		else if (case_num == 8)
		{
			card.nUseCount = std::stoi(temp_cur);
		}
		else if (case_num == 9)
		{
			istringstream isa_str(temp_cur);
			isa_str >> card.fBalance;
		}
		else
		{
			card.nDel = std::stoi(temp_cur);
		}
		temp_cur.clear();
		temp_cur.resize(0);
	}
	return card;
}

bool init_list()			//��ʼ������
{
	head = new(CardNode);
	if (head != NULL)
	{
		head->next = NULL;
		CardList = head;
		return 1;
	}
	return 0;
}

bool addCard_index_setup(Card card)		//���ļ��еĿ���Ϣ���浽������
{
	lpCardNode temp = NULL;
	if (CardList == NULL)
	{
		init_list();
	}
	else
	{
		temp = new(CardNode);
		CardList->next = temp;
		CardList = CardList->next;
		CardList->next = NULL;
	}
	//���ݱ��浽���
	CardList->data = card;
	CardList->next = NULL;
	return 0;
}

bool updateCard(lpCardNode pCard, const char* pPath)
{

	return 0;
}