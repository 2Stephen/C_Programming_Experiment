#include"model.h"
#include"billing_file.h"
bool addBilling(const char* path, Card* pCard)
{
	saveBilling(path, pCard);
	return 1;
}