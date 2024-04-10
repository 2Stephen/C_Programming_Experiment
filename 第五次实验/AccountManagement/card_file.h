#ifndef CARD_FILE_H
#define CARD_FILE_H
#include"model.h"
int saveCard(const Card* pCard,const char*ip,int stat);
bool addCard_index_setup(Card card);
bool readCard();
bool updateCard(lpCardNode pCard, const char* pPath);
#endif
