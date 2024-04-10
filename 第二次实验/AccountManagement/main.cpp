#include"menu.h"

#include<iostream>
using namespace std;
int main()
{
	int nSelection = -1;			//菜单编号输入
	cout << "欢迎进入计费管理系统" << endl;
	cout << endl;
	do
	{
		outputMenu();			//菜单输出函数
		cin >> nSelection;		//输入菜单编号
		switch (nSelection)
		{
		case 1:		//添加卡
			add();
			break;
		case 2:		//查询卡
			query();
			break;
		case 3:		//登陆
			logon();
			break;
		case 4:		//登出
			settle();
			break;
		case 5:		//充值功能
			addMoney();
			break;
		case 6:		//退费功能
			refundMoney();
			break;
		case 7:		//查询统计

			break;
		case 8:		//注销卡
			annul();
			break;
		case 0:		//退出程序
			exitApp();
			break;
		default:
			cout << "输入的菜单编号错误！" << endl;
			break;
		}
		cout << endl;
	} while (nSelection != 0);
	return 0;
}