#include"model.h"
#include<string>

struct Card aCard[50];		//����Ϣ�ṹ������
int nCount = 0;		//����Ϣʵ����
int addCard(Card card)
{
	aCard[nCount] = card;
	nCount++;
	return 0;
}
Card* queryCard(const char* pName)
{
	for (int i = 0; i < nCount; i++)
	{
		if (strcmp(pName, aCard[i].aName) == 0)
			return &aCard[i];
	}
}
