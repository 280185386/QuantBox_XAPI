#include "stdafx.h"
#include "TraderApi.h"

#include "../include/QueueEnum.h"
#include "../include/QueueHeader.h"

#include "../include/ApiHeader.h"
#include "../include/ApiStruct.h"

#include "../include/toolkit.h"

#include "../QuantBox_Queue/MsgQueue.h"

#include "TypeConvert.h"

#include <cstring>
#include <assert.h>


void* __stdcall Query(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	// ���ڲ����ã����ü���Ƿ�Ϊ��
	CTraderApi* pApi = (CTraderApi*)pApi2;
	pApi->QueryInThread(type, pApi1, pApi2, double1, double2, ptr1, size1, ptr2, size2, ptr3, size3);
	return nullptr;
}

void CTraderApi::QueryInThread(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
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
	case E_QryOrderField:
		iRet = _ReqQryOrder(type, pApi1, pApi2, double1, double2, ptr1, size1, ptr2, size2, ptr3, size3);
		break;
	case E_QryTradeField:
		iRet = _ReqQryTrade(type, pApi1, pApi2, double1, double2, ptr1, size1, ptr2, size2, ptr3, size3);
		break;
	case E_QryInvestorField:
		iRet = _ReqQryInvestor(type, pApi1, pApi2, double1, double2, ptr1, size1, ptr2, size2, ptr3, size3);
		break;
	case E_InputOrderField:
		iRet = _ReqOrderInsert(type, pApi1, pApi2, double1, double2, ptr1, size1, ptr2, size2, ptr3, size3);
		break;
	case E_InputOrderActionField:
		iRet = _ReqOrderAction(type, pApi1, pApi2, double1, double2, ptr1, size1, ptr2, size2, ptr3, size3);
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

int CTraderApi::_Init()
{
	if (m_pApi == nullptr)
	{
		m_pApi = CTdxApi::CreateApi(m_ServerInfo.ExtendInformation);
	}

	Error_STRUCT* pErr = nullptr;

	m_pApi->LoadScript(m_ServerInfo.Address, true, false);
	m_pApi->Init(m_ServerInfo.ExtendInformation, &pErr);

	if (pErr)
	{
		RspUserLoginField* pField = (RspUserLoginField*)m_msgQueue->new_block(sizeof(RspUserLoginField));

		pField->ErrorID = pErr->ErrCode;
		strcpy(pField->ErrorMsg, pErr->ErrInfo);

		m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Disconnected, 0, pField, sizeof(RspUserLoginField), nullptr, 0, nullptr, 0);
	}
	else
	{
		m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Initialized, 0, nullptr, 0, nullptr, 0, nullptr, 0);

		ReqUserLogin();
	}

	DeleteError(pErr);

	return 0;
}

void CTraderApi::ReqUserLogin()
{
	if (m_UserInfo_Pos >= m_UserInfo_Count)
		return;

	//STTraderLogin* pBody = (STTraderLogin*)m_msgQueue_Query->new_block(sizeof(STTraderLogin));

	//strncpy(pBody->cust_no, m_pUserInfos[m_UserInfo_Pos].UserID, sizeof(TCustNoType));
	//strncpy(pBody->cust_pwd, m_pUserInfos[m_UserInfo_Pos].Password, sizeof(TCustPwdType));

	m_msgQueue_Query->Input_NoCopy(RequestType::E_ReqUserLoginField, m_msgQueue_Query, this, 0, 0,
		nullptr, 0, nullptr, 0, nullptr, 0);
}

int CTraderApi::_ReqUserLogin(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	char** ppResults = nullptr;
	Error_STRUCT* pErr = nullptr;

	m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Logining, 0, nullptr, 0, nullptr, 0, nullptr, 0);

	m_pClient = m_pApi->Login(m_UserInfo.UserID, m_UserInfo.Password, &ppResults, &pErr);

	if (m_pClient)
	{
		// ����Ȩ��ϢҪ���
		RspUserLoginField* pField = (RspUserLoginField*)m_msgQueue->new_block(sizeof(RspUserLoginField));
		if (pErr)
		{
			pField->ErrorID = pErr->ErrCode;
			strcpy(pField->ErrorMsg, pErr->ErrInfo);
		}

		m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Logined, 0, pField, sizeof(pField), nullptr, 0, nullptr, 0);
		
		m_pApi->SetClient(m_pClient);
		m_pApi->SetAccount(m_UserInfo.UserID);

		// ��ѯ�ɶ��б�
		ReqQryInvestor();

		// ������,�º���Ҫɾ��
		ReqQryTrade();

		m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Done, 0, nullptr, 0, nullptr, 0, nullptr, 0);


		// ��¼��һ���˺�
		//++m_UserInfo_Pos;
		//ReqUserLogin();
	}
	else
	{
		if (pErr)
		{
			RspUserLoginField* pField = (RspUserLoginField*)m_msgQueue->new_block(sizeof(RspUserLoginField));

			pField->ErrorID = pErr->ErrCode;
			strcpy(pField->ErrorMsg, pErr->ErrInfo);

			m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Disconnected, 0, pField, sizeof(RspUserLoginField), nullptr, 0, nullptr, 0);
		}
	}

	DeleteError(pErr);
	DeleteTableBody(ppResults);

	return 0;
}

void CTraderApi::ReqQryInvestor()
{
	m_msgQueue_Query->Input_NoCopy(RequestType::E_QryInvestorField, m_msgQueue_Query, this, 0, 0,
		nullptr, 0, nullptr, 0, nullptr, 0);
}

int CTraderApi::_ReqQryInvestor(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	if (m_pApi == nullptr)
		return 0;

	FieldInfo_STRUCT** ppFieldInfos = nullptr;
	char** ppResults = nullptr;
	Error_STRUCT* pErr = nullptr;

	m_pApi->ReqQueryData(REQUEST_GDLB, &ppFieldInfos, &ppResults, &pErr);

	if (!IsErrorRspInfo(pErr))
	{
		if (ppResults)
		{
			int count = GetRowCountTableBody(ppResults);
			for (int i = 0; i < count; ++i)
			{
				InvestorField* pField = (InvestorField*)m_msgQueue->new_block(sizeof(InvestorField));

				//strcpy(pField->BrokerID, pInvestor->BrokerID);
				strcpy(pField->InvestorID, ppResults[i * COL_EACH_ROW + 0]);
				strcpy(pField->InvestorName, ppResults[i * COL_EACH_ROW + 1]);

				m_msgQueue->Input_NoCopy(ResponeType::OnRspQryInvestor, m_msgQueue, m_pClass, i == count - 1, 0, pField, sizeof(InvestorField), nullptr, 0, nullptr, 0);
			}
		}
	}

	DeleteTableBody(ppResults);
	DeleteError(pErr);

	return 0;
}

CTraderApi::CTraderApi(void)
{
	m_pIDGenerator = nullptr;
	m_pApi = nullptr;
	m_pClient = nullptr;
	m_lRequestID = 0;
	m_nSleep = 1;

	// �Լ�ά��������Ϣ����
	m_msgQueue = new CMsgQueue();
	m_msgQueue_Query = new CMsgQueue();

	m_msgQueue_Query->Register(Query,this);
	m_msgQueue_Query->StartThread();
}


CTraderApi::~CTraderApi(void)
{
	Disconnect();
}

void CTraderApi::Register(void* pCallback, void* pClass)
{
	m_pClass = pClass;
	if (m_msgQueue == nullptr)
		return;

	m_msgQueue_Query->Register(Query,this);
	m_msgQueue->Register(pCallback,this);
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

bool CTraderApi::IsErrorRspInfo(Error_STRUCT *pRspInfo)
{
	bool bRet = ((pRspInfo) && (pRspInfo->ErrType != 0));
	if (bRet)
	{
		ErrorField* pField = (ErrorField*)m_msgQueue->new_block(sizeof(ErrorField));

		pField->ErrorID = pRspInfo->ErrCode;
		strcpy(pField->ErrorMsg, pRspInfo->ErrInfo);

		m_msgQueue->Input_NoCopy(ResponeType::OnRtnError, m_msgQueue, m_pClass, true, 0, pField, sizeof(ErrorField), nullptr, 0, nullptr, 0);
	}
	return bRet;
}

void CTraderApi::Connect(const string& szPath,
	ServerInfoField* pServerInfo,
	UserInfoField* pUserInfo,
	int count)
{
	m_szPath = szPath;
	memcpy(&m_ServerInfo, pServerInfo, sizeof(ServerInfoField));
	memcpy(&m_UserInfo, pUserInfo, sizeof(UserInfoField));

	m_pUserInfos = (UserInfoField*)(new char[sizeof(UserInfoField)*count]);
	memcpy(m_pUserInfos, pUserInfo, sizeof(UserInfoField)*count);

	m_UserInfo_Pos = 0;
	m_UserInfo_Count = count;

	m_pIDGenerator = new CIDGenerator();
	m_pIDGenerator->SetPrefix(m_UserInfo.UserID);

	m_msgQueue_Query->Input_NoCopy(E_Init, m_msgQueue_Query, this, 0, 0, nullptr, 0, nullptr, 0, nullptr, 0);
}

void CTraderApi::Disconnect()
{
	if (m_msgQueue_Query)
	{
		m_msgQueue_Query->StopThread();
		m_msgQueue_Query->Register(nullptr,nullptr);
		m_msgQueue_Query->Clear();
		delete m_msgQueue_Query;
		m_msgQueue_Query = nullptr;
	}

	if(m_pApi)
	{
		// ��û�еǳ�
		m_pApi->Logout(m_pClient);
		m_pClient = nullptr;
		m_pApi->Exit();
		
		m_pApi->Release();
		m_pApi = nullptr;

		// ȫ����ֻ�����һ��
		if (m_msgQueue)
		{
			m_msgQueue->Clear();
			m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, m_pClass, ConnectionStatus::Disconnected, 0, nullptr, 0, nullptr, 0, nullptr, 0);
			// ��������
			m_msgQueue->Process();
		}
	}

	if (m_msgQueue)
	{
		m_msgQueue->StopThread();
		m_msgQueue->Register(nullptr,nullptr);
		m_msgQueue->Clear();
		delete m_msgQueue;
		m_msgQueue = nullptr;
	}

	if (m_pIDGenerator)
	{
		delete m_pIDGenerator;
		m_pIDGenerator = nullptr;
	}
}

int CTraderApi::ReqOrderInsert(
	OrderField* pOrder,
	int count,
	OrderIDType* pInOut)
{
	memset(pInOut, 0, sizeof(OrderIDType)*count);

	if (count < 1)
		return 0;	

	OrderField** ppOrders = new OrderField*[count];
	
	// ���ɱ���ID�����ϲ���ж�λʹ��
	for (int i = 0; i < count; ++i)
	{
		OrderField* pNewOrder = (OrderField*)m_msgQueue->new_block(sizeof(OrderField));
		memcpy(pNewOrder, pOrder, sizeof(OrderField));

		strcpy(pInOut[i], m_pIDGenerator->GetIDString());
		strcpy(pNewOrder[i].LocalID, pInOut[i]);
		ppOrders[i] = pNewOrder;

		// ע�����ﱣ�����ʼ�����Ľṹ��ı���
		m_id_platform_order.insert(pair<string, OrderField*>(pNewOrder->LocalID, pNewOrder));
	}

	m_msgQueue_Query->Input_Copy(RequestType::E_InputOrderField, m_msgQueue_Query, this, 0, 0,
		ppOrders, sizeof(OrderField*)*count, nullptr, 0, nullptr, 0);

	delete[] ppOrders;
	
	return 0;
}

void BuildOrder(OrderField* pIn, Order_STRUCT* pOut)
{
	strcpy(pOut->ZQDM, pIn->InstrumentID);
	pOut->Price = pIn->Price;
	pOut->Qty = pIn->Qty;

	// ����ط�����Ҫ�ٸ�
	switch (pIn->Type)
	{
	case OrderType::Market:
		pOut->WTFS = WTFS_Five_IOC;
		if (pIn->Side == OrderSide::Buy)
		{
			pOut->MMBZ = MMBZ_Buy_Market;
		}
		else
		{
			pOut->MMBZ = MMBZ_Sell_Market;
		}
		break;
	case OrderType::Limit:
		pOut->WTFS = WTFS_Limit;
		if (pIn->Side == OrderSide::Buy)
		{
			pOut->MMBZ = MMBZ_Buy_Limit;
		}
		else
		{
			pOut->MMBZ = MMBZ_Sell_Limit;
		}
		break;
	}

	pOut->RZRQBS = RZRQBS_NO;
}

int CTraderApi::_ReqOrderInsert(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	if (m_pApi == nullptr)
		return 0;

	// �õ�����ָ���б�
	OrderField** ppOrders = (OrderField**)ptr1;
	int count = (int)size1 / sizeof(OrderField*);

	Order_STRUCT** ppTdxOrders = new Order_STRUCT*[count];
	for (int i = 0; i < count; ++i)
	{
		ppTdxOrders[i] = (Order_STRUCT*)m_msgQueue->new_block(sizeof(Order_STRUCT));
		BuildOrder(ppOrders[i], ppTdxOrders[i]);
	}

	FieldInfo_STRUCT** ppFieldInfos = nullptr;
	char** ppResults = nullptr;
	Error_STRUCT** ppErrs = nullptr;

	// ע�⣺pTdxOrders�����ﱻ�޸��ˣ���Ҫʹ���޸ĺ�Ķ���
	int n = m_pApi->SendMultiOrders(ppTdxOrders, count, &ppFieldInfos, &ppResults, &ppErrs);

	// ���������ȡ����
	for (int i = 0; i < count;++i)
	{
		m_id_api_order.insert(pair<string, Order_STRUCT*>(ppOrders[i]->LocalID, ppTdxOrders[i]));
		// �������
		if (ppErrs && ppErrs[i])
		{
			ppOrders[i]->ErrorID = ppErrs[i]->ErrCode;
			strcpy(ppOrders[i]->Text, ppErrs[i]->ErrInfo);
		}

		// ������
		if (ppResults && ppResults[i*COL_EACH_ROW + 0])
		{
			// д�Ϲ�̨��ID���Ժ󽫻��ڴ˽��ж�λ
			strcpy(ppOrders[i]->ID, ppResults[i*COL_EACH_ROW + 0]);

			m_id_api_order.erase(ppOrders[i]->LocalID);
			m_id_api_order.insert(pair<string, Order_STRUCT*>(ppOrders[i]->ID, ppTdxOrders[i]));

			m_id_platform_order.erase(ppOrders[i]->LocalID);
			m_id_platform_order.insert(pair<string, OrderField*>(ppOrders[i]->ID, ppOrders[i]));
		}

		// �����������ṹ�壬��Ҫ���в�����
		// 1.֪ͨ�µ��Ľ��
		// 2.��¼�µ�
		
		OrderField* pField = ppOrders[i];
		if (pField->ErrorID != 0)
		{
			pField->ExecType = ExecType::ExecRejected;
			pField->Status = OrderStatus::Rejected;
		}
		else
		{
			pField->ExecType = ExecType::ExecNew;
			pField->Status = OrderStatus::New;
		}
		
		m_msgQueue->Input_Copy(ResponeType::OnRtnOrder, m_msgQueue, m_pClass, 0, 0, pField, sizeof(OrderField), nullptr, 0, nullptr, 0);
	}

	// �������ˣ�����ɾ����ǰ����
	delete[] ppTdxOrders;

	DeleteTableBody(ppResults, count);
	DeleteErrors(ppErrs, count);

	return 0;
}

int CTraderApi::ReqOrderAction(OrderIDType* szId, int count, OrderIDType* pOutput)
{
	memset(pOutput, 0, sizeof(OrderIDType)*count);

	OrderField** ppOrders = new OrderField*[count];
	Order_STRUCT** ppTdxOrders = new Order_STRUCT*[count];

	for (int i = 0; i < count; ++i)
	{
		ppOrders[i] = nullptr;
		ppTdxOrders[i] = nullptr;

		{
			unordered_map<string, OrderField*>::iterator it = m_id_platform_order.find(szId[i]);
			if (it != m_id_platform_order.end())
				ppOrders[i] = it->second;
		}
		
		{
			unordered_map<string, Order_STRUCT*>::iterator it = m_id_api_order.find(szId[i]);
			if (it != m_id_api_order.end())
				ppTdxOrders[i] = it->second;
		}
	}

	m_msgQueue_Query->Input_Copy(RequestType::E_InputOrderActionField, m_msgQueue_Query, this, 0, 0,
		ppOrders, sizeof(OrderField*)*count, ppTdxOrders, sizeof(Order_STRUCT*)*count, nullptr, 0);

	delete[] ppOrders;
	delete[] ppTdxOrders;

	return 0;
}

int CTraderApi::_ReqOrderAction(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	int count = (int)size1 / sizeof(OrderField*);
	// ͨ��ID�ҵ�ԭʼ�ṹ�����ڳ���
	// ͨ��ID�ҵ�ͨ�ýṹ�����ڽ��ջر�
	OrderField** ppOrders = (OrderField**)ptr1;
	Order_STRUCT** ppTdxOrders = (Order_STRUCT**)ptr2;

	FieldInfo_STRUCT** ppFieldInfos = nullptr;
	char** ppResults = nullptr;
	Error_STRUCT** ppErrs = nullptr;

	int n = m_pApi->CancelMultiOrders(ppTdxOrders, count, &ppFieldInfos, &ppResults, &ppErrs);

	// ���������ȡ����
	for (int i = 0; i < count; ++i)
	{
		if (ppErrs)
		{
			if (ppErrs[i])
			{
				ppOrders[i]->ErrorID = ppErrs[i]->ErrCode;
				strcpy(ppOrders[i]->Text, ppErrs[i]->ErrInfo);

				ppOrders[i]->ExecType = ExecType::ExecCancelReject;
			}
			else
			{
				ppOrders[i]->ExecType = ExecType::ExecCancelled;
				ppOrders[i]->Status = OrderStatus::Cancelled;
			}
		}
		// �����ɹ�ʱ�����صĶ�������null,��������ʹ�ô�����Ϣ����������
		//if (ppResults)
		//{	
		//	if (ppResults[i*COL_EACH_ROW + 0])
		//	{
		//	}
		//}

		m_msgQueue->Input_Copy(ResponeType::OnRtnOrder, m_msgQueue, m_pClass, 0, 0, ppOrders[i], sizeof(OrderField), nullptr, 0, nullptr, 0);
	}

	DeleteTableBody(ppResults, count);
	DeleteErrors(ppErrs, count);

	return 0;
}

void CTraderApi::ReqQryOrder()
{
	m_msgQueue_Query->Input_NoCopy(RequestType::E_QryOrderField, m_msgQueue_Query, this, 0, 0,
		nullptr, 0, nullptr, 0, nullptr, 0);
}

int CTraderApi::_ReqQryOrder(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	FieldInfo_STRUCT** ppFieldInfos = nullptr;
	char** ppResults = nullptr;
	Error_STRUCT* pErr = nullptr;

	m_pApi->ReqQueryData(REQUEST_DRWT, &ppFieldInfos, &ppResults, &pErr);

	WTLB_STRUCT** ppRS = nullptr;
	CharTable2WTLB(ppFieldInfos, ppResults, &ppRS);

	if (ppRS)
	{
		// ��Ҫ�������뵽һ���ط����ڼ���
	}

	DeleteTableBody(ppResults);
	DeleteError(pErr);

	return 0;
}

void CTraderApi::ReqQryTrade()
{
	m_msgQueue_Query->Input_NoCopy(RequestType::E_QryTradeField, m_msgQueue_Query, this, 0, 0,
		nullptr, 0, nullptr, 0, nullptr, 0);
}

int CTraderApi::_ReqQryTrade(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	FieldInfo_STRUCT** ppFieldInfos = nullptr;
	char** ppResults = nullptr;
	Error_STRUCT* pErr = nullptr;

	m_pApi->ReqQueryData(REQUEST_DRCJ, &ppFieldInfos, &ppResults, &pErr);

	CJLB_STRUCT** ppRS = nullptr;
	CharTable2CJLB(ppFieldInfos, ppResults, &ppRS);

	if (ppRS)
	{
		// ��Ҫ�������뵽һ���ط����ڼ���
		TradeField* pField = (TradeField*)m_msgQueue->new_block(sizeof(TradeField));

		CJLB_2_TradeField(ppRS[0], pField);
		
		m_msgQueue->Input_Copy(ResponeType::OnRtnTrade, m_msgQueue, m_pClass, 0, 0, pField, sizeof(TradeField), nullptr, 0, nullptr, 0);
	}

	DeleteTableBody(ppResults);
	DeleteError(pErr);

	return 0;
}

void CTraderApi::ReqQryInstrument(const string& szInstrumentId, const string& szExchange)
{

}

//void CTraderApi::OnPST16203PushData(PST16203PushData pEtxPushData)
//{
//	OrderIDType orderId = { 0 };
//
//	// ֻ�Ǵ�ӡ�ɽ�
//	ErrorField* pField = (ErrorField*)m_msgQueue->new_block(sizeof(ErrorField));
//
//	//pField->ErrorID = pRspInfo->error_no;
//	sprintf(pField->ErrorMsg,"OnPST16203PushData %s",pEtxPushData->order_status_name);
//
//	m_msgQueue->Input_NoCopy(ResponeType::OnRtnError, m_msgQueue, m_pClass, true, 0, pField, sizeof(ErrorField), nullptr, 0, nullptr, 0);
//}
//
//void CTraderApi::OnPST16204PushData(PST16204PushData pEtxPushData)
//{
//	OrderIDType orderId = { 0 };
//
//	// ֻ�Ǵ�ӡ�ɽ�
//	ErrorField* pField = (ErrorField*)m_msgQueue->new_block(sizeof(ErrorField));
//
//	//pField->ErrorID = pRspInfo->error_no;
//	sprintf(pField->ErrorMsg, "OnPST16204PushData %s", pEtxPushData->order_status_name);
//
//	m_msgQueue->Input_NoCopy(ResponeType::OnRtnError, m_msgQueue, m_pClass, true, 0, pField, sizeof(ErrorField), nullptr, 0, nullptr, 0);
//}