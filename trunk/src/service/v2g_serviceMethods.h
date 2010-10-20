



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
 * @version 0.2.2
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/
 
 #ifdef __cplusplus
extern "C" {
#endif

#ifndef SERVICEMETHODS_H
#define SERVICEMETHODS_H

#include "v2g_serviceDataTypes.h"
#include "EXITypes.h"

/* This service methods has to be implemented by the EVSE server */

int	sessionSetup(struct SessionSetupReqType* param, struct SessionSetupResType* result);
					
int	serviceDiscovery(struct ServiceDiscoveryReqType* param, struct ServiceDiscoveryResType* result);
					
int	selectedServicePayment(struct ServicePaymentSelectionReqType* param, struct ServicePaymentSelectionResType* result);
					
int	paymentDetails(struct PaymentDetailsReqType* param, struct PaymentDetailsResType* result);
					
int	powerDiscovery(struct PowerDiscoveryReqType* param, struct PowerDiscoveryResType* result);
					
int	lineLock(struct LineLockReqType* param, struct LineLockResType* result);
					
int	powerDelivery(struct PowerDeliveryReqType* param, struct PowerDeliveryResType* result);
					
int	meteringStatus(struct MeteringStatusReqType* param, struct MeteringStatusResType* result);
					
int	meteringReceipt(struct MeteringReceiptReqType* param, struct MeteringReceiptResType* result);
						
	

	
	
	
#endif

#ifdef __cplusplus
}
#endif
