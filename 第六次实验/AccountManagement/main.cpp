#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "menu.h"

using namespace std;
int main()
{
	int nSelection = -1;//����˵�����
	cout << "\n��ӭ����Ʒѹ���ϵͳ\n";
	cout << endl;
	do
	{
		//���ϵͳ�˵�
		outputMenu();
		nSelection = -1;
		cin >> nSelection;
		//���ѡ��Ĳ˵����
		switch (nSelection)
		{
		case 1://��ӿ�
		{
			add();
			break;
		}
		case 2://��ѯ��
		{
			query();
			break;
		}
		case 3://�ϻ�
		{
			logon();
			break;
		}
		case 4://�»�
		{
			settle();
			break;
		}
		case 5://��ֵ
		{
			addMoney();
			break;
		}
		case 6://�˷�
		{
			refundMoney();
			break;
		}
		case 7://��ѯͳ��
		{

			break;
		}
		case 8://ע����
		{
			annual();
			break;
		}
		case 0://�˳�
		{
			exitApp();
			break;
		}
		default:
		{
			cout << "����Ĳ˵���Ŵ���" << endl;
			break;
		}
		}
		cout << endl;
	} while (nSelection != 0);
	return 0;
}
