#include "stdafx.h"
#include "toolkit.h"
#include <string.h>
#include <time.h>

#if defined _WIN32 || WIN32 || _WINDOWS
    #include <direct.h>
    #define MKDIR(X) _mkdir((X));
#else
    #include <sys/stat.h>
    #define MKDIR(X) mkdir((X),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif // defined


void makedirs(const char* dir)
{
	if (nullptr == dir)
		return;

	int len = strlen(dir);

	char * p = new char[len+1];
	strcpy(p,dir);
	for (int i=0;i<len;++i)
	{
		char ch = p[i];
		if ('\\' == ch ||'/' == ch)
		{
			p[i] = '\0';
			MKDIR(p);
			p[i] = ch;
		}
	}
	delete[] p;
}

char* GetSetFromString(const char* szString, const char* seps, vector<char*>& vct, set<char*>& st, int modify, set<string>& st2)
{
	vct.clear();
	st.clear();

	if(nullptr == szString
		||nullptr == seps)
		return nullptr;

	if(strlen(szString)==0
		||strlen(seps)==0)
		return nullptr;

	size_t len = strlen(szString)+1;
	char* buf = new char[len];
	strncpy(buf,szString,len);

	char* token = strtok(buf, seps);
	while(token)
	{
		if (strlen(token)>0)
		{
			if (modify > 0)
				st2.insert(token);
			else if (modify<0)
				st2.erase(token);

			vct.push_back(token);
			st.insert(token);
		}
		token = strtok( nullptr, seps);
	}

	return buf;
}

void GetExchangeTime(char* TradingDay, char* ActionDay, char* UpdateTime, int* _TradingDay, int* _ActionDay, int* _UpdateTime)
{
	// TradingDay����
	*_TradingDay = atoi(TradingDay);

	// UpdateTime����
	int HH = atoi(&UpdateTime[0]);
	int mm = atoi(&UpdateTime[3]);
	int ss = atoi(&UpdateTime[6]);

	*_UpdateTime = HH * 10000 + mm * 100 + ss;
	if (*_UpdateTime == 0)
	{
		time_t now = time(0);
		struct tm *ptmNow = localtime(&now);
		int datetime = ptmNow->tm_hour * 10000 + ptmNow->tm_min * 100 + ptmNow->tm_sec;
		if (datetime > 1500 && datetime < 234500)
			*_UpdateTime = datetime;
	}

	// ActionDay����
	if ((ActionDay != nullptr) && (strlen(ActionDay) == 8))
	{
		*_ActionDay = atoi(ActionDay);
	}
	else
	{
		time_t now = time(0);
		struct tm *ptmNow = localtime(&now);
		if (HH >= 23)
		{
			if (ptmNow->tm_hour<1)
			{
				now -= 86400;
				ptmNow = localtime(&now);
			}
		}
		else if (HH<1)
		{
			if (ptmNow->tm_hour >= 23)
			{
				now += 86400;
				ptmNow = localtime(&now);
			}
		}

		*_ActionDay = (1900 + ptmNow->tm_year) * 10000 + (1 + ptmNow->tm_mon) * 100 + ptmNow->tm_mday;
	}
}

void GetOnFrontDisconnectedMsg(int ErrorId, char* ErrorMsg)
{
	switch (ErrorId)
	{
	case 0x1001:
		strcpy(ErrorMsg,"0x1001 4097 �����ʧ��");
		break;
	case 0x1002:
		strcpy(ErrorMsg,"0x1002 4098 ����дʧ��");
		break;
	case 0x2001:
		strcpy(ErrorMsg,"0x2001 8193 ����������ʱ");
		break;
	case 0x2002:
		strcpy(ErrorMsg,"0x2002 8194 ��������ʧ��");
		break;
	case 0x2003:
		strcpy(ErrorMsg,"0x2003 8195 �յ�������");
		break;
	default:
		sprintf(ErrorMsg, "%x %d δ֪����", ErrorId, ErrorId);
		break;
	}
}
