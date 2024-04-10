#ifndef BILLING_SERVICE_H
#define BILLING_SERVICE_H
#include <stdio.h>
#include "model.h"
void initBillingList();
void releaseBillingList();
int addBilling( Billing billing);
int getBilling();
Billing* queryBilling(const char* pName, int* pIndex);
void ShowBilling(const char* pName);
#endif


