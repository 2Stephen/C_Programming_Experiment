#include"model.h"
#include<string>

//struct Card aCard[50];		//卡信息结构体数组
//int nCount = 0;		//卡信息实际数
/*int addCard(Card card)
{
	aCard[nCount] = card;
	nCount++;
	return 0;
}*/
/*Card* queryCard(const char* pName)
{
	for (int i = 0; i < nCount; i++)
	{
		if (strcmp(pName, aCard[i].aName) == 0)
			return &aCard[i];
	}
}*/
/*------------以上为第二次实验内容------------*/

lpCardNode head = NULL;
lpCardNode CardList = NULL;

bool init_list()
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

bool addCard(Card card)
{
	lpCardNode temp = NULL;
	if (CardList == NULL)
	{
		init_list();
	}
	//数据保存到结点
	temp = new(CardNode);
	if (temp != NULL)
	{
		temp->data = card;
		temp->next = NULL;
		//遍历链表 找到最后一个结点
		while (CardList->next != NULL)
		{
			CardList = CardList->next;
		}
		CardList->next = temp;
		return 1;
	}
	return 0;
}

void delete_list()
{
	lpCardNode temp_ip = NULL, cache = NULL;
	temp_ip = head;
	cache = temp_ip->next;
	while (temp_ip != NULL)
	{
		delete(temp_ip);
		temp_ip = NULL;
		temp_ip = cache;
		cache = cache->next;
	}
}

Card* queryCard(const char* pName)
{
	lpCardNode cur = NULL;
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
	Card* pCard = new(Card);
	if (pCard == NULL)
	{
		return NULL;
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