#pragma once

#include "stdafx.h"

struct SendMsg
{
	TCHAR userName[20];//������
	TCHAR sendUser[20];
	TCHAR recvUser[20];
	TCHAR sendMsg[250];
	BOOL isSingleSend;
	BOOL isFriendInfo;
	BOOL isOnLine;
	
	//��������ļ�������
	BOOL isFile;
	BOOL isFinished;
	UINT transSize;
	UINT fileOffset;
	char sendFile[20480];
	TCHAR fileName[50];
	ULONGLONG fileLen;

	BOOL isWindowShake;//�ж���Ϣ�ǲ��Ǵ��ڶ���

	//ͷ��ͬ��
	BOOL isHeadPic;
	UINT headNum;
};