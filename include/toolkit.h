#ifndef _TOOLKIT_H_
#define _TOOLKIT_H_

#include <vector>
#include <set>
#include <string>

using namespace std;

//����·�������ɶ༶Ŀ¼
void makedirs(const char* dir);

//���ַ�����ָ���ַ��ָ�
typedef void fnGetSetFromStringProcess(char* token);
char* GetSetFromString(const char* szString, const char* seps, vector<char*>& vct, set<char*>& st, int modify, set<string>& st2);

//����OnFrontDisconnected(int nReason)��ֵ���ϴ�����Ϣ
void GetOnFrontDisconnectedMsg(int ErrorId, char* ErrorMsg);

#endif