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

//�ͻ���ʵ�����ͻص�����
void __stdcall OnReadPushData(ETX_APP_FUNCNO FuncNO, void* pEtxPushData)
{
	char szmsg[2048] = { 0 };

	PST16203PushData pCJData = NULL;
	PST16204PushData pCDFDData = NULL;

	if (ETX_16203 == FuncNO)
	{
		pCJData = (PST16203PushData)pEtxPushData;

		//cout << pCJData->cust_no << " " << pCJData->order_no << endl;

	}
	else if (ETX_16204 == FuncNO)
	{
		//cout << pCDFDData->cust_no << " " << pCDFDData->order_no << endl;
	}
	else
	{
		sprintf(szmsg, "�޷�ʶ�����������[%d]", FuncNO);
		printf(szmsg);
	}

}

void* __stdcall Query(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	// ���ڲ����ã����ü���Ƿ�Ϊ��
	CTraderApi* pApi = (CTraderApi*)pApi1;
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
	//���ص�ַ�������Ϣ�ɿͻ��������ã�����ʵ��������ã��������ã�
	//����������Ϣ
	SPX_API_SetParam(MAINSERVER_IP, m_ServerInfo.Address, &m_err_msg);
	SPX_API_SetParam(MAINSERVER_PORT, "8085", &m_err_msg);
	//SPX_API_SetParam(BACKSERVER_IP, "127.0.0.1", &m_err_msg);
	//SPX_API_SetParam(BACKSERVER_PORT, "17990", &m_err_msg);
	//���ô�����Ϣ
	//SPX_API_SetParam(PROXY_TYPE, "1", &m_err_msg);
	//SPX_API_SetParam(PROXY_IP, "127.0.0.1", &m_err_msg);
	//SPX_API_SetParam(PROXY_PORT, "9999", &m_err_msg);
	//SPX_API_SetParam(PROXY_USER, "", &m_err_msg);
	//SPX_API_SetParam(PROXY_PASS, "", &m_err_msg);


	STInitPara init_para;
	init_para.pOnReadPushData = OnReadPushData;
	init_para.bWriteLog = true;
	init_para.emLogLevel = LL_INFO;
	init_para.nTimeOut = 60000;

	m_msgQueue->Input_Copy(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Uninitialized, 0, nullptr, 0, nullptr, 0, nullptr, 0);

	bool bRet = SPX_API_Initialize(&init_para, &m_err_msg);
	//IsErrorRspInfo(&m_err_msg, 0, true);
	if (!bRet)
	{
		RspUserLoginField* pField = (RspUserLoginField*)m_msgQueue->new_block(sizeof(RspUserLoginField));

		//����ʧ�ܷ��ص���Ϣ��ƴ�Ӷ��ɣ���Ҫ��Ϊ��ͳһ���
		pField->ErrorID = m_err_msg.error_no;
		strcpy(pField->ErrorMsg, m_err_msg.msg);

		m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Disconnected, 0, pField, sizeof(RspUserLoginField), nullptr, 0, nullptr, 0);

		return 0;
	}

	m_pApi = SPX_API_CreateHandle(&m_err_msg);
	IsErrorRspInfo(&m_err_msg, 0, true);
	
	ReqUserLogin();

	return 0;
}

void CTraderApi::ReqUserLogin()
{
	STTraderLogin* pBody = (STTraderLogin*)m_msgQueue_Query->new_block(sizeof(STTraderLogin));

	strncpy(pBody->cust_no, m_UserInfo.UserID, sizeof(TCustNoType));
	strncpy(pBody->cust_pwd, m_UserInfo.Password, sizeof(TCustPwdType));

	m_msgQueue_Query->Input_NoCopy(RequestType::E_ReqUserLoginField, this, nullptr, 0, 0,
		pBody, sizeof(STTraderLogin), nullptr, 0, nullptr, 0);
}

int CTraderApi::_ReqUserLogin(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	int row_num = 0;
	STTraderLoginRsp *p_login_rsp = nullptr;
	bool bRet = SPX_API_Login(m_pApi, (STTraderLogin*)ptr1, &p_login_rsp, &row_num, &m_err_msg);

	if (bRet && m_err_msg.error_no == 0)
	{
		if (row_num <= 0)
		{
			printf("���ؽ��Ϊ��");
		}
		else if (p_login_rsp != nullptr)
		{
			for (int i = 0; i<row_num; i++)
			{
				//cout << p_login_rsp[i].cust_name << " " << p_login_rsp[i].market_code << " " << p_login_rsp[i].holder_acc_no << endl;
			}
		}
	}


	//m_msgQueue->Input(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Logining, 0, nullptr, 0, nullptr, 0, nullptr, 0);
	//return m_pApi->ReqUserLogin((CThostFtdcReqUserLoginField*)ptr1, ++m_lRequestID);
	return 0;
}

CTraderApi::CTraderApi(void)
{
	m_pApi = nullptr;
	m_lRequestID = 0;
	m_nSleep = 1;

	// �Լ�ά��������Ϣ����
	m_msgQueue = new CMsgQueue();
	m_msgQueue_Query = new CMsgQueue();

	m_msgQueue_Query->Register(Query);
	m_msgQueue_Query->StartThread();
}


CTraderApi::~CTraderApi(void)
{
	Disconnect();
}

void CTraderApi::Register(void* pCallback)
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

bool CTraderApi::IsErrorRspInfo(STRspMsg *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bRet = ((pRspInfo) && (pRspInfo->error_no != 0));
	if (bRet)
	{
		ErrorField* pField = (ErrorField*)m_msgQueue->new_block(sizeof(ErrorField));

		pField->ErrorID = pRspInfo->error_no;
		strcpy(pField->ErrorMsg, pRspInfo->msg);

		m_msgQueue->Input_NoCopy(ResponeType::OnRtnError, m_msgQueue, this, bIsLast, 0, pField, sizeof(ErrorField), nullptr, 0, nullptr, 0);
	}
	return bRet;
}

bool CTraderApi::IsErrorRspInfo(STRspMsg *pRspInfo)
{
	bool bRet = ((pRspInfo) && (pRspInfo->error_no != 0));

	return bRet;
}

void CTraderApi::Connect(const string& szPath,
	ServerInfoField* pServerInfo,
	UserInfoField* pUserInfo)
{
	m_szPath = szPath;
	memcpy(&m_ServerInfo, pServerInfo, sizeof(ServerInfoField));
	memcpy(&m_UserInfo, pUserInfo, sizeof(UserInfoField));

	m_msgQueue_Query->Input_NoCopy(E_Init, this, nullptr, 0, 0, nullptr, 0, nullptr, 0, nullptr, 0);
}

void CTraderApi::Disconnect()
{
	if (m_msgQueue_Query)
	{
		m_msgQueue_Query->StopThread();
		m_msgQueue_Query->Register(nullptr);
		m_msgQueue_Query->Clear();
		delete m_msgQueue_Query;
		m_msgQueue_Query = nullptr;
	}

	if(m_pApi)
	{
		SPX_API_DestroyHandle(&m_pApi, &m_err_msg);
		m_pApi = nullptr;

		// ȫ����ֻ�����һ��
		m_msgQueue->Clear();
		m_msgQueue->Input_NoCopy(ResponeType::OnConnectionStatus, m_msgQueue, this, ConnectionStatus::Disconnected, 0, nullptr, 0, nullptr, 0, nullptr, 0);
		// ��������
		m_msgQueue->Process();
	}
	SPX_API_Finalize(&m_err_msg);

	if (m_msgQueue)
	{
		m_msgQueue->StopThread();
		m_msgQueue->Register(nullptr);
		m_msgQueue->Clear();
		delete m_msgQueue;
		m_msgQueue = nullptr;
	}
}