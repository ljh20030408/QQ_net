#pragma once

#include "stdafx.h"

//�û���Ϣ�ṹ
struct UserInfo
{
	UINT	headNum;//����ȡ1��2��3��4��5��6
	TCHAR	userName[20];
	TCHAR	passWord[20];
	BOOL	bOnLine;
	BOOL	accFlag;
	SOCKET	userSocket;
	SOCKET	friendSocket;
	BOOL	isFriendInfo;//���Է�������Ϣ�Ǻ��ѵ���Ϣ���� �����Ҹý��յ���Ϣ
	BOOL	isRegister;
};
