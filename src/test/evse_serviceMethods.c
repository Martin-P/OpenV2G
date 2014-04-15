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
 * @author Sebastian.Kaebisch@siemens.com
 * @version 0.8
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#include "v2g_serviceMethods.h"
#include "v2g_dataTypes.h"
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
	header->SessionID.data[0] = 1;
	header->SessionID.data[1] = 2;
	header->SessionID.data[2] = 3;
	header->SessionID.data[3] = 4;
	header->SessionID.data[4] = 5;
	header->SessionID.data[5] = 6;
	header->SessionID.data[6] = 7;
	header->SessionID.data[7] = 8;
	header->SessionID.arraylen.data=8;

	/* Prepare data for EV */
	result->ResponseCode = OK_responseCodeType;
	result->EVSEID.data[1]=20;
	result->EVSEID.arraylen.data=2;
	result->EVSETimeStamp=123456789;
	result->isused.EVSETimeStamp=1;


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


	/* result->ChargeService.SupportedEnergyTransferMode = AC_single_phase_core_EnergyTransferModeType; */
	result->ChargeService.ServiceID=1; /* ID of the charge service */
	result->ChargeService.ServiceName.data[0]='A';
	result->ChargeService.ServiceName.data[1]='C';
	result->ChargeService.ServiceName.data[2]='_';
	result->ChargeService.ServiceName.data[3]='D';
	result->ChargeService.ServiceName.data[4]='C';
	result->ChargeService.ServiceName.arraylen.data=5;
	result->ChargeService.isused.ServiceName=1;
	result->ChargeService.isused.ServiceScope=1;

	result->ChargeService.FreeService = 1;
	result->ChargeService.ServiceCategory = EVCharging_serviceCategoryType;
	result->ChargeService.ServiceScope.data[0] = 100;
	result->ChargeService.ServiceScope.arraylen.data = 1;

	result->ChargeService.SupportedEnergyTransferMode.EnergyTransferMode[0] = DC_combo_core_EnergyTransferModeType;
	result->ChargeService.SupportedEnergyTransferMode.EnergyTransferMode[1] = AC_single_phase_core_EnergyTransferModeType;
	result->ChargeService.SupportedEnergyTransferMode.arraylen.EnergyTransferMode=2;

	result->PaymentOptionList.PaymentOption[0] = ExternalPayment_paymentOptionType; /* EVSE handles the payment */
	result->PaymentOptionList.PaymentOption[1] = Contract_paymentOptionType;
	result->PaymentOptionList.arraylen.PaymentOption=2;

	if(param->ServiceCategory==Internet_serviceCategoryType || param->ServiceCategory==OtherCustom_serviceCategoryType || param->isused.ServiceCategory==0)
	{

		result->ServiceList.Service[0].FreeService=1;
		result->ServiceList.Service[0].ServiceID=22; /* ID of the charge service */
		result->ServiceList.Service[0].ServiceName.data[0]='W';
		result->ServiceList.Service[0].ServiceName.data[1]='W';
		result->ServiceList.Service[0].ServiceName.data[2]='W';
		result->ServiceList.Service[0].ServiceName.arraylen.data=3;
		result->ServiceList.Service[0].ServiceCategory=Internet_serviceCategoryType;
		result->ServiceList.Service[0].isused.ServiceName=1;
		result->ServiceList.Service[0].isused.ServiceScope=0;

		result->ServiceList.Service[1].FreeService=0;
		result->ServiceList.Service[1].ServiceID=33; /* ID of the charge service */
		result->ServiceList.Service[1].ServiceName.data[0]='H';
		result->ServiceList.Service[1].ServiceName.data[1]='T';
		result->ServiceList.Service[1].ServiceName.data[2]='T';
		result->ServiceList.Service[1].ServiceName.data[3]='P';
		result->ServiceList.Service[1].ServiceName.data[4]='S';
		result->ServiceList.Service[1].ServiceName.arraylen.data=5;
		result->ServiceList.Service[1].ServiceCategory=Internet_serviceCategoryType;
		result->ServiceList.Service[1].isused.ServiceName=1;
		result->ServiceList.Service[1].isused.ServiceScope=0;



	result->ServiceList.arraylen.Service=2;
	result->isused.ServiceList=1;

	} else {
		result->isused.ServiceList=0; /* no value added service requested */
	}


	return 0;
}

int	paymentServiceSelection(struct MessageHeaderType* header, struct PaymentServiceSelectionReqType* param, struct PaymentServiceSelectionResType* result)
{
	size_t i;

	printf("EVSE side: servicePaymentSelection called\n"  );
	printf("\tReceived data:\n");
	printf("\tHeader SessionID=");
	printBinaryArray(header->SessionID.data,header->SessionID.arraylen.data );

	if(param->SelectedPaymentOption == ExternalPayment_paymentOptionType)
		printf("\t\t SelectedPaymentOption=ExternalPayment\n");

	for(i=0; i<param->SelectedServiceList.arraylen.SelectedService;i++)
	{
		printf("\t\t ServiceID=%d\n",param->SelectedServiceList.SelectedService[i].ServiceID);
		if( param->SelectedServiceList.SelectedService[i].isused.ParameterSetID)
				printf("\t\t ParameterSetID=%d\n",param->SelectedServiceList.SelectedService[i].ParameterSetID);
	}
	result->ResponseCode = OK_responseCodeType;

	return 0;
}

int	paymentDetails(struct MessageHeaderType* header, struct PaymentDetailsReqType* param, struct PaymentDetailsResType* result)
{


	printf("EVSE side: paymentDetails called\n"  );
	printf("\tReceived data:\n");

	printf("\t\t eMAID=%d\n", param->eMAID.data[0]);
	printf("\t\t ID=%c%c\n", param->ContractSignatureCertChain.attr_Id.data[0], param->ContractSignatureCertChain.attr_Id.data[1]);
	printf("\t\t Certificate=%c%c\n", param->ContractSignatureCertChain.Certificate.data[0],  param->ContractSignatureCertChain.Certificate.data[1]);
	printf("\t\t SubCertificate 1=%c%c\n", param->ContractSignatureCertChain.SubCertificates.Certificate[0].data[0], param->ContractSignatureCertChain.SubCertificates.Certificate[0].data[1]);
	printf("\t\t SubCertificate 2=%c%c%c\n", param->ContractSignatureCertChain.SubCertificates.Certificate[1].data[0], param->ContractSignatureCertChain.SubCertificates.Certificate[1].data[1], param->ContractSignatureCertChain.SubCertificates.Certificate[1].data[2]);

	result->ResponseCode = OK_responseCodeType;
	result->GenChallenge.data[0]=1;
	result->GenChallenge.arraylen.data=1;
	result->EVSETimeStamp=123456;

	return 0;
}

int	chargeParameterDiscovery(struct MessageHeaderType* header, struct ChargeParameterDiscoveryReqType* param, struct ChargeParameterDiscoveryResType* result)
{
	struct PhysicalValueType f;

	printf("EVSE side: chargeParameterDiscovery called\n"  );
	printf("\tReceived data:\n");
	printf("\t\t EVRequestedEnergyTransferType=%d\n",param->RequestedEnergyTransferMode);

	/* check,if DC or AC is requested */
	if(param->RequestedEnergyTransferMode==DC_core_EnergyTransferModeType || param->isused.DC_EVChargeParameter==1)
	{
		printf("\t\t MaxEntriesSAScheduleTuple=%d\n", param->MaxEntriesSAScheduleTuple);
		printf("\t\t EVStatus:\n");
		printf("\t\t\t EVReady=%d\n", param->DC_EVChargeParameter->DC_EVStatus.EVReady);
		printf("\t\t\t EVRESSSOC=%d\n", param->DC_EVChargeParameter->DC_EVStatus.EVRESSSOC);
		printf("\t\t\t EVErrorCode=%d\n", param->DC_EVChargeParameter->DC_EVStatus.EVErrorCode);


		printf("\t\t DepartureTime=%d\n", param->DC_EVChargeParameter->DepartureTime);
		printf("\t\t EVMaximumCurrentLimit=%d\n", param->DC_EVChargeParameter->EVMaximumCurrentLimit.Value);
		printf("\t\t EVMaximumPowerLimit=%d\n", param->DC_EVChargeParameter->EVMaximumPowerLimit.Value);
		printf("\t\t EVMaximumVoltageLimit=%d\n", param->DC_EVChargeParameter->EVMaximumVoltageLimit.Value);
		printf("\t\t EVEnergyCapacity=%d\n", param->DC_EVChargeParameter->EVEnergyCapacity.Value);
		printf("\t\t EVEnergyRequest=%d\n", param->DC_EVChargeParameter->EVEnergyRequest.Value);
		printf("\t\t FullSOC=%d\n", param->DC_EVChargeParameter->FullSOC);
		printf("\t\t BulkSOC=%d\n", param->DC_EVChargeParameter->BulkSOC);

		result->ResponseCode = OK_responseCodeType;
		result->EVSEProcessing = Finished_EVSEProcessingType;

		result->isused.DC_EVSEChargeParameter = 1;
		result->isused.AC_EVSEChargeParameter = 0;
		result->DC_EVSEChargeParameter->DC_EVSEStatus.EVSEStatusCode = EVSE_Ready_DC_EVSEStatusCodeType;
		result->DC_EVSEChargeParameter->DC_EVSEStatus.EVSEIsolationStatus = Valid_isolationLevelType;
		result->DC_EVSEChargeParameter->DC_EVSEStatus.isused.EVSEIsolationStatus = 1;
		result->DC_EVSEChargeParameter->DC_EVSEStatus.EVSENotification = None_EVSENotificationType;
		result->DC_EVSEChargeParameter->DC_EVSEStatus.NotificationMaxDelay = 10;

		f.Multiplier = 0;
		f.Unit = A_unitSymbolType;
		f.Value = 50;

		result->DC_EVSEChargeParameter->EVSEMaximumCurrentLimit=f;

		f.Unit = W_unitSymbolType;
		f.Value = 20000;

		result->DC_EVSEChargeParameter->EVSEMaximumPowerLimit=f;


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

		/* set up two PMax entries: #1 */
		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[0].PMax.Value=20000;
		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[0].PMax.Unit = W_unitSymbolType;
		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[0].PMax.Multiplier =0;
		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[0].RelativeTimeInterval.start=0;
		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[0].RelativeTimeInterval.isused.duration=0;

		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[1].PMax.Value=0;
		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[1].PMax.Unit = W_unitSymbolType;
		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[1].PMax.Multiplier =0;
		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[1].RelativeTimeInterval.start=1200; /* 20 min */
		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[1].RelativeTimeInterval.isused.duration=0;

		result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.arraylen.PMaxScheduleEntry=2; /* we set up two time entries */


		/* #2 */
		result->SAScheduleList->SAScheduleTuple[1].SAScheduleTupleID=15;
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[0].PMax.Value=10000;
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[0].PMax.Unit = W_unitSymbolType;
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[0].PMax.Multiplier =0;
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[0].RelativeTimeInterval.start=0;
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[0].RelativeTimeInterval.isused.duration=0;

		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[1].PMax.Value=0;
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[1].PMax.Unit = W_unitSymbolType;
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[1].PMax.Multiplier =1;
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[1].RelativeTimeInterval.start=1800; /* 30 min */
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[1].RelativeTimeInterval.duration=3600;
		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.PMaxScheduleEntry[1].RelativeTimeInterval.isused.duration=1;

		result->SAScheduleList->SAScheduleTuple[1].PMaxSchedule.arraylen.PMaxScheduleEntry=2; /* we set up two time entries */

		result->SAScheduleList->arraylen.SAScheduleTuple=2; /* we used 2 tuple */




	} else { /* AC related */

		printf("\t\t DepartureTime=%d\n", param->AC_EVChargeParameter->DepartureTime);
		printf("\t\t EAmount=%d\n", param->AC_EVChargeParameter->EAmount.Value);
		printf("\t\t EVMaxCurrent=%d\n", param->AC_EVChargeParameter->EVMaxCurrent.Value);
		printf("\t\t EVMaxVoltage=%d\n", param->AC_EVChargeParameter->EVMaxVoltage.Value);
		printf("\t\t EVMinCurrent=%d\n", param->AC_EVChargeParameter->EVMinCurrent.Value);


		result->ResponseCode = OK_responseCodeType;
		result->EVSEProcessing = Finished_EVSEProcessingType;

		result->isused.AC_EVSEChargeParameter = 1;
		result->isused.DC_EVSEChargeParameter = 0;

		result->AC_EVSEChargeParameter->AC_EVSEStatus.RCD=1;
		result->AC_EVSEChargeParameter->AC_EVSEStatus.EVSENotification=None_EVSENotificationType;
		result->AC_EVSEChargeParameter->AC_EVSEStatus.NotificationMaxDelay=123;



		f.Multiplier = 0;
		f.Unit = A_unitSymbolType;
		f.Value = 100;

		result->AC_EVSEChargeParameter->EVSEMaxCurrent=f;


		f.Unit = V_unitSymbolType;
		f.Value = 300;
		result->AC_EVSEChargeParameter->EVSENominalVoltage=f;

		result->EVSEProcessing=1;


			/* set up a PMax schedule */
			result->isused.SAScheduleList=1;
			result->SAScheduleList->SAScheduleTuple[0].SAScheduleTupleID=10;
			result->SAScheduleList->SAScheduleTuple[0].isused.SalesTariff=0; /* no tariffs */

			/* set up two PMax entries: #1 */
			result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[0].PMax.Value=20000;
			result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[0].PMax.Unit = W_unitSymbolType;
			result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[0].PMax.Multiplier =0;
			result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[0].RelativeTimeInterval.start=0;
			result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[0].RelativeTimeInterval.isused.duration=0;

			result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[1].PMax.Value=0;
			result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[1].PMax.Unit = W_unitSymbolType;
			result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[1].PMax.Multiplier =0;
			result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[1].RelativeTimeInterval.start=1200; /* 20 min */
			result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.PMaxScheduleEntry[1].RelativeTimeInterval.isused.duration=0;

			result->SAScheduleList->SAScheduleTuple[0].PMaxSchedule.arraylen.PMaxScheduleEntry=2; /* we set up two time entries */

			result->SAScheduleList->arraylen.SAScheduleTuple=1;
			result->isused.SAScheduleList=1;

			result->SAScheduleList->SAScheduleTuple[0].isused.SalesTariff=1;


			/* set up sale entries */
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->NumEPriceLevels=2;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->isused.NumEPriceLevels=1;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffID=20;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->attr_Id.data[0]=100;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->attr_Id.arraylen.data=1;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->isused.attr_Id=1;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[0].EPriceLevel=2;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[0].isused.EPriceLevel=1;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[0].isused.ConsumptionCost=0;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[0].RelativeTimeInterval.start=0;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[0].RelativeTimeInterval.duration=10;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[0].RelativeTimeInterval.isused.duration=1;


			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[1].EPriceLevel=3;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[1].RelativeTimeInterval.start=11;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[1].RelativeTimeInterval.duration=10;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[1].RelativeTimeInterval.isused.duration=1;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[1].ConsumptionCost[0].Cost[0].amount=10;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[1].ConsumptionCost[0].Cost[0].amountMultiplier=1;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[1].ConsumptionCost[0].Cost[0].isused.amountMultiplier=1;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[1].ConsumptionCost[0].Cost[0].costKind=RenewableGenerationPercentage_costKindType;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[1].ConsumptionCost[0].startValue.Value=123;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[1].ConsumptionCost[0].arraylen.Cost=1;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[1].isused.EPriceLevel=1;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[1].isused.ConsumptionCost=1;


			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->SalesTariffEntry[1].arraylen.ConsumptionCost=1;
			result->SAScheduleList->SAScheduleTuple[0].SalesTariff->arraylen.SalesTariffEntry=2;
			result->SAScheduleList->arraylen.SAScheduleTuple=1;

	}



	return 0;
}

int	powerDelivery(struct MessageHeaderType* header, struct PowerDeliveryReqType* param, struct PowerDeliveryResType* result)
{

	size_t i;

	printf("EVSE side: powerDelivery called\n"  );
	printf("\tReceived data:\n");

	printf("\t\t  ChargeProgress=%d\n", param->ChargeProgress);
	printf("\t\t  SAScheduleTupleID=%d\n", param->SAScheduleTupleID);

	if(param->isused.DC_EVPowerDeliveryParameter)
	{

		printf("\t\t EVStatus:\n");
		printf("\t\t\t EVReady=%d\n", param->DC_EVPowerDeliveryParameter->DC_EVStatus.EVReady);
		printf("\t\t\t EVRESSSOC=%d\n", param->DC_EVPowerDeliveryParameter->DC_EVStatus.EVRESSSOC);
		printf("\t\t\t EVErrorCode=%d\n", param->DC_EVPowerDeliveryParameter->DC_EVStatus.EVErrorCode);

		printf("\t\t BulkChargingComplete=%d\n", param->DC_EVPowerDeliveryParameter->BulkChargingComplete);
		printf("\t\t ChargingComplete=%d\n", param->DC_EVPowerDeliveryParameter->ChargingComplete);

		if(param->isused.ChargingProfile)
		{
			printf("\t\t\tChargingProfile:\n");
			printf("\t\t\t SAScheduleTupleID=%d\n",param->SAScheduleTupleID );
			for(i=0;i<param->ChargingProfile.arraylen.ProfileEntry;i++)
			{
				printf("\t\t\t Entry#%d\n",i);
				printf("\t\t\t\t ChargingProfileEntryMaxPower=%d (%d %d) \n", param->ChargingProfile.ProfileEntry[i].ChargingProfileEntryMaxPower.Value, param->ChargingProfile.ProfileEntry[i].ChargingProfileEntryMaxPower.Unit, param->ChargingProfile.ProfileEntry[i].ChargingProfileEntryMaxPower.Multiplier);
				printf("\t\t\t\t ChargingProfileEntryStart=%d\n", param->ChargingProfile.ProfileEntry[i].ChargingProfileEntryStart);
				printf("\t\t\t\t ChargingProfileEntryMaxNumberOfPhasesInUse=%d\n", param->ChargingProfile.ProfileEntry[i].ChargingProfileEntryMaxNumberOfPhasesInUse);

			}


		}


		result->ResponseCode = OK_responseCodeType;
		result->DC_EVSEStatus->EVSEIsolationStatus =0;
		result->DC_EVSEStatus->isused.EVSEIsolationStatus = 1;
		result->DC_EVSEStatus->EVSEStatusCode = EVSE_Ready_DC_EVSEStatusCodeType;
		result->DC_EVSEStatus->EVSENotification=None_EVSENotificationType;
		result->DC_EVSEStatus->NotificationMaxDelay=123;

		result->isused.DC_EVSEStatus=1;
		result->isused.AC_EVSEStatus=0;





	} else {


		result->ResponseCode = OK_responseCodeType;
		result->AC_EVSEStatus->RCD=0;
		result->AC_EVSEStatus->EVSENotification=3;
		result->AC_EVSEStatus->NotificationMaxDelay=12;


		result->isused.AC_EVSEStatus=1;
		result->isused.DC_EVSEStatus=0;

	}

	return 0;
}

int	chargingStatus(struct MessageHeaderType* header, struct ChargingStatusReqType* param, struct ChargingStatusResType* result)
{
	printf("EVSE side: chargingStatus called\n"  );



	result->ResponseCode=OK_responseCodeType;
	result->EVSEID.data[0]=12;
	result->EVSEID.arraylen.data=1;

	result->AC_EVSEStatus.RCD=1;
	result->AC_EVSEStatus.EVSENotification=None_EVSENotificationType;
	result->AC_EVSEStatus.NotificationMaxDelay=123;
	result->ReceiptRequired=1;
	result->isused.ReceiptRequired=1;
	result->EVSEMaxCurrent.Multiplier = 2;
	result->EVSEMaxCurrent.Unit = A_unitSymbolType;

	result->EVSEMaxCurrent.Value = 400;
	result->isused.EVSEMaxCurrent=1;
	result->SAScheduleTupleID=10;

	result->isused.MeterInfo=1;
	result->MeterInfo.MeterID.arraylen.data=1;
	result->MeterInfo.MeterID.data[0]=2;

	result->MeterInfo.MeterReading = 5000;
	result->MeterInfo.MeterStatus = 4321;
	result->MeterInfo.TMeter =123456789;
	result->MeterInfo.SigMeterReading.data[0]=123;
	result->MeterInfo.SigMeterReading.arraylen.data=1;
	result->MeterInfo.isused.MeterReading = 1;
	result->MeterInfo.isused.MeterStatus=1;
	result->MeterInfo.isused.TMeter=1;
	result->MeterInfo.isused.SigMeterReading=1;

	return 0;
}

int	meteringReceipt(struct MessageHeaderType* header, struct MeteringReceiptReqType* param, struct MeteringReceiptResType* result)
{

	printf("EVSE side: meteringReceipt called\n"  );
	printf("\tReceived data:\n");

	printf("\t\t ID=%c%c%c\n", param->attr_Id.data[0],param->attr_Id.data[1],param->attr_Id.data[2]);
	printf("\t\t SAScheduleTupleID=%d\n", param->SAScheduleTupleID);
	printf("\t\t SessionID=%d\n", param->SessionID.data[1]);
	printf("\t\t MeterInfo.MeterStatus=%d\n", param->MeterInfo.MeterStatus);
	printf("\t\t MeterInfo.MeterID=%d\n",		param->MeterInfo.MeterID.data[0]);
	printf("\t\t MeterInfo.isused.MeterReading=%d\n", param->MeterInfo.isused.MeterReading);
	printf("\t\t MeterReading.Value=%d\n",		param->MeterInfo.MeterReading);
	printf("\t\t MeterInfo.TMeter=%d\n",		param->MeterInfo.TMeter);

	result->ResponseCode = OK_responseCodeType;


	result->AC_EVSEStatus->RCD=1;
	result->AC_EVSEStatus->EVSENotification=None_EVSENotificationType;
	result->AC_EVSEStatus->NotificationMaxDelay=123;



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


	result->ResponseCode = OK_responseCodeType;
	result->EVSEProcessing = Finished_EVSEProcessingType;
	result->DC_EVSEStatus.EVSEIsolationStatus= Valid_isolationLevelType;
	result->DC_EVSEStatus.isused.EVSEIsolationStatus = 1;
	result->DC_EVSEStatus.EVSEStatusCode = EVSE_Ready_DC_EVSEStatusCodeType;
	result->DC_EVSEStatus.EVSENotification=None_EVSENotificationType;
	result->DC_EVSEStatus.NotificationMaxDelay=1234;

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
	printf("\t\t EVTargetCurrent=%d (%d %d)\n", param->EVTargetCurrent.Value,param->EVTargetCurrent.Unit, param->EVTargetCurrent.Multiplier);
	printf("\t\t EVTargetVoltage=%d (%d %d)\n", param->EVTargetVoltage.Value, param->EVTargetVoltage.Unit, param->EVTargetVoltage.Multiplier);

	result->ResponseCode = OK_responseCodeType;
	result->DC_EVSEStatus.EVSEIsolationStatus= Valid_isolationLevelType;
	result->DC_EVSEStatus.isused.EVSEIsolationStatus = 1;
	result->DC_EVSEStatus.EVSEStatusCode = EVSE_Ready_DC_EVSEStatusCodeType;
	result->DC_EVSEStatus.EVSENotification=None_EVSENotificationType;
	result->DC_EVSEStatus.NotificationMaxDelay=1234;

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
	result->DC_EVSEStatus.EVSEIsolationStatus= Valid_isolationLevelType;
	result->DC_EVSEStatus.isused.EVSEIsolationStatus = 1;
	result->DC_EVSEStatus.EVSEStatusCode = EVSE_Ready_DC_EVSEStatusCodeType;
	result->DC_EVSEStatus.EVSENotification=None_EVSENotificationType;
	result->DC_EVSEStatus.NotificationMaxDelay=1234;

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

	result->EVSEID.data[0]=12;
	result->EVSEID.arraylen.data=1;

	result->SAScheduleTupleID = 123;


	result->isused.MeterInfo=1;
	result->MeterInfo.MeterID.arraylen.data=1;
	result->MeterInfo.MeterID.data[0]=2;

	result->MeterInfo.MeterReading = 500;
	result->MeterInfo.MeterStatus = 4321;
	result->MeterInfo.TMeter =123456789;
	result->MeterInfo.isused.MeterReading = 1;
	result->MeterInfo.isused.MeterStatus=1;
	result->MeterInfo.isused.TMeter=1;
	result->MeterInfo.isused.SigMeterReading=0;

	result->ReceiptRequired = 1;
	result->isused.ReceiptRequired=1;

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


	result->ResponseCode = OK_responseCodeType;
	result->DC_EVSEStatus.EVSEIsolationStatus= Valid_isolationLevelType;
	result->DC_EVSEStatus.isused.EVSEIsolationStatus = 1;
	result->DC_EVSEStatus.EVSEStatusCode = EVSE_Ready_DC_EVSEStatusCodeType;
	result->DC_EVSEStatus.EVSENotification=None_EVSENotificationType;
	result->DC_EVSEStatus.NotificationMaxDelay=123;
	result->EVSEPresentVoltage.Value = 1234;
	result->EVSEPresentVoltage.Unit = V_unitSymbolType;
	result->EVSEPresentVoltage.Multiplier = 0;

	return 0;
}

int	sessionStop(struct MessageHeaderType* header, struct SessionStopReqType* param, struct SessionStopResType* result)
{


	printf("EVSE side: sessionStop called\n"  );
	printf("\tReceived data:\n");
	printf("\tHeader SessionID=");
	printBinaryArray(header->SessionID.data,header->SessionID.arraylen.data );
	printf("\t\t ChargingSession=%d\n", param->ChargingSession);
	result->ResponseCode = OK_responseCodeType;



	return 0;

}

int	serviceDetail(struct MessageHeaderType* header, struct ServiceDetailReqType* param, struct ServiceDetailResType* result)
{

	printf("EVSE side: serviceDetail called\n"  );
	printf("\tReceived data:\n");
	printf("\tHeader SessionID=");
		printBinaryArray(header->SessionID.data,header->SessionID.arraylen.data );
	printf("\t\t ServiceDetailID=%d\n", param->ServiceID);

	result->ServiceID = 1234;

	/* Parameter Set 1*/
	result->ServiceParameterList.ParameterSet[0].ParameterSetID = 1;
	result->ServiceParameterList.ParameterSet[0].Parameter[0].attr_Name.data[0] = 'P';
	result->ServiceParameterList.ParameterSet[0].Parameter[0].attr_Name.data[1] = 'r';
	result->ServiceParameterList.ParameterSet[0].Parameter[0].attr_Name.data[2] = 'o';
	result->ServiceParameterList.ParameterSet[0].Parameter[0].attr_Name.data[3] = 't';
	result->ServiceParameterList.ParameterSet[0].Parameter[0].attr_Name.data[4] = 'o';
	result->ServiceParameterList.ParameterSet[0].Parameter[0].attr_Name.data[5] = 'c';
	result->ServiceParameterList.ParameterSet[0].Parameter[0].attr_Name.data[6] = 'o';
	result->ServiceParameterList.ParameterSet[0].Parameter[0].attr_Name.data[7] = 'l';
	result->ServiceParameterList.ParameterSet[0].Parameter[0].attr_Name.arraylen.data = 8;
	result->ServiceParameterList.ParameterSet[0].Parameter[0].intValue=15119;
	result->ServiceParameterList.ParameterSet[0].Parameter[0].isused.intValue=1;

	result->ServiceParameterList.ParameterSet[0].Parameter[1].attr_Name.data[0] = 'N';
	result->ServiceParameterList.ParameterSet[0].Parameter[1].attr_Name.data[1] = 'a';
	result->ServiceParameterList.ParameterSet[0].Parameter[1].attr_Name.data[2] = 'm';
	result->ServiceParameterList.ParameterSet[0].Parameter[1].attr_Name.data[3] = 'e';
	result->ServiceParameterList.ParameterSet[0].Parameter[1].attr_Name.arraylen.data = 4;
	result->ServiceParameterList.ParameterSet[0].Parameter[1].stringValue.data[0] = 'V';
	result->ServiceParameterList.ParameterSet[0].Parameter[1].stringValue.data[1] = '2';
	result->ServiceParameterList.ParameterSet[0].Parameter[1].stringValue.data[2] = 'G';
	result->ServiceParameterList.ParameterSet[0].Parameter[1].stringValue.arraylen.data = 3;
	result->ServiceParameterList.ParameterSet[0].Parameter[1].isused.stringValue=1;
	result->ServiceParameterList.ParameterSet[0].arraylen.Parameter = 2;

	/* Parameter Set 2 */
	result->ServiceParameterList.ParameterSet[1].ParameterSetID = 2;
	result->ServiceParameterList.ParameterSet[1].Parameter[0].attr_Name.data[0] = 'C';
	result->ServiceParameterList.ParameterSet[1].Parameter[0].attr_Name.data[1] = 'h';
	result->ServiceParameterList.ParameterSet[1].Parameter[0].attr_Name.data[2] = 'a';
	result->ServiceParameterList.ParameterSet[1].Parameter[0].attr_Name.data[3] = 'n';
	result->ServiceParameterList.ParameterSet[1].Parameter[0].attr_Name.data[4] = 'n';
	result->ServiceParameterList.ParameterSet[1].Parameter[0].attr_Name.data[5] = 'e';
	result->ServiceParameterList.ParameterSet[1].Parameter[0].attr_Name.data[6] = 'l';
	result->ServiceParameterList.ParameterSet[1].Parameter[0].attr_Name.arraylen.data = 7;
	result->ServiceParameterList.ParameterSet[1].Parameter[0].physicalValue.Value=1234;
	result->ServiceParameterList.ParameterSet[1].Parameter[0].physicalValue.Unit=m_unitSymbolType;
	result->ServiceParameterList.ParameterSet[1].Parameter[0].physicalValue.Multiplier=0;
	result->ServiceParameterList.ParameterSet[1].Parameter[0].isused.physicalValue=1;
	result->ServiceParameterList.ParameterSet[1].arraylen.Parameter =1;

	result->ServiceParameterList.arraylen.ParameterSet = 2;
	result->isused.ServiceParameterList = 1;

	result->ResponseCode = OK_responseCodeType;



	return 0;
}

int	authorization(struct MessageHeaderType* header, struct AuthorizationReqType* param, struct AuthorizationResType* result)
{

	printf("EVSE: contractAuthentication called\n"  );
	printf("\tReceived data:\n");

	if(param->isused.GenChallenge)
		printf("\t\t\t GenChallenge=%d\n", param->GenChallenge.data[0]);

	if(param->isused.attr_Id)
		printf("\t\t\t ID=%c%c%c\n", param->attr_Id.data[0],param->attr_Id.data[1],param->attr_Id.data[2]);



	result->ResponseCode=OK_responseCodeType;
	result->EVSEProcessing=Finished_EVSEProcessingType;


	return 0;
}

int	certificateUpdate(struct MessageHeaderType* header, struct CertificateUpdateReqType* param, struct CertificateUpdateResType* result)
{
	return 0;
}

int	certificateInstallation(struct MessageHeaderType* header, struct CertificateInstallationReqType* param, struct CertificateInstallationResType* result)
{



	return 0;
}

static void printBinaryArray(uint8_t* byte, uint32_t len) {
	unsigned int i;
	for(i=0; i<len; i++) {
		printf("%d ",byte[i]);
	}
	printf("\n");
}


