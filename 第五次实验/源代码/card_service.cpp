#include"model.h"
#include"global.h"
#include"card_file.h"
#include"card_service.h"
#include<string>
extern lpCardNode head;
extern lpCardNode CardList;


bool addCard(Card card)			//第四次实验文件实现添加卡
{
	return saveCard(&card, CARDPATH,1);
	return 0;
}


void delete_list()
{
	lpCardNode cache = NULL;
	if (head == NULL) return;
	while (head != NULL)
	{
		if (head->next != NULL)
			cache = head->next;
		else break;
		delete(head);
		if (cache == NULL)
			break;
		head = NULL;
		head = cache;
	}
}

Card* queryCard(const char* pName)		//精确查找
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

Card* queryCards(const char* pName, int* plndex)		//模糊查找
{
	delete_list();
	head = NULL;
	CardList = NULL;
	readCard();
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

Card* delogon(const char* pName, const char* pPwd)
{
	delete_list();
	head = NULL;
	CardList = NULL;
	lpCardNode cur = NULL;
	readCard();
	if (head != NULL)
	{
		cur = head;
		while (cur != NULL)
		{
			if (strcmp(cur->data.aName, pName) == 0)
			{
				if(strcmp(cur->data.aPwd, pPwd) == 0)
				{
					return &cur->data;
				}
			}
			cur = cur->next;
		}
	}
	return NULL;
}

void saveLogonCard(const char* ip)
{
	lpCardNode cur = head;
	int flag = 0;
	while (cur != NULL)
	{
		saveCard(&cur->data, ip, flag);
		flag = 1;
		if (cur->next != NULL)
			cur = cur->next;
		else break;
	}
}
