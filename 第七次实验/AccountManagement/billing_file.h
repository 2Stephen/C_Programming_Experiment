#ifndef BILLING_FILE_H
#define BILLING_FILE_H
#define _CRT_SECURE_NO_WARNINGS
#include "model.h"
int saveBilling(const Billing* pBilling, const char* pPath);
Billing praseBilling(char* pBuf);
int readBilling(Billing* pBilling, const char* pPath);
int getBillingCount(const char* pPath);
int updataBilling(Billing* pBilling,const  char* pPath, int nIndex);
#endif BILLING_FILE_H


