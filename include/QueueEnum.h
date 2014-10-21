#ifndef _QUEUE_ENUM_H_
#define _QUEUE_ENUM_H_

enum RequestType :char
{
	Create = 0, // ����
	Release, // ����
	Register, // ע��ص�
	

	Connect, // ��ʼ/����
	Disconnect, // ֹͣ/�Ͽ�

	Clear, // ����
	Process, // ����

	Subscribe,	// ����
	Unsubscribe, // ȡ������

	SubscribeQuote, // ����ѯ��
	UnsubscribeQuote, // ȡ������ѯ��

	ReqOrderInsert,
	ReqQuoteInsert,
	ReqOrderAction,
	ReqQuoteAction,

	ReqQryOrder,
	ReqQryTrade,

	ReqQryInstrument,
	ReqQryTradingAccount,
	ReqQryInvestorPosition,
	ReqQryInvestorPositionDetail,
	ReqQryInstrumentCommissionRate,
	ReqQryInstrumentMarginRate,
	ReqQrySettlementInfo,
};

enum ResponeType :char
{
	OnConnectionStatus = 64,
	OnRtnDepthMarketData,
	OnRtnError,
	OnRspQryInstrument,
	OnRspQryTradingAccount,
	OnRspQrySettlementInfo,
	OnRtnOrder,
	OnRtnTrade,
	OnRtnQuoteRequest,
};

#endif
