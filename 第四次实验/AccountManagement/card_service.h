#ifndef CARD_SERVICE_H
#define CARD_SERVICE_H
//int addCard(Card card);		//����
//Card* queryCard(const char* pName);	//��������
/*------------����Ϊ�ڶ���ʵ������------------*/

bool init_list();
bool addCard(Card card);
void delete_list();
Card* queryCards(const char* pName, int* plndex);
Card* queryCard(const char* pName);
#endif
