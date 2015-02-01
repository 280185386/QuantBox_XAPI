#ifndef __SPXAPI_TYPE_H__
#define __SPXAPI_TYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup Group11 1.1 ���ݳ��ȶ��� */
/** @{ */
/// API�汾����
#define API_VERSION_LEN				30
/// ������Ϣ����
#define MSG_LEN						256
/// �ͻ��ų���
#define CUST_NO_LEN					16
/// �ɶ����볤��
#define HOLDER_NO_LEN				16
/// ���볤��
#define PWD_LEN						33
/// ֤ȯ���볤��
#define SEC_CODE_LEN				20
/// ��ע����
#define NOTE_LEN					256
/// ��ע����
#define NOTE_LEN2					21
/// ��̨ʵ���ų���
#define INSTANCE_ID_LEN				32
/// �ͻ����Ƴ���
#define CUST_NAME_LEN				21
/// ֤ȯ���Ƴ���
#define SEC_NAME_LEN				21
/// ETF���Ƴ���
#define ETF_NAME_LEN				81
/// ETF���Գ���
#define ETF_PROP_LEN				3
/// �������ͳ���
#define BS_TYPE_LEN					3
/// �������ͳ���
#define DATE_TYPE_LEN				9
/// ί����ˮ�ų���
#define ORDER_NO_LEN				17
/// ί��״̬���Ƴ���
#define ORDER_STATUS_NAME_LEN		21
/// �ϵ�ԭ�򳤶�
#define INVALID_ORDER_REASON_LEN	7
/// ҵ���ܺų���
#define	APP_FUNC_NO_LEN				11
/// ����ʮ�����Ƶ�ַ����
#define MAC_ADDR_LEN				18
/// IP��ַ����
#define IP_ADDR_LEN					20
/// �����ų���
#define ORG_NO_LEN					21
/// �ɽ���ų���
#define DONE_NO_LEN					13
/// �����û�������
#define PROXYUSER_LEN				100
/// �����û����볤��
#define PROXYPASS_LEN				100
/** @} */

/** \defgroup Group12 1.2 �������Ͷ��� */
/** @{ */
/// ��������
#ifndef BOOL
    typedef int BOOL;
#endif

/// ��ֵ
#ifndef TRUE
#define TRUE	1
#endif
/// ��ֵ
#ifndef FALSE
#define FALSE	0
#endif


    /// API�汾����
    typedef char            TApiVersionType[API_VERSION_LEN];
	/// ������
	typedef char			TOrganizationNO[ORG_NO_LEN];
	/// IP
	typedef char			TIPADDR[IP_ADDR_LEN];
	//  �˿�
	typedef int				TPort;

    /// �����������
    typedef int             TErrorNoType;
    /// ������Ϣ����
    typedef char            TErrorMsgType[MSG_LEN];

    /// �ͻ�������
    typedef char            TCustNoType[CUST_NO_LEN];
	/// �ɶ��ʺ�����
    typedef char            THolderNoType[HOLDER_NO_LEN];
    /// �ͻ���¼��������
    typedef char            TCustPwdType[PWD_LEN];
    /// �ն���������
    typedef int             TTerminalTypeType;
    /// ��ע����
    typedef char            TNoteType[NOTE_LEN];
	/// ��ժҪ����
    typedef char            TNoteType2[NOTE_LEN2];
    /// ��̨ʵ��������
    typedef char            TInstanceIdType[INSTANCE_ID_LEN];
    /// ������ַ����
    typedef char            TMacType[MAC_ADDR_LEN];
    
    /// �Ự������
    typedef int             TSessionIdType;
    /// ���ӻỰ������
    typedef int             TConnSessionIdType;
    /// �ͻ���������
    typedef char            TCustNameType[CUST_NAME_LEN];
    /// ������������
    typedef char            TDateType[DATE_TYPE_LEN];


    /// �г��������ͣ�����ֵ����������ֵ�-�г�����
    typedef char            TMarketCodeType;
    /// ֤ȯ��������
    typedef char            TSecCodeType[SEC_CODE_LEN];
    /// ί���������ͣ�����ֵ����������ֵ�-ί������
    typedef char            TOrderTypeType;
    /// �����������ͣ�����ֵ����������ֵ�-��������
    typedef char            TBSType[BS_TYPE_LEN];
	/// ������־����
    typedef char            TBSFLAG;
    /// �м۵��������ͣ�����ֵ����������ֵ�-�м۵�����
    typedef char            TMarketOrderFlagType;
    /// ί�м۸�����
    typedef double          TPriceType;
    /// ί����������
    typedef double          TStockVolType;
    /// ί����������
    typedef int             TOrderPropType;
    /// ���Ա��/��������
    typedef int             TBatchNoType;
    
    /// ί����������
    typedef int             TOrderPropType;
    /// ί����ˮ������
    typedef char            TOrderNoType[ORDER_NO_LEN];
	/// ��ͬ������
	typedef int				TContractNoType;
    /// ί��״̬���ͣ�����ֵ����������ֵ�-ί��״̬
    typedef char            TOrderStatusType;
    /// ί��״̬����
    typedef char            TOrderStatusName[ORDER_STATUS_NAME_LEN];
    /// ί��ʱ������
    typedef int             TTimeType;
    /// �ɽ���������
    typedef int             TDoneCountType;
	//	��������
	typedef int             TOrderCancelType;
    
    /// �ɽ��������
    typedef char            TDoneNoType[DONE_NO_LEN];
	/// �ɽ�ID����
	typedef int				TDoneIDType;
    
    /// �����������ͣ�����ֵ����������ֵ�-��������
    typedef char            TCurrencyTypeType;
    /// �ʽ���������
    typedef double          TFundAmountType;
    /// ��ѯ�˻��ʽ�����
    typedef int             TQueryAccountProp;
    /// ��ѯ�ֲ�����
    typedef int             TQueryPositionProp;
    
    /// ��ѯί����������
    typedef int             TQueryOrderPropType;
    
	//	��ѯ���� ���� ȫ��
	typedef int             TQueryType;
    /// ֤ȯ�������
    typedef char            TSecNameType[SEC_NAME_LEN];
    /// ֤ȯ״̬����
    typedef short           TSecStatusType;
    /// ֤ȯƷ�֣�����ֵ����������ֵ�-֤ȯƷ��
    typedef int             TSecVarietyType;
    /// ETF�������
    typedef char            TEtfNameType[ETF_NAME_LEN];
    /// ��λ����
    typedef int             TUnitType;
    /// ��������
    typedef double          TRatioType;
    /// ������λ���ο�ֵ��־����
    typedef char            TPublishIOPVFlag;
    /// ETF״̬���ͣ�����ֵ����������ֵ�-ETF����״̬
    typedef char            TEtfStatusType;
    /// ���ӹ�Ʊ��������
    typedef int             TRecordNumType;
    /// �ֽ������־���ͣ�����ֵ����������ֵ�-�ֽ������־
    typedef char            TCashReplFlagType;
	/// ETF���ԣ�����ֵ����������ֵ�-ETF����
    typedef char            TEtfPropType[ETF_PROP_LEN];

	/// �ϵ�ԭ��ETX���ͣ����ϵ���Ч������65-88ΪWTCLBZ��ascii�룬����ΪHBCDYY���Ϻ�REMARK
	typedef char			TInvalidOrderReason[INVALID_ORDER_REASON_LEN];
	/// ҵ���ܺ����ͣ�ETX���ͣ���16203-�ɽ������ϵ��������ͣ�16204-�����ķϵ���������
	typedef char			TAppFunctionNO[APP_FUNC_NO_LEN];

	/// �����û���
	typedef char			TProxyUser[PROXYUSER_LEN];
	/// �����û�����
	typedef char			TProxyPass[PROXYPASS_LEN];

/** @} */
#ifdef __cplusplus
}
#endif

#endif //__SPXAPI_TYPE_H__
