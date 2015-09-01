#ifndef HLUSERAPIDEFINE_HHH_
#define HLUSERAPIDEFINE_HHH_

//errcode
const int API_ERROR_OK = 0;             //OK
const int API_ERROR_DISCONNECTED = -1;  //δ����
const int API_ERROR_NORESULT = 0xD000;  //û�в�ѯ���

#define API_PACKET_FIRST    0x01		//�װ����
#define API_PACKET_LAST     0x02		//β�����

#define API_ERRORMSG_LEN    256
#define API_APP_LEN         16
#define API_CLIENT_LEN      16
#define API_ORDERID_LEN     11
#define API_ACCOUNT_LEN     16
#define API_PSW_LEN         16
#define API_IPADDR          16
#define API_CLIENTINFO      32
#define API_DATE_LEN        9   //���ڽṹ yyyymmdd
#define API_TIME_LEN        9   //ʱ��ṹ hh:mm:ss
#define API_MARKET_LEN      4
#define API_SYMBOL_LEN      8
#define API_SYMBOLNAME_LEN  16
#define API_SAVE_LEN        32
#define API_PREFIX_LEN      4
#define API_MATCHED_SN_LEN  17  //�ɽ����
#define API_STOCK_PBU_LEN   9   //���׵�Ԫ
#define API_TRADE_COUNT_LEN 11  //֤ȯ�ʻ�
#define API_QUERY_POS_LEN   33  //��Ϊ��
#define API_ORD_TIME_LEN    33  //ί��ʱ��
#define API_ORDER_ID_LEN    11  //��ͬ���


#define API_MAX_BATCH_ORDER_COUNT           15  //����ί���������
#define API_MAX_DAY_ORDER_RECORDSET_COUNT   100 //����ί�в�ѯ���ؼ�¼�������
#define API_MAX_AVL_STK_COUNTS              100 //��ѯ���ùɷ�ʱ��ÿ�η������ɷ����� 

//������
#define API_EXCH_SZ "SZ"    //���� 
#define API_EXCH_SH "SH"    //�Ϻ� 
#define API_EXCH_CF "CF"    //�й������ڻ������� 
#define API_EXCH_SP "SP"    //��Ʒ�ڻ� 

typedef char API_MARKETFLAG[API_MARKET_LEN];

//����־
typedef enum
{
	SectorSHA   = '1',      //�Ϻ�A��
	SectorSZA   = '2',      //����A��
	SectorSHB   = '3',      //�Ϻ�B��
	SectorSZB   = '4',      //����B��
	SectorSBA   = '5',      //����A
	SectorSBB   = '6',      //����B
} SECTORSYMBOL;

//�ɽ�״̬����
typedef enum
{
	MatchStatusDone     = 0,  //������������¼
	MatchStatusCancel   = 1,  //����������¼
} MATCHSTATUSSET;

//֤ȯҵ��
typedef enum
{
	ETFSubcribe     = 1,        //�깺
	ETFRedeem       = 2,        //���
	StockBuy        = 100,      //֤ȯ����
	StockSel        = 101,      //֤ȯ����

	Fund_Creation	= 102,		//�����깺
	Fund_Redemption	= 103,		//�������
	Fund_Merger		= 104,		//����ϲ�
	Fund_Demerger	= 105,		//����ֲ�

} STOCKBIZ;

//���۷�ʽ
typedef enum
{
	StockLimit = 100,   //�����걨-�޼�ί��(֧�����)
	//StockCancel = 101,  //�����걨
	StockAction1 = 120, //�����걨-���ųɽ�ת��(֧�����)
	StockAction2 = 121, //�����걨-���ųɽ�ʣ��(֧������)
	StockAction3 = 122, //�����걨-ȫ�ɽ�����(֧������)
	StockAction4 = 123, //�����걨-�������ż۸�(֧������)
	StockAction5 = 124, //�����걨-�������ż۸�(֧������)
	StockAction6 = 125, //�����걨-��ʱ�ɽ�ʣ��(֧�ֻ���)
} STOCKBIZACTION;

//ί�е�����
typedef enum
{
	OrderLimited    = 0,    //�޼�
	OrderAutoOffer  = 1,    //�Զ��̿�
	OrderAskPrice1  = 2,    //��һ��
	OrderBidPrice1  = 3,    //��һ��
} ORDERPRICETYPE;

//ί��״̬
typedef enum
{
	OrderNotSend        = 'o',  //δ��
	OrderSending        = 's',  //����
	OrderNewComer       = 'n',  //����
	OrderSended         = 'a',  //�ѱ�
	OrderToBeDel        = '3',  //�ѱ�����
	OrderPartCToBeDel   = '4',  //���ɴ���
	OrderPartDeleted    = 'b',  //���ɲ���
	OrderToBeDelete     = 'f',  //���⳷��
	OrderPartCDeleted   = 'p',  //����
	OrderCompleted      = 'c',  //ȫ��
	OrderUseless        = 'e',  //��
	OrderBeDeleted      = 'd',  //ȫ��
	OrderConfirmed      = 'D',  //��ȷ��
	OrderDenied         = 'E',  //�ѷ��
	OrderCanceling      = 'Z',  //���ڳ���
	LogoicOrderAbandoned= 'L',  //�߼�������
} ORDERSTATUS;

//���ͱ�־
typedef enum
{
	MatchPushDeal           = 0,    //�ɽ�����
	MatchPushCancel         = 1,    //��������
	MatchPushOrderFailed    = 2,    //ί��ʧ������
	MatchPushCancelFailed   = 4,    //����ʧ������
} MATCHPUSHFLAG;

//ί����Ч��־
typedef enum
{
	OrderFlagInvalid    = 0,    //��Ч
	OrderFlagValid      = 1,    //��Ч
} ORDERVALIDFLAG;

//������־
typedef enum
{
	FlagNormal      = 'F',  //����
	FlagCanceled    = 'T',  //����
} ISWITHDRAW;

//����
typedef enum
{
	CurrencyRMB    = 1,    //�����
	CurrencyUSD    = 2,    //��Ԫ
	CurrencyHK     = 3,    //�۱�
} CURRENCYTYPE;

//�ʽ�״̬
typedef enum
{
	FundStatusNormal    = 0,    //����
	FundStatusCancel    = 9,    //����
} FUNDSTATUS;

//ETF�����־
typedef enum
{
	ETFSubcribeFlag     = 1,    //�깺
	ETFRedeemFlag       = 2,    //���
} ETFSUBSCRIBEFLAG;


//ί������
typedef struct
{
	char chSecurityCode[API_SYMBOL_LEN];    //֤ȯ����
	double dOrderPrice;                     //ί�м�
	ORDERPRICETYPE eOrderPriceType;         //ί�м۷�ʽ
	int nOrderQty;                          //ί�й���
	STOCKBIZ eStockBiz;                     //֤ȯҵ��
	STOCKBIZACTION eStockBizAction;         //���۷�ʽ
} ORDERDATA;


//֤ȯ����
struct HLApiSecurityCode
{
	int  nType;                 //֤ȯ����
	char chSecurityCode[API_SYMBOL_LEN];    //֤ȯ����
	char chSymbol[API_SYMBOLNAME_LEN];     //֤ȯ����
};

//ETF��Ʊ����
struct ETFItemData
{
	char chSecurityCode[API_SYMBOL_LEN];        //��Ʊ����
	char chSymbol[API_SYMBOLNAME_LEN];          //��Ʊ����
	SECTORSYMBOL eSectorSymbol;                 //����־
	int nNum;                                   //��Ʊ����
	int nFlag;                                  //�ֽ������־
	double dRatio;                              //��۱���
	double dReplaceAmount;                      //������
};

///��Ӧ��Ϣ
struct CHLRspInfoData
{
	int  ErrorID;
	char ErrorMsg[API_ERRORMSG_LEN];
};

//�û���¼����
struct HLApiReqUserLoginData
{
	char chApplication[API_APP_LEN];    //Ӧ������
	char chClientID[API_CLIENT_LEN];    //�ͻ���
	char chPassword[API_PSW_LEN];       //����
	char chDynPassword[API_PSW_LEN];    //��̬����
	char chCurIP[API_IPADDR];           //IP
	int  nUserType;                     //�ͻ�����
	char chClientInfo[API_CLIENTINFO];  //�ͻ�����Ϣ
};

//�û���¼��Ӧ
struct HLApiRspUserLoginData
{
	char chTradingDay[API_DATE_LEN];    //������
	char chLoginTime[API_TIME_LEN];     //��¼ʱ��
	char chClientID[API_CLIENT_LEN];    //�ͻ���
	int  nSessionID;                    //session id
	char chSvrInfo[API_CLIENTINFO];     //�������Ϣ
	int  nMarkets;                      //�г�����
	API_MARKETFLAG* chMarketFlag;       //�г���־(SZ;SH;HK;CF)
	int*  nDynDate;                     //��̬��������
};

//�г���������
struct HLApiReqCodeTable
{
	char    chMarket[API_MARKET_LEN];   //�г���־(SZ;SH;HK;CF)
};

//�г���������Ӧ��
struct HLApiRspCodeTable
{
	API_MARKETFLAG chMarketFlag;            //�г���־(SZ;SH;HK;CF)
	int  nDate;                             //��������
	int  nCount;                            //��������(-1:δ��Ȩ)
	HLApiSecurityCode* pSecurityCode;       //����
};

//����ETF�嵥����
struct HLApiReqETFList
{
	char    chSecurityCode[API_SYMBOL_LEN]; //֤ȯ����
};

//ETF�嵥������Ӧ
struct HLApiRspETFList
{
	char chSecurityCode[API_SYMBOL_LEN];    //ETF����
	char chSymbol[API_SYMBOLNAME_LEN];      //ETF����
	char szFundid[API_SYMBOL_LEN];          //һ���г�����
	SECTORSYMBOL eSectorSymbol;             //����־
	int nCreationRedemptionUnit;            //��С�깺��ص�λ
	double dMaxCashRatio;                   //�ֽ������������
	int nCreationRedemption;                //�������깺���״̬(1,0)
	double dEstimateCashComponent;          //T��Ԥ���ֽ����
	int nTradingDay;                        //T������
	double dCashComponent;                  //T-1���ֽ���(��λ��Ԫ)
	double dNAVperCU;                       //T-1����С�깺����ص�λ�ʲ���ֵ(��λ��Ԫ)
	ETFItemData* pETFItemData;              //�ɷݹ�����ָ��
	int nItemDataSize;                      //�ɷݹ�����
};

//���鶩������
struct HLApiReqMarketData
{
	int     nType;                                  //��������(0���� 1�˶�)
	char    chMarket[API_MARKET_LEN];               //�г���־(SZ;SH;HK;CF)
	char    chSecurityCode[API_SYMBOL_LEN];         //��Ʊ����(����Ϊȫ�г�����)
};

//���鶩������Ӧ��
struct HLApiRspMarketData
{
	int     nResult;                                //������(0�ɹ� 1ʧ��)
	int     nType;                                  //��������(0���� 1�˶�)
	char    chMarket[API_MARKET_LEN];               //�г���־(SZ;SH;HK;CF)
	char    chSecurityCode[API_SYMBOL_LEN];         //��Ʊ����(����Ϊȫ�г�����)
};

//������Ϣ
struct HLApiMarketData
{
	char        chMarket[API_MARKET_LEN];   //�г���־(SZ;SH;HK;CF)
	char        chSymbol[API_SYMBOL_LEN];   //��Ʊ����
	int         nTime;                      //ʱ��(HHMMSSmmm)
	int         nStatus;                    //״̬
	double      dPreClose;                  //ǰ���̼�
	double      dOpen;                      //���̼�
	double      dHigh;                      //��߼�
	double      dLow;                       //��ͼ�
	double      dMatch;                     //���¼�
	double      dAskPrice[10];              //������
	unsigned int nAskVol[10];               //������
	double      dBidPrice[10];				//�����
	unsigned int nBidVol[10];				//������
	unsigned int nNumTrades;				//�ɽ�����
	long long   iVolume;					//�ɽ�����
	long long   iTurnover;					//�ɽ��ܽ��
	long long   nTotalBidVol;				//ί����������
	long long   nTotalAskVol;				//ί����������
	double      dHighLimited;				//��ͣ��
	double      dLowLimited;				//��ͣ��
};

//�û�ί������
struct HLApiCmdOrder
{
	char chClientID[API_CLIENT_LEN];        //�ͻ���
	char chAccountNO[API_ACCOUNT_LEN];      //�ʽ��˻�
	//int nOrderBsn;                          //ί�����ţ�0��ϵͳ���ɣ�
	ORDERDATA stOrderData;                  //ί������
	int nSaveInt1;                          //�ͻ������ֶ�1
	int nSaveInt2;                          //�ͻ������ֶ�2
	char chSaveString[API_SAVE_LEN];        //�ͻ������ֶ�3
};

//�û�ί������Ӧ��
struct HLApiRspOrder
{
	char chClientID[API_CLIENT_LEN];        //�ͻ���
	char chAccountNO[API_ACCOUNT_LEN];      //�ʽ��˻�
	char chSecurityCode[API_SYMBOL_LEN];    //֤ȯ����
	char chSecurityName[API_SYMBOLNAME_LEN];//֤ȯ����
	char chOrderID[API_ORDER_ID_LEN];       //��ͬ���
	ORDERSTATUS eOrderStatus;               //ί��״̬
	STOCKBIZ eStockBiz;                     //֤ȯҵ��
	double dOrderPrice;                     //ί�м۸�
	int nOrderQty;                          //ί������
	double dMatchedPrice;                   //�ѳɾ���
	int nMatchedQty;                        //�ѳ�����
	char chOrderTime[API_ORD_TIME_LEN];     //ί��ʱ��
	int nOrderDay;                          //ί������
	int nSaveInt1;                          //�ͻ������ֶ�1
	int nSaveInt2;                          //�ͻ������ֶ�2
	char chSaveString[API_SAVE_LEN];        //�ͻ������ֶ�3
};

//�û���������
struct HLApiCmdCancelOrder
{
	char chOrderID[API_ORDERID_LEN];        //��ͬ���
	char chClientID[API_CLIENT_LEN];        //�ͻ���
	char chAccountNO[API_ACCOUNT_LEN];      //�ʽ��˻�
};

//�û���������Ӧ��
typedef struct HLApiCmdCancelOrder HLApiRspCancelOrder;

//�û�����ί������
struct HLApiCmdBatchOrder
{
	char chClientID[API_CLIENT_LEN];                    //�ͻ���
	char chAccountNO[API_ACCOUNT_LEN];                  //�ʽ��˻�
	int nOrderCount;                                    //ί������������API_MAX_BATCH_ORDER_COUNT
	ORDERDATA stOrderData[API_MAX_BATCH_ORDER_COUNT];   //ί������
	int nSaveInt1;                                      //�ͻ������ֶ�1
	int nSaveInt2;                                      //�ͻ������ֶ�2
	char chSaveString[API_SAVE_LEN];                    //�ͻ������ֶ�3
};

//ETF��������
struct HLApiCmdETFSubscribe
{
	char chClientID[API_CLIENT_LEN];                    //�ͻ���
	char chAccountNO[API_ACCOUNT_LEN];                  //�ʽ��˻�
	ETFSUBSCRIBEFLAG eSubscribeFlag;                    //�����־
	char chSecurityCode[API_SYMBOL_LEN];                //ETF����
	int nSubscribeQty;                                  //����ݶ�
};

//ETF��������Ӧ��
struct HLApiRspETFSubscribe
{
	char chClientID[API_CLIENT_LEN];                    //�ͻ���
	char chAccountNO[API_ACCOUNT_LEN];                  //�ʽ��˻�
	ETFSUBSCRIBEFLAG eSubscribeFlag;                    //�����־
	char chSecurityCode[API_SYMBOL_LEN];                //ETF����
	int nSubscribeQty;                                  //����ݶ�
	char chOrderID[API_ORDERID_LEN];                    //��ͬ���
};

//�ɽ����������ϵ�֪ͨ����
struct HLApiRtnMatchInfo
{
	char chMatchedSN[API_MATCHED_SN_LEN];   //�ɽ����
	SECTORSYMBOL eSectorSymbol;             //����־
	char chSecurityCode[API_SYMBOL_LEN];    //֤ȯ����
	char chSecurityName[API_SYMBOLNAME_LEN];//֤ȯ����
	char chClientID[API_CLIENT_LEN];        //�ͻ���
	char chAccountNO[API_ACCOUNT_LEN];      //�ʽ��˻�
	char chOrderID[API_ORDER_ID_LEN];       //��ͬ���
	int nMatchedQty;                        //�ɽ��򳷵�����
	double dMatchedPrice;                   //�ɽ��򳷵�����
	int nMatchedDate;                       //�ɽ��򳷵�����
	char chMatchedTime[API_ORD_TIME_LEN];   //�ɽ��򳷵�ʱ��
	MATCHPUSHFLAG eMatchPushFlag;           //�������ͱ�־
	STOCKBIZ eStockBiz;                     //֤ȯҵ��(�ɽ���ѯʱ��Ч)
};

typedef struct HLApiRspOrder HLApiRtnOrderInfo;

typedef struct HLApiRspAvlStocksInfoQry HLApiRtnAvlStockInfo;

typedef struct HLApiRspMoneyInfoQry HLApiRtnMoneyInfo;

//ί�в�ѯ����
struct HLApiCmdOrderQry
{
	char chClientID[API_CLIENT_LEN];        //�ͻ���
	char chAccountNO[API_ACCOUNT_LEN];      //�ʽ��˻�
	char chBeginDate[API_DATE_LEN];         //��ʼ����(��Ϊ��ѯ����)
	char chEndDate[API_DATE_LEN];           //��ֹ����(��Ϊ��ѯ����)
	char chOrderID[API_ORDERID_LEN];        //��ͬ���(��Ϊ��ѯ����)
	char chSecurityCode[API_SYMBOL_LEN];    //֤ȯ����(��Ϊ��ѯ����)
	STOCKBIZ eStockBiz;                     //֤ȯҵ��(0Ϊ��ѯ����)
	double dOrderPrice;                     //ί�м�(0Ϊ��ѯ����)
	int nOrderQty;                          //ί�й���(0Ϊ��ѯ����)
};

//ί�в�ѯ����Ӧ��
typedef struct HLApiRspOrder HLApiRspOrderQry;

//�����ʽ��ѯ
struct HLApiCmdMoneyInfoQry
{
	char chClientID[API_CLIENT_LEN];        //�ͻ���
	char chAccountNO[API_ACCOUNT_LEN];      //�ʽ��˻�
	CURRENCYTYPE eCurrencyType;             //����
};

//�����ʽ��ѯӦ��
struct HLApiRspMoneyInfoQry
{
	char chClientID[API_CLIENT_LEN];        //�ͻ���
	char chAccountNO[API_ACCOUNT_LEN];      //�ʽ��˻�
	CURRENCYTYPE eCurrencyType;             //����
	//unsigned short nIntOrg;                 //�ڲ�����
	//double dMarketValue;                    //�ʲ���ֵ
	//double dFundValue;                      //�ʽ��ʲ�
	//double dStkValue;                       //��ֵ
	//double dFundLoan;                       //�����ܽ��
	//double dFundPreBln;                     //�ʽ��������
	double dFundBln;                        //�ʽ����
	double dFundAvl;                        //�����ʽ�
	double dFundWithDraw;                   //��ȡ�ʽ�
	//double dFundUnFrz;                      //�ʽ�ⶳ���
	//double dFundTradeFrz;                   //�ʽ��׶�����
	//double dFundTradeUnFrz;                 //�ʽ��׽ⶳ���
	//double dFundTradeInTransit;             //�ʽ�����;���
	//double FundTradeInBln;                  //�ʽ���������
	//FUNDSTATUS nFundStatus;                 //�ʽ�״̬(����������)
};

//���ùɷݲ�ѯ
struct HLApiCmdAvlStocksInfoQry
{
	char chClientID[API_CLIENT_LEN];        //�ͻ���
	char chAccountNO[API_ACCOUNT_LEN];      //�ʽ��˻�
	char chSecurityCode[API_SYMBOL_LEN];    //֤ȯ����(��Ϊ��ѯ����)
};

//���ùɷݲ�ѯӦ��
struct HLApiRspAvlStocksInfoQry
{
	char chClientID[API_CLIENT_LEN];        //�ͻ���
	char chAccountNO[API_ACCOUNT_LEN];      //�ʽ��˻�
	SECTORSYMBOL eSectorSymbol;             //����־
	char chSecurityCode[API_SYMBOL_LEN];    //֤ȯ����
	char chSecurityName[API_SYMBOLNAME_LEN];//֤ȯ����
	int nStockBln;                          //֤ȯ�������ճɽ�����ӵ������
	int nStockAvlValue;                     //�������
	int nStockPreBln;                       //���տ��
	double dStkValue;                       //��ֵ
	double dProPrice;                       //�ɱ���
	int nStockSR;                           //����������
	int nStockAskFrn;                       //��������
	int nStockBidFrn;                       //���붳��
};

//���ճɽ���ѯ
struct HLApiCmdTodayDealQry
{
	char chClientID[API_CLIENT_LEN];        //�ͻ���
	char chAccountNO[API_ACCOUNT_LEN];      //�ʽ��˻�
	char chSecurityCode[API_SYMBOL_LEN];    //֤ȯ����
	MATCHSTATUSSET eMatchStatus;            //�ɽ�״̬����
};

//���ճɽ���ѯӦ��
typedef struct HLApiRtnMatchInfo HLApiRspTodayDealQry;


//�ּ�����ɷ���Ϣ��ѯ
struct HLApiCmdStruFundInfoQry
{
	char chFundCode[API_SYMBOL_LEN];	//ĸ�������,�մ�""���ѯ�����嵥
};


//�ּ�����ɷ���Ϣ��ѯ_Ӧ��
struct HLApiRspStruFundInfoQry
{
	char chFundCode[API_SYMBOL_LEN];		//ĸ�������
	char chFundName[API_SYMBOLNAME_LEN];	//ĸ��������
	char chFundACode[API_SYMBOL_LEN];		//�ּ�A����
	char chFundAName[API_SYMBOLNAME_LEN];	//�ּ�A����
	char chFundBCode[API_SYMBOL_LEN];		//�ּ�B����
	char chFundBName[API_SYMBOLNAME_LEN];	//�ּ�B����
	int  nFundAShare;						//�ּ�A����(0,100), Ĭ��:50
	int	 nFundBShare;						//�ּ�B����(0,100), Ĭ��:50
};



#endif /*HLUSERAPIDEFINE_HHH_*/



