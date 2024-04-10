#define _CRT_SECURE_NO_WARNINGS
#include<fstream>
#include<sstream>
#include<iostream>
#include<ctime>
#include"model.h"
bool saveBilling(const char* path, Card* pCard)
{
	Billing* temp = new(Billing);
	strcpy(temp->aCardName, pCard->aName);
	temp->fAmount = 0;
	temp->nDel = 0;
	temp->nStatus = 0;
	temp->tEnd = time(NULL);
	temp->tStart = time(NULL);
	FILE* fp = fopen(path, "ab");//打开文件
	fwrite(temp, sizeof(*temp), 1, fp);
	
	return 1;
}