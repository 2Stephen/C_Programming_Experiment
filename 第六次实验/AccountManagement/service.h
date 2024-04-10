#ifndef SERVICE_H//·ÀÖ¹ÖØ¸´±àÒë
#define SERVICE_H

int addCardInfo(Card card);//ÉùÃ÷addCardlnfo()º¯Êı
Card* queryCardInfo(const char* pName);
Card* queryCardsInfo(const char* pName, int* plndex);
void releaseList();
int doSettle(const char* pName, const char* pPwd, SettleInfo* pInfo);
double getAmount(time_t t);
#endif
