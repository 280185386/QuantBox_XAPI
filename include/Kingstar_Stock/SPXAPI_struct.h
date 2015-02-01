#ifndef __SPXAPI_STRUCT_H__
#define __SPXAPI_STRUCT_H__

#include "SPXAPI_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
#define __PACKED__
#pragma pack(push, 1)
#else
#ifdef __GNUC__
#define __PACKED__    __attribute__ ((packed))
#else
#ifdef HP_UX
#define __PACKED__
#pragma pack 1
#else
#define __PACKED__
#pragma options align = packed
#endif
#endif
#endif

#ifndef WIN32
#if defined(__i386__) && ! defined(__x86_64__)
#ifndef __stdcall
#define __stdcall __attribute__((stdcall))
#endif
#elif defined(__x86_64__)
#ifndef __stdcall
#define __stdcall
#endif
#endif
#endif

/** \defgroup Group13 1.3 ö�ٶ��� */
/** @{ */

/**
 * @brief ��־����
 * @details API��¼��־�ļ�������Ϊĳһ����󣬸ü��𼰸����ؼ������־�����¼����־�ļ���
 */
enum LOG_LEVEL
{
    LL_DEBUG           = 0,		///< ���Լ���
    LL_INFO,					///< ��Ϣ����(ȱʡѡ��)
    LL_WARNING,					///< ���漶��
    LL_ERROR,					///< ���󼶱�
    LL_FATAL,					///< ���ش��󼶱�
};

/**
 * @brief ETXҵ���ܺ�ö��
 * @details VIP��̨ETX����ҵ���ܺ�
 */
enum ETX_APP_FUNCNO
{
	ETX_16203          = 16203,	///< 16203 - �ɽ������ϵ�
	ETX_16204,					///< 16204 - �����ķϵ�
};

/**
 * @brief API��������ö��
 * @details API��������
 */
enum PARAM_TYPE
{
	MAINSERVER_IP       = 0,	///< ������IP
	MAINSERVER_PORT,			///< �����ض˿�
	BACKSERVER_IP,				///< ������IP
	BACKSERVER_PORT,			///< �����ض˿�

	PROXY_TYPE,					///< socks��������
	PROXY_IP,					///< socks����IP
	PROXY_PORT,					///< socks����˿�
	PROXY_USER,					///< socks5/http�����û���
	PROXY_PASS,					///< socks5/http��������
};

/**
 * @brief ��������ö��
 * @details socks��������
 */
enum PROXYTYPE
{
	NOPROXY				= 0,	///< û�д���
	SOCKS4,						///< sock4����
	SOCKS5,						///< sock5����
	SOCKS5_LOGON,				///< ���û���֤��sock5����
	HTTP,						///< HTTP����
	HTTP_LOGON,					///< ���û���֤��HTTP����
};
/** @} */

/** \defgroup Group14 1.4 ���ݽṹ���� */
/** @{ */
/// �޳�ʱ����
#ifndef INFINITE
    #define INFINITE	0xFFFFFFFF
#endif

///��ѯ��󷵻�����
#define ZB_MAX_RETU		99999


/// ����
#define EMPTY_ROW       -1
/// ��ID
#define EMPTY_ID        -1
/// ��NO
#define EMPTY_NO        -1


	///	ETX���ͻص�
	typedef void (CALLBACK* TOnReadPushData)(ETX_APP_FUNCNO FuncNO, void* pEtxPushData);

	/// ��ʼ������
	typedef struct _STInitPara
    {
		TOnReadPushData     pOnReadPushData;            ///< ETX���ͻص�����
		bool			    bWriteLog;					///< �Ƿ��¼��־��Ϣ
		LOG_LEVEL		    emLogLevel;					///< ��־���𣬲μ�LOG_LEVEL
		int				    nTimeOut;					///< ��ʱʱ�䣬��λms
    }__PACKED__ STInitPara, *PSTInitPara;

    /// Ӧ����Ϣ
    typedef struct _STRspMsg
    {
        TErrorNoType        error_no;                   ///< ������루0Ϊ�ɹ�������Ϊʧ�ܣ�
        TErrorMsgType       msg;                        ///< ������Ϣ
    }__PACKED__ STRspMsg, *PSTRspMsg;
    
    /// ����Ա��¼ָ��  //��Ӧspx61
    typedef struct _STTraderLogin
    {
        TCustNoType         cust_no;                    ///< �ͻ���
        TCustPwdType        cust_pwd;                   ///< �ͻ�����
    } __PACKED__ STTraderLogin, *PSTTraderLogin;
    
    /// ��¼Ӧ��
    typedef struct _STTraderLoginRsp
    {
        TCustNameType       cust_name;                  ///< �ͻ�����
        TDateType           tx_date;                    ///< ��������
		TMarketCodeType     market_code;                ///< �г�����
		THolderNoType       holder_acc_no;              ///< �ɶ��ʺ�
    } __PACKED__ STTraderLoginRsp, *PSTTraderLoginRsp;

    /// Api��Ϣ
    typedef struct _STApiInfo
    {
        TApiVersionType     api_version;                ///< Api�汾��
		TOrganizationNO		org_no;						///< ������
		TIPADDR				server_ip;					///< ����IP
		TPort				server_port;				///< ���ض˿�
		TDateType			auth_date;					///< ��Ȩ������
    } __PACKED__ STApiInfo, *PSTApiInfo;

    /// ί������  
    typedef struct _STOrder
    {
        TSecCodeType        sec_code;                   ///< ֤ȯ����
        TBSType             bs;                         ///< �������(1��2��0��9��U�ֲ�P�ϲ�)
        TMarketOrderFlagType market_order_flag;         ///< �м�ί�б�ǣ��м�ί�к�ί�м۸��ѡһ
														/*
														2  ����ַ����ż۸�ί��		���� 
														3  ������ż۸�ί��		���� 
														4  �ʱ�ɽ�ʣ�೷��ί��	 
														5  ���������嵵������ί��	�Ϻ������� 
														6  ��ȫ��ɽ�����ί��		 
														7  �������嵵��ת�޼�ί��	�Ϻ� 
		                                                */
        TPriceType          price;                      ///< ί�м۸�
        TStockVolType       order_vol;                  ///< ί������
        TOrderPropType      order_prop;                 ///< ί������(Ԥ��)
    }__PACKED__ STOrder, *PSTOrder;

    /// ί��Ӧ��
    typedef struct _STOrderRsp
    {
        TBatchNoType        batch_no;                   ///< ����
		TContractNoType     order_no;                   ///< ϵͳί����ˮ��
		TFundAmountType     forzen_amount;              ///< ί�ж�����      
		TStockVolType       forzen_vol;                 ///< ί�ж�������
		TErrorNoType        error_no;                   ///< ί�д�����루0Ϊ�ɹ�������Ϊʧ�ܣ�
        TErrorMsgType       err_msg;                    ///< ί�д�����Ϣ
    }__PACKED__ STOrderRsp, *PSTOrderRsp;

    /// �������� 
    typedef struct _STOrderCancel
    {
		TMarketCodeType     market_code;                ///< �г����루�������������룩
		TCustNoType         cust_no;                    ///< �ͻ���
        TOrderCancelType    ordercancel_type;           ///< ������ʽ��0��������1�����ʳ���
		TContractNoType     order_no;                   ///< ��ˮ��
    }__PACKED__ STOrderCancel, *PSTOrderCancel;

	 /// ����Ӧ��
    typedef struct _STOrderCancelRsp
    {
		TErrorNoType        error_no;                   ///< ����������루0Ϊ�ɹ�������Ϊʧ�ܣ�
        TErrorMsgType       err_msg;                    ///< ����������Ϣ
    }__PACKED__ STOrderCancelRsp, *PSTOrderCancelRsp;
   
    /// ��ѯ�˻��ʽ����� 
    typedef struct _STQueryFund
    {
	    TCustNoType         cust_no;                    ///< �ͻ���
        TCurrencyTypeType   currency_type;              ///< ����(0-���б��֣�1-����ң�2����Ԫ��3���۱ң�4���۹ɸ۱�) 
    }__PACKED__ STQueryFund, *PSTQueryFund;

    /// �˻��ʽ���Ϣ
    typedef struct _STFundInfo
    {
        TCurrencyTypeType   currency_type;              ///< ����
        TFundAmountType     deposite;                   ///< �ʽ����
        TFundAmountType     buyable;                    ///< �����ʽ����
    }__PACKED__ STFundInfo, *PSTFundInfo;

    /// ��ѯ�ֲ����� 
    typedef struct _STQueryPosition
    {
	    TCustNoType         cust_no;                    ///< �ͻ���
        TMarketCodeType     market_code;                ///< �г�����(Ϊ0ʱ��ѯ�����г�)
        TSecCodeType        sec_code;                   ///< ֤ȯ����(Ϊ��ʱ��ѯ����֤ȯ����) 
    }__PACKED__ STQueryPosition, *PSTQueryPosition;

    /// �ֲ���Ϣ
    typedef struct _STPositionInfo
    {
        TMarketCodeType     market_code;                ///< �г�����
        TSecCodeType        sec_code;                   ///< ֤ȯ����
		TSecNameType        sec_name;                   ///< ֤ȯ���
		TStockVolType       buy_vol;                    ///< ��������ɽ�����
		TStockVolType       sell_vol;                   ///< ���������ɽ�����
        TStockVolType       total_vol;                  ///< ��ǰ�ֲ֣ܳ������޿�桢����������
        TStockVolType       avail_vol;                  ///< ��ǰ�������
		TFundAmountType     market_value;               ///< ��ֵ
        TFundAmountType     total_cost;                 ///< �ֲֳɱ�
        TPriceType          last_price;                 ///< ���¼�
        TFundAmountType     float_profit;               ///< ����ӯ��
    }__PACKED__ STPositionInfo, *PSTPositionInfo;
   
   ///��ѯ�ʲ�
	typedef struct _STQueryAssest
    {
		TCustNoType         cust_no;                    ///< �ͻ���
        TCurrencyTypeType   currency_type;              ///< ����(���1-����ң�2����Ԫ��3���۱ң�4���۹ɸ۱�) 
    }__PACKED__ STQueryAssest, *PSTQueryAssest;

    /// ��ѯ�ʲ�
    typedef struct _STAssestInfo
    {
       TFundAmountType      total_amount;               ///< ���ʲ�(�����޿�桢����;�ʽ�)
    }__PACKED__ STAssestInfo, *PSTAssestInfo;
	
	
	 /// ��ѯ����
    typedef struct _STQueryAccount
    {
        TCustNoType         cust_no;                    ///< �ͻ���
        TMarketCodeType     market_code;                ///< �г�����(Ϊ0ʱ��ѯ�����г�)
		TCurrencyTypeType   currency_type;              ///< ����
		TDateType           begin_date;                 ///< ��ʼ����(Ϊ�ղ�ѯ����)
		TDateType           end_date;                   ///< ��������(Ϊ�ղ�ѯ����)
		TQueryType          query_type;                 ///< ��ѯ���(0������1ȫ��) 
    }__PACKED__ STQueryAccount, *PSTQueryAccount;

    /// ������Ϣ
    typedef struct _STAccountInfo
    {
	    TDateType           date;                 	    ///< �������� 
	    TMarketCodeType     market_code;                ///< �г�����
		THolderNoType       holder_acc_no;              ///< �ɶ��ʺ�
        TSecCodeType        sec_code;                   ///< ֤ȯ����
	    TNoteType2          note;        				///< ժҪ��������
		TBSType             bs;                         ///< ��������(������ת����)
		TCurrencyTypeType   currency_type;              ///< ����
		TFundAmountType     fund_change_amount;         ///< �䶯���
		TFundAmountType     fund_amount;        	    ///< �������
		TPriceType          done_price;                 ///< �ɽ��۸�
        TStockVolType       done_vol;                   ///< �ɽ�����
		TFundAmountType     done_amount;                ///< �ɽ����
		TTimeType           done_time;                  ///< �ɽ�ʱ��
		TDoneNoType         done_no;                    ///< �ɽ����
		TFundAmountType     trade_fee;                  ///< ���׷���(Ӷ�𡢹����ѡ�ӡ��˰����������)
		TFundAmountType     commission;                 ///< Ӷ��
		TFundAmountType     chg_owner_fee;              ///< ������
		TFundAmountType     stamp_tax;                  ///< ӡ��˰
		TFundAmountType     other_fee;                  ///< ��������
		TOrderNoType        order_no;                   ///< ϵͳί����ˮ��
    }__PACKED__ STAccountInfo, *PSTAccountInfo;
	
    /// ��ѯί������
    typedef struct _STQueryOrder
    {
		TCustNoType         cust_no;                    ///< �ͻ���
        TMarketCodeType     market_code;                ///< �г�����(Ϊ0ʱ��ѯ�����г�)
        TSecCodeType        sec_code;                   ///< ֤ȯ����(Ϊ��ʱ��ѯ����֤ȯ����)		
		TBatchNoType        batch_no;                   ///< ����(��EMPTY_NOʱ�����Ų�ѯ)�����ʲ�ѯʱ��Ϊ0
		TContractNoType     order_no;                   ///< ϵͳί����ˮ�ţ�������ѯʱ��Ϊ0
        TQueryOrderPropType query_order_prop;           ///< ��ѯί������(0Ϊ��ѯ����,1Ϊ����ѯ�ɳ���ί��)
		TQueryType          query_type;                 ///< ��ѯ���(0������1ȫ��)  
    }__PACKED__ STQueryOrder, *PSTQueryOrder;
    
	/// ί����Ϣ(ί��Ӧ��ί�в�ѯӦ��)
    typedef struct _STOrderInfo
    {
        TMarketCodeType     market_code;                ///< �г�����
		THolderNoType       holder_acc_no;              ///< �ɶ��ʺ�
		TBSFLAG             bs;                         ///< ��������(1��2��)
        TSecCodeType        sec_code;                   ///< ֤ȯ����
		TSecNameType        sec_name;                   ///< ֤ȯ���
        TPriceType          price;                      ///< ί�м۸�
        TStockVolType       order_vol;                  ///< ί������
        TBatchNoType        batch_no;                   ///< ����
        TContractNoType     order_no;                   ///< ϵͳί����ˮ��		
        TOrderStatusType    order_status;               ///< ί��״̬
		TFundAmountType     frozen_amount;              ///< ������
        TStockVolType       frozen_vol;                 ///< ��������
        TPriceType          done_price;                 ///< �ɽ��۸�
        TStockVolType       done_vol;                   ///< �ɽ�����
        TStockVolType       cancel_vol;                 ///< �ѳ�������
		TDateType           order_date;                 ///< ί������  
        TTimeType           order_time;                 ///< ί��ʱ��   
    }__PACKED__ STOrderInfo, *PSTOrderInfo;
	
    /// ��ѯ�ɽ�����
    typedef struct _STQueryDone
    {
		TCustNoType         cust_no;                    ///< �ͻ���
        TMarketCodeType     market_code;                ///< �г�����(Ϊ0ʱ��ѯ�����г�)
        TSecCodeType        sec_code;                   ///< ֤ȯ����(Ϊ��ʱ��ѯ����֤ȯ����)
		TQueryType          query_type;                 ///< ��ѯ���(0������1ȫ��)
    }__PACKED__ STQueryDone, *PSTQueryDone;
    
	 /// �ɽ���Ϣ(�ɽ����ء��ɽ���ѯӦ��)
    typedef struct _STDoneInfo
    {
        TMarketCodeType     market_code;                ///< �г�����
        TBSFLAG             bs;                         ///< ��������(1��2��)
        TSecCodeType        sec_code;                   ///< ֤ȯ����
		TSecNameType        sec_name;                   ///< ֤ȯ���
        //TBatchNoType        batch_no;                 ///< ����
        TContractNoType     order_no;                   ///< ϵͳί����ˮ��
        TPriceType          done_price;                 ///< �ɽ��۸�
        TStockVolType       done_vol;                   ///< �ɽ�����
        TFundAmountType     done_amount;                ///< �ɽ����
        TTimeType           done_time;                  ///< �ɽ�ʱ��
		TDoneNoType         done_no;                    ///< �ɽ����
		TFundAmountType     forzen_amount;              ///< �ⶳ�ʽ���
		TStockVolType       forzen_vol;                 ///< �ⶳ֤ȯ����
    }__PACKED__ STDoneInfo, *PSTDoneInfo;

    /// ֤ȯ������Ϣ��ѯ
    typedef struct _STQuerySecCode
    {
        TMarketCodeType     market_code;                ///< �г����루����ض��г���ѯ����֧��Ϊ0ʱ��ѯ���У�
        TSecCodeType        sec_code;                   ///< ֤ȯ���루����ض�֤ȯ��ѯ����֧��Ϊ��ʱ��ѯ���У�
    }__PACKED__ STQuerySecCode, *PSTQuerySecCode;
    
    /// ֤ȯ������Ϣ
    typedef struct _STSecCodeInfo
    {
        TMarketCodeType     market_code;                ///< �г�����
        TSecCodeType        sec_code;                   ///< ֤ȯ����
        TSecNameType        sec_name;                   ///< ֤ȯ���
        TSecVarietyType     sec_variety;                ///< ֤ȯ���
        TSecStatusType      sec_status;                 ///< ֤ȯ״̬��1-ͣ�Ʊ�־��
        TPriceType          raise_limit_price;          ///< ��ͣ�۸�
        TPriceType          fall_limit_price;           ///< ��ͣ�۸�
    }__PACKED__ STSecCodeInfo, *PSTSecCodeInfo;
    
    /// ETF������Ϣ��ѯ
    typedef struct _STQueryEtfBaseInfo
    {
        TMarketCodeType     market_code;                ///< �г�����(Ϊ0ʱ��ѯ�����г�)
        TSecCodeType        sgsh_tx_code;				///< �깺���֤ȯ����(Ϊ��ʱ��ѯ�����깺���֤ȯ����)
    }__PACKED__ STQueryEtfBaseInfo, *PSTQueryEtfBaseInfo;
    
    /// ETF������Ϣ
    typedef struct _STEtfBaseInfo
    {
        TSecCodeType        sgsh_tx_code;               ///< �����깺���֤ȯ����
        TSecCodeType        bs_code;                    ///< ��������֤ȯ����
        TEtfNameType        etf_name;                   ///< ETF���
        TUnitType           sgsh_min_unit;              ///< �깺�����С�ݶ�
        TFundAmountType     estimate_cash_bal;          ///< ����Ԥ���ֽ����
        TFundAmountType     cash_bal;                   ///< �����ֽ������
        TRatioType          max_cash_ratio;             ///< �ֽ������������
        TFundAmountType     etf_nav;                    ///< �ο�����ֵ
        TRecordNumType      record_num;                 ///< ���ӹ�Ʊ����
		TEtfPropType        etf_proptype;               ///< ETF����
    }__PACKED__ STEtfBaseInfo, *PSTEtfBaseInfo;
    
    /// ETF������Ϣ��ѯ
    typedef struct _STQueryEtfBasketInfo
    {
        TMarketCodeType     market_code;                ///< �г�����(Ϊ0ʱ��ѯ�����г�)
        TSecCodeType        sgsh_tx_code;				///< �깺���֤ȯ����(Ϊ��ʱ��ѯ�����깺���֤ȯ����)
    }__PACKED__ STQueryEtfBasketInfo, *PSTQueryEtfBasketInfo;

    /// ETF������Ϣ
    typedef struct _STEtfBasketInfo
    {
        TMarketCodeType     market_code;                ///< �г�����
        TSecCodeType        sec_code;                   ///< ֤ȯ����
        TSecNameType        sec_name;                   ///< ֤ȯ���
        TStockVolType       stock_vol;                  ///< ��Ʊ����
        TCashReplFlagType   cash_repl_flag;             ///< �ֽ������־
        TRatioType          over_ratio;                 ///< ��۱���
        TFundAmountType     cash_repl_amt;              ///< �ֽ�������
    }__PACKED__ STEtfBasketInfo, *PSTEtfBasketInfo;
	
	// 16203���ɽ������ϵ����������ݽṹ��
	typedef struct _ST16203PushData
	{
		TAppFunctionNO		app_func_no;				///< ҵ���ܺ� 16203
		TCustNoType         cust_no;                    ///< �ͻ���
		TMarketCodeType     market_code;                ///< �г�����
		THolderNoType       holder_acc_no;              ///< �ɶ�����
        TSecCodeType        sec_code;                   ///< ֤ȯ����
		TSecNameType        sec_name;                   ///< ֤ȯ���
        TBatchNoType        batch_no;                   ///< ί������
        TContractNoType     order_no;                   ///< ϵͳί����ˮ��
		TOrderStatusType    order_status;               ///< ί��״̬
		TOrderStatusName	order_status_name;			///< ί��״̬����
        TPriceType          done_price;                 ///< �ɽ��۸񣨸ñ�ί�е�ƽ���ɽ��۸�
        TStockVolType       done_vol;                   ///< �ɽ��������ñ�ί�еĳɽ�������
        TTimeType           done_time;                  ///< �ɽ�ʱ��
		TDoneNoType         done_no;                    ///< �������ɽ���ţ��ñʳɽ��ģ���������ϵ���Ϊ"-1"��
		TPriceType          unit_done_price;            ///< ���ʳɽ��۸񣨸ñʳɽ��ĳɽ�������
        TStockVolType       unit_done_vol;              ///< ���ʳɽ��������ñʳɽ��ĳɽ��۸�
		TInvalidOrderReason invalid_order_reason;		///< �ϵ�ԭ��
		TDoneIDType			done_id;					///< �ɽ�ID
	}__PACKED__ ST16203PushData, *PST16203PushData;

	//16204�������ķϵ����������ݽṹ��
	typedef struct _ST16204PushData
	{
		TAppFunctionNO		app_func_no;				///< ҵ���ܺ� 16204
		TCustNoType         cust_no;                    ///< �ͻ���
		TMarketCodeType     market_code;                ///< �г�����
		THolderNoType       holder_acc_no;              ///< �ɶ�����
        TSecCodeType        sec_code;                   ///< ֤ȯ����
		TSecNameType        sec_name;                   ///< ֤ȯ���
        TBatchNoType        batch_no;                   ///< ί������
        TContractNoType     order_no;                   ///< ϵͳί����ˮ��
		TOrderStatusType    order_status;               ///< ί��״̬
		TOrderStatusName	order_status_name;			///< ί��״̬����
		TInvalidOrderReason invalid_order_reason;		///< �ϵ�ԭ��
		TTimeType           done_time;                  ///< �ɽ�ʱ��
	}__PACKED__ ST16204PushData, *PST16204PushData;

/** @} */

#ifdef WIN32
#pragma pack(pop)
#else
#ifdef __GNUC__
#else
#ifdef HP_UX
#pragma pack 0
#else
#pragma options align = reset
#endif
#endif
#endif
#undef __PACKED__
#ifdef __cplusplus
}
#endif

#endif //__SPXAPI_STRUCT_H__
