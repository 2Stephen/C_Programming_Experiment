#ifndef CARD_SERVICE_H
#define CARD_SERVICE_H
//int addCard(Card card);		//声明
//Card* queryCard(const char* pName);	//声明函数
/*------------以上为第二次实验内容------------*/

bool init_list();
bool addCard(Card card);
void delete_list();
Card* queryCards(const char* pName, int* plndex);
Card* queryCard(const char* pName);
#endif
