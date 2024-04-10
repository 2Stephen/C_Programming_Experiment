#ifndef CAED_FILE_H
#define CARD_FILE_H
#include "model.h"
int saveCard(const Card* pCard, const char* pPath);
Card praseCard(char* pBuf);
int readCard(Card* pCard, const char* pPath);
int getCardCount(const char* pPath);
int updateCard(const Card* pCard, const char* pPath, int nlndex);
#endif
