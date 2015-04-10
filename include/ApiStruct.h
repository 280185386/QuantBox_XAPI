#ifndef _API_STRUCT_H_
#define _API_STRUCT_H_

#include "ApiDataType.h"
#include "ApiEnum.h"


struct PositionField
{
	PositionSide	Side;
	QtyType Position;
	QtyType TdPosition;
	QtyType YdPosition;
	HedgeFlagType HedgeFlag;
	//TThostFtdcPositionDateType ��û����
	///Ψһ����
	SymbolType			Symbol;
	///��Լ����
	InstrumentIDType	InstrumentID;
	///����������
	ExchangeIDType	ExchangeID;
};

struct QuoteField
{
	QtyType AskQty;
	PriceType AskPrice;
	OpenCloseType AskOpenClose;
	HedgeFlagType AskHedgeFlag;

	QtyType BidQty;
	PriceType BidPrice;
	OpenCloseType BidOpenClose;
	HedgeFlagType BidHedgeFlag;

	OrderStatus Status;
	ExecType ExecType;

	ErrorIDType ErrorID;

	InstrumentIDType InstrumentID;
	ExchangeIDType	ExchangeID;

	///ѯ�۱��
	OrderIDType	QuoteReqID;

	OrderIDType ID;
	OrderIDType AskID;
	OrderIDType BidID;
	OrderIDType AskOrderID;
	OrderIDType BidOrderID;

	ErrorMsgType Text;
};

struct OrderField
{

	OrderType Type;
	OrderSide Side;
	QtyType Qty;
	PriceType Price;
	OpenCloseType OpenClose;
	HedgeFlagType HedgeFlag;

	PriceType StopPx;
	TimeInForce TimeInForce;

	OrderStatus Status;
	ExecType ExecType;
	QtyType LeavesQty;
	QtyType CumQty;
	PriceType AvgPx;
	ErrorIDType ErrorID;
	TimeIntType Time;
	InstrumentIDType InstrumentID;
	ExchangeIDType	ExchangeID;
	ErrorMsgType Text;

	OrderIDType ID;
	OrderIDType OrderID;
	UserIDType ClientID;
	AccountIDType Account;
};

struct TradeField
{
	OrderSide Side;
	QtyType Qty;
	PriceType Price;
	OpenCloseType OpenClose;
	HedgeFlagType HedgeFlag;
	MoneyType Commission;
	TimeIntType Time;
	InstrumentIDType InstrumentID;
	ExchangeIDType	ExchangeID;

	
	OrderIDType ID;
	TradeIDType TradeID;
};

struct ServerInfoField
{
	bool IsUsingUdp;
	bool IsMulticast;
	int	TopicId;
	int Port;
	ResumeType	MarketDataTopicResumeType;
	ResumeType	PrivateTopicResumeType;
	ResumeType	PublicTopicResumeType;
	ResumeType	UserTopicResumeType;
	BrokerIDType	BrokerID;
	ProductInfoType	UserProductInfo;
	AuthCodeType	AuthCode;
	AddressType	Address;
	ExtendInformationType	ExtendInformation;
};

struct ConfigInfoField
{
	bool DirectOutput;
};

// �û���Ϣ
struct UserInfoField
{
	///�û�����
	UserIDType	UserID;
	///����
	PasswordType	Password;
};


// ������Ϣ
struct ErrorField
{
	// �������
	ErrorIDType	ErrorID;
	// ������Ϣ
	ErrorMsgType	ErrorMsg;
};


// ��¼�ر�
struct RspUserLoginField
{
	///������
	DateIntType	TradingDay;
	// ʱ��
	TimeIntType	LoginTime;
	// �������
	ErrorIDType	ErrorID;
	// �ỰID
	SessionIDType	SessionID;
	// ������Ϣ
	ErrorMsgType	ErrorMsg;
	///Ͷ��������
	PartyNameType	InvestorName;
};



///�������
struct DepthMarketDataField
{
	///������ʱ��
	DateIntType			TradingDay; // �����գ����ڸ����ݽ��������ֵ�ͬһ�ļ�ʹ�ã�����ûɶ����ô�
	DateIntType			ActionDay;
	TimeIntType			UpdateTime;
	TimeIntType			UpdateMillisec;

	///���¼�
	PriceType	LastPrice;
	///����
	LargeVolumeType	Volume;
	///�ɽ����
	MoneyType	Turnover;
	///�ֲ���
	LargeVolumeType	OpenInterest;
	///���վ���
	PriceType	AveragePrice;


	///����
	PriceType	OpenPrice;
	///��߼�
	PriceType	HighestPrice;
	///��ͼ�
	PriceType	LowestPrice;
	///������
	PriceType	ClosePrice;
	///���ν����
	PriceType	SettlementPrice;

	///��ͣ���
	PriceType	UpperLimitPrice;
	///��ͣ���
	PriceType	LowerLimitPrice;
	///������
	PriceType	PreClosePrice;
	///�ϴν����
	PriceType	PreSettlementPrice;
	///��ֲ���
	LargeVolumeType	PreOpenInterest;


	///�����һ
	PriceType	BidPrice1;
	///������һ
	VolumeType	BidVolume1;
	///������һ
	PriceType	AskPrice1;
	///������һ
	VolumeType	AskVolume1;
	///����۶�
	PriceType	BidPrice2;
	///��������
	VolumeType	BidVolume2;
	///�����۶�
	PriceType	AskPrice2;
	///��������
	VolumeType	AskVolume2;
	///�������
	PriceType	BidPrice3;
	///��������
	VolumeType	BidVolume3;
	///��������
	PriceType	AskPrice3;
	///��������
	VolumeType	AskVolume3;
	///�������
	PriceType	BidPrice4;
	///��������
	VolumeType	BidVolume4;
	///��������
	PriceType	AskPrice4;
	///��������
	VolumeType	AskVolume4;
	///�������
	PriceType	BidPrice5;
	///��������
	VolumeType	BidVolume5;
	///��������
	PriceType	AskPrice5;
	///��������
	VolumeType	AskVolume5;

	///Ψһ����
	SymbolType			Symbol;
	///��Լ����
	InstrumentIDType	InstrumentID;
	///����������
	ExchangeIDType	ExchangeID;
};

///Tick����
struct TickField
{
	///������ʱ��
	DateIntType			Date;
	TimeIntType			Time;
	TimeIntType			Millisecond;

	PriceType	LastPrice;
	///����
	LargeVolumeType	Volume;
	///�ֲ���
	LargeVolumeType	OpenInterest;
	PriceType	BidPrice1;
	PriceType	AskPrice1;
	VolumeType	BidSize1;
	VolumeType	AskSize1;
};


///Bar����
struct BarField
{
	///������ʱ��
	DateIntType			Date;
	TimeIntType			Time;

	///��
	PriceType	Open;
	///��
	PriceType	High;
	///��
	PriceType	Low;
	///��
	PriceType	Close;
	///����
	LargeVolumeType	Volume;
	///�ֲ���
	LargeVolumeType	OpenInterest;
	///�ɽ����
	MoneyType	Turnover;
};

///���������̵�ѯ������
struct QuoteRequestField
{
	///������
	DateIntType	TradingDay;
	///ѯ��ʱ��
	TimeIntType	QuoteTime;
	///Ψһ����
	SymbolType			Symbol;
	///��Լ����
	InstrumentIDType	InstrumentID;
	///����������
	ExchangeIDType	ExchangeID;
	///ѯ�۱��
	OrderIDType	QuoteID;
};

///��Լ
struct InstrumentField
{
	///��Լ����
	InstrumentType		Type;
	///��Լ��������
	VolumeMultipleType	VolumeMultiple;
	///��С�䶯��λ
	PriceType	PriceTick;
	///������
	DateIntType	ExpireDate;

	///ִ�м�
	PriceType	StrikePrice;
	///��Ȩ����
	PutCall	OptionsType;

	///Ψһ����
	SymbolType			Symbol;
	///��Լ����
	InstrumentIDType	InstrumentID;
	///����������
	ExchangeIDType	ExchangeID;
	///��Լ����
	InstrumentNameType InstrumentName;
	///������Ʒ����
	InstrumentIDType	UnderlyingInstrID;
};

///�˺�
struct AccountField
{
	///�ϴν���׼����
	MoneyType	PreBalance;
	///��ǰ��֤���ܶ�
	MoneyType	CurrMargin;
	///ƽ��ӯ��
	MoneyType	CloseProfit;
	///�ֲ�ӯ��
	MoneyType	PositionProfit;
	///�ڻ�����׼����
	MoneyType	Balance;
	///�����ʽ�
	MoneyType	Available;

	///�����
	MoneyType	Deposit;
	///������
	MoneyType	Withdraw;

	///����Ĺ�����
	MoneyType	FrozenTransferFee;
	///�����ӡ��˰
	MoneyType	FrozenStampTax;
	///�����������
	MoneyType	FrozenCommission;
	///������ʽ�
	MoneyType	FrozenCash;

	///������
	MoneyType	TransferFee;
	///ӡ��˰
	MoneyType	StampTax;
	///������
	MoneyType	Commission;
	///�ʽ���
	MoneyType	CashIn;

};

///�˺�
struct SettlementInfoField
{
	///������
	DateIntType	TradingDay;
	///��Ϣ����
	ContentType	Content;
};

///Ͷ����
struct InvestorField
{
	IdCardType		IdentifiedCardType;
	///�û�����
	UserIDType	InvestorID;

	BrokerIDType	BrokerID;

	///֤������
	IdentifiedCardNoType	IdentifiedCardNo;
	///Ͷ��������
	PartyNameType	InvestorName;

};

struct HistoricalDataRequestField
{
	int Date1;
	int Date2;
	int Time1;
	int Time2;

	DataObjetType DataType;
	BarType BarType;
	long BarSize;

	int RequestId;
	int CurrentDate;
	int lRequest;

	///Ψһ����
	SymbolType			Symbol;
	///��Լ����
	InstrumentIDType	InstrumentID;
	///����������
	ExchangeIDType	ExchangeID;
};
#endif
