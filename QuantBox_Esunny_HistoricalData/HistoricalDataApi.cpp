#include "stdafx.h"
#include "HistoricalDataApi.h"

#include "../include/QueueEnum.h"
#include "../include/QueueHeader.h"

#include "../include/ApiHeader.h"
#include "../include/ApiStruct.h"

#include "../include/toolkit.h"

#include "../QuantBox_Queue/MsgQueue.h"

#include <cstring>
#include <assert.h>

void DateTimeChat2Int(char* time, int& yyyyMMdd, int& hhmmss)
{
	int yyyy = atoi(&time[0]);
	int MM = atoi(&time[5]);
	int dd = atoi(&time[8]);
	int hh = atoi(&time[11]);
	int mm = atoi(&time[14]);
	int ss = atoi(&time[17]);

	yyyyMMdd = yyyy * 10000 + MM * 100 + dd;
	hhmmss = hh * 10000 + mm * 100 + ss;
}

int GetNextTradingDate(int date)
{
	int yyyy = date / 10000;
	int MM = date % 10000 / 100;
	int dd = date % 100;

	tm start_tm;
	memset(&start_tm, 0, sizeof(tm));
	start_tm.tm_year = yyyy - 1900;
	start_tm.tm_mon = MM - 1;
	start_tm.tm_mday = dd;

	time_t temp_time_t = mktime(&start_tm);
	temp_time_t += 86400;
	while (true)
	{
		tm* next_tm = localtime(&temp_time_t);
		if (next_tm->tm_wday == 0 || next_tm->tm_wday == 6)
			temp_time_t += 86400;
		else
		{
			return (next_tm->tm_year + 1900) * 10000 + (next_tm->tm_mon + 1) * 100 + (next_tm->tm_mday);
		}
	}
}

void* __stdcall Query(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	// ���ڲ����ã����ü���Ƿ�Ϊ��
	CHistoricalDataApi* pApi = (CHistoricalDataApi*)pApi1;
	pApi->QueryInThread(type, pApi1, pApi2, double1, double2, ptr1, size1, ptr2, size2, ptr3, size3);
	return nullptr;
}

void CHistoricalDataApi::QueryInThread(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	int iRet = 0;
	switch (type)
	{
	case E_Init:
		iRet = _Init();
		if (iRet != 0)
			this_thread::sleep_for(chrono::milliseconds(1000 * 20));
		break;
	case E_ReqQryHistoricalTicks:
	{
									HistoricalDataRequestField* pHDR = (HistoricalDataRequestField*)ptr1;
									if (pHDR->CurrentDate != pHDR->Date1)
										this_thread::sleep_for(chrono::milliseconds(1000 * 6));
									iRet = ReqQryHistoricalTicks_(pHDR);
	}
		break;
	case E_ReqQryHistoricalBars:
	{
								   HistoricalDataRequestField* pHDR = (HistoricalDataRequestField*)ptr1;
								   if (pHDR->CurrentDate != pHDR->Date1)
									   this_thread::sleep_for(chrono::milliseconds(1000 * 6));
								   iRet = ReqQryHistoricalBars_(pHDR);
	}
		break;
	case E_ReqQryHistoricalTicks_Check:
		iRet = ReqQryHistoricalTicks_Check();
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
		m_msgQueue_Query->Input(type, pApi1, pApi2, double1, double2, ptr1, size1, ptr2, size2, ptr3, size3);
		//ʧ�ܣ���4���ݽ�����ʱ����������1s
		m_nSleep *= 4;
		m_nSleep %= 1023;
	}
	this_thread::sleep_for(chrono::milliseconds(m_nSleep));
}

CHistoricalDataApi::CHistoricalDataApi(void)
{
	m_pApi = nullptr;
	m_lRequestID = 0;
	m_nSleep = 1;

	// �Լ�ά��������Ϣ����
	m_msgQueue = new CMsgQueue();
	m_msgQueue_Query = new CMsgQueue();

	m_msgQueue_Query->Register(Query);
	m_msgQueue_Query->StartThread();

	m_nHdRequestId = 0;
}


CHistoricalDataApi::~CHistoricalDataApi(void)
{
	Disconnect();
}

void CHistoricalDataApi::Register(void* pCallback)
{
	if (m_msgQueue == nullptr)
		return;

	m_msgQueue_Query->Register(Query);
	m_msgQueue->Register(pCallback);
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

void CHistoricalDataApi::Connect(const string& szPath,
	ServerInfoField* pServerInfo,
	UserInfoField* pUserInfo)
{
	m_szPath = szPath;
	memcpy(&m_ServerInfo, pServerInfo, sizeof(ServerInfoField));
	memcpy(&m_UserInfo, pUserInfo, sizeof(UserInfoField));

	m_msgQueue_Query->Input(RequestType::E_Init, this, nullptr, 0, 0,
		nullptr, 0, nullptr, 0, nullptr, 0);
}

int CHistoricalDataApi::_Init()
{
	m_pApi = CreateEsunnyQuotClient(this);
	m_msgQueue->Input(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Initialized, 0, nullptr, 0, nullptr, 0, nullptr, 0);

	m_msgQueue->Input(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Connecting, 0, nullptr, 0, nullptr, 0, nullptr, 0);
	//��ʼ������
	int iRet = m_pApi->Connect(m_ServerInfo.Address, m_ServerInfo.Port);
	if (0 == iRet)
	{
		m_msgQueue->Input(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Connected, 0, nullptr, 0, nullptr, 0, nullptr, 0);
		iRet = m_pApi->Login(m_UserInfo.UserID, m_UserInfo.Password);
		m_msgQueue->Input(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Logining, 0, nullptr, 0, nullptr, 0, nullptr, 0);
	}
	else
	{
		RspUserLoginField field = { 0 };
		field.ErrorID = iRet;
		strcpy(field.ErrorMsg, "���ӳ�ʱ");

		m_msgQueue->Input(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Disconnected, 0, &field, sizeof(RspUserLoginField), nullptr, 0, nullptr, 0);

		return iRet;
	}
	return iRet;
}

void CHistoricalDataApi::Disconnect()
{
	// �����ѯ����
	if (m_msgQueue_Query)
	{
		m_msgQueue_Query->StopThread();
		m_msgQueue_Query->Register(nullptr);
		m_msgQueue_Query->Clear();
		delete m_msgQueue_Query;
		m_msgQueue_Query = nullptr;
	}

	if (m_pApi)
	{
		m_pApi->DisConnect();
		DelEsunnyQuotClient(m_pApi);
		m_pApi = nullptr;

		// ȫ����ֻ�����һ��
		m_msgQueue->Clear();
		m_msgQueue->Input(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Disconnected, 0, nullptr, 0, nullptr, 0, nullptr, 0);
		// ��������
		m_msgQueue->Process();
	}

	// ������Ӧ����
	if (m_msgQueue)
	{
		m_msgQueue->StopThread();
		m_msgQueue->Register(nullptr);
		m_msgQueue->Clear();
		delete m_msgQueue;
		m_msgQueue = nullptr;
	}

	m_lRequestID = 0;
}
//
//CHistoricalDataApi::SRequest* CHistoricalDataApi::MakeRequestBuf(RequestType type)
//{
//	SRequest *pRequest = new SRequest;
//	if (nullptr == pRequest)
//		return nullptr;
//
//	memset(pRequest, 0, sizeof(SRequest));
//	pRequest->type = type;
//	switch (type)
//	{
//	case E_Init:
//		pRequest->pBuf = nullptr;
//		break;
//	case E_ReqQryHistoricalTicks:
//	case E_ReqQryHistoricalBars:
//		pRequest->pBuf = new HistoricalDataRequestField;
//		break;
//	case E_ReqQryHistoricalTicks_Check:
//		pRequest->pBuf = nullptr;
//		break;
//	default:
//		assert(false);
//		break;
//	}
//	return pRequest;
//}
//
//void CHistoricalDataApi::RunInThread()
//{
//	int iRet = 0;
//
//	while (!m_reqList.empty() && m_bRunning)
//	{
//		SRequest * pRequest = m_reqList.front();
//		int lRequest = ++m_lRequestID;// ����ط��Ƿ�����ԭ�Ӳ����������أ�
//		switch (pRequest->type)
//		{
//		case E_Init:
//			iRet = ReqInit();
//			if (iRet != 0 && m_bRunning)
//                this_thread::sleep_for(chrono::milliseconds(1000 * 20));
//			break;
//		case E_ReqQryHistoricalTicks:
//		{
//										HistoricalDataRequestField* pHDR = (HistoricalDataRequestField*)pRequest->pBuf;
//										// ����̫���ˣ������û�л�Ӧ
//										if (pHDR->CurrentDate != pHDR->Date1)
//											this_thread::sleep_for(chrono::milliseconds(1000 * 6));
//										iRet = ReqQryHistoricalTicks_(pHDR, lRequest);
//		}
//			break;
//		case E_ReqQryHistoricalBars:
//		{
//										HistoricalDataRequestField* pHDR = (HistoricalDataRequestField*)pRequest->pBuf;
//										// ����̫���ˣ������û�л�Ӧ
//										this_thread::sleep_for(chrono::milliseconds(1000 * 6));
//										iRet = ReqQryHistoricalBars_(pHDR, lRequest);
//		}
//			break;
//		case E_ReqQryHistoricalTicks_Check:
//			iRet = ReqQryHistoricalTicks_Check();
//			break;
//		default:
//			assert(false);
//			break;
//		}
//
//		if (0 == iRet)
//		{
//			//���سɹ�����ӵ��ѷ��ͳ�
//			m_nSleep = 1;
//			AddRequestMapBuf(lRequest, pRequest);
//
//			lock_guard<mutex> cl(m_csList);
//			m_reqList.pop_front();
//		}
//		else
//		{
//			//ʧ�ܣ���4���ݽ�����ʱ����������1s
//			m_nSleep *= 4;
//			m_nSleep %= 1023;
//		}
//		this_thread::sleep_for(chrono::milliseconds(m_nSleep));
//	}
//
//	// �����߳�
//	m_hThread = nullptr;
//	m_bRunning = false;
//}


int __cdecl CHistoricalDataApi::OnRspLogin(int err, const char *errtext)
{
	RspUserLoginField field = { 0 };
	field.ErrorID = err;
	strncpy(field.ErrorMsg, errtext, sizeof(ErrorMsgType));

	if (err == 0)
	{
		m_msgQueue->Input(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Logined, 0, &field, sizeof(RspUserLoginField), nullptr, 0, nullptr, 0);
		m_msgQueue->Input(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Done, 0, nullptr, 0, nullptr, 0, nullptr, 0);
	}
	else
	{
		m_msgQueue->Input(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Disconnected, 0, &field, sizeof(RspUserLoginField), nullptr, 0, nullptr, 0);
	}

	return 0;
}

int __cdecl CHistoricalDataApi::OnChannelLost(int err, const char *errtext)
{
	RspUserLoginField field = { 0 };
	field.ErrorID = err;
	strncpy(field.ErrorMsg, errtext, sizeof(ErrorMsgType));

	m_msgQueue->Input(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Disconnected, 0, &field, sizeof(RspUserLoginField), nullptr, 0, nullptr, 0);

	return 0;
}
int __cdecl CHistoricalDataApi::OnStkQuot(struct STKDATA *pData)
{
	return 0;
}

int __cdecl CHistoricalDataApi::OnRspHistoryQuot(struct STKHISDATA *pHisData)
{
	BarField* pFields = new BarField[pHisData->nCount];

	for (short i = 0; i < pHisData->nCount; i++)
	{
		HISTORYDATA item = pHisData->HisData[i];

		BarField* pF = &pFields[i];
		memset(pF, 0, sizeof(BarField));
		DateTimeChat2Int(item.time, pF->Date, pF->Time);
		pF->Open = round(item.fOpen);
		pF->High = round(item.fHigh);
		pF->Low = item.fLow;
		pF->Close = item.fClose;
		pF->Volume = item.fVolume;
		pF->OpenInterest = item.fAmount;
	}

	m_msgQueue->Input(ResponeType::OnRspQryHistoricalBars, m_msgQueue, this, true, 0, pFields, sizeof(BarField)*pHisData->nCount, &m_RequestBar, sizeof(HistoricalDataRequestField), nullptr, 0);

	if (pFields)
		delete[] pFields;

	return 0;
}

int CHistoricalDataApi::ReqQryHistoricalTicks(HistoricalDataRequestField* request)
{
	if (request->Date1 > request->Date2)
	{
		return 0;
	}

	++m_nHdRequestId;
	request->RequestId = m_nHdRequestId;
	request->CurrentDate = request->Date1;

	m_msgQueue_Query->Input(RequestType::E_ReqQryHistoricalTicks, this, nullptr, 0, 0,
		request, sizeof(HistoricalDataRequestField), nullptr, 0, nullptr, 0);

	return m_nHdRequestId;
}

int CHistoricalDataApi::ReqQryHistoricalTicks_(HistoricalDataRequestField* request)
{
	request->lRequest = ++m_lRequestID;
	if (request->CurrentDate > request->Date2)
	{
		return 0;
	}

	memcpy(&m_RequestTick, request, sizeof(HistoricalDataRequestField));

	char buf1[20] = { 0 };
	sprintf(buf1, "%d", request->CurrentDate);
	int iRet = m_pApi->RequestTrace(request->ExchangeID, request->InstrumentID, buf1);
	if (iRet == 0)
	{
		// ÿ��������9��ǰ��ǰ�ǲ���û�з��صģ�����Ҫ��ʱ���,û�оͷ���һ�������ı�ʶ
		m_timer_1 = time(NULL);
		m_msgQueue_Query->Input(RequestType::E_ReqQryHistoricalTicks_Check, this, nullptr, 0, 0,
			nullptr, 0, nullptr, 0, nullptr, 0);
	}
	else
	{
		RtnEmptyRspQryHistoricalTicks();
	}
	return 0;
}

int CHistoricalDataApi::ReqQryHistoricalTicks_Check()
{
	m_timer_2 = time(NULL);
	if (m_timer_1 == 0)
		return 0;

	if (m_timer_2 - m_timer_1 > 10)
	{
		RtnEmptyRspQryHistoricalTicks();
		return 0;
	}
	else
	{
		return -1;
	}
}

int CHistoricalDataApi::RtnEmptyRspQryHistoricalTicks()
{
	bool bIsLast = m_RequestTick.CurrentDate >= m_RequestTick.Date2;

	m_msgQueue->Input(ResponeType::OnRspQryHistoricalTicks, m_msgQueue, this, bIsLast, 0, 0, 0, &m_RequestTick, sizeof(HistoricalDataRequestField), nullptr, 0);

	if (!bIsLast)
	{
		m_RequestTick.CurrentDate = GetNextTradingDate(m_RequestTick.CurrentDate);

		m_msgQueue_Query->Input(RequestType::E_ReqQryHistoricalTicks, this, nullptr, 0, 0,
			&m_RequestTick, sizeof(HistoricalDataRequestField), nullptr, 0, nullptr, 0);
	}

	return 0;
}

double my_round(float val, int x = 0)
{
	double i = ((int)(val * 10000 + 0.5)) / 10000.0;
	return i;
}

int __cdecl CHistoricalDataApi::OnRspTraceData(struct STKTRACEDATA *pTraceData)
{
	m_timer_1 = 0;

	TickField* pFields = new TickField[pTraceData->nCount];

	for (size_t i = 0; i < pTraceData->nCount; i++)
	{
		STOCKTRACEDATA item = pTraceData->TraceData[i];

		TickField* pF = &pFields[i];
		memset(pF, 0, sizeof(TickField));
		DateTimeChat2Int(item.time, pF->Date, pF->Time);
		pF->LastPrice = my_round(item.m_NewPrice);
		pF->Volume = item.m_Volume;
		pF->OpenInterest = item.m_Amount;
		pF->BidPrice1 = my_round(item.m_BuyPrice);
		pF->AskPrice1 = my_round(item.m_SellPrice);
		pF->BidSize1 = (VolumeType)item.m_BuyVol;
		pF->AskSize1 = (VolumeType)item.m_SellVol;
	}

	bool bIsLast = m_RequestTick.CurrentDate >= m_RequestTick.Date2;

	m_msgQueue->Input(ResponeType::OnRspQryHistoricalTicks, m_msgQueue, this, bIsLast, 0, pFields, sizeof(TickField)*pTraceData->nCount, &m_RequestTick, sizeof(HistoricalDataRequestField), nullptr, 0);

	if (pFields)
		delete[] pFields;

	if (!bIsLast)
	{
		m_RequestTick.CurrentDate = GetNextTradingDate(m_RequestTick.CurrentDate);
		m_msgQueue_Query->Input(RequestType::E_ReqQryHistoricalTicks, this, nullptr, 0, 0,
			&m_RequestTick, sizeof(HistoricalDataRequestField), nullptr, 0, nullptr, 0);
	}

	return 0;
}

int __cdecl CHistoricalDataApi::OnRspMarketInfo(struct MarketInfo *pMarketInfo, int bLast)
{
	for (unsigned short i = 0; i < pMarketInfo->stocknum; i++)
	{
		StockInfo item = pMarketInfo->stockdata[i];

		InstrumentField field = { 0 };

		strcpy(field.InstrumentID, item.szCode);
		strcpy(field.ExchangeID, pMarketInfo->Market);

		strcpy(field.Symbol, item.szCode);

		strcpy(field.InstrumentName, item.szName);
		field.Type = InstrumentType::Future;

		m_msgQueue->Input(ResponeType::OnRspQryInstrument, m_msgQueue, this, i >= pMarketInfo->stocknum - 1, 0, &field, sizeof(InstrumentField), nullptr, 0, nullptr, 0);
	}

	return 0;
}


int Period2BarSize(int period)
{
	int barSize = 0;
	switch (period)
	{
	case 1:
		barSize = 60;
		break;
	case 2:
		barSize = 300;
		break;
	case 3:
		barSize = 3600;
		break;
	case 4:
		barSize = 86400;
		break;
	default:
		break;
	}
	return barSize;
}

int BarSize2Period(int barSize)
{
	int period = 0;
	switch (barSize)
	{
	case 60:
		period = 1;
		break;
	case 60 * 5:
		period = 2;
		break;
	case 3600:
		period = 3;
		break;
	case 86400:
		period = 4;
		break;
	default:
		break;
	}
	return period;
}

int CHistoricalDataApi::ReqQryHistoricalBars(HistoricalDataRequestField* request)
{
	++m_nHdRequestId;
	request->RequestId = m_nHdRequestId;

	m_msgQueue_Query->Input(RequestType::E_ReqQryHistoricalBars, this, nullptr, 0, 0,
		request, sizeof(HistoricalDataRequestField), nullptr, 0, nullptr, 0);

	return m_nHdRequestId;
}

int CHistoricalDataApi::ReqQryHistoricalBars_(HistoricalDataRequestField* request)
{
	request->lRequest = ++m_lRequestID;
	memcpy(&m_RequestBar, request, sizeof(HistoricalDataRequestField));

	int period = BarSize2Period(request->BarSize);
	if (period == 0)
		return 0;

	return m_pApi->RequestHistory(request->ExchangeID, request->InstrumentID, period);
}