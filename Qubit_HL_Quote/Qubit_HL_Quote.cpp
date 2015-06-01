// Qubit_HL_Quote.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "Qubit_HL_Quote.h"
#include "../include/QueueEnum.h"

#include "../include/ApiHeader.h"
#include "../include/ApiStruct.h"

#include "../include/toolkit.h"

#include "../QuantBox_Queue/MsgQueue.h"
#ifdef _REMOTE
#include "../QuantBox_Queue/RemoteQueue.h"
#endif

#include <string.h>
#include <cfloat>

#include <mutex>
#include <vector>
using namespace std;

void* __stdcall Query(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	// ���ڲ����ã����ü���Ƿ�Ϊ��
	CMdUserApi* pApi = (CMdUserApi*)pApi2;
	pApi->QueryInThread(type, pApi1, pApi2, double1, double2, ptr1, size1, ptr2, size2, ptr3, size3);
	return nullptr;
}

CMdUserApi::CMdUserApi(void)
{
	m_pApi = nullptr;
	m_lRequestID = 0;
	m_nSleep = 1;

	// �Լ�ά��������Ϣ����
	m_msgQueue = new CMsgQueue();
	m_msgQueue_Query = new CMsgQueue();

	m_msgQueue_Query->Register((void*)Query, this);
	m_msgQueue_Query->StartThread();

	//m_msgQueue->m_bDirectOutput = true;

	m_remoteQueue = nullptr;
}

CMdUserApi::~CMdUserApi(void)
{
	Disconnect();
}

void CMdUserApi::QueryInThread(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	int iRet = 0;
	switch (type)
	{
	case E_Init:
		iRet = _Init();
		break;
	case E_ReqUserLoginField:
		iRet = _ReqUserLogin(type, pApi1, pApi2, double1, double2, ptr1, size1, ptr2, size2, ptr3, size3);
		break;
	default:
		break;
	}

	if (0 == iRet)
	{
		//���سɹ�����ӵ��ѷ��ͳ�
		m_nSleep = 1;
	}
	else
	{
		m_msgQueue_Query->Input_Copy(type, pApi1, pApi2, double1, double2, ptr1, size1, ptr2, size2, ptr3, size3);
		//ʧ�ܣ���4���ݽ�����ʱ����������1s
		m_nSleep *= 4;
		m_nSleep %= 1023;
	}
	this_thread::sleep_for(chrono::milliseconds(m_nSleep));
}

void CMdUserApi::Register(void* pCallback, void* pClass)
{
	m_pClass = pClass;
	if (m_msgQueue == nullptr)
		return;

	m_msgQueue_Query->Register((void*)Query, this);
	m_msgQueue->Register(pCallback, this);
	if (pCallback)
	{
		m_msgQueue_Query->StartThread();
		m_msgQueue->StartThread();
	}
	else
	{
		m_msgQueue_Query->StopThread();
		m_msgQueue->StopThread();
	}
}

ConfigInfoField* CMdUserApi::Config(ConfigInfoField* pConfigInfo)
{
	return nullptr;
}

void CMdUserApi::Connect(const string& szPath,
	ServerInfoField* pServerInfo,
	UserInfoField* pUserInfo,
	int count)
{
	m_szPath = szPath;
	memcpy(&m_ServerInfo, pServerInfo, sizeof(ServerInfoField));
	memcpy(&m_UserInfo, pUserInfo, sizeof(UserInfoField));

	m_msgQueue_Query->Input_NoCopy(RequestType::E_Init, m_msgQueue_Query, this, 0, 0,
		nullptr, 0, nullptr, 0, nullptr, 0);

#ifdef _REMOTE
	// ���յ�������ͨ��ZeroMQ���ͳ�ȥ
	if (strlen(m_ServerInfo.ExtendInformation) > 0)
	{
		m_remoteQueue = new CRemoteQueue(m_ServerInfo.ExtendInformation);
		m_remoteQueue->StartThread();
	}
#endif
}

int CMdUserApi::_Init()
{
	//sprintf(pszPath, "%s/%s/%s/Md/%d/", m_szPath.c_str(), m_ServerInfo.BrokerID, m_UserInfo.UserID, rand());
	//makedirs(pszPath);

	m_pApi = HLQuoteApi::CreateHLQuoteApi();

	m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Initialized, 0, nullptr, 0, nullptr, 0, nullptr, 0);

	if (m_pApi)
	{
		m_pApi->RegisterSpi(this);

		//��ӵ�ַ
		size_t len = strlen(m_ServerInfo.Address) + 1;
		char* buf = new char[len];
		strncpy(buf, m_ServerInfo.Address, len);

		char* token = strtok(buf, _QUANTBOX_SEPS_);
		while (token)
		{
			if (strlen(token)>0)
			{
				m_pApi->RegisterNetwork(m_ServerInfo.Port, token);
			}
			token = strtok(NULL, _QUANTBOX_SEPS_);
		}
		delete[] buf;

		//��ʼ������
		m_pApi->Init();
		m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Connecting, 0, nullptr, 0, nullptr, 0, nullptr, 0);
	}

	return 0;
}

void CMdUserApi::ReqUserLogin()
{
	HLApiReqUserLoginData* pBody = (HLApiReqUserLoginData*)m_msgQueue_Query->new_block(sizeof(HLApiReqUserLoginData));

	strncpy(pBody->chClientID, m_UserInfo.UserID, sizeof(pBody->chClientID));
	strncpy(pBody->chPassword, m_UserInfo.Password, sizeof(pBody->chPassword));

	m_msgQueue_Query->Input_NoCopy(RequestType::E_ReqUserLoginField, m_msgQueue_Query, this, 0, 0,
		pBody, sizeof(HLApiReqUserLoginData), nullptr, 0, nullptr, 0);
}

int CMdUserApi::_ReqUserLogin(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Logining, 0, nullptr, 0, nullptr, 0, nullptr, 0);
	return m_pApi->ReqUserLogin((HLApiReqUserLoginData*)ptr1, ++m_lRequestID);
}

void CMdUserApi::Disconnect()
{
	// �����ѯ����
	if (m_msgQueue_Query)
	{
		m_msgQueue_Query->StopThread();
		m_msgQueue_Query->Register(nullptr, nullptr);
		m_msgQueue_Query->Clear();
		delete m_msgQueue_Query;
		m_msgQueue_Query = nullptr;
	}

	if (m_pApi)
	{
		m_pApi->RegisterSpi(NULL);
		m_pApi->Release();
		m_pApi = NULL;

		// ȫ����ֻ�����һ��
		m_msgQueue->Clear();
		m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Disconnected, 0, nullptr, 0, nullptr, 0, nullptr, 0);
		// ��������
		m_msgQueue->Process();
	}

	// ������Ӧ����
	if (m_msgQueue)
	{
		m_msgQueue->StopThread();
		m_msgQueue->Register(nullptr, nullptr);
		m_msgQueue->Clear();
		delete m_msgQueue;
		m_msgQueue = nullptr;
	}

	// �������
	if (m_remoteQueue)
	{
		m_remoteQueue->StopThread();
		m_remoteQueue->Register(nullptr, nullptr);
		m_remoteQueue->Clear();
		delete m_remoteQueue;
		m_remoteQueue = nullptr;
	}
}


void CMdUserApi::OnFrontConnected()
{
	m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Connected, 0, nullptr, 0, nullptr, 0, nullptr, 0);

	//���ӳɹ����Զ������¼
	ReqUserLogin();
}

void CMdUserApi::OnFrontDisconnected(int nReason)
{
	RspUserLoginField* pField = (RspUserLoginField*)m_msgQueue->new_block(sizeof(RspUserLoginField));
	//����ʧ�ܷ��ص���Ϣ��ƴ�Ӷ��ɣ���Ҫ��Ϊ��ͳһ���
	pField->ErrorID = nReason;
	GetOnFrontDisconnectedMsg(nReason, pField->ErrorMsg);

	m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Disconnected, 0, pField, sizeof(RspUserLoginField), nullptr, 0, nullptr, 0);
}

void CMdUserApi::OnRspUserLogin(HLApiRspUserLoginData *pRspUserLogin, CHLRspInfoData *pRspInfo, int nRequestID, char cIsLast)
{
	RspUserLoginField* pField = (RspUserLoginField*)m_msgQueue->new_block(sizeof(RspUserLoginField));

	if (pRspInfo->ErrorID == 0)
	{
		pField->TradingDay = GetDate(pRspUserLogin->chTradingDay);
		pField->LoginTime = GetTime(pRspUserLogin->chLoginTime);

		sprintf_s(pField->SessionID, "%d", pRspUserLogin->nSessionID);

		m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Logined, 0, pField, sizeof(RspUserLoginField), nullptr, 0, nullptr, 0);
		m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Done, 0, nullptr, 0, nullptr, 0, nullptr, 0);

		HLApiReqCodeTable req = { 0 };
		for (int i = 0; i < pRspUserLogin->nMarkets; i++)
		{
			//req.nDate = pRspUserLogin->nDynDate[i];
			memcpy(req.chMarket, pRspUserLogin->chMarketFlag + i, API_MARKET_LEN);
			m_pApi->ReqCodeTable(&req, ++m_lRequestID);
		}
	}
	else
	{
		pField->ErrorID = pRspInfo->ErrorID;
		strncpy(pField->ErrorMsg, pRspInfo->ErrorMsg, sizeof(ErrorMsgType));

		m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Disconnected, 0, pField, sizeof(RspUserLoginField), nullptr, 0, nullptr, 0);
	}
}

void CMdUserApi::OnRspCodeTable(HLApiRspCodeTable *pRspCodeTable, CHLRspInfoData *pRspInfo, int nRequestID, char cIsLast)
{
	HLApiReqMarketData data = { 0 };
	strncpy(data.chMarket, pRspCodeTable->chMarketFlag, sizeof (data.chMarket));
	m_pApi->ReqMarketData(&data, ++m_lRequestID);
}

//����ص����ñ�֤�˺������췵��
void CMdUserApi::OnRtnMarketData(HLApiMarketData *pMarketData, int nSize)
{
	//for (int i = 0; i < 50; ++i)
	//{
	//	// ����ƽ̨��Խ�ٶȣ��������Ҫע�͵�
	//	WriteLog("CTP:OnRtnDepthMarketData:%s %f %s.%03d", pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice, pDepthMarketData->UpdateTime, pDepthMarketData->UpdateMillisec);

	DepthMarketDataField* pField = (DepthMarketDataField*)m_msgQueue->new_block(sizeof(DepthMarketDataField));


	sprintf(pField->Symbol, "%s.%s", pField->InstrumentID, pField->ExchangeID);

	//TODO:CTP����û��ActionDay������API���ǽ�TradingDay�������������������÷����ܻ����Ҫ��
	GetExchangeTime(pDepthMarketData->TradingDay, pDepthMarketData->ActionDay, pDepthMarketData->UpdateTime
		, &pField->TradingDay, &pField->ActionDay, &pField->UpdateTime, &pField->UpdateMillisec);

	pField->UpdateMillisec = pDepthMarketData->UpdateMillisec;

	pField->LastPrice = pDepthMarketData->LastPrice == DBL_MAX ? 0 : pDepthMarketData->LastPrice;
	pField->Volume = pDepthMarketData->Volume;
	pField->Turnover = pDepthMarketData->Turnover;
	pField->OpenInterest = pDepthMarketData->OpenInterest;
	pField->AveragePrice = pDepthMarketData->AveragePrice;

	if (pDepthMarketData->OpenPrice != DBL_MAX)
	{
		pField->OpenPrice = pDepthMarketData->OpenPrice;
		pField->HighestPrice = pDepthMarketData->HighestPrice;
		pField->LowestPrice = pDepthMarketData->LowestPrice;
	}
	else
	{
		pField->OpenPrice = 0;
		pField->HighestPrice = 0;
		pField->LowestPrice = 0;
	}
	pField->SettlementPrice = pDepthMarketData->SettlementPrice != DBL_MAX ? pDepthMarketData->SettlementPrice : 0;

	pField->UpperLimitPrice = pDepthMarketData->UpperLimitPrice;
	pField->LowerLimitPrice = pDepthMarketData->LowerLimitPrice;
	pField->PreClosePrice = pDepthMarketData->PreClosePrice;
	pField->PreSettlementPrice = pDepthMarketData->PreSettlementPrice;
	pField->PreOpenInterest = pDepthMarketData->PreOpenInterest;

	do
	{
		if (pDepthMarketData->BidVolume1 == 0)
			break;
		pField->BidPrice1 = pDepthMarketData->BidPrice1;
		pField->BidVolume1 = pDepthMarketData->BidVolume1;

		if (pDepthMarketData->BidVolume2 == 0)
			break;
		pField->BidPrice2 = pDepthMarketData->BidPrice2;
		pField->BidVolume2 = pDepthMarketData->BidVolume2;

		if (pDepthMarketData->BidVolume3 == 0)
			break;
		pField->BidPrice3 = pDepthMarketData->BidPrice3;
		pField->BidVolume3 = pDepthMarketData->BidVolume3;

		if (pDepthMarketData->BidVolume4 == 0)
			break;
		pField->BidPrice4 = pDepthMarketData->BidPrice4;
		pField->BidVolume4 = pDepthMarketData->BidVolume4;

		if (pDepthMarketData->BidVolume5 == 0)
			break;
		pField->BidPrice5 = pDepthMarketData->BidPrice5;
		pField->BidVolume5 = pDepthMarketData->BidVolume5;
	} while (false);

	do
	{
		if (pDepthMarketData->AskVolume1 == 0)
			break;
		pField->AskPrice1 = pDepthMarketData->AskPrice1;
		pField->AskVolume1 = pDepthMarketData->AskVolume1;

		if (pDepthMarketData->AskVolume2 == 0)
			break;
		pField->AskPrice2 = pDepthMarketData->AskPrice2;
		pField->AskVolume2 = pDepthMarketData->AskVolume2;

		if (pDepthMarketData->AskVolume3 == 0)
			break;
		pField->AskPrice3 = pDepthMarketData->AskPrice3;
		pField->AskVolume3 = pDepthMarketData->AskVolume3;

		if (pDepthMarketData->AskVolume4 == 0)
			break;
		pField->AskPrice4 = pDepthMarketData->AskPrice4;
		pField->AskVolume4 = pDepthMarketData->AskVolume4;

		if (pDepthMarketData->AskVolume5 == 0)
			break;
		pField->AskPrice5 = pDepthMarketData->AskPrice5;
		pField->AskVolume5 = pDepthMarketData->AskVolume5;
	} while (false);

	// ������������ͷѭ��Ҫ��죬��ɾ�����ܵ����Ҫ���ں���
	// �����ǰ�棬�ᵼ��Զ���յ�����
#ifdef _REMOTE
	if (m_remoteQueue)
	{
		m_remoteQueue->Input_Copy(ResponeType::OnRtnDepthMarketData, m_msgQueue, m_pClass, 0, 0, pField, sizeof(DepthMarketDataField), nullptr, 0, nullptr, 0);
	}
#endif

	m_msgQueue->Input_NoCopy(ResponeType::OnRtnDepthMarketData, m_msgQueue, m_pClass, 0, 0, pField, sizeof(DepthMarketDataField), nullptr, 0, nullptr, 0);
	// Ҫ��עһ�����ڵ�
	//}	
}


