#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "menu.h"

using namespace std;
int main()
{
	int nSelection = -1;//输入菜单项编号
	cout << "\n欢迎进入计费管理系统\n";
	cout << endl;
	do
	{
		//输出系统菜单
		outputMenu();
		nSelection = -1;
		cin >> nSelection;
		//输出选择的菜单编号
		switch (nSelection)
		{
		case 1://添加卡
		{
			add();
			break;
		}
		case 2://查询卡
		{
			query();
			break;
		}
		case 3://上机
		{
			logon();
			break;
		}
		case 4://下机
		{
			settle();
			break;
		}
		case 5://充值
		{
			addMoney();
			break;
		}
		case 6://退费
		{
			refundMoney();
			break;
		}
		case 7://查询统计
		{

			break;
		}
		case 8://注销卡
		{
			annual();
			break;
		}
		case 0://退出
		{
			exitApp();
			break;
		}
		default:
		{
			cout << "输入的菜单编号错误！" << endl;
			break;
		}
		}
		cout << endl;
	} while (nSelection != 0);
	return 0;
}
