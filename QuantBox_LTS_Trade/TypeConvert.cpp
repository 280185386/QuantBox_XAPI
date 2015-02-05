#include "stdafx.h"
#include "TypeConvert.h"

#include <stdlib.h>

#include <string.h>
/// ������OpenQuant FIXһ����Ч���������򵥣�������Ҫ����ô�������
/// ����һ�����ӵ�ĳ��״̬�����������ģ��µ������ֳɽ�����ȫ�ɽ�
/// EmitAccept,EmitFill
/// OnRtnOrder,OnRtnTrade,���ת��Emit
/// EmitAccept��ʲô
///
/// �ӿ������ṩ�Ļر����Է����ַ�����ExecutionReport��ί�лر���ɽ��ر�
/// OpenQuant��ʹ��ExecutionReport��������ΪOQ�Լ���OrderManager������������Ҫ����ί�кͳɽ��б���û���õ���
/// ���Խӿ�Ӧ������ί����ɽ��ر�


HedgeFlagType TSecurityFtdcHedgeFlagType_2_HedgeFlagType(TSecurityFtdcHedgeFlagType In)
{
	switch (In)
	{
	//case SECURITY_FTDC_HF_Arbitrage:
	//	return HedgeFlagType::Arbitrage;
	case SECURITY_FTDC_HF_Hedge:
		return HedgeFlagType::Hedge;
	case SECURITY_FTDC_HF_Speculation:
	default:
		return HedgeFlagType::Speculation;
	}
}

TSecurityFtdcHedgeFlagType HedgeFlagType_2_TSecurityFtdcHedgeFlagType(HedgeFlagType In)
{
	switch (In)
	{
	//case HedgeFlagType::Arbitrage:
	//	return SECURITY_FTDC_HF_Arbitrage;
	case HedgeFlagType::Hedge:
		return SECURITY_FTDC_HF_Hedge;
	case HedgeFlagType::Speculation:
	default:
		return SECURITY_FTDC_HF_Speculation;
	}
}

OpenCloseType TSecurityFtdcOffsetFlagType_2_OpenCloseType(TSecurityFtdcOffsetFlagType In)
{
	switch (In)
	{
	case SECURITY_FTDC_OF_CloseToday:
		return OpenCloseType::CloseToday;
	case SECURITY_FTDC_OF_Close:
		return OpenCloseType::Close;
	case SECURITY_FTDC_OF_Open:
	default:
		return OpenCloseType::Open;
	}
}

TSecurityFtdcOffsetFlagType OpenCloseType_2_TSecurityFtdcOffsetFlagType(OpenCloseType In)
{
	switch (In)
	{
	case OpenCloseType::CloseToday:
		return SECURITY_FTDC_OF_CloseToday;
	case OpenCloseType::Close:
		return SECURITY_FTDC_OF_Close;
	case OpenCloseType::Open:
	default:
		return SECURITY_FTDC_OF_Open;
	}
}

TSecurityFtdcDirectionType OrderSide_2_TSecurityFtdcDirectionType(OrderSide In)
{
	if (In == OrderSide::Sell)
		return SECURITY_FTDC_D_Sell;
	return SECURITY_FTDC_D_Buy;
}

OrderSide TSecurityFtdcDirectionType_2_OrderSide(TSecurityFtdcDirectionType In)
{
	if (In == SECURITY_FTDC_D_Sell)
		return OrderSide::Sell;
	return OrderSide::Buy;
}

PositionSide TSecurityFtdcPosiDirectionType_2_PositionSide(TSecurityFtdcPosiDirectionType In)
{
	if (In == SECURITY_FTDC_PD_Short)
		return PositionSide::Short;
	return PositionSide::Long;
}

PositionSide TradeField_2_PositionSide(TradeField* pIn)
{
	//if (pIn->OpenClose == OpenCloseType::Open)
	//{
	//	if (pIn->Side == OrderSide::Buy)
	//		return PositionSide::Long;
	//	return PositionSide::Short;
	//}
	//else
	//{
	//	if (pIn->Side == OrderSide::Buy)
	//		return PositionSide::Short;
	//	return PositionSide::Long;
	//}
	return PositionSide::Long;
}

TSecurityFtdcOrderPriceTypeType OrderType_2_TSecurityFtdcOrderPriceTypeType(OrderType In)
{
	switch (In)
	{
	case Market:
		return SECURITY_FTDC_OPT_AnyPrice;
	case Stop:
		return SECURITY_FTDC_OPT_AnyPrice;
	case Limit:
		return SECURITY_FTDC_OPT_LimitPrice;
	case StopLimit:
		return SECURITY_FTDC_OPT_LimitPrice;
	case MarketOnClose:
		return SECURITY_FTDC_OPT_AnyPrice;
	case TrailingStop:
		return SECURITY_FTDC_OPT_AnyPrice;
	case TrailingStopLimit:
		return SECURITY_FTDC_OPT_LimitPrice;
	default:
		return SECURITY_FTDC_OPT_LimitPrice;
	}
}

OrderStatus CSecurityFtdcOrderField_2_OrderStatus(CSecurityFtdcOrderField* pIn)
{
	switch (pIn->OrderStatus)
	{
	case SECURITY_FTDC_OST_Canceled:
		if (pIn->OrderSubmitStatus == SECURITY_FTDC_OSS_InsertRejected)
			return OrderStatus::Rejected;
		return OrderStatus::Cancelled;
	case SECURITY_FTDC_OST_Unknown:
		// ����ǳ�����Ҳ�п��ܳ�����һ������ι��ˣ�
		if (pIn->OrderSubmitStatus == SECURITY_FTDC_OSS_InsertSubmitted)
			return OrderStatus::New;
	default:
		if (pIn->VolumeTotal == 0)
			return OrderStatus::Filled;
		else if (pIn->VolumeTotal == pIn->VolumeTotalOriginal)
			return OrderStatus::New;
		else
			return OrderStatus::PartiallyFilled;
	}
}

OrderType CSecurityFtdcOrderField_2_OrderType(CSecurityFtdcOrderField* pIn)
{
	switch (pIn->OrderPriceType)
	{
	case SECURITY_FTDC_OPT_AnyPrice:
		return OrderType::Market;
	case SECURITY_FTDC_OPT_LimitPrice:
		return OrderType::Limit;
	default:
		return OrderType::Limit;
	}
}

TimeInForce CSecurityFtdcOrderField_2_TimeInForce(CSecurityFtdcOrderField* pIn)
{
	switch (pIn->TimeCondition)
	{
	case SECURITY_FTDC_TC_GFD:
		return TimeInForce::Day;
	case SECURITY_FTDC_TC_IOC:
		switch (pIn->VolumeCondition)
		{
		case SECURITY_FTDC_VC_AV:
			return TimeInForce::IOC;
		case SECURITY_FTDC_VC_CV:
			return TimeInForce::FOK;
		default:
			return TimeInForce::IOC;
		}
	default:
		return TimeInForce::Day;
	}
}

ExecType CSecurityFtdcOrderField_2_ExecType(CSecurityFtdcOrderField* pIn)
{
	switch (pIn->OrderStatus)
	{
	case SECURITY_FTDC_OST_Canceled:
		if (pIn->OrderSubmitStatus == SECURITY_FTDC_OSS_InsertRejected)
			return ExecType::ExecRejected;
		return ExecType::ExecCancelled;
	case SECURITY_FTDC_OST_Unknown:
		// ����ǳ�����Ҳ�п��ܳ�����һ������ι��ˣ�
		if (pIn->OrderSubmitStatus == SECURITY_FTDC_OSS_InsertSubmitted)
			return ExecType::ExecNew;
	case SECURITY_FTDC_OST_AllTraded:
	case SECURITY_FTDC_OST_PartTradedQueueing:
		return ExecType::ExecTrade;
	default:
		return ExecType::ExecNew;
	}
}

PutCall CSecurityFtdcInstrumentField_2_PutCall(CSecurityFtdcInstrumentField* pIn)
{
	if (strlen(pIn->InstrumentID) == 8)
	{
		if (pIn->ExchangeInstID[6] == 'C')
		{
			return PutCall::Call;
		}
	}
	return PutCall::Put;
}

// �Ϻ�֤ȯ������֤ȯ����������
// http://wenku.baidu.com/link?url=fhnAW62VTXqHTn8p9xlyXKa_oDIfR2xIxBF3y_fryeoFnz7MFbeWJbMLx4n1H61ERFnhr6PtaxF_j01x8iIT0wArZzrBtABRysi-KEpBa9S
InstrumentType CSecurityFtdcInstrumentField_2_InstrumentType_SSE(CSecurityFtdcInstrumentField* pIn)
{
	// ֻ��6λ��8λ����Ȩ�Ѿ���ǰ����
	int prefix1 = atoi(pIn->InstrumentID) / 100000;
	int prefix3 = atoi(pIn->InstrumentID) / 1000;
	switch (prefix1)
	{
	case 0:
		switch (prefix3)
		{
		case 0:
			return InstrumentType::Index;
		case 9:
		case 10:
		case 90:
		case 99:
			return InstrumentType::Bond;
		default:
			return InstrumentType::Index;
		}
	case 1:
		return InstrumentType::Bond;
	case 2:
		return InstrumentType::Bond;
	case 3:
		return InstrumentType::Future;
	case 5:
		switch (prefix3)
		{
		case 500:
		case 510:
		case 519:
		case 521:
		case 522:
		case 523:
		case 524:
			return InstrumentType::ETF;
		case 580:
		case 582:
			return InstrumentType::Option;
		default:
			return InstrumentType::ETF;
		}
	case 6:
		return InstrumentType::Stock;
	case 9:
		return InstrumentType::Stock;
	default:
		return InstrumentType::Synthetic;
	}
}

// ����֤ȯ������֤ȯ������뷽��
// http://wenku.baidu.com/view/e41fba85ec3a87c24028c416.html
InstrumentType CSecurityFtdcInstrumentField_2_InstrumentType_SZE(CSecurityFtdcInstrumentField* pIn)
{
	// ֻ��6λ��ȡǰ2
	int prefix1 = atoi(pIn->InstrumentID) / 100000;
	int prefix2 = atoi(pIn->InstrumentID) / 10000;
	switch (prefix2)
	{
	case 0:
	case 7:
	case 9:
		return InstrumentType::Stock;
	case 3:
	case 8:
		return InstrumentType::Option;
	case 10:
	case 11:
	case 12:
	case 13:
		return InstrumentType::Bond;
	case 17:
	case 18:
		return InstrumentType::ETF;
	case 20:
	case 30:
		return InstrumentType::Stock;
	case 27:
	case 37:
		return InstrumentType::Stock;
	case 28:
	case 38:
		return InstrumentType::Option;
	case 39:
		return InstrumentType::Index;
	default:
		return InstrumentType::Synthetic;
	}
}

InstrumentType CSecurityFtdcInstrumentField_2_InstrumentType(CSecurityFtdcInstrumentField* pIn)
{
	switch (pIn->ProductClass)
	{
	case SECURITY_FTDC_PC_Futures:
		return InstrumentType::Future;
	case SECURITY_FTDC_PC_Options:
		return InstrumentType::Option;
	case SECURITY_FTDC_PC_Combination:
		return InstrumentType::MultiLeg;
	case SECURITY_FTDC_PC_EFP:
		return InstrumentType::Future;
	case SECURITY_FTDC_PC_ETF:
		return InstrumentType::ETF;
	case SECURITY_FTDC_PC_ETFPurRed:
		return InstrumentType::ETF;
	default:
		if (strlen(pIn->InstrumentID) == 8)
		{
			return InstrumentType::Option;
		}
		if (pIn->ExchangeID[1] == 'Z')
		{
			return CSecurityFtdcInstrumentField_2_InstrumentType_SZE(pIn);
		}
		else
		{
			return CSecurityFtdcInstrumentField_2_InstrumentType_SSE(pIn);
		}
	}
}

PriceType CSecurityFtdcInstrumentField_2_PriceTick_SSE(CSecurityFtdcInstrumentField* pIn)
{
	// ֻ��6λ��8λ����Ȩ�Ѿ���ǰ����
	int prefix1 = atoi(pIn->InstrumentID) / 100000;
	int prefix3 = atoi(pIn->InstrumentID) / 1000;
	switch (prefix1)
	{
	case 0:
		return 0.01;
	case 1:
		return 0.01;
	case 2:
		return 0.001;
	case 3:
		return 0.01;
	case 5:
		return 0.001;
	case 6:
		return 0.01;
	case 9:
		return 0.001;
	default:
		return 0.01;
	}

	return 0.01;
}

PriceType CSecurityFtdcInstrumentField_2_PriceTick_SZE(CSecurityFtdcInstrumentField* pIn)
{
	// ֻ��6λ��ȡǰ2
	int prefix1 = atoi(pIn->InstrumentID) / 100000;
	int prefix2 = atoi(pIn->InstrumentID) / 10000;
	switch (prefix2)
	{
	case 0:
	case 7:
	case 9:
		return 0.01;
	case 3:
	case 8:
		return 0.001;
	case 10:
	case 11:
	case 12:
	case 13:
		return 0.001;
	case 17:
	case 18:
		return 0.001;
	case 20:
	case 30:
		return 0.01;
	case 27:
	case 37:
		return 0.01;
	case 28:
	case 38:
		return 0.001;
	case 39:
		return 0.01;
	default:
		return 0.01;
	}
}

PriceType CSecurityFtdcInstrumentField_2_PriceTick(CSecurityFtdcInstrumentField* pIn)
{
	if (pIn->PriceTick != 0)
		return pIn->PriceTick;

	// ��ȨΪ0.001
	if (strlen(pIn->InstrumentID) == 8)
	{
		return 0.001;
	}

	if (pIn->ExchangeID[1] == 'Z')
	{
		return CSecurityFtdcInstrumentField_2_PriceTick_SZE(pIn);
	}
	else
	{
		return CSecurityFtdcInstrumentField_2_PriceTick_SSE(pIn);
	}
}

IdCardType TSecurityFtdcIdCardTypeType_2_IdCardType(TSecurityFtdcIdCardTypeType In)
{
	switch (In)
	{
	case SECURITY_FTDC_ICT_EID:
		return IdCardType::EID;
	case SECURITY_FTDC_ICT_IDCard:
		return IdCardType::IDCard;
	case SECURITY_FTDC_ICT_OfficerIDCard:
		return IdCardType::OfficerIDCard;
	case SECURITY_FTDC_ICT_PoliceIDCard:
		return IdCardType::PoliceIDCard;
	case SECURITY_FTDC_ICT_SoldierIDCard:
		return IdCardType::SoldierIDCard;
	case SECURITY_FTDC_ICT_HouseholdRegister:
		return IdCardType::HouseholdRegister;
	case SECURITY_FTDC_ICT_Passport:
		return IdCardType::Passport;
	case SECURITY_FTDC_ICT_TaiwanCompatriotIDCard:
		return IdCardType::TaiwanCompatriotIDCard;
	case SECURITY_FTDC_ICT_HomeComingCard:
		return IdCardType::HomeComingCard;
	case SECURITY_FTDC_ICT_LicenseNo:
		return IdCardType::LicenseNo;
	case SECURITY_FTDC_ICT_TaxNo:
		return IdCardType::TaxNo;
	case SECURITY_FTDC_ICT_OtherCard:
	default:
		return IdCardType::OtherCard;
	}
}
