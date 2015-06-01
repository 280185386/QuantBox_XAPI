#ifndef HLQUOTEAPI_HHH_
#define HLQUOTEAPI_HHH_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HLUserApiDefine.h"

#if defined(ISLIB) && defined(WIN32)
    #ifdef LIB_HLQUOTEAPI_EXPORT
        #define HLQUOTEAPI_EXPORT __declspec(dllexport)
    #else
        #define HLQUOTEAPI_EXPORT __declspec(dllimport)
    #endif
#else
    #define HLQUOTEAPI_EXPORT 
#endif


class HLQUOTEAPI_EXPORT HLQuoteSpi
{
public:
    ///���ͻ����뽻�׺�̨������ͨ�����ӣ��ͻ�����Ҫ���е�¼��
    virtual void OnFrontConnected() {};

    ///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������ã��ͻ��˲���Ҫ����API���Զ�������
    virtual void OnFrontDisconnected(int nReason) {};

    ///����Ӧ��
    //@cIsLast ����־ API_PACKET_FIRST | API_PACKET_LAST ��ͬ
    virtual void OnRspError(CHLRspInfoData *pRspInfo, int nRequestID, char cIsLast) {};

	///�û���¼Ӧ��
	virtual void OnRspUserLogin(HLApiRspUserLoginData *pRspUserLogin, CHLRspInfoData *pRspInfo, int nRequestID, char cIsLast) {};

    ///�û��˳�Ӧ��
    //virtual void OnRspUserLogout(void *pRspUserLogout, void *pRspInfo, int nRequestID, char cIsLast) {};

    ///�г���������Ӧ��
    virtual void OnRspCodeTable (HLApiRspCodeTable *pRspCodeTable, CHLRspInfoData *pRspInfo, int nRequestID, char cIsLast) {};

    ///���鶩������Ӧ��
    virtual void OnRspMarketData (HLApiRspMarketData *pRspMarketData, CHLRspInfoData *pRspInfo, int nRequestID, char cIsLast) {};

    //��������仯֪ͨ
    virtual void OnRtnMarketData (HLApiMarketData *pMarketData) {};

    //ȫ�г�����仯֪ͨ(���Ĺ�Ʊ����Ϊ��ʱ��Ϊȫ�г���������)
    virtual void OnRtnMarketData (HLApiMarketData *pMarketData, int nSize) {};
	virtual void OnRtnPushStkData(HLApiMarketData *pMarketData, int nSize = 1){};

protected:
    virtual ~HLQuoteSpi (void) = 0 {};
};

class HLQUOTEAPI_EXPORT HLQuoteApi
{
public:
    //����һ��HLQuoteApi
    //���Դ������API
    //һ��API���ֻ��һ������ͨ��
    static HLQuoteApi* CreateHLQuoteApi (void);

    ///��ȡϵͳ�汾��
    ///@return ϵͳ�汾�ű�ʶ�ַ���
    static const char *GetVersion (void);

    virtual void RegisterNetwork (unsigned short nPort, const char *pszFrontAddr) = 0;

    virtual void RegisterSpi (HLQuoteSpi *pSpi) = 0;

    virtual int Init (void) = 0;

    virtual void Release (void) = 0;

	///�û���¼����
	virtual int ReqUserLogin (HLApiReqUserLoginData *pReqUserLogin, int nRequestID) = 0;

	///�г���������
	virtual int ReqCodeTable (HLApiReqCodeTable *pReqCodeTable, int nRequestID) = 0;

    ///���鶩������
	virtual int ReqMarketData (HLApiReqMarketData *pReqMarketData, int nRequestID) = 0;

protected:
    virtual ~HLQuoteApi (void);
};

#endif /*HLQUOTEAPI_HHH_*/

