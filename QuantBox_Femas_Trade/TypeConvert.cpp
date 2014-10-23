#include "stdafx.h"
#include "TypeConvert.h"


/// ������OpenQuant FIXһ����Ч���������򵥣�������Ҫ����ô�������
/// ����һ�����ӵ�ĳ��״̬�����������ģ��µ������ֳɽ�����ȫ�ɽ�
/// EmitAccept,EmitFill
/// OnRtnOrder,OnRtnTrade,���ת��Emit
/// EmitAccept��ʲô
///
/// �ӿ������ṩ�Ļر����Է����ַ�����ExecutionReport��ί�лر���ɽ��ر�
/// OpenQuant��ʹ��ExecutionReport��������ΪOQ�Լ���OrderManager������������Ҫ����ί�кͳɽ��б���û���õ���
/// ���Խӿ�Ӧ������ί����ɽ��ر�

PutCall TUstpFtdcOptionsTypeType_2_PutCall(TUstpFtdcOptionsTypeType In)
{
	if (In == USTP_FTDC_OT_CallOptions)
		return PutCall::Call;
	return PutCall::Put;
}

HedgeFlagType TUstpFtdcHedgeFlagType_2_HedgeFlagType(TUstpFtdcHedgeFlagType In)
{
	switch (In)
	{
	case USTP_FTDC_CHF_Arbitrage:
		return HedgeFlagType::Arbitrage;
	case USTP_FTDC_CHF_Hedge:
		return HedgeFlagType::Hedge;
	case USTP_FTDC_CHF_MarketMaker:
		return HedgeFlagType::MarketMaker;
	case USTP_FTDC_CHF_Speculation:
	default:
		return HedgeFlagType::Speculation;
	}
}

TUstpFtdcHedgeFlagType HedgeFlagType_2_TUstpFtdcHedgeFlagType(HedgeFlagType In)
{
	switch (In)
	{
	case HedgeFlagType::Arbitrage:
		return USTP_FTDC_CHF_Arbitrage;
	case HedgeFlagType::Hedge:
		return USTP_FTDC_CHF_Hedge;
	case HedgeFlagType::MarketMaker:
		return USTP_FTDC_CHF_MarketMaker;
	case HedgeFlagType::Speculation:
	default:
		return USTP_FTDC_CHF_Speculation;
	}
}

OpenCloseType TUstpFtdcOffsetFlagType_2_OpenCloseType(TUstpFtdcOffsetFlagType In)
{
	switch (In)
	{
	case USTP_FTDC_OF_CloseToday:
		return OpenCloseType::CloseToday;
	case USTP_FTDC_OF_Close:
		return OpenCloseType::Close;
	case USTP_FTDC_OF_Open:
	default:
		return OpenCloseType::Open;
	}
}

TUstpFtdcOffsetFlagType OpenCloseType_2_TUstpFtdcOffsetFlagType(OpenCloseType In)
{
	switch (In)
	{
	case OpenCloseType::CloseToday:
		return USTP_FTDC_OF_CloseToday;
	case OpenCloseType::Close:
		return USTP_FTDC_OF_Close;
	case OpenCloseType::Open:
	default:
		return USTP_FTDC_OF_Open;
	}
}

TUstpFtdcDirectionType OrderSide_2_TUstpFtdcDirectionType(OrderSide In)
{
	if (In == OrderSide::Sell)
		return USTP_FTDC_D_Sell;
	return USTP_FTDC_D_Buy;
}

OrderSide TUstpFtdcDirectionType_2_OrderSide(TUstpFtdcDirectionType In)
{
	if (In == USTP_FTDC_D_Sell)
		return OrderSide::Sell;
	return OrderSide::Buy;
}

TUstpFtdcOrderPriceTypeType OrderType_2_TUstpFtdcOrderPriceTypeType(OrderType In)
{
	switch (In)
	{
	case Market:
		return USTP_FTDC_OPT_AnyPrice;
	case Stop:
		return USTP_FTDC_OPT_AnyPrice;
	case Limit:
		return USTP_FTDC_OPT_LimitPrice;
	case StopLimit:
		return USTP_FTDC_OPT_LimitPrice;
	case MarketOnClose:
		return USTP_FTDC_OPT_AnyPrice;
	case TrailingStop:
		return USTP_FTDC_OPT_AnyPrice;
	case TrailingStopLimit:
		return USTP_FTDC_OPT_LimitPrice;
	default:
		return USTP_FTDC_OPT_LimitPrice;
	}
}

OrderStatus CUstpFtdcOrderField_2_OrderStatus(CUstpFtdcOrderField* pIn)
{
	//switch (pIn->OrderStatus)
	//{
	//case USTP_FTDC_OS_Canceled:
	//	if (pIn->OrderSubmitStatus == USTP_FTDC_OSS_InsertRejected)
	//		return OrderStatus::Rejected;
	//	return OrderStatus::Cancelled;
	//case USTP_FTDC_OST_Unknown:
	//	// ����ǳ�����Ҳ�п��ܳ�����һ������ι��ˣ�
	//	if (pIn->OrderSubmitStatus == USTP_FTDC_OSS_InsertSubmitted)
	//		return OrderStatus::New;
	//default:
	//	if (pIn->VolumeTotal == 0)
	//		return OrderStatus::Filled;
	//	else if (pIn->VolumeTotal == pIn->VolumeTotalOriginal)
	//		return OrderStatus::New;
	//	else
	//		return OrderStatus::PartiallyFilled;
	//}

	return OrderStatus::PartiallyFilled;
}

OrderType CUstpFtdcOrderField_2_OrderType(CUstpFtdcOrderField* pIn)
{
	switch (pIn->OrderPriceType)
	{
	case USTP_FTDC_OPT_AnyPrice:
		return OrderType::Market;
	case USTP_FTDC_OPT_LimitPrice:
		return OrderType::Limit;
	default:
		return OrderType::Limit;
	}
}

TimeInForce CUstpFtdcOrderField_2_TimeInForce(CUstpFtdcOrderField* pIn)
{
	switch (pIn->TimeCondition)
	{
	case USTP_FTDC_TC_GFD:
		return TimeInForce::Day;
	case USTP_FTDC_TC_IOC:
		switch (pIn->VolumeCondition)
		{
		case USTP_FTDC_VC_AV:
			return TimeInForce::IOC;
		case USTP_FTDC_VC_CV:
			return TimeInForce::FOK;
		default:
			return TimeInForce::IOC;
		}
	default:
		return TimeInForce::Day;
	}
}

ExecType CUstpFtdcOrderField_2_ExecType(CUstpFtdcOrderField* pIn)
{
	//switch (pIn->OrderStatus)
	//{
	//case USTP_FTDC_OST_Canceled:
	//	if (pIn->OrderSubmitStatus == USTP_FTDC_OSS_InsertRejected)
	//		return ExecType::ExecRejected;
	//	return ExecType::ExecCancelled;
	//case USTP_FTDC_OST_Unknown:
	//	// ����ǳ�����Ҳ�п��ܳ�����һ������ι��ˣ�
	//	if (pIn->OrderSubmitStatus == USTP_FTDC_OSS_InsertSubmitted)
	//		return ExecType::ExecNew;
	//case USTP_FTDC_OST_AllTraded:
	//case USTP_FTDC_OST_PartTradedQueueing:
	//	return ExecType::ExecTrade;
	//default:
		return ExecType::ExecNew;
	//}
}

InstrumentType CUstpFtdcRspInstrumentField_2_InstrumentType(CUstpFtdcRspInstrumentField* pIn)
{
	switch (pIn->OptionsType)
	{
	case USTP_FTDC_OT_NotOptions:
		return InstrumentType::Future;
	default:
		return InstrumentType::Option;
	}
}
