#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "model.h"
#include "money_file.h"
#include <stdlib.h>
#include "tool.h"
#include "global.h"
int saveMoney(const Money* pMoney, const char* pPath)
{
	FILE* fp=NULL;
	//���ļ�
	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			return FALSE;
		}
	}
	fwrite(pMoney, sizeof(Money), 1, fp);
	//�ر��ļ�
	fclose(fp);
	return TRUE;
}