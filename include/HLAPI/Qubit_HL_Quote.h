// Qubit_HL_Quote.h : Qubit_HL_Quote DLL ����ͷ�ļ�
//

#pragma once



// CQubit_HL_QuoteApp
// �йش���ʵ�ֵ���Ϣ������� Qubit_HL_Quote.cpp
//

#pragma once

#include "../include/ApiStruct.h"
#include "../include/HLAPI/HLQuoteApi.h"


#pragma comment(lib, "../include/HLAPI/HLQuoteApi.lib")
#pragma comment(lib, "../lib/QuantBox_Queue_x86.lib")

#include <set>
#include <string>
#include <atomic>
#include <mutex>
#include <map>

using namespace std;

class CMsgQueue;

class CMdUserApi :
	public HLQuoteSpi
{
	enum RequestType
	{
		E_Init,
		E_ReqUserLoginField,
	};

public:
	CMdUserApi(void);
	virtual ~CMdUserApi(void);

	void Register(void* pCallback, void* pClass);
	ConfigInfoField* Config(ConfigInfoField* pConfigInfo);

	void Connect(const string& szPath,
		ServerInfoField* pServerInfo,
		UserInfoField* pUserInfo,
		int count);
	void Disconnect();

	//void Subscribe(const string& szInstrumentIDs, const string& szExchageID);
	//void Unsubscribe(const string& szInstrumentIDs, const string& szExchageID);

	//void SubscribeQuote(const string& szInstrumentIDs, const string& szExchageID);
	//void UnsubscribeQuote(const string& szInstrumentIDs, const string& szExchageID);

private:
	friend void* __stdcall Query(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3);
	void QueryInThread(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3);

	int _Init();
	//��¼����
	void ReqUserLogin();
	int _ReqUserLogin(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3);

	//��������
	void Subscribe(const set<string>& instrumentIDs, const string& szExchageID);
	void SubscribeQuote(const set<string>& instrumentIDs, const string& szExchageID);

	///���ͻ����뽻�׺�̨������ͨ�����ӣ��ͻ�����Ҫ���е�¼��
	virtual void OnFrontConnected();

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������ã��ͻ��˲���Ҫ����API���Զ�������
	virtual void OnFrontDisconnected(int nReason);

	///����Ӧ��
	//@cIsLast ����־ API_PACKET_FIRST | API_PACKET_LAST ��ͬ
	virtual void OnRspError(CHLRspInfoData *pRspInfo, int nRequestID, char cIsLast);

	///�û���¼Ӧ��
	virtual void OnRspUserLogin(HLApiRspUserLoginData *pRspUserLogin, CHLRspInfoData *pRspInfo, int nRequestID, char cIsLast);

	///�û��˳�Ӧ��
	//virtual void OnRspUserLogout(void *pRspUserLogout, void *pRspInfo, int nRequestID, char cIsLast) {};

	///�г���������Ӧ��
	virtual void OnRspCodeTable(HLApiRspCodeTable *pRspCodeTable, CHLRspInfoData *pRspInfo, int nRequestID, char cIsLast);

	///���鶩������Ӧ��
	virtual void OnRspMarketData(HLApiRspMarketData *pRspMarketData, CHLRspInfoData *pRspInfo, int nRequestID, char cIsLast);

	//��������仯֪ͨ
	virtual void OnRtnMarketData(HLApiMarketData *pMarketData);

	//ȫ�г�����仯֪ͨ(���Ĺ�Ʊ����Ϊ��ʱ��Ϊȫ�г���������)
	virtual void OnRtnMarketData(HLApiMarketData *pMarketData, int nSize);
	virtual void OnRtnPushStkData(HLApiMarketData *pMarketData, int nSize);

private:
	mutex						m_csMapInstrumentIDs;
	mutex						m_csMapQuoteInstrumentIDs;

	atomic<int>					m_lRequestID;			//����ID��ÿ������ǰ����

	set<string>					m_setInstrumentIDs;		//���ڶ��ĵĺ�Լ
	set<string>					m_setQuoteInstrumentIDs;		//���ڶ��ĵĺ�Լ
	HLQuoteApi*					m_pApi;					//����API

	string						m_szPath;				//���������ļ���·��
	ServerInfoField				m_ServerInfo;
	UserInfoField				m_UserInfo;
	int							m_nSleep;

	CMsgQueue*					m_msgQueue;				//��Ϣ����ָ��
	CMsgQueue*					m_msgQueue_Query;
	void*						m_pClass;

	CMsgQueue*					m_remoteQueue;
};


