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
 * @version 0.5
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#include "v2g_serviceMethods.h"
#include "v2g_serviceDataTypes.h"
#include <stdio.h>

int	sessionSetup(struct MessageHeaderType* header, struct SessionSetupReqType* param, struct SessionSetupResType* result)
{

	printf("EVSE: sessionSetup called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t Header SessionID=%d\n",header->SessionInformation.SessionID.data[0]);
	printf("\t\t PEVID=%d\n",param->PEVID.data[0]);

	header->SessionInformation.SessionID.data[0] = 10;
	header->SessionInformation.SessionID.arraylen.data=1;

	/* Prepare data for PEV */
	result->ResponseCode = OK_responseCodeType;
	result->EVSEID.data[0]=1;
	result->EVSEID.arraylen.data=1;
	result->TCurrent=12345678;

	return 0;

}

int	serviceDiscovery(struct MessageHeaderType* header, struct ServiceDiscoveryReqType* param, struct ServiceDiscoveryResType* result)
{
	printf("EVSE: serviceDiscovery called\n"  );
	printf("\tReceived data:\n");

	printf("\t\t ServiceType=%d\n", param->ServiceType);

	result->isused.ServiceList=0;
	result->ResponseCode= OK_responseCodeType;
	result->ChargeService.ServiceTag.ServiceID.data[0]=1;
	result->ChargeService.ServiceTag.ServiceID.arraylen.data=1;

	result->ChargeService.ServiceTag.isused.ServiceName=0;
	result->ChargeService.ServiceTag.isused.ServiceCategory=0;
	result->ChargeService.ServiceTag.isused.ServiceScope=0;

	result->ChargeService.FreeService = 1;
	result->PaymentOptions.PaymentOption[0] = ExternalPayment_paymentOptionType; /* only free of charge yet ;-) */
	result->PaymentOptions.arraylen.PaymentOption=1;
	result->ChargeService.EnergyTransferType = DC_core_EVSESupportedEnergyTransferType;

	result->isused.ServiceList=0;

	return 0;
}

int	selectedServicePayment(struct MessageHeaderType* header, struct ServicePaymentSelectionReqType* param, struct ServicePaymentSelectionResType* result)
{
	return 0;
}

int	paymentDetails(struct MessageHeaderType* header, struct PaymentDetailsReqType* param, struct PaymentDetailsResType* result)
{
	return 0;
}

int	chargeParameterDiscovery(struct MessageHeaderType* header, struct ChargeParameterDiscoveryReqType* param, struct ChargeParameterDiscoveryResType* result)
{
	struct FloatingValueType f;

	printf("EVSE: chargeParameterDiscovery called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVRequestedEnergyTransferType=%d\n",param->PEVRequestedEnergyTransferType);

	/* check,if DC or AC is requested */
	if(param->PEVRequestedEnergyTransferType==DC_core_PEVRequestedEnergyTransferType || param->isused.DC_PEVChargeParameter==1)
	{

		printf("\t\t PEVStatus:\n\t\t\t PEVStandby=%d\n",param->DC_PEVChargeParameter->DC_PEVStatus.PEVStandby);
		printf("\t\t\t PEVReady=%d\n", param->DC_PEVChargeParameter->DC_PEVStatus.PEVReady);
		printf("\t\t\t PEVRESSSOC=%d\n", param->DC_PEVChargeParameter->DC_PEVStatus.PEVRESSSOC);
		printf("\t\t\t PEVStatusCode=%d\n", param->DC_PEVChargeParameter->DC_PEVStatus.PEVStatusCode);
		printf("\t\t\t ConnectorLocked=%d\n", param->DC_PEVChargeParameter->DC_PEVStatus.ConnectorLocked);

		printf("\t\t PEVMaximumCurrentLimit=%d\n", param->DC_PEVChargeParameter->PEVMaximumCurrentLimit.Value);
		printf("\t\t PEVMaximumPowerLimit=%d\n", param->DC_PEVChargeParameter->PEVMaximumPowerLimit.Value);
		printf("\t\t PEVMaximumVoltageLimit=%d\n", param->DC_PEVChargeParameter->PEVMaximumVoltageLimit.Value);
		printf("\t\t PEVEnergyCapacity=%d\n", param->DC_PEVChargeParameter->PEVEnergyCapacity.Value);
		printf("\t\t PEVEnergyRequest=%d\n", param->DC_PEVChargeParameter->PEVEnergyRequest.Value);
		printf("\t\t FullSOC=%d\n", param->DC_PEVChargeParameter->FullSOC);
		printf("\t\t BulkSOC=%d\n", param->DC_PEVChargeParameter->BulkSOC);
		printf("\t\t PEVProtocolVersion=%d\n", param->DC_PEVChargeParameter->PEVProtocolVersion);

		result->ResponseCode = OK_responseCodeType;
		result->isused.EnergyProvider=0;
		result->isused.TariffTable=0;


		result->isused.DC_EVSEChargeParameter = 1;
		result->isused.AC_EVSEChargeParameter = 0;
		result->DC_EVSEChargeParameter->DC_EVSEStatus.EVSEStandby = 1;
		result->DC_EVSEChargeParameter->DC_EVSEStatus.EVSEStatusCode = IsolationMonitoringActive_DC_EVSEStatusCodeType;

		f.Multiplier = 0;
		f.Unit = A_unitSymbolType;
		f.Value = 100;

		result->DC_EVSEChargeParameter->EVSEMaximumCurrentLimit=f;

		f.Unit = W_unitSymbolType;
		f.Value = 200;

		result->DC_EVSEChargeParameter->EVSEMaximumPowerLimit=f;
		result->DC_EVSEChargeParameter->isused.EVSEMaximumPowerLimit=1;

		f.Unit = V_unitSymbolType;
		f.Value = 300;

		result->DC_EVSEChargeParameter->EVSEMaximumVoltageLimit=f;

		f.Unit = A_unitSymbolType;
		f.Value = 400;

		result->DC_EVSEChargeParameter->EVSEMinimumCurrentLimit=f;

		f.Unit = V_unitSymbolType;
		f.Value = 500;

		result->DC_EVSEChargeParameter->EVSEMinimumVoltageLimit=f;

		f.Unit = A_unitSymbolType;
		f.Value = 600;

		result->DC_EVSEChargeParameter->EVSECurrentRegulationTolerance=f;
		result->DC_EVSEChargeParameter->isused.EVSECurrentRegulationTolerance=1;

		f.Unit = V_unitSymbolType;
		f.Value = 700;

		result->DC_EVSEChargeParameter->EVSEPeakCurrentRipple=f;

		f.Unit = A_unitSymbolType;
		f.Value = 800;

		result->DC_EVSEChargeParameter->EVSEEnergyToBeDelivered=f;
		result->DC_EVSEChargeParameter->isused.EVSEEnergyToBeDelivered=1;

		result->DC_EVSEChargeParameter->EVSEProtocolVersion=12;

	} else { /* AC related */

		printf("\t\t PEVStatus:\n\t\t\t PEVStandby=%d\n",param->AC_PEVChargeParameter->AC_PEVStatus.PEVStandby);
		printf("\t\t\t ConnectorLocked=%d\n", param->AC_PEVChargeParameter->AC_PEVStatus.ConnectorLocked);


		printf("\t\t EAmount=%d\n", param->AC_PEVChargeParameter->EAmount.Value);
		printf("\t\t EoC=%d\n", param->AC_PEVChargeParameter->EoC);
		printf("\t\t PEVMaxCurrent=%d\n", param->AC_PEVChargeParameter->PEVMaxCurrent.Value);
		printf("\t\t PEVMaxPhases=%d\n", param->AC_PEVChargeParameter->PEVMaxPhases);
		printf("\t\t PEVMaxPower=%d\n", param->AC_PEVChargeParameter->PEVMaxPower.Value);
		printf("\t\t PEVMaxVoltage=%d\n", param->AC_PEVChargeParameter->PEVMaxVoltage.Value);
		printf("\t\t PEVMinCurrent=%d\n", param->AC_PEVChargeParameter->PEVMinCurrent.Value);
		printf("\t\t PEVMinVoltage=%d\n", param->AC_PEVChargeParameter->PEVMinVoltage.Value);


		result->ResponseCode = OK_responseCodeType;
		result->isused.EnergyProvider=0;
		result->isused.TariffTable=0;


		result->isused.AC_EVSEChargeParameter = 1;
		result->isused.DC_EVSEChargeParameter = 0;




		result->AC_EVSEChargeParameter->AC_EVSEStatus.ConnectorLocked=1;
		result->AC_EVSEChargeParameter->AC_EVSEStatus.EVSEStandby=1;
		result->AC_EVSEChargeParameter->AC_EVSEStatus.PowerSwitchClosed=1;
		result->AC_EVSEChargeParameter->AC_EVSEStatus.RCD=1;
		result->AC_EVSEChargeParameter->AC_EVSEStatus.ShutDownTime=12345;
		result->AC_EVSEChargeParameter->AC_EVSEStatus.StopCharging=1;


		f.Multiplier = 0;
		f.Unit = A_unitSymbolType;
		f.Value = 100;

		result->AC_EVSEChargeParameter->EVSEMaxCurrent=f;
		result->AC_EVSEChargeParameter->EVSEMaxPhases=3;

		f.Unit = V_unitSymbolType;
		f.Value = 200;
		result->AC_EVSEChargeParameter->EVSEMaxVoltage=f;

		f.Unit = A_unitSymbolType;
		f.Value = 300;
		result->AC_EVSEChargeParameter->EVSEMinCurrent=f;

		f.Unit = V_unitSymbolType;
		f.Value = 400;
		result->AC_EVSEChargeParameter->EVSEMinVoltage=f;

	}



	return 0;
}

int	lineLock(struct MessageHeaderType* header, struct LineLockReqType* param, struct LineLockResType* result)
{
	printf("EVSE: lineLock called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t PEVStandby=%d\n",param->AC_PEVStatus.PEVStandby);
	printf("\t\t\t ConnectorLocked=%d\n", param->AC_PEVStatus.ConnectorLocked);
	printf("\t\t ReqLockStatus=%d\n", param->ReqLockStatus);


	result->ResponseCode = OK_responseCodeType;
	result->AC_EVSEStatus.ConnectorLocked=1;
	result->AC_EVSEStatus.EVSEStandby=1;
	result->AC_EVSEStatus.PowerSwitchClosed=1;
	result->AC_EVSEStatus.RCD=1;
	result->AC_EVSEStatus.ShutDownTime=12345;
	result->AC_EVSEStatus.StopCharging=1;


	return 0;
}

int	powerDelivery(struct MessageHeaderType* header, struct PowerDeliveryReqType* param, struct PowerDeliveryResType* result)
{
	printf("EVSE: powerDelivery called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t\t ReqSwitchStatus=%d\n", param->ReqSwitchStatus);


	if(param->isused.DC_PEVPowerDeliveryParameter)
	{

		printf("\t\t PEVStatus:\n\t\t\t PEVStandby=%d\n",param->DC_PEVPowerDeliveryParameter->DC_PEVStatus.PEVStandby);
		printf("\t\t\t PEVReady=%d\n", param->DC_PEVPowerDeliveryParameter->DC_PEVStatus.PEVReady);
		printf("\t\t\t PEVRESSSOC=%d\n", param->DC_PEVPowerDeliveryParameter->DC_PEVStatus.PEVRESSSOC);
		printf("\t\t\t PEVStatusCode=%d\n", param->DC_PEVPowerDeliveryParameter->DC_PEVStatus.PEVStatusCode);
		printf("\t\t\t ConnectorLocked=%d\n", param->DC_PEVPowerDeliveryParameter->DC_PEVStatus.ConnectorLocked);
		printf("\t\t BulkChargingComplete=%d\n", param->DC_PEVPowerDeliveryParameter->BulkChargingComplete);
		printf("\t\t ChargingComplete=%d\n", param->DC_PEVPowerDeliveryParameter->ChargingComplete);

		result->ResponseCode = FAILED_NotReady_responseCodeType;
		result->DC_EVSEStatus->EVSEStandby =1;
		result->DC_EVSEStatus->EVSEStatusCode = IsolationMonitoringActive_DC_EVSEStatusCodeType;
		result->isused.DC_EVSEStatus=1;
		result->isused.AC_EVSEStatus=0;
	} else {

		printf("\t\t PEVStatus:\n\t\t\t PEVStandby=%d\n",param->AC_PEVPowerDeliveryParameter->AC_PEVStatus.PEVStandby);
		printf("\t\t\t ConnectorLocked=%d\n", param->AC_PEVPowerDeliveryParameter->AC_PEVStatus.ConnectorLocked);


		result->ResponseCode = OK_responseCodeType;
		result->AC_EVSEStatus->ConnectorLocked=1;
		result->AC_EVSEStatus->EVSEStandby=1;
		result->AC_EVSEStatus->PowerSwitchClosed=1;
		result->AC_EVSEStatus->RCD=1;
		result->AC_EVSEStatus->ShutDownTime=12345;
		result->AC_EVSEStatus->StopCharging=1;


		result->isused.AC_EVSEStatus=1;
		result->isused.DC_EVSEStatus=0;
	}

	return 0;
}

int	meteringStatus(struct MessageHeaderType* header, struct MeteringStatusReqType* param, struct MeteringStatusResType* result)
{
	printf("EVSE: meteringStatus called\n"  );

	if(param->isused.AC_PEVStatus==1)
	{
		printf("\t\t PEVStatus:\n\t\t\t PEVStandby=%d\n",param->AC_PEVStatus->PEVStandby);
		printf("\t\t\t ConnectorLocked=%d\n", param->AC_PEVStatus->ConnectorLocked);
	}


	result->ResponseCode=OK_responseCodeType;
	result->EVSEID.data[0]=1;
	result->EVSEID.arraylen.data=1;
	result->isused.AC_EVSEStatus=1;
	result->isused.DC_EVSEStatus=0;
	result->AC_EVSEStatus->ConnectorLocked=1;
	result->AC_EVSEStatus->EVSEStandby=1;
	result->AC_EVSEStatus->PowerSwitchClosed=1;
	result->AC_EVSEStatus->RCD=1;
	result->AC_EVSEStatus->ShutDownTime=12345;
	result->AC_EVSEStatus->StopCharging=1;
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

int	meteringReceipt(struct MessageHeaderType* header, struct MeteringReceiptReqType* param, struct MeteringReceiptResType* result)
{

	printf("EVSE: meteringReceipt called\n"  );
	printf("\tReceived data:\n");

	if(param->isused.AC_PEVStatus)
	{
		printf("\t\t PEVStatus:\n\t\t\t PEVStandby=%d\n",param->AC_PEVStatus->PEVStandby);
		printf("\t\t\t ConnectorLocked=%d\n", param->AC_PEVStatus->ConnectorLocked);
	}

	printf("\t\t TCurrent=%d\n", param->TCurrent);
	printf("\t\t Tariff=%d\n", param->Tariff);
	printf("\t\t MeterInfo.MeterStatus=%d\n", param->MeterInfo.MeterStatus);
	printf("\t\t MeterInfo.MeterID=%d\n",		param->MeterInfo.MeterID.data[0]);
	printf("\t\t MeterInfo.isused.MeterReading=%d\n", param->MeterInfo.isused.MeterReading);
	printf("\t\t MeterReading.Value=%d\n",		param->MeterInfo.MeterReading.Value);
	printf("\t\t MeterInfo.TMeter=%d\n",		param->MeterInfo.TMeter);
	if(param->Tariff==12)
		printf("\t\t Tariff==Green_charge_tariffIDType\n");
	result->ResponseCode = 0;

	result->isused.AC_EVSEStatus=1;
	result->isused.DC_EVSEStatus=0;
	result->AC_EVSEStatus->ConnectorLocked=1;
	result->AC_EVSEStatus->EVSEStandby=1;
	result->AC_EVSEStatus->PowerSwitchClosed=1;
	result->AC_EVSEStatus->RCD=1;
	result->AC_EVSEStatus->ShutDownTime=12345;
	result->AC_EVSEStatus->StopCharging=1;

	return 0;
}

int	cableCheck(struct MessageHeaderType* header, struct CableCheckReqType* param, struct CableCheckResType* result)
{
	printf("EVSE: cableCheck called\n"  );
	printf("\tReceived data:\n");


	printf("\t\t PEVStatus:\n\t\t\t PEVStandby=%d\n",param->DC_PEVStatus.PEVStandby);
	printf("\t\t\t PEVReady=%d\n", param->DC_PEVStatus.PEVReady);
	printf("\t\t\t PEVRESSSOC=%d\n", param->DC_PEVStatus.PEVRESSSOC);
	printf("\t\t\t PEVStatusCode=%d\n", param->DC_PEVStatus.PEVStatusCode);
	printf("\t\t\t ConnectorLocked=%d\n", param->DC_PEVStatus.ConnectorLocked);

	result->ResponseCode = OK_responseCodeType;
	result->DC_EVSEStatus.EVSEStandby = 1;
	result->DC_EVSEStatus.EVSEStatusCode = IsolationMonitoringActive_DC_EVSEStatusCodeType;

	return 0;
}


int	preCharge(struct MessageHeaderType* header, struct PreChargeReqType* param, struct PreChargeResType* result)
{
	struct FloatingValueType float_type;


	printf("EVSE: preCharge called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t PEVStandby=%d\n",param->DC_PEVStatus.PEVStandby);
	printf("\t\t\t PEVReady=%d\n", param->DC_PEVStatus.PEVReady);
	printf("\t\t\t PEVRESSSOC=%d\n", param->DC_PEVStatus.PEVRESSSOC);
	printf("\t\t\t PEVStatusCode=%d\n", param->DC_PEVStatus.PEVStatusCode);
	printf("\t\t\t ConnectorLocked=%d\n", param->DC_PEVStatus.ConnectorLocked);

	result->ResponseCode = OK_responseCodeType;
	result->DC_EVSEStatus.EVSEStandby = 1;
	result->DC_EVSEStatus.EVSEStatusCode = IsolationMonitoringActive_DC_EVSEStatusCodeType;

	float_type.Multiplier = 0;
	float_type.Unit = V_unitSymbolType;
	float_type.Value = 100;
	result->EVSEPresentVoltage = float_type;




	return 0;


}

int	currentDemand(struct MessageHeaderType* header, struct CurrentDemandReqType* param, struct CurrentDemandResType* result)
{

	struct FloatingValueType f;

	printf("EVSE: currentDemand called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t PEVStandby=%d\n",param->DC_PEVStatus.PEVStandby);
	printf("\t\t\t PEVReady=%d\n", param->DC_PEVStatus.PEVReady);
	printf("\t\t\t PEVRESSSOC=%d\n", param->DC_PEVStatus.PEVRESSSOC);
	printf("\t\t\t PEVStatusCode=%d\n", param->DC_PEVStatus.PEVStatusCode);
	printf("\t\t\t ConnectorLocked=%d\n", param->DC_PEVStatus.ConnectorLocked);

	printf("\t\t ChargeCurrentRequest=%d\n", param->ChargeCurrentRequest.Value);
	printf("\t\t PEVMaximumVoltageLimit=%d\n", param->PEVMaximumVoltageLimit.Value);
	printf("\t\t PEVMaximumPowerLimit=%d\n", param->PEVMaximumPowerLimit.Value);
	printf("\t\t PEVMaximumCurrentLimit=%d\n", param->PEVMaximumCurrentLimit.Value);
	printf("\t\t BulkChargingComplete=%d\n", param->BulkChargingComplete);
	printf("\t\t ChargingComplete=%d\n", param->ChargingComplete);
	printf("\t\t RemainingTimeToFullSoC=%d\n", param->RemainingTimeToFullSoC.Value);
	printf("\t\t RemainingTimeToBulkSoC=%d\n", param->RemainingTimeToBulkSoC.Value);

	printf("\t\t PEVTargetVoltage=%d\n", param->PEVTargetVoltage.Value);
	printf("\t\t CurrentDifferential=%d\n", param->CurrentDifferential.Value);

	printf("\t\t VoltageDifferential=%d\n", param->VoltageDifferential.Value);


	result->ResponseCode = OK_responseCodeType;
	result->DC_EVSEStatus.EVSEStandby = 1;
	result->DC_EVSEStatus.EVSEStatusCode = IsolationMonitoringActive_DC_EVSEStatusCodeType;

	f.Multiplier = 0;
	f.Unit = V_unitSymbolType;
	f.Value = 100;

	result->EVSEPresentVoltage=f;

	f.Unit = A_unitSymbolType;
	f.Value = 200;

	result->EVSEPresentCurrent=f;

	result->EVSECurrentLimitAchieved=1;

	result->EVSEVoltageLimitAchieved=0;

	result->EVSEPowerLimitAchieved=1;

	f.Unit = V_unitSymbolType;
	f.Value = 300;

	result->EVSEMaximumVoltageLimit=f;
	result->isused.EVSEMaximumVoltageLimit=1;

	f.Unit = A_unitSymbolType;
	f.Value = 400;

	result->EVSEMaximumCurrentLimit=f;
	result->isused.EVSEMaximumCurrentLimit=1;

	f.Unit = W_unitSymbolType;
	f.Value = 500;

	result->EVSEMaximumPowerLimit=f;
	result->isused.EVSEMaximumPowerLimit=1;

	return 0;
}

int	weldingDetection(struct MessageHeaderType* header, struct WeldingDetectionReqType* param, struct WeldingDetectionResType* result)
{

	printf("EVSE: weldingDetection called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t PEVStandby=%d\n",param->DC_PEVStatus.PEVStandby);
	printf("\t\t\t PEVReady=%d\n", param->DC_PEVStatus.PEVReady);
	printf("\t\t\t PEVRESSSOC=%d\n", param->DC_PEVStatus.PEVRESSSOC);
	printf("\t\t\t PEVStatusCode=%d\n", param->DC_PEVStatus.PEVStatusCode);
	printf("\t\t\t ConnectorLocked=%d\n", param->DC_PEVStatus.ConnectorLocked);

	result->ResponseCode = OK_responseCodeType;
	result->DC_EVSEStatus.EVSEStandby = 1;
	result->DC_EVSEStatus.EVSEStatusCode = IsolationMonitoringActive_DC_EVSEStatusCodeType;
	result->EVSEPresentVoltage.Value = 123;
	result->EVSEPresentVoltage.Unit = V_unitSymbolType;
	result->EVSEPresentVoltage.Multiplier = 0;

	return 0;
}

int	terminateCharging(struct MessageHeaderType* header, struct TerminateChargingReqType* param, struct TerminateChargingResType* result)
{

	printf("EVSE: terminateCharging called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t PEVStatus:\n\t\t\t PEVStandby=%d\n",param->DC_PEVStatus.PEVStandby);
	printf("\t\t\t PEVReady=%d\n", param->DC_PEVStatus.PEVReady);
	printf("\t\t\t PEVRESSSOC=%d\n", param->DC_PEVStatus.PEVRESSSOC);
	printf("\t\t\t PEVStatusCode=%d\n", param->DC_PEVStatus.PEVStatusCode);
	printf("\t\t\t ConnectorLocked=%d\n", param->DC_PEVStatus.ConnectorLocked);


	result->ResponseCode = OK_responseCodeType;
	result->EVSEPresentVoltage.Value = 123;
	result->EVSEPresentVoltage.Unit = V_unitSymbolType;
	result->EVSEPresentVoltage.Multiplier = 0;



	return 0;

}

int	serviceDetail(struct MessageHeaderType* header, struct ServiceDetailReqType* param, struct ServiceDetailResType* result)
{
	return 0;
}

int	contractAuthentication(struct MessageHeaderType* header, struct ContractAuthenticationReqType* param, struct ContractAuthenticationResType* result)
{
	return 0;
}

int	certificateUpdate(struct MessageHeaderType* header, struct CertificateUpdateReqType* param, struct CertificateUpdateResType* result)
{
	return 0;
}

int	certificateInstallation(struct MessageHeaderType* header, struct CertificateInstallationReqType* param, struct CertificateInstallationResType* result)
{

	printf("EVSE: certificateInstallation called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t\t OEMProvisioningCert=%d\n", param->OEMProvisioningCert.data[0]);

	return 0;
}




