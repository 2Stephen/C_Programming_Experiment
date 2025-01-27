#ifndef MODEL_H
#define MODEL_H
#endif
#include<ctime>
typedef struct Card
{
	char aName[18];		//卡号
	char aPwd[8];		//密码
	int nStatus;			//卡状态（0-未上机；1-正在上机；2-已注销；3-失效）
	time_t tStart;		//开卡时间
	time_t tEnd;		//卡的截止时间
	float fTotalUse;		//累计金额
	time_t tLast;	//最后使用时间
	int nUseCount;		//使用次数
	float fBalance;		//余额
	int nDel;			//删除标识（0-未删除；1-删除）
}Card;

typedef struct Billing
{
	char aCardName[18];	// 卡号
	time_t tStart;			// 上机时间
	time_t tEnd;			// 下机时间
	float fAmount;			// 消费金额
	int nStatus;				// 消费状态，0-未结算，1-已经结算
	int nDel;				// 删除标识，0-未删除,1-删除
}Billing;

typedef struct LogonInfo
{
	char aCardName[18];	// 上机卡号
	time_t tLogon;			// 上机时间
	float fBalance;			// 上机时的卡余额
}LogonInfo;

typedef struct SettleInfo
{
	char aCardName[18];	 // 卡号
	time_t tStart;		     // 上机时间
	time_t tEnd;		     // 下机时间
	float fAmount;			// 消费金额
	float fBalance;			// 余额
}SettleInfo;

typedef struct Money
{
	char aCardName[18];	// 卡号
	time_t tTime;			// 充值退费的时间
	int nStatus;				// 状态：0-表示充值；1-表示退费
	float fMoney;			// 充值退费金额
	int nDel;				// 删除标识，0-未删除,1-删除
}Money;

typedef struct MoneyInfo
{
	char aCardName[18];	// 卡号
	float fMoney;			// 充值退费金额
	float fBalance;			// 余额
}MoneyInfo;

typedef struct admin
{
	char name[18];			//用户名
	char pwd[8];			//密码
	int privilege;			//权限等级
	int del;					//删除标志：0-未删除；1-已删除
}admin;

typedef struct CardNode
{
	Card data;				//结点数据区
	struct CardNode* next;	//指向下个结点的指针
}CardNode, * lpCardNode;