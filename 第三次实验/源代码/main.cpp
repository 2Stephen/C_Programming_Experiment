#include"menu.h"

#include<iostream>
using namespace std;
int main()
{
	int nSelection = -1;			//�˵��������
	cout << "��ӭ����Ʒѹ���ϵͳ" << endl;
	cout << endl;
	do
	{
		outputMenu();			//�˵��������
		cin >> nSelection;		//����˵����
		switch (nSelection)
		{
		case 1:		//��ӿ�
			add();
			break;
		case 2:		//��ѯ��
			query();
			break;
		case 3:		//��½
			logon();
			break;
		case 4:		//�ǳ�
			settle();
			break;
		case 5:		//��ֵ����
			addMoney();
			break;
		case 6:		//�˷ѹ���
			refundMoney();
			break;
		case 7:		//��ѯͳ��

			break;
		case 8:		//ע����
			annul();
			break;
		case 0:		//�˳�����
			exitApp();
			break;
		default:
			cout << "����Ĳ˵���Ŵ���" << endl;
			break;
		}
		cout << endl;
	} while (nSelection != 0);
	return 0;
}