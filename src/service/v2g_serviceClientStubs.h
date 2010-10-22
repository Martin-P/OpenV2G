



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
 * @version 0.2
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

 
 
 #ifdef __cplusplus
extern "C" {
#endif

#ifndef SERVICECLIENTSTUBS_H
#define SERVICECLIENTSTUBS_H

 #include "v2g_service.h"
 #include "v2g_serviceDataTypes.h"
 #include "v2g_serviceClientStubs.h"
 
	/* call sessionSetup  */
	int call_sessionSetup(struct v2gService* service, struct HeaderType* header, struct SessionSetupReqType* params, struct SessionSetupResType* result);

 

	
	/* call serviceDiscovery  */
	int call_serviceDiscovery(struct v2gService* service, struct HeaderType* header, struct ServiceDiscoveryReqType* params, struct ServiceDiscoveryResType* result);

 

	
	/* call selectedServicePayment  */
	int call_selectedServicePayment(struct v2gService* service, struct HeaderType* header, struct ServicePaymentSelectionReqType* params, struct ServicePaymentSelectionResType* result);

 

	
	/* call paymentDetails  */
	int call_paymentDetails(struct v2gService* service, struct HeaderType* header, struct PaymentDetailsReqType* params, struct PaymentDetailsResType* result);

 

	
	/* call powerDiscovery  */
	int call_powerDiscovery(struct v2gService* service, struct HeaderType* header, struct PowerDiscoveryReqType* params, struct PowerDiscoveryResType* result);

 

	
	/* call lineLock  */
	int call_lineLock(struct v2gService* service, struct HeaderType* header, struct LineLockReqType* params, struct LineLockResType* result);

 

	
	/* call powerDelivery  */
	int call_powerDelivery(struct v2gService* service, struct HeaderType* header, struct PowerDeliveryReqType* params, struct PowerDeliveryResType* result);

 

	
	/* call meteringStatus  */
	int call_meteringStatus(struct v2gService* service, struct HeaderType* header, struct MeteringStatusResType* result);

 

	
	/* call meteringReceipt  */
	int call_meteringReceipt(struct v2gService* service, struct HeaderType* header, struct MeteringReceiptReqType* params, struct MeteringReceiptResType* result);

 

	

/* Initialize the v2g client */
int init_v2gServiceClient(struct v2gService* service, bytes_t bytes, string_ucs_t string, uint8_t* inStream, size_t max_inStream_size, uint8_t* outStream, size_t max_outStream_size);
 
#endif

#ifdef __cplusplus
}
#endif
