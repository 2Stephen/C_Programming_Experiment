#ifndef CARD_SERVICE_H
#define CARD_SERVICE_H
#include "model.h"
int addCard(Card card);
int initCardList();
void releaseCardList();
Card* queryCard(const char* pName);
Card* queryCards(const char* pName, int* plndex);
int getCard();
int doLogon(const char* pName, const char* pPwd, LogonInfo* pLogonInfo);
Card* checkCard(const char* pName, const char* pPwd, int* pIndex);
#endif