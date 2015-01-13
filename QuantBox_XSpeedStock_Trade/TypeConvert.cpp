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

//PutCall TThostFtdcOptionsTypeType_2_PutCall(TThostFtdcOptionsTypeType In)
//{
//	if (In == THOST_FTDC_CP_CallOptions)
//		return PutCall::Call;
//	return PutCall::Put;
//}

HedgeFlagType DFITCSpeculatorType_2_HedgeFlagType(DFITCSpeculatorType In)
{
	switch (In)
	{
	case DFITC_SPD_ARBITRAGE:
		return HedgeFlagType::Arbitrage;
	case DFITC_SPD_HEDGE:
		return HedgeFlagType::Hedge;
	case DFITC_SPD_SPECULATOR:
	default:
		return HedgeFlagType::Speculation;
	}
}

DFITCSpeculatorType HedgeFlagType_2_DFITCSpeculatorType(HedgeFlagType In)
{
	switch (In)
	{
	case HedgeFlagType::Arbitrage:
		return DFITC_SPD_ARBITRAGE;
	case HedgeFlagType::Hedge:
		return DFITC_SPD_HEDGE;
	case HedgeFlagType::Speculation:
	default:
		return DFITC_SPD_SPECULATOR;
	}
}

OpenCloseType DFITCOpenCloseTypeType_2_OpenCloseType(DFITCOpenCloseTypeType In)
{
	switch (In)
	{
	case DFITC_SPD_CLOSETODAY:
		return OpenCloseType::CloseToday;
	case DFITC_SPD_CLOSE:
		return OpenCloseType::Close;
	case DFITC_SPD_OPEN:
	default:
		return OpenCloseType::Open;
	}
}

DFITCOpenCloseTypeType OpenCloseType_2_DFITCOpenCloseTypeType(OpenCloseType In)
{
	switch (In)
	{
	case OpenCloseType::CloseToday:
		return DFITC_SPD_CLOSETODAY;
	case OpenCloseType::Close:
		return DFITC_SPD_CLOSE;
	case OpenCloseType::Open:
	default:
		return DFITC_SPD_OPEN;
	}
}

DFITCBuySellTypeType OrderSide_2_DFITCBuySellTypeType(OrderSide In)
{
	if (In == OrderSide::Sell)
		return DFITC_SPD_SELL;
	return DFITC_SPD_BUY;
}

OrderSide DFITCBuySellTypeType_2_OrderSide(DFITCBuySellTypeType In)
{
	if (In == DFITC_SPD_SELL)
		return OrderSide::Sell;
	return OrderSide::Buy;
}

DFITCOrderTypeType OrderType_2_DFITCOrderTypeType(OrderType In)
{
	switch (In)
	{
	case Market:
		return DFITC_MKORDER;
	case Stop:
		return DFITC_MKORDER;
	case Limit:
		return DFITC_LIMITORDER;
	case StopLimit:
		return DFITC_LIMITORDER;
	case MarketOnClose:
		return DFITC_MKORDER;
	case TrailingStop:
		return DFITC_MKORDER;
	case TrailingStopLimit:
		return DFITC_LIMITORDER;
	default:
		return DFITC_LIMITORDER;
	}
}

TimeInForce DFITCOrderPropertyType_2_TimeInForce(DFITCOrderPropertyType In)
{
	switch (In)
	{
	case DFITC_SP_FAK:
		return TimeInForce::IOC;
	case DFITC_SP_FOK:
		return TimeInForce::FOK;
	case DFITC_SP_NON:
	default:
		return TimeInForce::Day;
	}
}

DFITCOrderPropertyType TimeInForce_2_DFITCOrderPropertyType(TimeInForce In)
{
	switch (In)
	{
	case TimeInForce::IOC:
		return DFITC_SP_FAK;
	case TimeInForce::FOK:
		return DFITC_SP_FOK;
	default:
		return DFITC_SP_NON;
	}
}

OrderStatus DFITCOrderRtnField_2_OrderStatus(DFITCOrderRtnField* pIn)
{
	//switch (In)
	//{
	//case DFITC_SPD_CANCELED:	// ��������Ǳ��ܾ��ˣ�
	//	return OrderStatus::Cancelled;
	//case DFITC_SPD_FILLED:
	//	return OrderStatus::Filled;
	//case DFITC_SPD_IN_QUEUE:
	//	return OrderStatus::Filled;
	//case DFITC_SPD_FILLED:
	//	return OrderStatus::Filled;
	//case DFITC_SPD_FILLED:
	//	return OrderStatus::Filled;
	//case DFITC_SPD_FILLED:
	//	return OrderStatus::Filled;
	//case DFITC_SPD_FILLED:
	//	return OrderStatus::Filled;
	//case DFITC_SPD_FILLED:
	//	return OrderStatus::Filled;
	//default:
	//	break;
	//}
	return OrderStatus::Filled;
}

OrderType DFITCOrderRtnField_2_OrderType(DFITCOrderRtnField* pIn)
{
	return OrderType::Limit;
}

TimeInForce DFITCOrderRtnField_2_TimeInForce(DFITCOrderRtnField* pIn)
{
	return TimeInForce::Day;
}

ExecType DFITCOrderRtnField_2_ExecType(DFITCOrderRtnField* pIn)
{
	return ExecType::ExecNew;
}
//OrderStatus DFITCOrderRtnField_2_OrderStatus(DFITCOrderRtnField* pIn)
//{
//	switch (pIn->OrderStatus)
//	{
//	case THOST_FTDC_OST_Canceled:
//		if (pIn->OrderSubmitStatus == THOST_FTDC_OSS_InsertRejected)
//			return OrderStatus::Rejected;
//		return OrderStatus::Cancelled;
//	case THOST_FTDC_OST_Unknown:
//		// ����ǳ�����Ҳ�п��ܳ�����һ������ι��ˣ�
//		if (pIn->OrderSubmitStatus == THOST_FTDC_OSS_InsertSubmitted)
//			return OrderStatus::New;
//	default:
//		if (pIn->VolumeTotal == 0)
//			return OrderStatus::Filled;
//		else if (pIn->VolumeTotal == pIn->VolumeTotalOriginal)
//			return OrderStatus::New;
//		else
//			return OrderStatus::PartiallyFilled;
//	}
//}
//
//OrderType DFITCOrderRtnField_2_OrderType(DFITCOrderRtnField* pIn)
//{
//	switch (pIn->OrderPriceType)
//	{
//	case THOST_FTDC_OPT_AnyPrice:
//		return OrderType::Market;
//	case THOST_FTDC_OPT_LimitPrice:
//		return OrderType::Limit;
//	default:
//		return OrderType::Limit;
//	}
//}
//
//TimeInForce DFITCOrderRtnField_2_TimeInForce(DFITCOrderRtnField* pIn)
//{
//	switch (pIn->TimeCondition)
//	{
//	case THOST_FTDC_TC_GFD:
//		return TimeInForce::Day;
//	case THOST_FTDC_TC_IOC:
//		switch (pIn->VolumeCondition)
//		{
//		case THOST_FTDC_VC_AV:
//			return TimeInForce::IOC;
//		case THOST_FTDC_VC_CV:
//			return TimeInForce::FOK;
//		default:
//			return TimeInForce::IOC;
//		}
//	default:
//		return TimeInForce::Day;
//	}
//}
//
//ExecType DFITCOrderRtnField_2_ExecType(DFITCOrderRtnField* pIn)
//{
//	switch (pIn->OrderStatus)
//	{
//	case THOST_FTDC_OST_Canceled:
//		if (pIn->OrderSubmitStatus == THOST_FTDC_OSS_InsertRejected)
//			return ExecType::ExecRejected;
//		return ExecType::ExecCancelled;
//	case THOST_FTDC_OST_Unknown:
//		// ����ǳ�����Ҳ�п��ܳ�����һ������ι��ˣ�
//		if (pIn->OrderSubmitStatus == THOST_FTDC_OSS_InsertSubmitted)
//			return ExecType::ExecNew;
//	case THOST_FTDC_OST_AllTraded:
//	case THOST_FTDC_OST_PartTradedQueueing:
//		return ExecType::ExecTrade;
//	default:
//		return ExecType::ExecNew;
//	}
//}
//
InstrumentType DFITCInstrumentTypeType_2_InstrumentType(DFITCInstrumentTypeType In)
{
	switch (In)
	{
	case DFITC_COMM_TYPE:
		return InstrumentType::Future;
	case DFITC_OPT_TYPE:
		return InstrumentType::Option;
	default:
		return InstrumentType::Future;
	}
}