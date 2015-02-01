#ifndef __SPXAPI_H__
#define __SPXAPI_H__

#include "SPXAPI_struct.h"

#define INTER_FAIL_USER_MESSAGE	-999

#ifdef WIN32
    #ifdef SPXAPI_EXPORTS
    #define SPX_API __declspec(dllexport)
    #else
    #define SPX_API __declspec(dllimport)
    #endif
#else
    #define SPX_API 
#endif

#ifdef __cplusplus
extern "C" {
#endif
	
//API���
typedef void *  APIHandle ;


//��̬���������


/**
 * @brief ȫ�ֳ�ʼ��
 * @param[in] p_init_para ��ʼ�������ṹ
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details APIȫ�ֳ�ʼ����������Ҫ�ҽ������һ��
 * @see SPX_API_Initialize
 */
SPX_API bool WINAPI SPX_API_Initialize(STInitPara *p_init_para, STRspMsg *err_msg);

/**
 * @brief ȫ���˳�
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details APIȫ���˳���������Ҫ�ҽ������һ��
 * @see SPX_API_Finalize
 */
SPX_API bool WINAPI SPX_API_Finalize(STRspMsg *err_msg);


/**
 * @brief ��������ԱAPI��� 
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return API���,����ʧ��ʱΪNULL,�����ɹ�ʱ��NULL
 * @details 
 * @see SPX_API_CreateHandle
 */
SPX_API APIHandle WINAPI SPX_API_CreateHandle(STRspMsg *err_msg);

/**
 * @brief  ���ٽ���ԱAPI������ͷ���Դ
 * @param[in] pHandle Ҫ���ٵ�API���ָ��,����ΪNULL
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details 
 * @see SPX_API_DestroyHandle
 */
SPX_API bool WINAPI SPX_API_DestroyHandle(APIHandle *pHandle, STRspMsg *err_msg);


/**
 * @brief ��ȡAPI��Ϣ
 * @param[out] p_api_info API��Ϣ���
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details ��ѯAPI��Ϣ
 * @see SPX_API_GetApiInfo
 */
SPX_API bool WINAPI SPX_API_GetApiInfo(STApiInfo* p_api_info, STRspMsg * err_msg);


/**
 * @brief  �˺ŵ�½У��
 * @param[in] handle API���
 * @param[in] p_login ��½������Ϣ
 * @param[out] p_login_rsp ��½���صĿͻ������Ϣ
 * @param[out] row_num ��½���صĿͻ������Ϣ�ļ�¼��
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details �˺ŵ�½У�飬ֻ���ڵ�½�ɹ�ʱ�ŷ��ؿͻ��������Ϣ��
 * @see SPX_API_Login
 */
SPX_API bool WINAPI SPX_API_Login(APIHandle handle,const STTraderLogin *p_login, STTraderLoginRsp **p_login_rsp,int *row_num,STRspMsg *err_msg);

/**
 * @brief  ί��
 * @param[in] handle API���
 * @param[in] cust_no ί�еĿͻ���
 * @param[in] market_code �г�����
 * @param[in] holder_acc_no �ɶ�����
 * @param[in] order_type ί������(0֤ȯ����/1��������/2ETF����/3�����ֺϲ�)
 * @param[in] p_order ί��������Ϣ
 * @param[in] order_count ί�м�¼��
 * @param[in] timeout ί�г�ʱʱ�䣬Ĭ��ȡ��ʼ��ʱ���õĳ�ʱʱ��
 * @param[out] p_order_rsp ί�з�����Ϣ
 * @param[out] row_num ί�з��ؼ�¼��
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details 
   1.ί����Ϣp_order�и�ί�м�¼��Ϊͬһ�������µ��������붼��ͬһ��ί������(0֤ȯ����/1��������/2ETF����/3�����ֺϲ�)
   2.p_order_rsp��ί��˳�����η���ͬһ���θ�ί�е��Ĵ�����
 * @see SPX_API_Order
 */
SPX_API bool WINAPI SPX_API_Order(APIHandle handle, char *cust_no,char *market_code,char *holder_acc_no,char *order_type,const STOrder *p_order, STOrderRsp **p_order_rsp,int order_count, int *row_num, STRspMsg *err_msg, int timeout=INFINITE-1);

/**
 * @brief  ����
 * @param[in] handle API���
 * @param[in] p_order_cancel ����������Ϣ
 * @param[in] cancel_count ������¼�� 
 * @param[in] timeout ί�г�ʱʱ�䣬Ĭ��ȡ��ʼ��ʱ���õĳ�ʱʱ��
 * @param[out] p_order_cancel_rsp ����������Ϣ
 * @param[out] row_num �������ؼ�¼��
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details 
   1.������Ϣp_order_cancel�ɶԶ��ί�е����г������ɰ����Ż�ί����ˮ�ų�����������ͬʱָ�����ź�ί����ˮ��
   2.p_order_cancel_rsp������˳�����η��ظ��ʳ���������
 * @see SPX_API_OrderCancel
 */
SPX_API bool WINAPI SPX_API_OrderCancel(APIHandle handle, const STOrderCancel *p_order_cancel, STOrderCancelRsp **p_order_cancel_rsp, int cancel_count, int *row_num, STRspMsg *err_msg, int timeout=INFINITE-1);

/**
 * @brief  ��ѯ�ʽ�
 * @param[in] handle API���
 * @param[in] p_qry_fund ��ѯ�ʽ�������Ϣ
 * @param[out] p_qry_fund_rsp �ʽ𷵻���Ϣ
 * @param[out] row_num �ʽ𷵻ؼ�¼��
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details  
 * @see SPX_API_QueryFund
 */
SPX_API bool WINAPI SPX_API_QueryFund(APIHandle handle, STQueryFund *p_qry_fund, STFundInfo **p_qry_fund_rsp, int *row_num, STRspMsg *err_msg);

/**
 * @brief  ��ѯ�ֲ�
 * @param[in] handle API���
 * @param[in] p_qry_position ��ѯ�ֲ�������Ϣ
 * @param[out] p_qry_position_rsp �ֲַ�����Ϣ
 * @param[out] row_num �ֲַ��ؼ�¼��
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details  
 * @see SPX_API_QueryPosition
 */
SPX_API bool WINAPI SPX_API_QueryPosition(APIHandle handle, STQueryPosition *p_qry_position, STPositionInfo **p_qry_position_rsp, int *row_num, STRspMsg *err_msg);

/**
 * @brief  �����ѯ
 * @param[in] handle API���
 * @param[in] p_qry_account �����ѯ������Ϣ
 * @param[out] p_qry_account_rsp �����ѯ������Ϣ
 * @param[out] row_num �����ѯ���ؼ�¼��
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details  
 * @see SPX_API_QueryAccount
 */
SPX_API bool WINAPI SPX_API_QueryAccount(APIHandle handle, STQueryAccount *p_qry_account, STAccountInfo **p_qry_account_rsp, int *row_num, STRspMsg *err_msg);

/**
 * @brief  ��ѯί��
 * @param[in] handle API���
 * @param[in] p_qry_order ��ѯί��������Ϣ
 * @param[out] p_qry_order_rsp ��ѯί�з�����Ϣ
 * @param[out] row_num ��ѯί�з��ؼ�¼��
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details  
 * @see SPX_API_QueryOrder
 */ 
SPX_API bool WINAPI SPX_API_QueryOrder(APIHandle handle, STQueryOrder *p_qry_order, STOrderInfo **p_qry_order_rsp, int *row_num, STRspMsg *err_msg);

/**
 * @brief  ��ѯ�ɽ�
 * @param[in] handle API���
 * @param[in] p_qry_done ��ѯ�ɽ�������Ϣ
 * @param[out] p_qry_done_rsp ��ѯ�ɽ�������Ϣ
 * @param[out] row_num ��ѯ�ɽ����ؼ�¼��
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details  
 * @see SPX_API_QueryDone
 */  
SPX_API bool WINAPI SPX_API_QueryDone(APIHandle handle, STQueryDone *p_qry_done, STDoneInfo **p_qry_done_rsp, int *row_num, STRspMsg *err_msg);

/**
 * @brief  ��ѯ֤ȯ��Ϣ
 * @param[in] handle API���
 * @param[in] p_qry_seccode ��ѯ֤ȯ��Ϣ������Ϣ
 * @param[out] p_qry_seccode_rsp ֤ȯ������Ϣ
 * @param[out] row_num ֤ȯ��Ϣ���ؼ�¼��
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details  
 * @see SPX_API_QuerySecCode
 */  
SPX_API bool WINAPI SPX_API_QuerySecCode(APIHandle handle, STQuerySecCode *p_qry_seccode, STSecCodeInfo **p_qry_seccode_rsp, int *row_num, STRspMsg *err_msg);

/**
 * @brief  ��ѯETF������Ϣ
 * @param[in] handle API���
 * @param[in] p_qry_etfbaseinfo ��ѯETF������Ϣ������Ϣ
 * @param[out] p_qry_etfbaseinfo_rsp ETF������Ϣ
 * @param[out] row_num ETF������Ϣ���ؼ�¼��
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details  
 * @see SPX_API_QueryEtfBaseInfo
 */  
SPX_API bool WINAPI SPX_API_QueryEtfBaseInfo(APIHandle handle, STQueryEtfBaseInfo *p_qry_etfbaseinfo, STEtfBaseInfo **p_qry_etfbaseinfo_rsp, int *row_num, STRspMsg *err_msg);

/**
 * @brief  ��ѯETF������Ϣ
 * @param[in] handle API���
 * @param[in] p_qry_etfbasketinfo ��ѯETF������Ϣ������Ϣ
 * @param[out] p_qry_etfbasketinfo_rsp ETF������Ϣ
 * @param[out] row_num ETF������Ϣ���ؼ�¼��
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details  
 * @see SPX_API_QueryEtfBasketInfo
 */   
SPX_API bool WINAPI SPX_API_QueryEtfBasketInfo(APIHandle handle, STQueryEtfBasketInfo *p_qry_etfbasketinfo, STEtfBasketInfo **p_qry_etfbasketinfo_rsp, int *row_num, STRspMsg *err_msg);


/**
 * @brief  �������
 * @param[in] handle API���
 * @return trueΪ�ɹ���falseΪʧ��
 * @details  ��ʽ������󷵻���Ϣ�Ļ���
   ��ҵ�������ڷ��ؽ����Ϣʱ���Զ������һ�ʵĻ���
 * @see SPX_API_Clear_Buf
 */   
SPX_API bool WINAPI SPX_API_Clear_Buf(APIHandle handle);

/**
 * @brief ��������
 * @param[in] type ��������
 * @param[in] value ����ֵ
 * @param[out] err_msg ʧ��ʱ�Ĵ�����Ϣ
 * @return trueΪ�ɹ���falseΪʧ��
 * @details ����Ҫ���õ�API�����������ã������SPX_API_Initializeǰ����
 * @see SPX_API_SetParam
 */
SPX_API bool WINAPI SPX_API_SetParam(PARAM_TYPE type, const char *value, STRspMsg *err_msg);


#ifdef __cplusplus
}
#endif

#endif //__SPXAPI_H__