#ifndef _API_ENUM_H_
#define _API_ENUM_H_

enum LogLevel
{
	E_Fatal,
	E_Critical,
	E_Error,
	E_Warning,
	E_Notice,
	E_Information,
	E_Debug,
	E_Trace,
};


//����״̬ö��
enum ConnectionStatus :char
{
	Uninitialized, //δ��ʼ��
	Initialized, //�Ѿ���ʼ��
	Disconnected, //�����Ѿ��Ͽ�
	Connecting, //������
	Connected, //���ӳɹ�
	Authorizing, //��Ȩ��
	Authorized, //��Ȩ�ɹ�
	Logining, //��¼��
	Logined, //��¼�ɹ�
	Confirming, //���㵥ȷ����
	Confirmed, //�Ѿ�ȷ��
	Doing,
	Done, //���
	Unknown, //δ֪
	ConnectFailed,
	InitializedFailed,
	LoginFailed,
	Logout,
};

enum ApiType :char
{
	Nono = 0,
	Trade = 1,
	MarketData = 2,
	Level2 = 4,
	QuoteRequest = 8,
	HistoricalData = 16,
	Instrument = 32,
};

enum DepthLevelType:char
{
	L0,
	L1,
	L5,
	L10,
	FULL,
};

enum ResumeType :char
{
	Restart,
	Resume,
	Quick,
};

enum PutCall :char
{
	Put,
	Call,
};

enum OrderStatus :char
{
	NotSent,
	PendingNew,
	New,
	Rejected,
	PartiallyFilled,
	Filled,
	PendingCancel,
	Cancelled,
	Expired,
	PendingReplace,
	Replaced,
};

enum OrderSide :char
{
	Buy,
	Sell,
	Creation,//�깺
	Redemption,//���
	Merger,//�ϲ�
	Demerger,//���
};

enum OrderType :char
{
	Market,
	Stop,
	Limit,
	StopLimit,
	MarketOnClose,
	TrailingStop,
	TrailingStopLimit,
};

enum TimeInForce :char
{
	ATC,
	Day,
	GTC,
	IOC,
	OPG,
	OC,
	FOK,
	GTX,
	GTD,
	GFS,
};



enum PositionSide :char
{
	Long,
	Short,
};

enum ExecType : char
{
	ExecNew,
	ExecRejected,
	ExecTrade,
	ExecPendingCancel,
	ExecCancelled,
	ExecCancelReject,
	ExecPendingReplace,
	ExecReplace,
	ExecReplaceReject,
};

enum OpenCloseType :char
{
	Open,
	Close,
	CloseToday,
};

enum HedgeFlagType :char
{
	Speculation,
	Arbitrage,
	Hedge,
	MarketMaker,
};

enum InstrumentType :char
{
	Stock,
	Future,
	Option,
	FutureOption,
	Bond,
	FX,
	Index,
	ETF,
	MultiLeg,
	Synthetic,
	LOF,
	Other,
};

enum BarType :char
{
	Time,
	Tick,
	Volume,
	Range,
};

enum DataObjetType : char
{
	Tick_,
	Bid,
	Ask,
	Trade_,
	Quote,
	Bar,
	Level2_,
	Level2Snapshot,
	Level2Update,
};

enum ExchangeType :char
{
	Undefined_,
	SHFE, // ������
	DCE, // ������
	CZCE, // ֣����
	CFFEX, // �н���
	INE, // ��Դ����
	SSE, // �Ͻ���
	SZE, // ���
	NEEQ, // ȫ����С��ҵ�ɷ�ת��ϵͳ,���壬��ʱ��ôд
	HKEx,
};

#endif
