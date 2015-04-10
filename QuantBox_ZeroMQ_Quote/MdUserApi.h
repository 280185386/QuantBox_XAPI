#pragma once

#include "../include/ApiStruct.h"
// ��Ҫ��zmq��czmq��Ŀ¼��Additional Include Directories�����
#include "zmq.h"
#include "czmq.h"

#ifdef _WIN64
#pragma comment(lib, "../include/CTP/win64/thostmduserapi.lib")
#pragma comment(lib, "../lib/QuantBox_Queue_x64.lib")
#else
#pragma comment(lib, "../include/ZeroMQ/x86/czmq.lib")
#pragma comment(lib, "../lib/QuantBox_Queue_x86.lib")
#endif

#include <set>
#include <string>
#include <atomic>
#include <mutex>
#include <thread>
#include <map>

using namespace std;

class CMsgQueue;

class CMdUserApi
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

	void Subscribe(const string& szInstrumentIDs, const string& szExchageID);
	void Unsubscribe(const string& szInstrumentIDs, const string& szExchageID);

	//void SubscribeQuote(const string& szInstrumentIDs, const string& szExchageID);
	//void UnsubscribeQuote(const string& szInstrumentIDs, const string& szExchageID);
private:
	void StartThread();
	void StopThread();

	static void ProcessThread(CMdUserApi* lpParam)
	{
		if (lpParam)
			lpParam->RunInThread();
	}
	void RunInThread();

private:
	friend void* __stdcall Query(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3);
	void QueryInThread(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3);
	
	//int _Init();
	////��¼����
	//void ReqUserLogin();
	//int _ReqUserLogin(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3);

	//��������
	bool Contains(const string& szInstrumentID, const string& szExchageID);

	void Subscribe(const set<string>& instrumentIDs, const string& szExchageID);
	//void SubscribeQuote(const set<string>& instrumentIDs, const string& szExchageID);

	//virtual void OnFrontConnected();
	//virtual void OnFrontDisconnected(int nReason);
	//virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

	//virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

	////����Ƿ����
	//bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);//��������Ϣ�͵���Ϣ����
	//bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);//���ͳ�����Ϣ

private:
	mutex						m_csMapInstrumentIDs;
	mutex						m_csMapQuoteInstrumentIDs;

	atomic<int>					m_lRequestID;			//����ID��ÿ������ǰ����

	map<string, set<string> >	m_mapInstrumentIDs;		//���ڶ��ĵĺ�Լ
	map<string, set<string> >	m_mapQuoteInstrumentIDs;		//���ڶ��ĵĺ�Լ
	//CThostFtdcMdApi*			m_pApi;					//����API
	void*						m_pContext;

	string						m_szPath;				//���������ļ���·��
	ServerInfoField				m_ServerInfo;
	UserInfoField				m_UserInfo;
	int							m_nSleep;

	CMsgQueue*					m_msgQueue;				//��Ϣ����ָ��
	//CMsgQueue*					m_msgQueue_Query;
	void*						m_pClass;

	//zctx_t*						m_ctx;

	volatile bool						m_bRunning;
	mutex								m_mtx;
	mutex								m_mtx_del;
	//condition_variable					m_cv;
	thread*								m_hThread;

	zctx_t*		m_ctx;
	void*		m_pubisher;
};

