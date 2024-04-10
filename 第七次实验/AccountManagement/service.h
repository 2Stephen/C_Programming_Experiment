#ifndef SERVICE_H//·ÀÖ¹ÖØ¸´±àÒë
#define SERVICE_H

int addCardInfo(Card card);//ÉùÃ÷addCardlnfo()º¯Êý
Card* queryCardInfo(const char* pName);
Card* queryCardsInfo(const char* pName, int* plndex);
void releaseList();
int doSettle(const char* pName, const char* pPwd, SettleInfo* pInfo);
double getAmount(time_t t);
int doAddMoney(const char* pName, const char* pPwd, MoneyInfo* pInfo);
int doRefundMoney(const char* pName, const char* pPwd, MoneyInfo* pInfo);
int annulCard(Card* pCard);
#endif
