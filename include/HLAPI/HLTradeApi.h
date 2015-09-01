#ifndef HLTRADEAPI_HHH_
#define HLTRADEAPI_HHH_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HLUserApiDefine.h"


#if defined(ISLIB) && defined(WIN32)
    #ifdef LIB_HLTRADEAPI_EXPORT
        #define HLTRADEAPI_EXPORT __declspec(dllexport)
    #else
        #define HLTRADEAPI_EXPORT __declspec(dllimport)
    #endif
#else
    #define HLTRADEAPI_EXPORT 
#endif

class HLTRADEAPI_EXPORT HLTradeSpi
{
public:
    ///���ͻ����뽻�׺�̨������ͨ�����ӣ��ͻ�����Ҫ���е�¼��
    virtual void OnFrontConnected() {};

    ///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������ã��ͻ��˲���Ҫ����API���Զ�������
    virtual void OnFrontDisconnected(int nReason) {};

    ///����Ӧ��
    //@cIsLast ����־ API_PACKET_FIRST | API_PACKET_LAST ��ͬ
    virtual void OnRspError(CHLRspInfoData* pRspInfo, int nRequestID, char cIsLast) {};

	///�û���¼_Ӧ��
	virtual void OnRspUserLogin(HLApiRspUserLoginData* pRspUserLogin, CHLRspInfoData* pRspInfo, int nRequestID, char cIsLast) {};

    ///�û��˳�_Ӧ��
    //virtual void OnRspUserLogout(void *pRspUserLogout, void *pRspInfo, int nRequestID, char cIsLast) {};

    ///�û�ί������_Ӧ��
    virtual void OnRspOrder(HLApiRspOrder* pRspOrder, CHLRspInfoData* pRspInfo, int nRequestID, char cIsLast) {};

    ///�û���������_Ӧ��
    virtual void OnRspCancelOrder(HLApiRspCancelOrder* pRspCancelOrder, CHLRspInfoData* pRspInfo, int nRequestID, char cIsLast) {};

    ///ETF�嵥����_Ӧ��
    virtual void OnRspETFList(HLApiRspETFList* pRspETFList, CHLRspInfoData* pRspInfo, int nRequestID, char cIsLast) {};

    ///ETF��������_Ӧ��
    virtual void OnRspETFSubscribe(HLApiRspETFSubscribe* pRspETFSubscribe, CHLRspInfoData* pRspInfo, int nRequestID, char cIsLast) {};

    ///��ί������_Ӧ��
    virtual void OnRspOrderQry(HLApiRspOrderQry* pRspQryOrder, CHLRspInfoData* pRspInfo, int nRequestID, char cIsLast) {};

    ///�鵱�ճɽ�����_Ӧ��
    virtual void OnRspTodayDealQry(HLApiRspTodayDealQry* pRspQryTodayDeal, CHLRspInfoData* pRspInfo, int nRequestID, char cIsLast) {};

    ///���ʽ�����_Ӧ��
    virtual void OnRspMoneyInfoQry(HLApiRspMoneyInfoQry* pRspQryMoneyInfo, CHLRspInfoData* pRspInfo, int nRequestID, char cIsLast) {};

    ///����֤ȯ��ѯ����_Ӧ��
    virtual void OnRspAvlStockInfoQry(HLApiRspAvlStocksInfoQry* pReqQryAvlStockInfo, CHLRspInfoData* pRspInfo, int nRequestID, char cIsLast) {};

    ///ί�С�����������ʧ��֪ͨ
    virtual void OnRtnOrderInfo(HLApiRtnOrderInfo* pRtnOrderInfo, CHLRspInfoData* pRspInfo, int nRequestID) {};

    ///�ɽ�֪ͨ
    virtual void OnRtnMatchInfo(HLApiRtnMatchInfo* pRtnMatchInfo, CHLRspInfoData* pRspInfo, int nRequestID) {};

    ///����֤ȯ�仯֪ͨ
    virtual void OnRtnAvlStockInfo(HLApiRtnAvlStockInfo* pRtnAvlStockInfo, CHLRspInfoData* pRspInfo, int nRequestID) {};

    ///�ʽ�仯֪ͨ
    virtual void OnRtnMoneyInfo(HLApiRtnMoneyInfo* pRtnMoneyInfo, CHLRspInfoData* pRspInfo, int nRequestID) {};

	///�ּ�����ɷ���Ϣ��ѯ_Ӧ��
	virtual void OnRspStruFundInfoQry(HLApiRspStruFundInfoQry* pRspQryStruFundInfo, CHLRspInfoData* pRspInfo, int nRequestID, char cIsLast) {};


protected:
    virtual ~HLTradeSpi(void) {};
};


class HLTRADEAPI_EXPORT HLTradeApi
{
public:
    ///����һ��HLTradeApi�����Դ��������һ��API���ֻ��һ������ͨ��
    static HLTradeApi* CreateHLTradeApi(void);

    ///��ȡϵͳ�汾��
    ///@return ϵͳ�汾�ű�ʶ�ַ���
    static const char* GetVersion(void);

    virtual void RegisterNetwork(unsigned short nPort, const char* pszFrontAddr) = 0;

    virtual void RegisterSpi(HLTradeSpi* pHLTradeSpi) = 0;

    virtual int Init(void) = 0;

    virtual void Release (void) = 0;	

	///�û���¼����
	virtual int ReqUserLogin(HLApiReqUserLoginData* pReqUserLogin, int nRequestID) = 0;

    ///ί������
    virtual int ReqOrder(HLApiCmdOrder* pReqOrder, int nRequestID) = 0;

    ///��������
    virtual int ReqCancelOrder(HLApiCmdCancelOrder* pReqOrder, int nRequestID) = 0;

    ///����ί������
    virtual int ReqBatchOrder(HLApiCmdBatchOrder* pReqBatchOrder, int nRequestID) = 0;

    ///ETF�嵥����
    virtual int ReqETFList(HLApiReqETFList* pReqETFList, int nRequestID) = 0;

    ///ETF��������
    virtual int ReqETFSubscribe(HLApiCmdETFSubscribe* pReqETFSubscribe, int nRequestID) = 0;

    ///��ί������
    virtual int ReqQryOrder(HLApiCmdOrderQry* pReqQryOrder, int nRequestID) = 0;

    ///�ʽ��ѯ����
    virtual int ReqQryMoneyInfo(HLApiCmdMoneyInfoQry* pReqQryAvailableMoneyInfo, int nRequestID) = 0;

    ///����֤ȯ��ѯ����
    virtual int ReqQryAvlStockInfo(HLApiCmdAvlStocksInfoQry* pReqQryAvailableStockInfo, int nRequestID) = 0;

    ///���ճɽ���ѯ����
    virtual int ReqQryTodayDeal(HLApiCmdTodayDealQry* pReqQryTodayDeal, int nRequestID) = 0;

	///�ּ�����ɷ���Ϣ��ѯ
	virtual int ReqQryStruFundInfo(const HLApiCmdStruFundInfoQry* pReqQryStruFundInfo, int nRequestID) = 0;

	///�޸�ί��״̬����
	virtual int ReqChangeOrderStatus (HLApiRspOrder *pReqUserLogin, int nRequestID) = 0;

protected:
    virtual ~HLTradeApi (void);

};


#endif /*HLTRADEAPI_HHH_*/


