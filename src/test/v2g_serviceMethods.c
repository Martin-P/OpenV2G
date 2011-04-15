/*
 * Copyright (C) 2007-2010 Siemens AG
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
 * @version 0.3.1
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
	printf("\t\t PEVStatus ChargerStandby=%d\n",param->PEVStatus.ChargerStandby);
	printf("\t\t PEVStatus ConnectorLocked=%d\n", param->PEVStatus.ConnectorLocked);

	/* Prepare data for PEV */
	result->ResponseCode = OK_SessionSetup_responseCode_SessionSetupType;
	result->EVSEID.data[0]='E';
	result->EVSEID.arraylen.data=1;
	result->EVSEStatus.ConnectorLocked=0;
	result->EVSEStatus.EVSEStandby=1;
	result->EVSEStatus.FatalError=0;
	result->EVSEStatus.PowerSwitchClosed=1;
	result->EVSEStatus.RCD=1;
	result->EVSEStatus.ShutDownTime=12345678L;
	result->TCurrent=12345678L;

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

int	powerDiscovery(struct PowerDiscoveryReqType* param, struct PowerDiscoveryResType* result)
{

	return 0;
}

int	lineLock(struct LineLockReqType* param, struct LineLockResType* result)
{
	return 0;
}

int	powerDelivery(struct PowerDeliveryReqType* param, struct PowerDeliveryResType* result)
{
	return 0;
}

int	meteringStatus(struct MeteringStatusReqType* param, struct MeteringStatusResType* result)
{
	return 0;
}

int	meteringReceipt(struct MeteringReceiptReqType* param, struct MeteringReceiptResType* result)
{
	return 0;
}
