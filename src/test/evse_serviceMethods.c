/*
 * Copyright (C) 2007-2012 Siemens AG
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
 * @version 0.6
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#include "v2g_serviceMethods.h"
#include "v2g_serviceDataTypes.h"
#include <stdio.h>

static void printBinaryArray(uint8_t* byte, uint32_t len);

int	sessionSetup(struct MessageHeaderType* header, struct SessionSetupReqType* param, struct SessionSetupResType* result)
{

	printf("EVSE side: sessionSetup called\n"  );
	printf("\tReceived data:\n");
	printf("\tHeader SessionID=");
	printBinaryArray(header->SessionID.data,header->SessionID.arraylen.data );
	printf("\t\t EVCCID=%d\n",param->EVCCID.data[0]);

	/* generate an unique sessionID */
	header->SessionID.data[0] = 0;
	header->SessionID.data[1] = 0;
	header->SessionID.data[2] = 0;
	header->SessionID.data[3] = 0;
	header->SessionID.data[4] = 0;
	header->SessionID.data[5] = 0;
	header->SessionID.data[6] = 0;
	header->SessionID.data[7] = 10;
	header->SessionID.arraylen.data=8;

	/* Prepare data for EV */
	result->ResponseCode = OK_responseCodeType;
	result->EVSEID.data[0]=1;
	result->EVSEID.arraylen.data=1;
	result->DateTimeNow=123456789;
	result->isused.DateTimeNow=1;

	return 0;

}

int	serviceDiscovery(struct MessageHeaderType* header, struct ServiceDiscoveryReqType* param, struct ServiceDiscoveryResType* result)
{
	printf("EVSE side: serviceDiscovery called\n"  );
	printf("\tReceived data:\n");
	printf("\tHeader SessionID=");
	printBinaryArray(header->SessionID.data,header->SessionID.arraylen.data );

	printf("\t\t ServiceCategory=%d\n", param->ServiceCategory);

	result->isused.ServiceList=0; /* we do not provide VAS */
	result->ResponseCode= OK_responseCodeType;


	result->ChargeService.EnergyTransferType = AC_single_DC_core_EVSESupportedEnergyTransferType;
	result->ChargeService.ServiceTag.ServiceID=1; /* ID of the charge service */
	result->ChargeService.ServiceTag.ServiceName.data[0]='A';
	result->ChargeService.ServiceTag.ServiceName.data[1]='C';
	result->ChargeService.ServiceTag.ServiceName.data[2]='_';
	result->ChargeService.ServiceTag.ServiceName.data[3]='D';
	result->ChargeService.ServiceTag.ServiceName.data[4]='C';
	result->ChargeService.ServiceTag.ServiceName.arraylen.data=5;
	result->ChargeService.ServiceTag.isused.ServiceName=1;
	result->ChargeService.ServiceTag.isused.ServiceCategory=0;
	result->ChargeService.ServiceTag.isused.ServiceScope=0;

	result->ChargeService.FreeService = 1;
	result->PaymentOptions.PaymentOption[0] = ExternalPayment_paymentOptionType; /* EVSE handles the payment */
	result->PaymentOptions.arraylen.PaymentOption=1;


	result->ServiceList.Service[0].FreeService=1;
	result->ServiceList.Service[0].ServiceTag.ServiceID=22; /* ID of the charge service */
	result->ServiceList.Service[0].ServiceTag.ServiceName.data[0]='W';
	result->ServiceList.Service[0].ServiceTag.ServiceName.data[1]='W';
	result->ServiceList.Service[0].ServiceTag.ServiceName.data[2]='W';
	result->ServiceList.Service[0].ServiceTag.ServiceName.arraylen.data=3;
	result->ServiceList.Service[0].ServiceTag.ServiceCategory=Internet_serviceCategoryType;
	result->ServiceList.Service[0].ServiceTag.isused.ServiceName=1;
	result->ServiceList.Service[0].ServiceTag.isused.ServiceCategory=1;
	result->ServiceList.Service[0].ServiceTag.isused.ServiceScope=0;

	result->ServiceList.arraylen.Service=1;
	result->isused.ServiceList=1;

	return 0;
}

int	servicePaymentSelection(struct MessageHeaderType* header, struct ServicePaymentSelectionReqType* param, struct ServicePaymentSelectionResType* result)
{
	printf("EVSE side: servicePaymentSelection called\n"  );
	printf("\tReceived data:\n");
	printf("\tHeader SessionID=");
	printBinaryArray(header->SessionID.data,header->SessionID.arraylen.data );

	if(param->SelectedPaymentOption == ExternalPayment_paymentOptionType)
		printf("\t\t SelectedPaymentOption=ExternalPayment\n");

	printf("\t\t ServiceID=%d\n",param->SelectedServiceList.SelectedService[0].ServiceID);

	result->ResponseCode = OK_responseCodeType;

	return 0;
}

int	paymentDetails(struct MessageHeaderType* header, struct PaymentDetailsReqType* param, struct PaymentDetailsResType* result)
{
	return 0;
}

int	chargeParameterDiscovery(struct MessageHeaderType* header, struct ChargeParameterDiscoveryReqType* param, struct ChargeParameterDiscoveryResType* result)
{
	struct PhysicalValueType f;

	printf("EVSE side: chargeParameterDiscovery called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t EVRequestedEnergyTransferType=%d\n",param->EVRequestedEnergyTransferType);

	/* check,if DC or AC is requested */
	if(param->EVRequestedEnergyTransferType==DC_core_EVRequestedEnergyTransferType || param->isused.DC_EVChargeParameter==1)
	{

		printf("\t\t EVStatus:\n");
		printf("\t\t\t EVReady=%d\n", param->DC_EVChargeParameter->DC_EVStatus.EVReady);
		printf("\t\t\t EVRESSSOC=%d\n", param->DC_EVChargeParameter->DC_EVStatus.EVRESSSOC);
		printf("\t\t\t EVErrorCode=%d\n", param->DC_EVChargeParameter->DC_EVStatus.EVErrorCode);
		printf("\t\t\t EVRESSConditioning=%d\n", param->DC_EVChargeParameter->DC_EVStatus.EVRESSConditioning);
		printf("\t\t\t EVCabinConditioning=%d\n", param->DC_EVChargeParameter->DC_EVStatus.EVCabinConditioning);


		printf("\t\t EVMaximumCurrentLimit=%d\n", param->DC_EVChargeParameter->EVMaximumCurrentLimit.Value);
		printf("\t\t EVMaximumPowerLimit=%d\n", param->DC_EVChargeParameter->EVMaximumPowerLimit.Value);
		printf("\t\t EVMaximumVoltageLimit=%d\n", param->DC_EVChargeParameter->EVMaximumVoltageLimit.Value);
		printf("\t\t EVEnergyCapacity=%d\n", param->DC_EVChargeParameter->EVEnergyCapacity.Value);
		printf("\t\t EVEnergyRequest=%d\n", param->DC_EVChargeParameter->EVEnergyRequest.Value);
		printf("\t\t FullSOC=%d\n", param->DC_EVChargeParameter->FullSOC);
		printf("\t\t BulkSOC=%d\n", param->DC_EVChargeParameter->BulkSOC);

		result->ResponseCode = OK_responseCodeType;
		result->isused.SAScheduleList=0;


		result->isused.DC_EVSEChargeParameter = 1;
		result->isused.AC_EVSEChargeParameter = 0;
		result->DC_EVSEChargeParameter->DC_EVSEStatus.EVSEStatusCode = EVSE_Ready_DC_EVSEStatusCodeType;
		result->DC_EVSEChargeParameter->DC_EVSEStatus.EVSEIsolationStatus = Safe_isolationLevelType;
		result->DC_EVSEChargeParameter->DC_EVSEStatus.isused.EVSEIsolationStatus = 1;


		f.Multiplier = 0;
		f.Unit = A_unitSymbolType;
		f.Value = 50;

		result->DC_EVSEChargeParameter->EVSEMaximumCurrentLimit=f;

		f.Unit = W_unitSymbolType;
		f.Value = 20000;

		result->DC_EVSEChargeParameter->EVSEMaximumPowerLimit=f;
		result->DC_EVSEChargeParameter->isused.EVSEMaximumPowerLimit=1;

		f.Unit = V_unitSymbolType;
		f.Value = 400;

		result->DC_EVSEChargeParameter->EVSEMaximumVoltageLimit=f;

		f.Unit = A_unitSymbolType;
		f.Value = 5;

		result->DC_EVSEChargeParameter->EVSEMinimumCurrentLimit=f;

		f.Unit = V_unitSymbolType;
		f.Value = 200;

		result->DC_EVSEChargeParameter->EVSEMinimumVoltageLimit=f;

		f.Unit = A_unitSymbolType;
		f.Value = 2;

		result->DC_EVSEChargeParameter->EVSECurrentRegulationTolerance=f;
		result->DC_EVSEChargeParameter->isused.EVSECurrentRegulationTolerance=1;

		f.Unit = A_unitSymbolType;
		f.Value = 1;

		result->DC_EVSEChargeParameter->EVSEPeakCurrentRipple=f;

		f.Unit = W_unitSymbolType;
		f.Value = 5000;

		result->DC_EVSEChargeParameter->EVSEEnergyToBeDelivered=f;
		result->DC_EVSEChargeParameter->isused.EVSEEnergyToBeDelivered=1;

		/* set up a PMax schedule */
		result->isused.SAScheduleList=1;
		result->SAScheduleList->SAScheduleTuple[0].SAScheduleTupleID=10;
		result->SAScheduleList->SAScheduleTuple[0].isused.SalesTariff=0; /* no tariffs */

		/* set up two PMax entries */
		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleID=20;
		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[0].PMax=20000;
		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[0].RelativeTimeInterval.start=0;

		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[1].PMax=0;
		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[1].RelativeTimeInterval.start=1200; /* 20 min */

		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.arraylen.PMaxScheduleEntry=2; /* we set up two time entries */


		/* set up two PMax entries */
		result->SAScheduleList->SAScheduleTuple[1].SAScheduleTupleID=15;
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleID=30;
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[0].PMax=10000;
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[0].RelativeTimeInterval.start=0;

		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[1].PMax=0;
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[1].RelativeTimeInterval.start=1800; /* 30 min */

		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.arraylen.PMaxScheduleEntry=2; /* we set up two time entries */

		result->SAScheduleList->arraylen.SAScheduleTuple=2; /* we used only 1 tuple */

	} else { /* AC related */

		printf("\t\t DepartureTime=%d\n", param->AC_EVChargeParameter->DepartureTime);
		printf("\t\t EAmount=%d\n", param->AC_EVChargeParameter->EAmount.Value);
		printf("\t\t EVMaxCurrent=%d\n", param->AC_EVChargeParameter->EVMaxCurrent.Value);
		printf("\t\t EVMaxVoltage=%d\n", param->AC_EVChargeParameter->EVMaxVoltage.Value);
		printf("\t\t EVMinCurrent=%d\n", param->AC_EVChargeParameter->EVMinCurrent.Value);


		result->ResponseCode = OK_responseCodeType;


		result->isused.AC_EVSEChargeParameter = 1;
		result->isused.DC_EVSEChargeParameter = 0;
		result->isused.SAScheduleList = 0;


		result->AC_EVSEChargeParameter->AC_EVSEStatus.PowerSwitchClosed=1;
		result->AC_EVSEChargeParameter->AC_EVSEStatus.RCD=1;
		result->AC_EVSEChargeParameter->AC_EVSEStatus.ShutDownTime=12345;
		result->AC_EVSEChargeParameter->AC_EVSEStatus.StopCharging=0;


		f.Multiplier = 0;
		f.Unit = A_unitSymbolType;
		f.Value = 100;

		result->AC_EVSEChargeParameter->EVSEMaxCurrent=f;

		f.Unit = V_unitSymbolType;
		f.Value = 200;
		result->AC_EVSEChargeParameter->EVSEMaxVoltage=f;

		f.Unit = A_unitSymbolType;
		f.Value = 300;
		result->AC_EVSEChargeParameter->EVSEMinCurrent=f;

		/* no sales schedule used */
		result->isused.SAScheduleList=0;
	}



	return 0;
}

int	powerDelivery(struct MessageHeaderType* header, struct PowerDeliveryReqType* param, struct PowerDeliveryResType* result)
{
	size_t i;

	printf("EVSE side: powerDelivery called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t\t ReadyToChargeState=%d\n", param->ReadyToChargeState);



	if(param->isused.DC_EVPowerDeliveryParameter)
	{

		printf("\t\t EVStatus:\n");
		printf("\t\t\t EVReady=%d\n", param->DC_EVPowerDeliveryParameter->DC_EVStatus.EVReady);
		printf("\t\t\t EVRESSSOC=%d\n", param->DC_EVPowerDeliveryParameter->DC_EVStatus.EVRESSSOC);
		printf("\t\t\t EVErrorCode=%d\n", param->DC_EVPowerDeliveryParameter->DC_EVStatus.EVErrorCode);
		printf("\t\t\t EVRESSConditioning=%d\n", param->DC_EVPowerDeliveryParameter->DC_EVStatus.EVRESSConditioning);
		printf("\t\t\t EVCabinConditioning=%d\n", param->DC_EVPowerDeliveryParameter->DC_EVStatus.EVCabinConditioning);


		if(param->isused.ChargingProfile)
		{
			printf("\t\t\tChargingProfile:\n");
			printf("\t\t\t SAScheduleTupleID=%d\n",param->ChargingProfile.SAScheduleTupleID );
			for(i=0;i<param->ChargingProfile.arraylen.ProfileEntry;i++)
			{
				printf("\t\t\t Entry#%d\n",i);
				printf("\t\t\t\t ChargingProfileEntryMaxPower=%d\n", param->ChargingProfile.ProfileEntry[i].ChargingProfileEntryMaxPower);
				printf("\t\t\t\t ChargingProfileEntryStart=%d\n", param->ChargingProfile.ProfileEntry[i].ChargingProfileEntryStart);

			}


		}


		result->ResponseCode = OK_responseCodeType;
		result->DC_EVSEStatus->EVSEIsolationStatus =1;
		result->DC_EVSEStatus->isused.EVSEIsolationStatus = 1;
		result->DC_EVSEStatus->EVSEStatusCode = EVSE_Ready_DC_EVSEStatusCodeType;
		result->isused.DC_EVSEStatus=1;
		result->isused.AC_EVSEStatus=0;





	} else {


		result->ResponseCode = OK_responseCodeType;
		result->AC_EVSEStatus->PowerSwitchClosed=1;
		result->AC_EVSEStatus->RCD=1;
		result->AC_EVSEStatus->ShutDownTime=12345;
		result->AC_EVSEStatus->StopCharging=1;


		result->isused.AC_EVSEStatus=1;
		result->isused.DC_EVSEStatus=0;

	}

	return 0;
}

int	chargingStatus(struct MessageHeaderType* header, struct ChargingStatusReqType* param, struct ChargingStatusResType* result)
{
	printf("EVSE side: chargingStatus called\n"  );



	result->ResponseCode=OK_responseCodeType;
	result->EVSEID.data[0]=1;
	result->EVSEID.arraylen.data=1;
	result->AC_EVSEStatus.PowerSwitchClosed=1;
	result->AC_EVSEStatus.RCD=1;
	result->AC_EVSEStatus.ShutDownTime=12345;
	result->AC_EVSEStatus.StopCharging=1;
	result->ReceiptRequired=0;
	result->EVSEMaxCurrent.Multiplier = 2;
	result->EVSEMaxCurrent.Unit = A_unitSymbolType;
	result->EVSEMaxCurrent.isused.Unit=1;
	result->EVSEMaxCurrent.Value = 400;
	result->isused.EVSEMaxCurrent=1;
	result->SAScheduleTupleID=10;
	result->isused.SAScheduleTupleID=1;

	result->isused.MeterInfo=1;
	result->MeterInfo.MeterID.arraylen.data=1;
	result->MeterInfo.MeterID.data[0]=2;
	result->MeterInfo.MeterReading.Multiplier = 0;
	result->MeterInfo.MeterReading.Unit = A_unitSymbolType;
	result->MeterInfo.MeterReading.Value = 500;
	result->MeterInfo.MeterStatus = 4321;
	result->MeterInfo.TMeter =123456789;
	result->MeterInfo.isused.MeterReading = 1;
	result->MeterInfo.isused.MeterStatus=1;
	result->MeterInfo.isused.TMeter=1;
	result->MeterInfo.isused.SigMeterReading=0;

	return 0;
}

int	meteringReceipt(struct MessageHeaderType* header, struct MeteringReceiptReqType* param, struct MeteringReceiptResType* result)
{

	printf("EVSE side: meteringReceipt called\n"  );
	printf("\tReceived data:\n");

	printf("\t\t SAScheduleTupleID=%d\n", param->SAScheduleTupleID);
	printf("\t\t MeterInfo.MeterStatus=%d\n", param->MeterInfo.MeterStatus);
	printf("\t\t MeterInfo.MeterID=%d\n",		param->MeterInfo.MeterID.data[0]);
	printf("\t\t MeterInfo.isused.MeterReading=%d\n", param->MeterInfo.isused.MeterReading);
	printf("\t\t MeterReading.Value=%d\n",		param->MeterInfo.MeterReading.Value);
	printf("\t\t MeterInfo.TMeter=%d\n",		param->MeterInfo.TMeter);

	result->ResponseCode = OK_responseCodeType;

	result->AC_EVSEStatus.PowerSwitchClosed=1;
	result->AC_EVSEStatus.RCD=1;
	result->AC_EVSEStatus.ShutDownTime=12345;
	result->AC_EVSEStatus.StopCharging=1;

	return 0;
}

int	cableCheck(struct MessageHeaderType* header, struct CableCheckReqType* param, struct CableCheckResType* result)
{
	printf("EVSE side: cableCheck called\n"  );
	printf("\tReceived data:\n");


	printf("\t\t EVStatus:\n");
	printf("\t\t\t EVReady=%d\n", param->DC_EVStatus.EVReady);
	printf("\t\t\t EVRESSSOC=%d\n", param->DC_EVStatus.EVRESSSOC);
	printf("\t\t\t EVErrorCode=%d\n", param->DC_EVStatus.EVErrorCode);
	printf("\t\t\t EVRESSConditioning=%d\n", param->DC_EVStatus.EVRESSConditioning);
	printf("\t\t\t EVCabinConditioning=%d\n", param->DC_EVStatus.EVCabinConditioning);


	result->ResponseCode = OK_responseCodeType;
	result->DC_EVSEStatus.EVSEIsolationStatus= Safe_isolationLevelType;
	result->DC_EVSEStatus.isused.EVSEIsolationStatus = 1;
	result->DC_EVSEStatus.EVSEStatusCode = EVSE_Ready_DC_EVSEStatusCodeType;

	return 0;
}


int	preCharge(struct MessageHeaderType* header, struct PreChargeReqType* param, struct PreChargeResType* result)
{
	struct PhysicalValueType float_type;


	printf("EVSE side: preCharge called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t EVStatus:\n");
	printf("\t\t\t EVReady=%d\n", param->DC_EVStatus.EVReady);
	printf("\t\t\t EVRESSSOC=%d\n", param->DC_EVStatus.EVRESSSOC);
	printf("\t\t\t EVErrorCode=%d\n", param->DC_EVStatus.EVErrorCode);
	printf("\t\t\t EVRESSConditioning=%d\n", param->DC_EVStatus.EVRESSConditioning);
	printf("\t\t\t EVCabinConditioning=%d\n", param->DC_EVStatus.EVCabinConditioning);

	result->ResponseCode = OK_responseCodeType;
	result->DC_EVSEStatus.EVSEIsolationStatus= Safe_isolationLevelType;
	result->DC_EVSEStatus.isused.EVSEIsolationStatus = 1;
	result->DC_EVSEStatus.EVSEStatusCode = EVSE_Ready_DC_EVSEStatusCodeType;

	float_type.Multiplier = 0;
	float_type.Unit = V_unitSymbolType;
	float_type.Value = 100;
	result->EVSEPresentVoltage = float_type;




	return 0;


}

int	currentDemand(struct MessageHeaderType* header, struct CurrentDemandReqType* param, struct CurrentDemandResType* result)
{

	struct PhysicalValueType f;

	printf("EVSE side: currentDemand called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t EVStatus:\n");
	printf("\t\t\t EVReady=%d\n", param->DC_EVStatus.EVReady);
	printf("\t\t\t EVRESSSOC=%d\n", param->DC_EVStatus.EVRESSSOC);
	printf("\t\t\t EVErrorCode=%d\n", param->DC_EVStatus.EVErrorCode);
	printf("\t\t\t EVRESSConditioning=%d\n", param->DC_EVStatus.EVRESSConditioning);
	printf("\t\t\t EVCabinConditioning=%d\n", param->DC_EVStatus.EVCabinConditioning);

	printf("\t\t EVTargetCurrent=%d\n", param->EVTargetCurrent.Value);
	printf("\t\t EVMaximumVoltageLimit=%d\n", param->EVMaximumVoltageLimit.Value);
	printf("\t\t EVMaximumPowerLimit=%d\n", param->EVMaximumPowerLimit.Value);
	printf("\t\t EVMaximumCurrentLimit=%d\n", param->EVMaximumCurrentLimit.Value);
	printf("\t\t BulkChargingComplete=%d\n", param->BulkChargingComplete);
	printf("\t\t ChargingComplete=%d\n", param->ChargingComplete);
	printf("\t\t RemainingTimeToFullSoC=%d\n", param->RemainingTimeToFullSoC.Value);
	printf("\t\t RemainingTimeToBulkSoC=%d\n", param->RemainingTimeToBulkSoC.Value);

	printf("\t\t EVTargetVoltage=%d\n", param->EVTargetVoltage.Value);


	result->ResponseCode = OK_responseCodeType;
	result->DC_EVSEStatus.EVSEIsolationStatus= Safe_isolationLevelType;
	result->DC_EVSEStatus.isused.EVSEIsolationStatus = 1;
	result->DC_EVSEStatus.EVSEStatusCode = EVSE_Ready_DC_EVSEStatusCodeType;

	f.Multiplier = 0;
	f.Unit = V_unitSymbolType;
	f.Value = 400;

	result->EVSEPresentVoltage=f;

	f.Unit = A_unitSymbolType;
	f.Value = 45;

	result->EVSEPresentCurrent=f;

	result->EVSECurrentLimitAchieved=0;

	result->EVSEVoltageLimitAchieved=1;

	result->EVSEPowerLimitAchieved=0;

	f.Unit = V_unitSymbolType;
	f.Value = 400;

	result->EVSEMaximumVoltageLimit=f;
	result->isused.EVSEMaximumVoltageLimit=1;

	f.Unit = A_unitSymbolType;
	f.Value = 50;

	result->EVSEMaximumCurrentLimit=f;
	result->isused.EVSEMaximumCurrentLimit=1;

	f.Unit = W_unitSymbolType;
	f.Value = 20000;

	result->EVSEMaximumPowerLimit=f;
	result->isused.EVSEMaximumPowerLimit=1;

	return 0;
}

int	weldingDetection(struct MessageHeaderType* header, struct WeldingDetectionReqType* param, struct WeldingDetectionResType* result)
{

	printf("EVSE side: weldingDetection called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t EVStatus:\n");
	printf("\t\t\t EVReady=%d\n", param->DC_EVStatus.EVReady);
	printf("\t\t\t EVRESSSOC=%d\n", param->DC_EVStatus.EVRESSSOC);
	printf("\t\t\t EVErrorCode=%d\n", param->DC_EVStatus.EVErrorCode);
	printf("\t\t\t EVRESSConditioning=%d\n", param->DC_EVStatus.EVRESSConditioning);
	printf("\t\t\t EVCabinConditioning=%d\n", param->DC_EVStatus.EVCabinConditioning);

	result->ResponseCode = OK_responseCodeType;
	result->DC_EVSEStatus.EVSEIsolationStatus= Safe_isolationLevelType;
	result->DC_EVSEStatus.isused.EVSEIsolationStatus = 1;
	result->DC_EVSEStatus.EVSEStatusCode = EVSE_Ready_DC_EVSEStatusCodeType;
	result->EVSEPresentVoltage.Value = 123;
	result->EVSEPresentVoltage.Unit = V_unitSymbolType;
	result->EVSEPresentVoltage.Multiplier = 0;

	return 0;
}

int	sessionStop(struct MessageHeaderType* header, struct SessionStopType* param, struct SessionStopResType* result)
{


	printf("EVSE side: sessionStop called\n"  );


	result->ResponseCode = OK_responseCodeType;



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
	printf("\t\t\t RootCertificateID[0]=%d\n", param->ListOfRootCertificateIDs.RootCertificateID[0].data[0]);
	printf("\t\t\t DHParams[0]=%d\n", param->DHParams.data[0]);




/*	result->ContractEncryptionEncryptedPrivateKey.data[0]=200;
	result->ContractEncryptionEncryptedPrivateKey.arraylen.data=1;
*/

	result->ContractID.data[0]=50;
	result->ContractID.arraylen.data=1;

	result->ContractSignatureEncryptedPrivateKey.data[0]=12;
	result->ContractSignatureEncryptedPrivateKey.arraylen.data=1;



	result->ContractSignatureCertChain.Certificate.data[0]=40;
	result->ContractSignatureCertChain.Certificate.arraylen.data=1;

	result->ContractSignatureCertChain.SubCertificates.arraylen.Certificate=2;
	result->ContractSignatureCertChain.SubCertificates.Certificate[0].data[0]=20;
	result->ContractSignatureCertChain.SubCertificates.Certificate[0].arraylen.data=1;
	result->ContractSignatureCertChain.SubCertificates.Certificate[1].data[0]=40;
	result->ContractSignatureCertChain.SubCertificates.Certificate[1].arraylen.data=1;
	result->ContractSignatureCertChain.isused.SubCertificates=1;

	result->DHParams.data[0]=99;
	result->DHParams.arraylen.data=1;

	result->attr_Id.data[0]=33;
	result->attr_Id.arraylen.data=1;

	result->ResponseCode = OK_responseCodeType;

	return 0;
}

static void printBinaryArray(uint8_t* byte, uint32_t len) {
	unsigned int i;
	for(i=0; i<len; i++) {
		printf("%d ",byte[i]);
	}
	printf("\n");
}


