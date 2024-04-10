#include<iostream>
#include<ctime>
#include<string>
#include<cstdlib>


using namespace std;
void outputMenu()
{
	cout << "----------菜单----------" << endl;
	cout << "1.添加卡" << endl;
	cout << "2.查询卡" << endl;
	cout << "3.上机" << endl;
	cout << "4.下机" << endl;
	cout << "5.充值" << endl;
	cout << "6.退费" << endl;
	cout << "7.查询统计" << endl;
	cout << "8.注销卡" << endl;
	cout << "0.退出" << endl;
	cout << "请选择菜单选编号（0~8）：";
}
void add()
{
	cout << "----------添加卡----------" << endl;
	cout << "请输入卡号（长度为1~18）：" << endl;
	//函数
	cout << "请输入密码（长度为1~8）：" << endl;
	//函数
	cout << "请输入开卡金额（RMB):" << endl;
	//函数
	cout << "添加卡信息成功！" << endl;
}
void query()
{
	cout << "----------查询卡----------" << endl;
}
void exitApp()
{
	cout << "----------退出----------" << endl;
}
void logon() 
{
	cout << "----------上机----------" << endl;
}
void settle()
{
	cout << "----------下机----------" << endl;
}
void annul()
{
	cout << "----------注销卡----------" << endl;
}
void addMoney()
{
	cout << "----------充值----------" << endl;
}
void refundMoney()
{
	cout << "----------退费----------" << endl;
}
