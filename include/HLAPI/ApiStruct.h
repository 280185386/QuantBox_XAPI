#ifndef _API_STRUCT_H_
#define _API_STRUCT_H_

#include "ApiDataType.h"
#include "ApiEnum.h"


struct PositionField
{
	///Ψһ����
	SymbolType			Symbol;
	///��Լ����
	InstrumentIDType	InstrumentID;
	///����������
	ExchangeIDType	ExchangeID;

	PositionSide	Side;
	/// �ֲܳ�
	QtyType Position;
	/// ���ճֲ�
	QtyType TdPosition;
	/// ���ճֲ�
	QtyType YdPosition;
	/// ���óֲ�
	QtyType AvbPosition;
	/// �������ճֲ�
	QtyType AvbYdPosition;
	/// ����������
	QtyType AvbETFPosition;

	InstrumentIDType InstrumentName;
	//QtyType 
	/// �ɱ���
	PriceType HoldPrice;
	/// ��ֵ
	PriceType MktValue;

	HedgeFlagType HedgeFlag;

	int StockAskFrn;                       //��������
	int StockBidFrn;                       //���붳��
	//TThostFtdcPositionDateType ��û����
};

struct QuoteField
{
	InstrumentIDType InstrumentID;
	ExchangeIDType	ExchangeID;

	QtyType AskQty;
	PriceType AskPrice;
	OpenCloseType AskOpenClose;
	HedgeFlagType AskHedgeFlag;

	QtyType BidQty;
	PriceType BidPrice;
	OpenCloseType BidOpenClose;
	HedgeFlagType BidHedgeFlag;

	///ѯ�۱��
	OrderIDType	QuoteReqID;

	OrderIDType ID;
	OrderIDType AskID;
	OrderIDType BidID;
	OrderIDType AskOrderID;
	OrderIDType BidOrderID;
	OrderStatus Status;
	ExecType ExecType;
	ErrorIDType ErrorID;
	ErrorMsgType Text;

	/*
	QtyType LeavesQty;
	QtyType CumQty;
	PriceType AvgPx;
	

	
	
	long DateTime;*/
};

struct EtfSubscribeField
{
	///�û�����
	UserIDType	UserID;
	//�û��ʽ��˺�
	UserAccountNoType UserAccountNo;
	InstrumentIDType InstrumentID;
	QtyType Qty;
	OrderSide Side;
	OrderIDType OrderID;
};

struct OrderField
{
	InstrumentNameType InstrumentName;
	InstrumentIDType InstrumentID;
	ExchangeIDType	ExchangeID;
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
	ErrorMsgType Text;

	OrderIDType ID;
	OrderIDType OrderID;
	int DateTime;


	TimeType Time;
	long OrderRef;
	ShareholderIDType ShareHolderID;
};

struct OrderCancelField
{

	///�û�����
	UserIDType	UserID;
	//�û��ʽ��˺�
	UserAccountNoType UserAccountNo;
	//������ͬ��
	OrderIDType OrderID;
};

struct TradeField
{
	InstrumentIDType InstrumentID;
	ExchangeIDType	ExchangeID;

	OrderSide Side;
	QtyType Qty;
	PriceType Price;
	OpenCloseType OpenClose;
	HedgeFlagType HedgeFlag;
	MoneyType Commission;
	int MatchedDate;                       //�ɽ��򳷵�����
	TimeType Time;
	OrderIDType ID;
	TradeIDType TradeID;

	InstrumentNameType InstrumentName;
	ShareholderIDType ShareHolderID;
	OrderStatus Status;
	QtyType LeavesQty;
	OrderStatus OdStatus;
	OrderIDType RefID;

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

};

// �û���Ϣ
struct UserInfoField
{
	///�û�����
	UserIDType	UserID;
	//�û��ʽ��˺�
	UserAccountNoType UserAccountNo;
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
	DateType	TradingDay;
	// ʱ��
	TimeType	LoginTime;
	// �ỰID
	SessionIDType	SessionID;
	// �������
	ErrorIDType	ErrorID;
	// ������Ϣ
	ErrorMsgType	ErrorMsg;
	// ���������
	ExchangeIDType	ExchangeID;
	// �ɶ����
	UserIDType		SecurityID;
	// ��������
	ReferIDType		ReferID;

};



///�������
struct DepthMarketDataField
{
	///������ʱ��
	DateIntType			TradingDay; // �����գ����ڸ����ݽ��������ֵ�ͬһ�ļ�ʹ�ã�����ûɶ����ô�
	DateIntType			ActionDay;
	TimeIntType			UpdateTime;
	TimeIntType			UpdateMillisec;

	///Ψһ����
	SymbolType			Symbol;
	///��Լ����
	InstrumentIDType	InstrumentID;
	///����������
	ExchangeIDType	ExchangeID;

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
	///Ψһ����
	SymbolType			Symbol;
	///��Լ����
	InstrumentIDType	InstrumentID;
	///����������
	ExchangeIDType	ExchangeID;
	///������
	DateType	TradingDay;
	///ѯ�۱��
	OrderIDType	QuoteID;
	///ѯ��ʱ��
	TimeType	QuoteTime;
};

///��Լ
struct InstrumentField
{
	///Ψһ����
	SymbolType			Symbol;
	///��Լ����
	InstrumentIDType	InstrumentID;
	///����������
	ExchangeIDType	ExchangeID;
	///��Լ����
	InstrumentNameType InstrumentName;

	///��Լ����
	InstrumentType		Type;
	///��Լ��������
	VolumeMultipleType	VolumeMultiple;
	///��С�䶯��λ
	PriceType	PriceTick;
	///������
	DateType	ExpireDate;
	///������Ʒ����
	InstrumentIDType	UnderlyingInstrID;
	///ִ�м�
	PriceType	StrikePrice;
	///��Ȩ����
	PutCall	OptionsType;
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
	DateType	TradingDay;
	///��Ϣ����
	ContentType	Content;
};

struct HistoricalDataRequestField
{
	///Ψһ����
	SymbolType			Symbol;
	///��Լ����
	InstrumentIDType	InstrumentID;
	///����������
	ExchangeIDType	ExchangeID;

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
};

//ETF�嵥������Ӧ
struct ETFListField
{
	//ETF����
	InstrumentIDType	ETFInstrumentID;
	//ETF����
	InstrumentNameType ETFInstrumentName;
	///����������
	ExchangeIDType	ExchangeID; //һ�����װ��
	double dMaxCashRatio;                   //�ֽ������������
	int nCreationRedemption;                //�������깺���״̬(1,0)
	int nCreationRedemptionUnit;            //��С�깺��ص�λ
	PriceType dEstimateCashComponent;          //T��Ԥ���ֽ����
	int nTradingDay;                        //T������
	InstrumentIDType	InstrumentID;
	PriceType dCashComponent;                  //T-1���ֽ���(��λ��Ԫ)
	double dNAVperCU;                       //T-1����С�깺����ص�λ�ʲ���ֵ(��λ��Ԫ)
	int nItemDataSize;                      //�ɷݹ�����
	int  size;

};

struct ETFListDataField
{
	InstrumentIDType	InstrumentID;  //��Ʊ����
	InstrumentNameType InstrumentName;//��Ʊ����
	ExchangeIDType	ExchangeID;        //����������
	int nNum;                                   //��Ʊ����
	int nFlag;                                  //�ֽ������־
	double dRatio;                              //��۱���
	double dReplaceAmount;                      //������
};


//ETF��������
struct ETFSubscribeInfo
{
	int eSubscribeFlag;                    //�����־
	InstrumentIDType	InstrumentID;                 //ETF����
	int nSubscribeQty;                                  //����ݶ�
	OrderIDType OrderID;                    //��ͬ���
};

//�ּ�����
struct RspStruFundInfoQry
{
	InstrumentIDType	FundInstrumentID;
	InstrumentNameType FundInstrumentName;
	InstrumentIDType	FundAInstrumentID;
	InstrumentNameType FundAInstrumentName;
	InstrumentIDType	FundBInstrumentID;
	InstrumentNameType FundBInstrumentName;
	int  nFundAShare;						//�ּ�A����(0,100), Ĭ��:50
	int	 nFundBShare;						//�ּ�B����(0,100), Ĭ��:50
};
///�������N��
struct DepthMarketDataNField
{
	///ռ�����ֽڴ�С
	SizeType			Size;
	///������ʱ��
	DateIntType			TradingDay; // �����գ����ڸ����ݽ��������ֵ�ͬһ�ļ�ʹ�ã�����ûɶ����ô�
	DateIntType			ActionDay;
	TimeIntType			UpdateTime;
	TimeIntType			UpdateMillisec;

	///����������
	ExchangeType	Exchange;
	///Ψһ����
	SymbolType			Symbol;
	///��Լ����
	InstrumentIDType	InstrumentID;

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
	///�򵵸���
	SizeType BidCount;
	char status;
};

struct DepthField
{
	PriceType	Price;
	VolumeType	Size;
	VolumeType	Count;
};
#endif
