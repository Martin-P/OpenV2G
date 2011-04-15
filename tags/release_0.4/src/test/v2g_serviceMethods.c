/*
 * Copyright (C) 2007-2011 Siemens AG
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Sebastian.Kaebisch.EXT@siemens.com
 * @version 0.4
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#include "v2g_serviceMethods.h"
#include "v2g_serviceDataTypes.h"
#include <stdio.h>

/* This service methods has to be implemented by the EVSE server */

int	sessionSetup(struct SessionSetupReqType* param, struct SessionSetupResType* result)
{
	printf("EVSE: sessionSetup called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t ChargerStandby=%d\n",param->PEVStatus.ChargerStandby);
	printf("\t\t\t ConnectorLocked=%d\n", param->PEVStatus.ConnectorLocked);
	printf("\t\t\t ReadyToCharge=%d\n", param->PEVStatus.ReadyToCharge);

	/* Prepare data for PEV */
	result->ResponseCode = OK_SessionSetup_responseCode_SessionSetupType;
	result->EVSEID.data[0]=1;
	result->EVSEID.arraylen.data=1;
	result->EVSEStatus.ConnectorLocked=0;
	result->EVSEStatus.EVSEStandby=1;
	result->EVSEStatus.FatalError=0;
	result->EVSEStatus.PowerSwitchClosed=1;
	result->EVSEStatus.RCD=1;
	result->EVSEStatus.ShutDownTime=12345678;
	result->EVSEStatus.ChargerStandby = 1;
	result->EVSEStatus.EVSEMalfunction = 0;
	result->TCurrent=12345678;

	return 0;
}

int	serviceDiscovery(struct ServiceDiscoveryReqType* param, struct ServiceDiscoveryResType* result)
{
	return 0;
}

int	selectedServicePayment(struct ServicePaymentSelectionReqType* param, struct ServicePaymentSelectionResType* result)
{
	return 0;
}

int	paymentDetails(struct PaymentDetailsReqType* param, struct PaymentDetailsResType* result)
{
	return 0;
}

int	chargeParameterDiscovery(struct ChargeParameterDiscoveryReqType* param, struct ChargeParameterDiscoveryResType* result)
{
	printf("EVSE: chargeParameterDiscovery called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t ChargerStandby=%d\n",param->PEVStatus.ChargerStandby);
	printf("\t\t\t ConnectorLocked=%d\n", param->PEVStatus.ConnectorLocked);
	printf("\t\t\t ReadyToCharge=%d\n", param->PEVStatus.ReadyToCharge);

	if(param->ChargingMode==AC_charging_chargingModeType)
		printf("\t\t ChargingMode=AC_charging\n");
	else
		printf("\t\t ChargingMode=DC_charging\n");

	printf("\t\t Eoc=%d\n", param->EoC);
	printf("\t\t EAmount=%d\n", param->EAmount.Value);
	printf("\t\t PEVMaxPower=%d\n", param->PEVMaxPower.Value);
	printf("\t\t PEVMaxPhases=%d\n", param->PEVMaxPhases);
	printf("\t\t PEVMaxVoltage=%d\n", param->PEVMaxVoltage.Value);
	printf("\t\t PEVMinVoltage=%d\n", param->PEVMinVoltage.Value);


	if(param->ChargingMode==DC_charging_chargingModeType)
	{
		printf("\t\t PEVMaxCurrent=%d\n", param->PEVMaxCurrent.Value);
		printf("\t\t PEVMinCurrent=%d\n", param->PEVMinCurrent.Value);
	}

	result->ResponseCode = 0;
	result->EVSEStatus.ConnectorLocked=0;
	result->EVSEStatus.FatalError=0;
	result->EVSEStatus.EVSEStandby=1;
	result->EVSEStatus.PowerSwitchClosed=0;
	result->EVSEStatus.RCD=1;
	result->EVSEStatus.ShutDownTime=12345;
	result->EVSEStatus.ChargerStandby = 1;
	result->EVSEStatus.EVSEMalfunction = 0;
	result->EVSEMaxVoltage.Multiplier = 0;
	result->EVSEMaxVoltage.Unit = V_unitSymbolType;
	result->EVSEMaxVoltage.Value = 950;
	result->EVSEMaxPhases = 3;

	/* only for DC charging */
	result->EVSEMaxCurrent.Multiplier = 0;
	result->EVSEMaxCurrent.Unit = A_unitSymbolType;
	result->EVSEMaxCurrent.Value = 10;
	result->EVSEMinCurrent.Multiplier = 0;
	result->EVSEMinCurrent.Unit = A_unitSymbolType;
	result->EVSEMinCurrent.Value = 2;


	result->isused.EnergyProvider=0;
	/*result->EnergyProvider.arraylen.data=1;
	result->EnergyProvider.data[0]=11; */
	result->isused.TariffTable = 0;

	return 0;
}

int	lineLock(struct LineLockReqType* param, struct LineLockResType* result)
{
	printf("EVSE: lineLock called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t ChargerStandby=%d\n",param->PEVStatus.ChargerStandby);
	printf("\t\t\t ConnectorLocked=%d\n", param->PEVStatus.ConnectorLocked);
	printf("\t\t\t ReadyToCharge=%d\n", param->PEVStatus.ReadyToCharge);
	printf("\t\t ReqLockStatus=%d\n", param->ReqLockStatus);

	result->ResponseCode = 0;
	result->EVSEStatus.ConnectorLocked=0;
	result->EVSEStatus.FatalError=0;
	result->EVSEStatus.EVSEStandby=1;
	result->EVSEStatus.PowerSwitchClosed=1;
	result->EVSEStatus.RCD=1;
	result->EVSEStatus.ShutDownTime=12345;
	result->EVSEStatus.ChargerStandby = 1;
	result->EVSEStatus.EVSEMalfunction = 0;

	return 0;
}

int	powerDelivery(struct PowerDeliveryReqType* param, struct PowerDeliveryResType* result)
{
	printf("EVSE: powerDelivery called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t ChargerStandby=%d\n",param->PEVStatus.ChargerStandby);
	printf("\t\t\t ConnectorLocked=%d\n", param->PEVStatus.ConnectorLocked);
	printf("\t\t\t ReadyToCharge=%d\n", param->PEVStatus.ReadyToCharge);

	result->ResponseCode=0;
	result->EVSEStatus.ConnectorLocked=0;
	result->EVSEStatus.FatalError=0;
	result->EVSEStatus.EVSEStandby=1;
	result->EVSEStatus.PowerSwitchClosed=1;
	result->EVSEStatus.RCD=1;
	result->EVSEStatus.ShutDownTime=12345;
	result->EVSEStatus.ChargerStandby = 1;
	result->EVSEStatus.EVSEMalfunction = 0;

	return 0;
}

int	meteringStatus(struct MeteringStatusReqType* param, struct MeteringStatusResType* result)
{
	printf("EVSE: meteringStatus called\n"  );

	result->ResponseCode=1;
	result->EVSEID.data[0]=1;
	result->EVSEID.arraylen.data=1;
	result->EVSEStatus.ConnectorLocked=1;
	result->EVSEStatus.EVSEStandby=1;
	result->EVSEStatus.FatalError=0;
	result->EVSEStatus.PowerSwitchClosed=1;
	result->EVSEStatus.RCD=1;
	result->EVSEStatus.ShutDownTime=12345678;
	result->EVSEStatus.EVSEMalfunction = 0;
	result->EVSEStatus.ChargerStandby = 1;
	result->TCurrent=12345678;
	result->EVSEMaxPower.Multiplier = 2;
	result->EVSEMaxPower.Unit = A_unitSymbolType;
	result->EVSEMaxPower.Value = 400;

	result->isused.MeterInfo=1;
	result->MeterInfo.MeterID.arraylen.data=1;
	result->MeterInfo.MeterID.data[0]=2;
	result->MeterInfo.MeterReading.Multiplier = 0;
	result->MeterInfo.MeterReading.Unit = A_unitSymbolType;
	result->MeterInfo.MeterReading.Value = 500;
	result->MeterInfo.MeterStatus = 4321;
	result->MeterInfo.TMeter =123456789;
	result->MeterInfo.isused.MeterID=1;
	result->MeterInfo.isused.MeterReading = 1;
	result->MeterInfo.isused.MeterStatus=1;
	result->MeterInfo.isused.TMeter=1;

	result->isused.PCurrent=1;
	result->PCurrent.Value=4321;

	return 0;
}

int	meteringReceipt(struct MeteringReceiptReqType* param, struct MeteringReceiptResType* result)
{

	printf("EVSE: meteringReceipt called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t ChargerStandby=%d\n",param->PEVStatus.ChargerStandby);
	printf("\t\t\t ConnectorLocked=%d\n", param->PEVStatus.ConnectorLocked);
	printf("\t\t\t ReadyToCharge=%d\n", param->PEVStatus.ReadyToCharge);
	printf("\t\t TCurrent=%d\n", param->TCurrent);
	printf("\t\t MeterInfo.MeterStatus=%d\n", param->MeterInfo.MeterStatus);
	printf("\t\t MeterInfo.MeterID=%d\n",		param->MeterInfo.MeterID.data[0]);
	printf("\t\t MeterInfo.isused.MeterReading=%d\n", param->MeterInfo.isused.MeterReading);
	printf("\t\t MeterReading.Value=%d\n",		param->MeterInfo.MeterReading.Value);
	printf("\t\t MeterInfo.TMeter=%d\n",		param->MeterInfo.TMeter);
	if(param->Tariff==Green_charge_tariffIDType)
		printf("\t\t Tariff==Green_charge_tariffIDType\n");
	result->ResponseCode = 0;

	return 0;
}

int	cableCheck(struct CableCheckReqType* param, struct CableCheckResType* result)
{
	printf("EVSE: cableCheck called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t ChargerStandby=%d\n",param->PEVStatus.ChargerStandby);
	printf("\t\t\t ConnectorLocked=%d\n", param->PEVStatus.ConnectorLocked);
	printf("\t\t\t ReadyToCharge=%d\n", param->PEVStatus.ReadyToCharge);

	result->EVSEStatus.ConnectorLocked=1;
	result->EVSEStatus.EVSEStandby=1;
	result->EVSEStatus.FatalError=0;
	result->EVSEStatus.PowerSwitchClosed=1;
	result->EVSEStatus.RCD=1;
	result->EVSEStatus.ShutDownTime=12345678;
	result->EVSEStatus.EVSEMalfunction = 0;
	result->EVSEStatus.ChargerStandby = 1;

	result->ResponseCode = OK_responseCode_CableCheckType;

	return 0;
}


int	preCharge(struct PreChargeReqType* param, struct PreChargeResType* result)
{
	struct FloatingValueType float_type;
	float_type.Multiplier = 0;
	float_type.Unit = V_unitSymbolType;

	printf("EVSE: currentDemand called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t ChargerStandby=%d\n",param->PEVStatus.ChargerStandby);
	printf("\t\t\t ConnectorLocked=%d\n", param->PEVStatus.ConnectorLocked);
	printf("\t\t\t ReadyToCharge=%d\n", param->PEVStatus.ReadyToCharge);

	printf("\t\t PEVDemandCurrent=%d\n",param->PEVDemandCurrent.Value);
	printf("\t\t PEVTargetVoltage=%d\n", param->PEVTargetVoltage.Value);

	result->ResponseCode=OK_responseCode_CurrentDemandType;
	result->EVSEStatus.ConnectorLocked=1;
	result->EVSEStatus.EVSEStandby=1;
	result->EVSEStatus.FatalError=0;
	result->EVSEStatus.PowerSwitchClosed=1;
	result->EVSEStatus.RCD=1;
	result->EVSEStatus.ShutDownTime=12345678;
	result->EVSEStatus.ChargerStandby=1;
	result->EVSEStatus.EVSEMalfunction=0;
	result->EVSEStatus.StopCharging=0;

	float_type.Value = 800;

	result->EVSEPresentVoltage = float_type;


	return 0;


}

int	currentDemand(struct CurrentDemandReqType* param, struct CurrentDemandResType* result)
{
	struct FloatingValueType float_type;
	float_type.Multiplier = 0;

	printf("EVSE: currentDemand called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t ChargerStandby=%d\n",param->PEVStatus.ChargerStandby);
	printf("\t\t\t ConnectorLocked=%d\n", param->PEVStatus.ConnectorLocked);
	printf("\t\t\t ReadyToCharge=%d\n", param->PEVStatus.ReadyToCharge);

	printf("\t\t PEVDemandCurrent=%d\n",param->PEVDemandCurrent.Value);
	printf("\t\t PEVTargetVoltage=%d\n", param->PEVTargetVoltage.Value);

	result->EVSEStatus.ConnectorLocked=1;
	result->EVSEStatus.EVSEStandby=1;
	result->EVSEStatus.FatalError=0;
	result->EVSEStatus.PowerSwitchClosed=1;
	result->EVSEStatus.RCD=1;
	result->EVSEStatus.ShutDownTime=12345678;
	result->EVSEStatus.ChargerStandby=1;
	result->EVSEStatus.EVSEMalfunction=0;
	result->EVSEStatus.StopCharging=0;
	result->ResponseCode=OK_responseCode_CurrentDemandType;

	float_type.Unit = A_unitSymbolType;
	float_type.Value = 40;
	result->EVSEPresentCurrent = float_type;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 700;
	result->EVSEPresentVoltage = float_type;

	return 0;
}

int	weldingDetection(struct WeldingDetectionReqType* param, struct WeldingDetectionResType* result)
{
	struct FloatingValueType float_type;
	float_type.Multiplier = 0;
	float_type.Unit = V_unitSymbolType;
	float_type.Value = 0;

	printf("EVSE: weldingDetection called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t ChargerStandby=%d\n",param->PEVStatus.ChargerStandby);
	printf("\t\t\t ConnectorLocked=%d\n", param->PEVStatus.ConnectorLocked);
	printf("\t\t\t ReadyToCharge=%d\n", param->PEVStatus.ReadyToCharge);

	result->ResponseCode = OK_responseCode_WeldingDetectionType;

	result->EVSEStatus.ConnectorLocked=1;
	result->EVSEStatus.EVSEStandby=1;
	result->EVSEStatus.FatalError=0;
	result->EVSEStatus.PowerSwitchClosed=1;
	result->EVSEStatus.RCD=1;
	result->EVSEStatus.ShutDownTime=12345678;
	result->EVSEStatus.ChargerStandby=1;
	result->EVSEStatus.EVSEMalfunction=0;
	result->EVSEStatus.StopCharging=0;

	result->EVSEPresentVoltage=float_type;

	return 0;
}

int	terminateCharging(struct TerminateChargingReqType* param, struct TerminateChargingResType* result)
{
	struct FloatingValueType float_type;
	float_type.Multiplier = 	0;
	float_type.Unit = V_unitSymbolType;
	float_type.Value =0;

	printf("EVSE: terminateCharging called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t ChargerStandby=%d\n",param->PEVStatus.ChargerStandby);
	printf("\t\t\t ConnectorLocked=%d\n", param->PEVStatus.ConnectorLocked);
	printf("\t\t\t ReadyToCharge=%d\n", param->PEVStatus.ReadyToCharge);

	result->EVSEPresentVoltage = float_type;
	result->ResponseCode = OK_responseCode_TerminateChargingType;


	return 0;

}
